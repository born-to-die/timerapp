# Timerapp Simple v.2.2

![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/born-to-die/timerapp) ![GitHub last commit](https://img.shields.io/github/last-commit/born-to-die/timerapp)

![timerapp screen](https://raw.githubusercontent.com/born-to-die/timerapp/master/screens/screen_1.png)

![timerapp screen](https://raw.githubusercontent.com/born-to-die/timerapp/master/screens/bar.png)

![timerapp screen](https://raw.githubusercontent.com/born-to-die/timerapp/master/screens/pie.png)

###### English description

**DESCRIPTION**

Program to track time spent in other programs (executable files).

**ALGORITHM**

During operation, it takes the active process of the system and 
starts counting the duration of its work in seconds. When changing 
the process does the same for him. When you press the "Escap" saves time.

**VERSIONS**

In the original, each time the active process was changed, the program 
recorded the time of the past immediately to the file. In version 2, the 
program stores all values in memory, and only after pressing the key, 
the output unloads data to disk.


This can have an unpleasant effect, if the program closes unexpectedly 
(blackout, system errors), then all data will be lost. 

If this bothers you, 
then download the project from the old branch.

**SYSTEM REQUIREMENTS**

1. Windows
2. Python 3.x.x

**TECHS, TOOLS**

1. MinGW C++, Code::Blocks 20.03;
2. Python 3.9, matplotlib (numpy, pillow), PyCharm Community 2021.1.1.

**INSTALL**

1. Download and unpack the archive from the releases section;
2. Run install.bat to install the required python libraries;
3. To start the program, run "Timerapp.exe";
4. To terminate the program, press "Escape", the session data will be saved in / apps / and / stats /;
5. To build graphs (10 popular time programs) run stats.py. 

---

###### Русское описание

**ОПИСАНИЕ**

Программа для отслеживания времени, проведенного в других программах 
(исполняемые файлы).

**АЛГОРИТМ**

Во время работы берет активный процесс системы и начинает считать 
продолжительность его работы в секундах. При смене процесса тоже 
самое делает для него. При нажатии клавиши "Escape" сохраняет время 
на диск в формате название_процесса.ехе.тхт, в котором указано 
общее время работы в формате "часы минуты секунды". И так для каждого процесса. 

**ВЕРСИИ**

В оригинале, каждый раз когда изменялся активный процесс, программа записывала время 
работы прошлой сразу в файл. В версии 2 программа хранит все значения в памяти, и только 
после нажатия клавиши выход выгружает данные на диск.

Это может иметь неприятный эффект, если программа неожиданно 
закроется (отключение света, ошибки системы), то все данные будут потеряны. 

Если это вас беспокоит, то скачайте проект из старого коммита.

**СИСТ. ТРЕБ.**

1. Windows
2. Python 3.x.x

**ТЕХНОЛОГИИ, ИНСТРУМЕНТЫ**

1. MinGW C++, Code::Blocks 20.03;
2. Python 3.9, matplotlib (numpy, pillow), PyCharm Community 2021.1.1.

**УСТАНОВКА**

1. Скачать и распаковать архив из раздела релизов;
2. Запустите install.bat для установки необходимых python библиотек;
3. Для старта программы запустить "Timerapp.exe";
4. Для завершения программы нажать "Escape", данные сеанса будут сохранены в /apps/ и /stats/;
5. Для построения графиков (10-популярных программ по времени) запустить stats.py.


