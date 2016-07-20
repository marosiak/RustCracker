#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>

using namespace std;

void createCodes(){
    srand( time( NULL ) );
    fstream file;
    for(int i=1; i<10001; i++){
        file.open( "dictionary/dictionary.txt", ios::in | ios::out | ios::ate);
        if( file.good() == true ){
            std::cout << "Uzyskano dostep do pliku!" << std::endl;
            for(int i=0; i<4; i++){
                int n = (std::rand() % 10);
                file << n;
            }
            file << "\n";
        }
        else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
        file.close();
    }
}

std::string getCode(int linenumber){
    fstream file;
    file.open( "dictionary/dictionary.txt", ios::in);
    std::string out;
    for(int i=0; i<=linenumber; i++){
        getline (file,out);
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
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

void enterCode(int index){
    type(getCode(index)[0]); type(getCode(index)[1]);
    type(getCode(index)[2]); type(getCode(index)[3]);
}

bool reloader = true;
int getProgress(){
    fstream file;
    file.open( "cfgs/progress.cfg", ios::in | ios::out);
    std::string out;
    getline (file,out);
    int output = std::stoi(out);
    return output;
}

void saveProgress(int curret){
    fstream file;
    file.open( "cfgs/progress.cfg", ios::in | ios::out | ios::trunc);
    file << curret;
    file.close();
}

void menu(){
    cout << "Hello, select what do you want \n"
            "a. Continue curret hacking\n"
            "b. Start new hacking\n";
    bool switcher=true;
    while(switcher == true){
        if(getch() == 97){
            switcher=false;
        }
        if(getch() == 98){
            saveProgress(0);
            switcher=false;
        }
    }
    system("cls");
}

int main(){
    menu();
    cout << "Press F2 to enter the code\n";
    while (true){
        if(reloader){
            if(GetAsyncKeyState(VK_F2)){
                fstream file;
                file.open( "logs/log.txt", ios::in | ios::out | ios::ate);
                cout << "Code nr. "<<getProgress()<<" has been written. ["<<getCode(getProgress())<<"]\n";
                file << "Code nr. "<<getProgress()<<" has been written. ["<<getCode(getProgress())<<"]\n";
                enterCode(getProgress());
                saveProgress(getProgress()+1);
                file.close();
            }
            reloader=false;
        }
        else{
            Sleep(200);
            reloader = true;
        }
    }
    return 0;
}
