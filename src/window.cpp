#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_CLOSE:
    DestroyWindow(hWnd);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam)
}


Window::Window() : m_hInstance(GetModuleHandle(nullptr)) {

  const wchar_t *CLASS_NAME = L"My Winows Class"; // L means wide string
  WNDCLASS wndClass = {};
  wndClass.lpszClassName = CLASS_NAME;
  wndClass.hInstance = m_hInstance;
  wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //  Mouse is an arrow
  wndClass.lpfnWndProc = WindowProc;              // Fix later says the tutorial guy

  RegisterClass(&wndClass);

  DWORD style =
      WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU; // caption - window title, bruh, windows stuff

  int width = 640;
  int height = 480;

  RECT rect;
  rect.left = 250;
  rect.top = 250;
  rect.right = 250;
  rect.bottom = rect.top * height;

  AdjustWindowRect(&rect, style, false);

  m_hwnd =
      CreateWindowEx(0, CLASS_NAME, L"Title", style, rect.left, rect.top, rect.right - rect.left,
                     rect.bottom - rect.top, NULL, NULL, m_hInstance, NULL

      );

  ShowWindow(m_hwnd, SW_SHOW);
}

Window::~Window() {
  const wchar_t *CLASS_NAME = L"My Winows Class";
  UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages() {

  MSG msg = {};

  while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {

    if (msg.message == WM_QUIT) return false;

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return true;
}


