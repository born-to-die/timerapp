/*
	Timerapp x86
	Code::Blocks 17.12, MinGW, Windows 7 Ultimate x86

	---

	The meter spent in the program.

    Life is so around the pc that it would be time
    This is to turn into statistics.
    Change, I'm waiting for change.

    ---

	—четчик проведенного времени в программе.

	∆изнь настолько вокруг компа, что пора бы
	это превратить в статистику.
	ѕеремен, € жду перемен.

	---

	14.09.2018
	Alexandr Baklankin (intbad)
*/

#include <Windows.h>
#include <fstream>
#include <tlhelp32.h>
#include <conio.h>
#include <ctime>

using namespace std;

HANDLE hSnap;
PROCESSENTRY32 proc;
DWORD PID;

time_t rawtime;
struct tm * time_start;

ifstream fin;
ofstream fout;

string* arr_names;
string* arr_names_temp;
string temp;
string sOldExeFile;

unsigned int* arr_seconds;
unsigned int* arr_seconds_temp;
unsigned int int_seconds = 0;

unsigned short count_execs = 0;
unsigned short past_active_in_arr = 0;

char szTitle[16] = {0};

bool bFirstProcess = true;
bool run = true;

void saveOnHDD() {

    unsigned short hours;
    unsigned short minutes;
    unsigned short seconds;

    fout.open(".\\stats\\history.txt", std::ios::app);

    fout << time_start->tm_year + 1900 << "/"
        << time_start->tm_mon + 1 << "/"
        << time_start->tm_mday << " "
        << time_start->tm_hour << ":"
        << time_start->tm_min << ":"
        << time_start->tm_sec << " - ";

    time_t rawtime2;
    struct tm * time_end;
    time(&rawtime2);
    time_end = localtime(&rawtime2);


    fout << time_end->tm_year + 1900 << "/"
        << time_end->tm_mon + 1 << "/"
        << time_end->tm_mday << " "
        << time_end->tm_hour << ":"
        << time_end->tm_min << ":"
        << time_end->tm_sec << "\n\n";

        localtime(&rawtime);

    for(int i = 0; i < count_execs; i++) {

        hours = arr_seconds[i] / 3600;
        minutes = (arr_seconds[i] - hours * 3600) / 60;
        seconds = arr_seconds[i] - (hours * 3600 + minutes * 60);

        fout << "\t" << hours << ":" << minutes << ":" << seconds << "\t" << arr_names[i] << "\n";

    }

    fout << "\n";

    fout.close();
}

int main()
{
    time ( &rawtime );
    time_start = localtime ( &rawtime );

    arr_names = new string[count_execs];
    arr_names_temp = new string[count_execs];

    arr_seconds = new unsigned int[count_execs];
    arr_seconds_temp = new unsigned int[count_execs];

    system("title Timerapp");

    printf("TIMERAPP v2.1 \t (https://github.com/born-to-die)\n\
           \nSPACE = PAUSE\
           \nENTER = SESSION INFO\
           \nBACKSPACE = HARD SAVE\
           \nESCAPE = EXIT\n\n");

    if (CreateDirectory(".\\apps", NULL))
        printf("Created folder 'apps'\n");
    else
        printf("Folder 'apps' already have\n");


    if (CreateDirectory(".\\stats", NULL))
        printf("Created folder 'stats'\n");
    else
        printf("Folder 'stats' already have\n");

    printf("\nSession start: %d/%d/%d %d:%d:%d\n",
                    time_start->tm_year + 1900,
                    time_start->tm_mon + 1,
                    time_start->tm_mday,
                    time_start->tm_hour,
                    time_start->tm_min,
                    time_start->tm_sec);

    while(run) {

            while(!kbhit()) {

                // TAKE PROGRAMM
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

                        printf("\nCurrent: %s\t%s\n", proc.szExeFile, szTitle);

                        bool not_found = true;

                        for(int i = 0; i < count_execs; i++) {

                            if(arr_names[i] == sOldExeFile) {
                                not_found = false;
                                past_active_in_arr = i;
                            }

                        }

                        if(not_found) {

                            for(int i = 0; i < count_execs; i++) {
                                arr_names_temp[i] = arr_names[i];
                                arr_seconds_temp[i] = arr_seconds[i];
                            }

                            count_execs++;

                            arr_names = new string[count_execs];
                            arr_seconds = new unsigned int[count_execs];

                            for(int i = 0; i < count_execs - 1; i++) {
                                arr_names[i] = arr_names_temp[i];
                                arr_seconds[i] = arr_seconds_temp[i];
                            }

                            arr_names_temp = new string[count_execs];
                            arr_seconds_temp = new unsigned int[count_execs];

                            past_active_in_arr = count_execs - 1;

                            arr_names[past_active_in_arr] = sOldExeFile;
                            arr_seconds[past_active_in_arr] = int_seconds;

                        }
                        else {
                            arr_seconds[past_active_in_arr] += int_seconds;
                        }

                        int_seconds = 0;
                    }
                }

                Sleep(1000);
                int_seconds++;

                if(int_seconds % 60 == 0)
                    printf("%s\t%d\t%s\n", proc.szExeFile, int_seconds / 60, szTitle);

                sOldExeFile = proc.szExeFile;
                bFirstProcess = false;

        }

        switch(getch()) {
            case 27: {

                unsigned short hours;
                unsigned short minutes;
                unsigned short seconds;

                fout.open(".\\stats\\history.txt", std::ios::app);

                fout << time_start->tm_year + 1900 << "/"
                    << time_start->tm_mon + 1 << "/"
                    << time_start->tm_mday << " "
                    << time_start->tm_hour << ":"
                    << time_start->tm_min << ":"
                    << time_start->tm_sec << " - ";

                time ( &rawtime );
                time_start = localtime ( &rawtime );

                fout << time_start->tm_year + 1900 << "/"
                    << time_start->tm_mon + 1 << "/"
                    << time_start->tm_mday << " "
                    << time_start->tm_hour << ":"
                    << time_start->tm_min << ":"
                    << time_start->tm_sec << "\n\n";

                for(int i = 0; i < count_execs; i++) {

                    hours = arr_seconds[i] / 3600;
                    minutes = (arr_seconds[i] - hours * 3600) / 60;
                    seconds = arr_seconds[i] - (hours * 3600 + minutes * 60);

                    fout << "\t" << hours << ":" << minutes << ":" << seconds << "\t" << arr_names[i] << "\n";

                }

                fout << "\n";

                fout.close();

                for(int i = 0; i < count_execs; i++) {

                    // UPLOAD DATA

                    fin.open(".\\apps\\" + arr_names[i] + ".txt");

                    if(fin) {
                        fin >> hours >> minutes >> seconds;
                        int_seconds = hours * 3600 + minutes * 60 + seconds;
                    }
                    else {
                        int_seconds = 0;
                    }

                    fin.close();

                    fout.open(".\\apps\\" + arr_names[i] + ".txt");

                    arr_seconds[i] += int_seconds;

                    hours = arr_seconds[i] / 3600;
                    minutes = (arr_seconds[i] - hours * 3600) / 60;
                    seconds = arr_seconds[i] - (hours * 3600 + minutes * 60);

                    fout << hours << " " << minutes << " " << seconds;

                    fout.close();

                    // UPLOAD STATS

                }

                run = false;
                break;
            }
            case 13: {



                printf("\n%d/%d/%d %d:%d:%d - ",
                    time_start->tm_year + 1900,
                    time_start->tm_mon + 1,
                    time_start->tm_mday,
                    time_start->tm_hour,
                    time_start->tm_min,
                    time_start->tm_sec);

                time_t rawtime2;
                struct tm * time_end;
                time(&rawtime2);
                time_end = localtime(&rawtime2);


                printf("%d/%d/%d %d:%d:%d\n\n",
                    time_end->tm_year + 1900,
                    time_end->tm_mon + 1,
                    time_end->tm_mday,
                    time_end->tm_hour,
                    time_end->tm_min,
                    time_end->tm_sec);

                localtime(&rawtime);

                unsigned short hours;
                unsigned short minutes;
                unsigned short seconds;

                for(int i = 0; i < count_execs; i++) {

                    hours = arr_seconds[i] / 3600;
                    minutes = (arr_seconds[i] - hours * 3600) / 60;
                    seconds = arr_seconds[i] - (hours * 3600 + minutes * 60);

                    printf("\t%d:%d:%d\t%s\n",
                        hours,
                        minutes,
                        seconds,
                        arr_names[i].c_str()
                    );

                }

                break;
            }
            case 8: {

                saveOnHDD();

                printf("\nSession information has been saved.\n");

                break;
            }
            case 32: {

                printf("\nPAUSE\n");
                getch();
                printf("\nPLAY\n");

                break;
            }
        }
    }

	return 0;
}
