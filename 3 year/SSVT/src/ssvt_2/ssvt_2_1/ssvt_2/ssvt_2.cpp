#define INITGUID
#include <initguid.h>
#include <ddraw.h>
#include <iostream>

#pragma comment(lib, "ddraw.lib")

int main() {
    LPDIRECTDRAW7 lpDD = nullptr;
    HRESULT result = DirectDrawCreateEx(nullptr, (VOID**)&lpDD, IID_IDirectDraw7, nullptr);

    if (result != DD_OK) {
        std::cerr << "Error: DirectDrawCreateEx failed!" << std::endl;
        return 1;
    }

    std::cout << "DirectDraw initialized successfully!" << std::endl;

    DDDEVICEIDENTIFIER2 dddi;
    result = lpDD->GetDeviceIdentifier(&dddi, 0);

    if (result == DD_OK) {
        std::cout << "Driver Information:" << std::endl;
        std::cout << "Driver: " << dddi.szDriver << std::endl;
        std::cout << "Description: " << dddi.szDescription << std::endl;
        std::cout << "Vendor ID: " << dddi.dwVendorId << std::endl;
        std::cout << "Device ID: " << dddi.dwDeviceId << std::endl;
        std::cout << "Driver Version: " << HIWORD(dddi.liDriverVersion.HighPart) << "."
            << LOWORD(dddi.liDriverVersion.HighPart) << "."
            << HIWORD(dddi.liDriverVersion.LowPart) << "."
            << LOWORD(dddi.liDriverVersion.LowPart) << std::endl;
    }
    else {
        std::cerr << "Error: Failed to get device identifier!" << std::endl;
    }

    if (lpDD) {
        lpDD->Release();
        lpDD = nullptr;
    }

    return 0;
}