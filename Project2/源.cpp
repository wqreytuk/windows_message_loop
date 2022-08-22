#if       _WIN32_WINNT < 0x0500
  #undef  _WIN32_WINNT
  #define _WIN32_WINNT   0x0500
#endif

#define _UNICODE
#define UNICODE

#include <windows.h>
#include <windowsx.h>
#include <iostream>

using namespace std;

LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);
void test_function();
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow){

    HWND hWnd;

    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass1";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL,
                          L"WindowCLass1",
                          L"Window Program",
                          WS_OVERLAPPEDWINDOW,
                          300,
                          300,
                          500,
                          400,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hWnd, nCmdShow);

    //ShowWindow( GetConsoleWindow(), SW_HIDE );

    MSG msg;

    // check this: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage
    // GetMessage has three potential return value zero/non-zero/-1
    BOOL bRet;
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            MessageBox(NULL, TEXT("some errors happen here, terminate this app"), TEXT(""), 0);
            return -1;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;

}

LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam)
                            {
                                switch(message)
                                {
                                case WM_DESTROY:
                                    {
                                        //ShowWindow( GetConsoleWindow(), SW_RESTORE );
                                        test_function();
                                        return 0;
                                    }break;

                                }
                                return DefWindowProc  (hWnd, message, wParam, lParam);
                            }

void test_function() {
	MessageBox(NULL, TEXT("whoami"), TEXT(""), 0);
}
