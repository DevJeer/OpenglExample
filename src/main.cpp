#include <Windows.h>

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
	wndClass.lpfnWndProc = NULL;
	wndClass.lpszClassName = "GLWindow";
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	// ע�ᴰ��
	ATOM atom = RegisterClassEx(&wndClass);
	if (!atom)
	{
		MessageBox(NULL, "Notice", "Error", MB_OK);
		return 0;
	}

	return 0;
}