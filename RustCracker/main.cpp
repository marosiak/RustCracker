#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <windows.h>

using namespace std;

void createCodes(){
    srand( time( NULL ) );
    fstream plik;
    for(int i=1; i<10001; i++){
    plik.open( "slownik.txt", ios::in | ios::out | ios::ate);
        if( plik.good() == true ){
            std::cout << "Uzyskano dostep do pliku!" << std::endl;
            for(int i=0; i<4; i++){
                int n = (std::rand() % 10);
                plik << n;
            }
            plik << "\n";
        }else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
        plik.close();
    }
}

std::string getCode(int linenumber){
    fstream plik;
    plik.open( "slownik.txt", ios::in);
    std::string out;
    for(int i=0; i<=linenumber; i++){
        getline (plik,out);
    }
    return out;
}

void type(char x){
    INPUT ip;
    char chars[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int keys[10] = {0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69};
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    int i = 0;
    while(chars[i] != x){
        i++;
    }

    ip.ki.wVk = keys[i];
    ip.ki.dwFlags = 0;
    SendInput(1, &ip, sizeof(INPUT));

    // Release
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

void enterCode(int index){
    type(getCode(index)[0]); type(getCode(index)[1]);
    type(getCode(index)[2]); type(getCode(index)[3]);
}

int main(){
    Sleep(3000);
    enterCode(1);
    return 0;
}
