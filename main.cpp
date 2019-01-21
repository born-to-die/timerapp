/*
	Timerapp x86
	Code::Blocks 17.12, MinGW, Windows 7 Ultimate x86

	Счетчик проведенного времени в программе.

	Жизнь настолько вокруг компа, что пора бы
	это превратить в статистику.
	Перемен, я жду перемен.

	14.09.2018
	Александр Бакланкин (intbad)
*/

#include <Windows.h>
#include <fstream>
#include <tlhelp32.h>
#include <conio.h>
using namespace std;

int main()
{

    HANDLE hSnap;
    PROCESSENTRY32 proc;
    DWORD PID;
    ifstream fin;
    ofstream fout;
    string temp;
    string sOldExeFile;
    unsigned short hours = 0;
    unsigned short minutes = 0;
    unsigned short seconds = 0;
    char szTitle[16] = {0};
    bool bFirstProcess = true;
    bool run = true;

    system("title Timerapp");

    printf("Timerapp \nSPACE = PAUSE; ESCAPE = EXIT\n");

    while(run) {

            while(!kbhit()) {

                hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
                HWND handle = GetForegroundWindow();

                GetWindowText(handle, szTitle, 16);
                GetWindowThreadProcessId(handle, (LPDWORD) &PID);

                proc = {0};
                proc.dwSize = sizeof(PROCESSENTRY32);

                do{
                    if(proc.th32ProcessID == PID) break;
                }while (Process32Next(hSnap, &proc));

                if(!bFirstProcess) {

                    temp = proc.szExeFile;

                    if(temp != sOldExeFile) {

                        fin.close();

                        fout.open((string)sOldExeFile + ".txt");
                        fout << hours << " " << minutes << " " << seconds;
                        fout.close();

                        fin.open((string)proc.szExeFile + ".txt");

                        if(fin) {
                            printf("File \"%s.txt\" successfully opened\n", proc.szExeFile);
                            fin >> hours >> minutes >> seconds;
                        }
                        else {
                            printf("Could not open \"%s.txt\"\n", proc.szExeFile);
                            minutes = 0;
                            seconds = 0;
                            hours = 0;
                        }
                    }
                }
                else {

                    fin.open((string)proc.szExeFile + ".txt");

                    if(fin) {
                        printf("File \"%s.txt\" successfully opened\n", proc.szExeFile);
                        fin >> hours >> minutes >> seconds;
                    }
                    else {
                        printf("Could not open \"%s.txt\"\n", proc.szExeFile);
                        minutes = 0;
                    }
                }

            if(seconds > 59) {
                minutes++;
                seconds = 0;
                printf("%s\t%d\t%s\n", proc.szExeFile, minutes, szTitle);
            }
            if(minutes > 59) {
                hours++;
                minutes = 0;
            }

            Sleep(1000);
            seconds++;

            sOldExeFile = proc.szExeFile;
            bFirstProcess = false;

        }

        switch(getch()) {
            case 27: {
                fin.close();
                fout.open((string)proc.szExeFile + ".txt");
                fout << hours << " " << minutes << " " << seconds;
                run = false;
                break;
            }
            case 32: {
                printf("PAUSE\n");
                getch();
                printf("PLAY\n");
                break;
            }
        }
    }

	return 0;
}
