#include <windows.h>
#include <ddraw.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

LPDIRECTDRAW7 lpDD = nullptr;
LPDIRECTDRAWSURFACE7 lpddsPrimary = nullptr;
HWND hWnd = nullptr;

// Функция для генерации случайного цвета
inline unsigned short RGB16BIT565(int r, int g, int b) {
    return ((r & 31) << 11) | ((g & 63) << 5) | (b & 31);
}

// Функция для отрисовки пикселя
inline void PlotPixel(int x, int y, unsigned short color, unsigned short* videoBuffer, int pitch) {
    videoBuffer[x + y * pitch] = color;
}

// Функция для отрисовки "звездного неба"
void DrawStars() {
    DDSURFACEDESC2 ddsd;
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);

    // Блокируем поверхность для рисования
    if (FAILED(lpddsPrimary->Lock(nullptr, &ddsd, DDLOCK_WAIT, nullptr))) {
        std::cerr << "Error: Failed to lock surface!" << std::endl;
        return;
    }

    // Получаем указатель на видеопамять и шаг строки
    unsigned short* videoBuffer = (unsigned short*)ddsd.lpSurface;
    int pitch = ddsd.lPitch / 2;

    // Очистка экрана (черный цвет)
    memset(videoBuffer, 0, SCREEN_HEIGHT * pitch * sizeof(unsigned short));

    // Рисуем случайные "звезды"
    for (int i = 0; i < 1000; ++i) {
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        int r = rand() % 32;
        int g = rand() % 64;
        int b = rand() % 32;
        PlotPixel(x, y, RGB16BIT565(r, g, b), videoBuffer, pitch);
    }

    // Разблокируем поверхность
    lpddsPrimary->Unlock(nullptr);
}

// Функция обработки сообщений окна
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

// Создание окна
HWND CreateGameWindow(HINSTANCE hInstance) {
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = L"GameWindowClass";

    if (!RegisterClassEx(&wc)) {
        std::cerr << "Error: Failed to register window class!" << std::endl;
        return nullptr;
    }

    HWND hWnd = CreateWindowEx(
        0,
        L"GameWindowClass",
        L"DirectDraw Full-Screen Demo",
        WS_POPUP | WS_VISIBLE,
        0, 0,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hWnd) {
        std::cerr << "Error: Failed to create window!" << std::endl;
        return nullptr;
    }

    return hWnd;
}

// Основная функция
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    srand(static_cast<unsigned int>(time(nullptr)));

    hWnd = CreateGameWindow(hInstance);
    if (!hWnd) return 1;

    if (FAILED(DirectDrawCreateEx(nullptr, (VOID**)&lpDD, IID_IDirectDraw7, nullptr))) {
        std::cerr << "Error: DirectDrawCreateEx failed!" << std::endl;
        return 1;
    }

    if (FAILED(lpDD->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE))) {
        std::cerr << "Error: SetCooperativeLevel failed!" << std::endl;
        return 1;
    }

    if (FAILED(lpDD->SetDisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, 0, 0))) {
        std::cerr << "Error: SetDisplayMode failed!" << std::endl;
        return 1;
    }

    DDSURFACEDESC2 ddsd;
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    if (FAILED(lpDD->CreateSurface(&ddsd, &lpddsPrimary, nullptr))) {
        std::cerr << "Error: CreateSurface failed!" << std::endl;
        return 1;
    }

    MSG msg = { 0 };
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        DrawStars();
        Sleep(100);
    }

    // Освобождаем ресурсы
    if (lpddsPrimary) {
        lpddsPrimary->Release();
        lpddsPrimary = nullptr;
    }
    if (lpDD) {
        lpDD->Release();
        lpDD = nullptr;
    }

    // Окно ожидания перед закрытием
    MessageBox(nullptr, L"Нажмите OK, чтобы выйти", L"Программа завершена", MB_OK);

    return 0;
}
