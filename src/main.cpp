#include "ggl.h"
#include "scene.h"
#include "utils.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
// 获取windows系统上的一些函数
#pragma comment(lib, "winmm.lib")
// 保存鼠标按下的位置
POINT originalPos;
// 是否在旋转摄像机
bool rotateView = false;

// 读取图片
unsigned char* LoadFileContent(const char* path, int& filesize)
{
	unsigned char* fileContent = nullptr;
	filesize = 0;
	// 打开文件，以read binary的方式打开
	// pFile是stream
	FILE* pFile = fopen(path, "rb");
	if (pFile)
	{
		// stream指针移动到文件尾部，准备获取文件的大小
		fseek(pFile, 0, SEEK_END);
		// 获取文件的大小
		int nLen = ftell(pFile);
		if (nLen > 0)
		{
			// 将stream指针移动到文件的头部
			rewind(pFile);
			// 为buffer开辟缓冲区
			fileContent = new unsigned char[nLen + 1];
			// 将信息读取到buffer中
			fread(fileContent, sizeof(unsigned char), nLen, pFile);
			// 在将文件的尾部加上 \0
			fileContent[nLen] = '\0';
			// 获取文件的长度
			filesize = nLen;
		}
		fclose(pFile);
	}
	return fileContent;
}

// 获取每帧的时间
float GetFrameTime()
{
	// 定义为static 变量只存在一次
	static unsigned long lastTime = 0, timeSinceComputerStart = 0;
	// 获取时间，单位是 ms  为unsigned long类型
	timeSinceComputerStart = timeGetTime();
	// 如果是刚启动，就设为0， 第一次之后就获取每帧的时间
	unsigned long frameTime = lastTime == 0 ? 0 : timeSinceComputerStart - lastTime;
	lastTime = timeSinceComputerStart;
	// 返回浮点数类型，并且单位是s
	return float(frameTime) / 1000.0f;
}

// 监听用户的操作
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_RBUTTONDOWN:	// 当鼠标右键按下的时候进入
		GetCursorPos(&originalPos);	// 获取光标的位置
		ShowCursor(false);	// 隐藏光标
		rotateView = true;
		return 0;
	case WM_RBUTTONUP:		// 当鼠标右键抬起的时候进入
		SetCursorPos(originalPos.x, originalPos.y);	// 设置光标的位置
		ShowCursor(true);	// 显示光标
		rotateView = false;
		return 0;
	case WM_MOUSEMOVE:		// 当鼠标移动的时候进入
		if (rotateView)		// 当移动摄像机的时候为 true
		{
			POINT currentPos;
			GetCursorPos(&currentPos);
			int deltaX = currentPos.x - originalPos.x;
			int deltaY = currentPos.y - originalPos.y;
			OnMouseMove(deltaX, deltaY);
			SetCursorPos(originalPos.x, originalPos.y);
		}
		return 0;
	case WM_KEYDOWN:  // 当鼠标按下的时候进入
		OnKeyDown(wParam);	// wParam 包含了按键的信息  哪个键被按下了
		return 0;
	case WM_KEYUP:    // 当鼠标抬起的时候进入
		OnKeyUp(wParam);    // wParam 包含了按键的信息  哪个键抬起了
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

// 程序的主入口
// WINAPI	 函数的调用方式
// 这些变量都是应用程序启动时，OS传入的
// hInstance	 表示当前应用程序的实例
// hPrevInstance 表示上一次应用程序启动的实例
// lpCmdLine	 表示通过命令行启动应用程序传递的参数
// nShowCmd		 表示如何显示窗口
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// 定义窗口的类
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

	// 注册窗口
	ATOM atom = RegisterClassEx(&wndClass);
	if (!atom)
	{
		MessageBox(NULL, L"Notice", L"Error", MB_OK);
		return 0;
	}

	// 调整视口的大小
	RECT rect;
	rect.left = 0;
	rect.right = 800;
	rect.top = 0;
	rect.bottom = 600;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	// 创建窗口
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

	//创建上下文  并且设置上下文
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);
	// 场景初始化
	Init();
	ShowWindow(hwnd, SW_SHOW);
	// 更新窗口
	UpdateWindow(hwnd);

	// 显示窗口 （让程序一直运行） 
	MSG msg;
	while (true)
	{
		// 读取消息 ， 读取到消息之后，把当前消息从消息队列中移除掉
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			// 当消息为推出消息的时候，就退出循环
			if (msg.message == WM_QUIT)
			{
				break;
			}
			// 转换为应用程序可以识别的消息
			TranslateMessage(&msg);
			// 分发消息
			DispatchMessage(&msg);
		}
		// 绘制
		Draw();
		// 绘制完成之后，交换缓冲区来显示绘制的结果
		SwapBuffers(dc);
	}

	return 0;
}