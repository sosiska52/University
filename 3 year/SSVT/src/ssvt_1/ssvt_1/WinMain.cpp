#include <windows.h>
#include <dinput.h>
#include <iostream>
#include <vector>
#include <string>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

LPDIRECTINPUT8 dInput = nullptr;
LPDIRECTINPUTDEVICE8 keyboard = nullptr;
LPDIRECTINPUTDEVICE8 mouse = nullptr;
BYTE keyStates[256] = { 0 };
BYTE prevKeyStates[256] = { 0 };
DIMOUSESTATE mouseState = { 0 };
DIMOUSESTATE prevMouseState = { 0 };

// Инициализация DirectInput
bool InitDirectInput(HWND hWnd) {
    if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dInput, NULL))) {
        std::cerr << "Ошибка DirectInput8Create\n";
        return false;
    }

    // Инициализация клавиатуры
    if (FAILED(dInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL))) {
        std::cerr << "Ошибка создания устройства клавиатуры\n";
        return false;
    }
    if (FAILED(keyboard->SetDataFormat(&c_dfDIKeyboard))) {
        std::cerr << "Ошибка установки формата данных клавиатуры\n";
        return false;
    }
    if (FAILED(keyboard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
        std::cerr << "Ошибка установки кооперативного уровня клавиатуры\n";
        return false;
    }
    keyboard->Acquire();

    // Инициализация мыши
    if (FAILED(dInput->CreateDevice(GUID_SysMouse, &mouse, NULL))) {
        std::cerr << "Ошибка создания устройства мыши\n";
        return false;
    }
    if (FAILED(mouse->SetDataFormat(&c_dfDIMouse))) {
        std::cerr << "Ошибка установки формата данных мыши\n";
        return false;
    }
    if (FAILED(mouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
        std::cerr << "Ошибка установки кооперативного уровня мыши\n";
        return false;
    }
    mouse->Acquire();

    return true;
}

// Перечисление устройств
BOOL CALLBACK EnumDevicesCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext) {
    std::wcout << L"Устройство: " << pdidInstance->tszProductName << std::endl;
    return DIENUM_CONTINUE;
}

void EnumDevices() {
    std::cout << "Перечисление устройств..." << std::endl;
    dInput->EnumDevices(DI8DEVCLASS_ALL, EnumDevicesCallback, NULL, DIEDFL_ATTACHEDONLY);
}

// Чтение состояния клавиатуры
void ReadKeyboard() {
    HRESULT hr = keyboard->GetDeviceState(sizeof(keyStates), (LPVOID)&keyStates);

    if (FAILED(hr)) {
        if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) {
            keyboard->Acquire();
        }
        return;
    }

    int keys[] = { DIK_W, DIK_A, DIK_S, DIK_D, DIK_SPACE };
    const char* keyNames[] = { "W", "A", "S", "D", "SPACE" };
    std::vector<std::string> pressedKeys;

    for (int i = 0; i < 5; i++) {
        if ((keyStates[keys[i]] & 0x80) && !(prevKeyStates[keys[i]] & 0x80)) {
            std::cout << "Клавиша " << keyNames[i] << " нажата\n";
        }
        if (!(keyStates[keys[i]] & 0x80) && (prevKeyStates[keys[i]] & 0x80)) {
            std::cout << "Клавиша " << keyNames[i] << " отпущена\n";
        }
        if (keyStates[keys[i]] & 0x80) {
            pressedKeys.push_back(keyNames[i]);
        }
    }

    if (!pressedKeys.empty()) {
        std::cout << "Комбинация: ";
        for (size_t i = 0; i < pressedKeys.size(); i++) {
            std::cout << pressedKeys[i];
            if (i < pressedKeys.size() - 1) std::cout << "+";
        }
        std::cout << "\n";
    }

    memcpy(prevKeyStates, keyStates, sizeof(keyStates));
}

void ReadMouse() {
    HRESULT hr = mouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);

    if (FAILED(hr)) {
        if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) {
            mouse->Acquire();
        }
        return;
    }

    if (mouseState.lX != prevMouseState.lX || mouseState.lY != prevMouseState.lY) {
        std::cout << "Движение X: " << mouseState.lX << " Y: " << mouseState.lY << std::endl;
    }

    if ((mouseState.rgbButtons[0] & 0x80) && !(prevMouseState.rgbButtons[0] & 0x80)) {
        std::cout << "Левая кнопка нажата\n";
    }
    if ((mouseState.rgbButtons[1] & 0x80) && !(prevMouseState.rgbButtons[1] & 0x80)) {
        std::cout << "Правая кнопка нажата\n";
    }

    memcpy(&prevMouseState, &mouseState, sizeof(DIMOUSESTATE));
}

void Cleanup() {
    if (keyboard) {
        keyboard->Unacquire();
        keyboard->Release();
    }
    if (mouse) {
        mouse->Unacquire();
        mouse->Release();
    }
    if (dInput) {
        dInput->Release();
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    HWND hWnd = GetConsoleWindow();

    if (!InitDirectInput(hWnd)) {
        return 1;
    }

    EnumDevices();

    std::cout << "Нажимайте W, A, S, D, SPACE и двигайте мышь...\n";

    while (true) {
        ReadKeyboard();
        ReadMouse();
        Sleep(50);
    }

    Cleanup();
    return 0;
}