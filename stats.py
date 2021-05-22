import matplotlib as matplotlib
import matplotlib.pyplot as plot
import matplotlib.dates as mdates
import datetime as dt
import numpy as np
import csv
import os

now = dt.datetime.now()

"""
Dumb data calculation for statistics
Goes through the files (several times) until there are 10 largest positions (in time) 
"""


def func(pct, values):
    """
    Formats caption for charts
    :param pct: string
    :param values: array
    :return: string
    """

    absolute = int(pct / 100. * np.sum(values))

    return "{:.1f}%\n({:d} ч.)".format(pct, absolute)


def get_pie():
    """
    Formats chart-pie
    """
    indexer = 1

    while True:

        arr_files = os.walk("apps")

        processes_names = []
        processes_times = []

        for address, dirs, files in arr_files:

            for file in files:

                print(file)

                time = open("apps/" + file)

                time_f = time.read().split()

                # print(time_f)

                hours = int(time_f[0])

                if hours >= indexer:
                    file = file.split('.')[0]

                    processes_times.append(hours)
                    processes_names.append(file)

        if len(processes_times) <= 10:
            break
        else:
            indexer += 1

    matplotlib.rcParams.update({'font.size': 9})
    plot.title('Hours spent in programs / games')

    plot.pie(
        processes_times,
        autopct=lambda pct: func(pct, processes_times),
        radius=1.1,
        labels=processes_names
    )

    plot.savefig(now.strftime("%Y-%m-%d") + ' stats (pie).png')


def get_bars():
    """
    Formats chart-bars
    """
    indexer = 1

    while True:

        arr_files = os.walk("apps")

        processes_names = []
        processes_times = []

        for address, dirs, files in arr_files:

            for file in files:

                print(file)

                time = open("apps/" + file)

                time_f = time.read().split()

                # print(time_f)

                hours = int(time_f[0])

                if hours >= indexer:
                    file = file.split('.')[0]

                    processes_times.append(hours)
                    processes_names.append(file)

        if len(processes_times) <= 10:
            break
        else:
            indexer += 1

    dpi = 80
    pic = plot.figure(dpi=dpi, figsize=(1000 / dpi, 1000 / dpi))

    matplotlib.rcParams.update({'font.size': 9})
    plot.title('Hours spent in programs / games')

    plot.bar(processes_names, processes_times)

    pic.savefig(now.strftime("%Y-%m-%d") + ' stats (bar).png')


print("\nBuild pie...\n")

get_pie()

print("\nBuild bar...\n")

get_bars()
