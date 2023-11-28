import random
import pandas as pd
import matplotlib.pyplot as plt

def read_info_merge(data, insert):
    for line in data:
        info = line.split()
        if (info[0] == 'random' and info[1] == 'HYBRID' and info[7] == f"{insert}"):
            hybrid_sort_random[int(info[3])] += float(info[2])

        if (info[0] == 'desc' and info[1] == 'HYBRID' and info[7] == f"{insert}"):
            hybrid_sort_desc[int(info[3])] += float(info[2])

        if (info[0] == 'almost' and info[1] == 'HYBRID' and info[7] == f"{insert}"):
            hybrid_sort_almost[int(info[3])] += float(info[2])
def show_graphic(sizes, type, stats, insert):
    values = []
    for key in stats:
        values.append(stats[key])

    plt.title(f'Hybrid Sort Time Complexity for {type} Arrays inser sort {insert}')
    plt.xlabel('Number of Elements')
    plt.ylabel('Time (microseconds)')
    plt.plot(sizes, values, label=f'{type} Array')
    plt.show()

f = open('test.txt')
data = f.readlines()

hybrid_sort_random = dict()
hybrid_sort_desc = dict()
hybrid_sort_almost = dict()

for i in range (500, 4001, 100):
    hybrid_sort_almost[i] = 0
    hybrid_sort_random[i] = 0
    hybrid_sort_desc[i] = 0

# manually input 5 10 20 50
insertion_value = 50

read_info_merge(data, insertion_value)

f = open('test1.txt')
data = f.readlines()

read_info_merge(data, insertion_value)

f = open('test2.txt')
data = f.readlines()

read_info_merge(data, insertion_value)

sizes = []
for i in range (500, 4001, 100):
    hybrid_sort_almost[i] = hybrid_sort_almost[i] / 3
    hybrid_sort_random[i] = hybrid_sort_random[i] / 3
    hybrid_sort_desc[i] = hybrid_sort_desc[i] / 3
    sizes.append(i)

show_graphic(sizes, "Random", hybrid_sort_random, insertion_value)
show_graphic(sizes, "Descending sorted", hybrid_sort_desc, insertion_value)
show_graphic(sizes, "Almost sorted", hybrid_sort_almost, insertion_value)