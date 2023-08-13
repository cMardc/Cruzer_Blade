#ifdef _WIN32   //If platform is windows

//Needed libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>


//Use cruzer namespace, to acces anything cruzer::thingToAccess
namespace cruzer {
    
    /*
    * @brief Function to hold a key until keyRelease() or keyPress() is called
    * @param virtualKeyCode - Is a code that is key (WORD)
    * @return This function does not return anything
    */
    void keyHold(WORD virtualKeyCode) {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;

        // Press the key
        input.ki.wVk = virtualKeyCode;
        input.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &input, sizeof(INPUT));
    }

    /*
    * @brief Function to Release a key
    * @param virtualKeyCode - Is a code that is key (WORD)
    * @return This function does not return anything
    */
    void keyRelease(WORD virtualKeyCode) {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        
        // Release the key
        input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
        SendInput(1, &input, sizeof(INPUT));
    }

/*
    * @brief Function to Press (Hold + Release) a key
    * @param virtualKeyCode - Is a code that is key (WORD)
    * @return This function does not return anything
    */
    void keyPress(WORD virtualKeyCode) {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;

        // Press the key
        input.ki.wVk = virtualKeyCode;
        input.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &input, sizeof(INPUT));

        // Release the key
        input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
        SendInput(1, &input, sizeof(INPUT));
    }

    /*
    * @brief Function to type text
    * @param text points to string that will be typed (const std::string&)
    * @return This function does not return anything
    */    
    void typeKeys(const std::string& text) {
        Sleep(170); // Adjust as needed
        bool shiftPressed = false;

        for (char c : text) {
            // Check if the character is uppercase or lowercase
            bool isUppercase = isupper(c);

            if (c == '~' || c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*' || c == '(' || c == ')' || c == '_' || c == '+' || c == '{' || c == '}' || c == ':' || c == '\"' || c == '|' || c == '?' || c == '>' || c == '<') {
                isUppercase = true;
            }

            // Simulate pressing the Shift key if needed
            if (isUppercase && !shiftPressed) {
                INPUT shiftInput;
                shiftInput.type = INPUT_KEYBOARD;
                shiftInput.ki.wVk = VK_SHIFT;
                shiftInput.ki.dwFlags = 0;
                SendInput(1, &shiftInput, sizeof(INPUT));
                shiftPressed = true;
            }

            // Convert character to virtual key code
            WORD virtualKeyCode = VkKeyScanA(c);

            INPUT input;
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = 0;
            input.ki.time = 0;
            input.ki.dwExtraInfo = 0;

            // Press the key
            input.ki.wVk = virtualKeyCode;
            input.ki.dwFlags = 0; // 0 for key press
            SendInput(1, &input, sizeof(INPUT));

            // Release the key
            input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
            SendInput(1, &input, sizeof(INPUT));

            // Release the Shift key if it was pressed
            if (isUppercase && shiftPressed) {
                INPUT shiftInputRelease;
                shiftInputRelease.type = INPUT_KEYBOARD;
                shiftInputRelease.ki.wVk = VK_SHIFT;
                shiftInputRelease.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &shiftInputRelease, sizeof(INPUT));
                shiftPressed = false;
            }

        }

    }

    /*
    * @brief Function to press keys as a shortcut
    * @param keys - Is a vector of codes that stores keycode of key (std::vector<WORD>)
    * @return This function does not return anything
    */
    void multiPress(std::vector<WORD> keys) {

        std::vector<INPUT> ips;

        for (size_t i = 0; i < keys.size(); i++) {

            INPUT input;
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = 0;
            input.ki.time = 0;
            input.ki.dwExtraInfo = 0;
            ips.push_back(input);


            // Press the key
            input.ki.wVk = keys[i];
            input.ki.dwFlags = 0; // 0 for key press
            SendInput(1, &input, sizeof(INPUT));

        }
        
        std::reverse(ips.begin(), ips.end());

        for (size_t i = 0; i < ips.size(); i++) {

            INPUT input = ips[i];

            // Release the key
            input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
            SendInput(1, &input, sizeof(INPUT));

        }

    }

    /*
    * @brief Function to wait
    * @param microseconds - shows how much microseconds to wait (DWORD)
    * @return This function does not return anything
    */
    void delay(DWORD microseconds) {
        if (microseconds >= 0) {
            Sleep(microseconds);
        }
        else {
            throw "Error: Can not delay(A.K.A \"Sleep\") for negative time.";
        }
    }

    /*
    * @brief Function to change console's visibility
    * @param show - variable to select to show or not (bool)
    * @return This function does not return anything
    */
    void toggleConsoleVisibility(bool show) {
        HWND hWnd = GetConsoleWindow(); // Get the console window handle
        if (show) {
            ShowWindow(hWnd, SW_SHOW); // Show the console window
        }
        else {
            ShowWindow(hWnd, SW_HIDE); // Hide the console window
        }
    }

    /* 
    * @brief Function to check if the console window is visible
    * This function does not take any parameters
    * @return This function returns true if window is visible, false if it's not (bool)
    */
    bool isVisible() {
        HWND hWnd = GetConsoleWindow(); // Get the console window handle
        return IsWindowVisible(hWnd); // Check if the window is visible
    }

    /* 
    * @brief Function to get drive letter of USB stick
    * This function does not take any parameters
    * @return This function returns letter/symbol assigned to (last plugged) USB drive (wchar_t)
    */
    wchar_t getDriveLetter() {
        for (wchar_t driveLetter = L'Z'; driveLetter >= L'A'; --driveLetter) {
            std::wstring rootPath = driveLetter + std::wstring(L":\\");
            UINT driveType = GetDriveTypeW(rootPath.c_str());

            if (driveType == DRIVE_REMOVABLE || driveType == DRIVE_FIXED) {
                return driveLetter;
                break; 
            }
        }

        return 0;
    }

    /* 
    * @brief Function to simulate left mouse click
    * This function does not take any parameters
    * @return This function does not return anything
    */
    void leftMouseClick() {
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    /* 
    * @brief Function to simulate right mouse click
    * This function does not take any parameters
    * @return This function does not return anything
    */
    void rightMouseClick() {
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    /* 
    * @brief Function to simulate movement of mouse
    * @param x - is X coordinate for mouse (int)
    * @param y - is Y coordinate for mouse (int)
    * @return This function does not return anything
    */
    void moveMouse(int x, int y) {
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
        input.mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
        SendInput(1, &input, sizeof(INPUT));
    }


}




#endif                  // End of ifdef statement