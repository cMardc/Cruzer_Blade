#ifdef _WIN32

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>


namespace cruzer {
    
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

    void delay(DWORD microseconds) {
        if (microseconds >= 0) {
            Sleep(microseconds);
        }
        else {
            throw "Error: Can not delay(A.K.A \"Sleep\") for negative time.";
        }
    }

    // Function to show or hide the console window
    void toggleConsoleVisibility(bool show) {
        HWND hWnd = GetConsoleWindow(); // Get the console window handle
        if (show) {
            ShowWindow(hWnd, SW_SHOW); // Show the console window
        }
        else {
            ShowWindow(hWnd, SW_HIDE); // Hide the console window
        }
    }

    // Function to check if the console window is visible
    bool isVisible() {
        HWND hWnd = GetConsoleWindow(); // Get the console window handle
        return IsWindowVisible(hWnd); // Check if the window is visible
    }

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

    void leftMouseClick() {
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    // Simulate a right mouse button click
    void rightMouseClick() {
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    // Move the mouse to the specified screen coordinates
    void moveMouse(int x, int y) {
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
        input.mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
        SendInput(1, &input, sizeof(INPUT));
    }


}




#endif