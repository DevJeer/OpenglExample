#include <Windows.h>

// �����û��Ĳ���
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
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
	}

	return 0;
}