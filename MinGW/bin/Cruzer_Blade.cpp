#include "CruzerKeyboard.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

int main() {
    /*
    //Fake Update
    if (cruzer::isVisible()) {
        cruzer::toggleConsoleVisibility(false);
    }
    cruzer::keyPress(VK_LWIN);
    cruzer::delay(300);
    cruzer::typeKeys("Edge");
    cruzer::delay(200);
    cruzer::keyPress(VK_RETURN);
    cruzer::delay(2000);
    cruzer::typeKeys("https://updatefaker.com/windows10/index.html");
    cruzer::delay(500);
    cruzer::keyPress(VK_RETURN);
    cruzer::delay(500);
    cruzer::keyPress(VK_F11);
    */
    

    

    /*
    //CMD Prompt
    if (cruzer::isVisible()) {
        cruzer::toggleConsoleVisibility(false);
    }
    std::vector<WORD> keys;
    keys.push_back(VK_LWIN);
    keys.push_back('R');
    cruzer::multiPress(keys);
    cruzer::delay(100);
    cruzer::typeKeys("cmd");
    cruzer::delay(100);
    cruzer::keyPress(VK_RETURN);
    */


    if (cruzer::isVisible()) {
        cruzer::toggleConsoleVisibility(false);
    }
    cruzer::keyPress(VK_LWIN);
    cruzer::delay(300);
    cruzer::typeKeys("Edge");
    cruzer::delay(200);
    cruzer::keyPress(VK_RETURN);
    cruzer::delay(2000);
    cruzer::typeKeys("https://updatefaker.com/windows10/index.html");
    cruzer::delay(500);
    cruzer::keyPress(VK_RETURN);
    cruzer::delay(500);
    cruzer::keyPress(VK_F11);


    return 0;
}
