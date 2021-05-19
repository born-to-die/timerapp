import matplotlib as matplotlib
import matplotlib.pyplot as pyplot
import matplotlib.dates as mdates
import datetime as dt
import numpy as np
import csv
import os

now = dt.datetime.now()

arr_files = os.walk("apps")

processes_names = []
processes_times = []

def func(pct, allvals):
    absolute = int(pct/100.*np.sum(allvals))
    return "{:.1f}%\n({:d} ч.)".format(pct, absolute)

def getPie():

    for address, dirs, files in arr_files:
        
        for file in files:

            print(file)
                    
            time = open("apps/" + file)       
            
            time_f = time.read().split()

            print(time_f)
                   
            minutes = int(time_f[2])
            
            if minutes >= 0:

                file = file.split('.')[0]
                
                processes_times.append(minutes)
                processes_names.append(file)

    print(processes_names)
    print(processes_times)

    dpi = 80
    pic = pyplot.figure(dpi = dpi, figsize = (1000 / dpi, 1000 / dpi) )

    matplotlib.rcParams.update({'font.size': 9})
    pyplot.title('Проведенные часы в программах/играх')
    xs = range(len(processes_names))

    pyplot.pie(
        processes_times,
        autopct=lambda pct: func(pct, processes_times),
        radius = 1.1,
        labels=processes_names
    )

    pyplot.savefig(now.strftime("%Y-%m-%d") + ' stats (p).png')

def getBars():

    for address, dirs, files in arr_files:
        
        for file in files:
                    
            time = open("apps/" + file)       
            
            time_f = time.read().split()
                   
            minutes = int(time_f[0])
            
            if minutes > 0:

                file = file.split('.')[0]
                
                processes_times.append(minutes)
                processes_names.append(file)

    dpi = 80
    pic = pyplot.figure(dpi = dpi, figsize = (1000 / dpi, 1000 / dpi) )
    matplotlib.rcParams.update({'font.size': 9})

    pyplot.title('Проведенные часы в программах/играх')

    ax = pyplot.axes()
    ax.yaxis.grid(True, zorder = 1)

    xs = range(len(processes_names))

    pyplot.bar([x + 0.05 for x in xs], [ d * 0.9 for d in processes_times],
        width = 0.2, color = 'red', alpha = 0.7, label = 'Часы',
        zorder = 2)

    pyplot.xticks(xs, processes_names)

    pic.autofmt_xdate(rotation = 25)

    pyplot.legend(loc = 'upper right')

    pic.savefig(now.strftime("%Y-%m-%d") + ' stats (b).png')
    

getPie()
getBars()
