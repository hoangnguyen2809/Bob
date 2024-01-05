#include <iostream>
#include <sapi.h>

int main() {
    // Initialize COM library
    if (FAILED(::CoInitialize(NULL))) {
        std::cerr << "COM initialization failed!" << std::endl;
        return -1;
    }

    // Create an instance of the voice
    ISpVoice* pVoice = NULL;
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    
    
    if (FAILED(hr)) {
        std::cerr << "Failed to create voice instance!" << std::endl;
        ::CoUninitialize();
        return -1;
    }

    else if (SUCCEEDED(hr))
    {
        // Release the voice
        hr = pVoice->Speak(L"Hello, Hoang", 0, NULL);
        pVoice->Release();
        pVoice = NULL;
    }

    // Uninitialize COM library
    ::CoUninitialize();

    return 0;
}
