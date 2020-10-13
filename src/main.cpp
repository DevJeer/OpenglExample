#include <Windows.h>

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
	wndClass.lpfnWndProc = NULL;
	wndClass.lpszClassName = "GLWindow";
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	// 注册窗口
	ATOM atom = RegisterClassEx(&wndClass);
	if (!atom)
	{
		MessageBox(NULL, "Notice", "Error", MB_OK);
		return 0;
	}

	return 0;
}