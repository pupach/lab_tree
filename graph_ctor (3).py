import matplotlib.pyplot as plt
import csv


dataDir   = "data/"
graphDir  = "graphs/"
units     = "ms"

def gen_graphs(fileNames, title):
    X = []
    Y = []
    for name in fileNames:
        with open(dataDir + name + ".txt", 'r') as dataFile:
            plotting = csv.reader(dataFile, delimiter=',')

            for ROWS in plotting:
                print(ROWS, name)
                X.append(int(ROWS[0]))
                Y.append(float(ROWS[1]))

        plt.plot(X, Y)
        X.clear()
        Y.clear()

    plt.legend(fileNames)
    plt.title(title)
    plt.xlabel("size")
    plt.ylabel(units)
    plt.savefig(graphDir + title)

gen_graphs(["AVL_remove", "decart_remove", "splay_remove", "RBT_remove", "Skip_remove"], "remove")

plt.cla()

gen_graphs(["AVL_insert", "decart_insert", "splay_insert", "RBT_insert", "Skip_insert"], "insert")