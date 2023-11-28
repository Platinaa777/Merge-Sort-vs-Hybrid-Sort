import random
import pandas as pd
import matplotlib.pyplot as plt

def read_info_merge(data):
    for line in data:
        info = line.split()
        if (info[0] == 'random' and info[1] == 'MERGE'):
            merge_sort_random[int(info[3])] += float(info[2])

        if (info[0] == 'desc' and info[1] == 'MERGE'):
            merge_sort_desc[int(info[3])] += float(info[2])

        if (info[0] == 'almost' and info[1] == 'MERGE'):
            merge_sort_almost[int(info[3])] += float(info[2])
def show_graphic(sizes, type, stats):
    values = []
    for key in stats:
        values.append(stats[key])

    plt.title(f'Merge Sort Time Complexity for {type} Arrays')
    plt.xlabel('Number of Elements')
    plt.ylabel('Time (microseconds)')
    plt.plot(sizes, values, label=f'{type} Array')
    plt.show()

f = open('test.txt')
data = f.readlines()

merge_sort_random = dict()
merge_sort_desc = dict()
merge_sort_almost = dict()

for i in range (500, 4001, 100):
    merge_sort_almost[i] = 0
    merge_sort_random[i] = 0
    merge_sort_desc[i] = 0

read_info_merge(data)

f = open('test1.txt')
data = f.readlines()

read_info_merge(data)

f = open('test2.txt')
data = f.readlines()

read_info_merge(data)

sizes = []
for i in range (500, 4001, 100):
    merge_sort_almost[i] = merge_sort_almost[i] / 3
    merge_sort_random[i] = merge_sort_random[i] / 3
    merge_sort_desc[i] = merge_sort_desc[i] / 3
    sizes.append(i)

show_graphic(sizes, "Random", merge_sort_random)
show_graphic(sizes, "Descending sorted", merge_sort_desc)
show_graphic(sizes, "Almost sorted", merge_sort_almost)