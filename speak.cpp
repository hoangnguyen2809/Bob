#include <iostream>
#include <sapi.h>
#pragma warning(disable:4996)
#include<sphelper.h>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>


int main() {
    // Initialize COM library
    if (FAILED(::CoInitialize(NULL))) {
        std::cerr << "COM initialization failed!" << std::endl;
        return -1;
    }

    //// Create an instance of the recognizer
    //ISpRecognizer* pRecognizer = NULL;
    //if (FAILED(::CoCreateInstance(CLSID_SpSharedRecognizer, NULL, CLSCTX_ALL, IID_ISpRecognizer, (void**)&pRecognizer))) {
    //    std::cerr << "Failed to create recognizer instance!" << std::endl;
    //    ::CoUninitialize();
    //    return -1;
    //}
    //// Set recognizer input to the default audio input (microphone)
    ///*if (FAILED(pRecognizer->SetInput(NULL, TRUE))) {
    //    std::cerr << "Failed to set input!" << std::endl;
    //    pRecognizer->Release();
    //    ::CoUninitialize();
    //    return -1;
    //}*/

    //// Create a speech recognition engine context
    //ISpRecoContext* pRecoContext = NULL;

    //if (FAILED(pRecognizer->CreateRecoContext(&pRecoContext))) {
    //    std::cerr << "Failed to create recognition context!" << std::endl;
    //    pRecognizer->Release();
    //    ::CoUninitialize();
    //    return -1;
    //}





    // Create an instance of the voice
    ISpVoice* pVoice = NULL;
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    
    //Create a voice token
    ISpObjectToken* pVoiceToken = NULL;
    HRESULT hrToken = SpFindBestToken(SPCAT_VOICES, L"gender=female", NULL, &pVoiceToken);
    if (SUCCEEDED(hrToken)) {
        if (FAILED(pVoice->SetVoice(pVoiceToken))) {
            std::cerr << "Failed to set voice!" << std::endl;
        }
        pVoiceToken->Release();
    }
    else {
        std::cerr << "No female voice found! Using default voice." << std::endl;
    }
    
    if (FAILED(hr)) {
        std::cerr << "Failed to create voice instance!" << std::endl;
        ::CoUninitialize();
        return -1;
    }


    else if (SUCCEEDED(hr))
    {
        const wchar_t* textToSpeak = L"Good bye.";
        std::string userInput;
        std::cout << "Hello, Hoang. How can I help you?" << std::endl;
        std::getline(std::cin, userInput);
        std::transform(userInput.begin(), userInput.end(), userInput.begin(),
            [](unsigned char c) { return std::tolower(c); });

        
        int action = -1; // Default action if no match is found
        if (userInput == "what day is today" || userInput == "date" || userInput == "day") {
            action = 2;
        }
        else if (userInput == "hello") {
            action = 1;
        }

        
        switch (action) {
            case 1:
                textToSpeak = L"Hello, Hoang.";
                break;
            case 2:
                textToSpeak = L"Today is Thursday."; 
                break;
            default:
                std::cout << "Sorry cannot understand!\n";
                break;
        }    

        if (textToSpeak != nullptr) {
            std::wstring wideString(textToSpeak); // Convert wide char pointer to wstring
            std::wcout << wideString << std::endl; // Output the wide string again
        }
        else {
            std::wcout << "textToSpeak is nullptr" << std::endl;
        }
        


        // Release the voice
        hr = pVoice->Speak(textToSpeak, 0, NULL);
        pVoice->Release();
        pVoice = NULL;
    }

    // Uninitialize COM library
    ::CoUninitialize();

    return 0;
}
