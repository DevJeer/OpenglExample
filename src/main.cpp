#include <Windows.h>

// 监听用户的操作
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
	}

	return 0;
}