#include "ggl.h"
#include "scene.h"
#include "utils.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
// ��ȡwindowsϵͳ�ϵ�һЩ����
#pragma comment(lib, "winmm.lib")
// ������갴�µ�λ��
POINT originalPos;
// �Ƿ�����ת�����
bool rotateView = false;

// ��ȡͼƬ
unsigned char* LoadFileContent(const char* path, int& filesize)
{
	unsigned char* fileContent = nullptr;
	filesize = 0;
	// ���ļ�����read binary�ķ�ʽ��
	// pFile��stream
	FILE* pFile = fopen(path, "rb");
	if (pFile)
	{
		// streamָ���ƶ����ļ�β����׼����ȡ�ļ��Ĵ�С
		fseek(pFile, 0, SEEK_END);
		// ��ȡ�ļ��Ĵ�С
		int nLen = ftell(pFile);
		if (nLen > 0)
		{
			// ��streamָ���ƶ����ļ���ͷ��
			rewind(pFile);
			// Ϊbuffer���ٻ�����
			fileContent = new unsigned char[nLen + 1];
			// ����Ϣ��ȡ��buffer��
			fread(fileContent, sizeof(unsigned char), nLen, pFile);
			// �ڽ��ļ���β������ \0
			fileContent[nLen] = '\0';
			// ��ȡ�ļ��ĳ���
			filesize = nLen;
		}
		fclose(pFile);
	}
	return fileContent;
}

// ��ȡÿ֡��ʱ��
float GetFrameTime()
{
	// ����Ϊstatic ����ֻ����һ��
	static unsigned long lastTime = 0, timeSinceComputerStart = 0;
	// ��ȡʱ�䣬��λ�� ms  Ϊunsigned long����
	timeSinceComputerStart = timeGetTime();
	// ����Ǹ�����������Ϊ0�� ��һ��֮��ͻ�ȡÿ֡��ʱ��
	unsigned long frameTime = lastTime == 0 ? 0 : timeSinceComputerStart - lastTime;
	lastTime = timeSinceComputerStart;
	// ���ظ��������ͣ����ҵ�λ��s
	return float(frameTime) / 1000.0f;
}

// �����û��Ĳ���
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_RBUTTONDOWN:	// ������Ҽ����µ�ʱ�����
		GetCursorPos(&originalPos);	// ��ȡ����λ��
		ShowCursor(false);	// ���ع��
		rotateView = true;
		return 0;
	case WM_RBUTTONUP:		// ������Ҽ�̧���ʱ�����
		SetCursorPos(originalPos.x, originalPos.y);	// ���ù���λ��
		ShowCursor(true);	// ��ʾ���
		rotateView = false;
		return 0;
	case WM_MOUSEMOVE:		// ������ƶ���ʱ�����
		if (rotateView)		// ���ƶ��������ʱ��Ϊ true
		{
			POINT currentPos;
			GetCursorPos(&currentPos);
			int deltaX = currentPos.x - originalPos.x;
			int deltaY = currentPos.y - originalPos.y;
			OnMouseMove(deltaX, deltaY);
			SetCursorPos(originalPos.x, originalPos.y);
		}
		return 0;
	case WM_KEYDOWN:  // ����갴�µ�ʱ�����
		OnKeyDown(wParam);	// wParam �����˰�������Ϣ  �ĸ�����������
		return 0;
	case WM_KEYUP:    // �����̧���ʱ�����
		OnKeyUp(wParam);    // wParam �����˰�������Ϣ  �ĸ���̧����
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ����������
// WINAPI	 �����ĵ��÷�ʽ
// ��Щ��������Ӧ�ó�������ʱ��OS�����
// hInstance	 ��ʾ��ǰӦ�ó����ʵ��
// hPrevInstance ��ʾ��һ��Ӧ�ó���������ʵ��
// lpCmdLine	 ��ʾͨ������������Ӧ�ó��򴫵ݵĲ���
// nShowCmd		 ��ʾ�����ʾ����
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// ���崰�ڵ���
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = NULL;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = NULL;
	wndClass.hIconSm = NULL;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = GLWindowProc;
	wndClass.lpszClassName = L"GLWindow";
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	// ע�ᴰ��
	ATOM atom = RegisterClassEx(&wndClass);
	if (!atom)
	{
		MessageBox(NULL, L"Notice", L"Error", MB_OK);
		return 0;
	}

	// �����ӿڵĴ�С
	RECT rect;
	rect.left = 0;
	rect.right = 800;
	rect.top = 0;
	rect.bottom = 600;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	// ��������
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGL Window", WS_OVERLAPPEDWINDOW, 100, 100, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);

	//����������  ��������������
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);
	// ������ʼ��
	Init();
	ShowWindow(hwnd, SW_SHOW);
	// ���´���
	UpdateWindow(hwnd);

	// ��ʾ���� ���ó���һֱ���У� 
	MSG msg;
	while (true)
	{
		// ��ȡ��Ϣ �� ��ȡ����Ϣ֮�󣬰ѵ�ǰ��Ϣ����Ϣ�������Ƴ���
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			// ����ϢΪ�Ƴ���Ϣ��ʱ�򣬾��˳�ѭ��
			if (msg.message == WM_QUIT)
			{
				break;
			}
			// ת��ΪӦ�ó������ʶ�����Ϣ
			TranslateMessage(&msg);
			// �ַ���Ϣ
			DispatchMessage(&msg);
		}
		// ����
		Draw();
		// �������֮�󣬽�������������ʾ���ƵĽ��
		SwapBuffers(dc);
	}

	return 0;
}