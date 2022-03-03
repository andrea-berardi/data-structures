#!/bin/python3

# library imports
from typing import List  # I like to specify the type of the variables
import matplotlib.pyplot as plt  # required to create the plots
from matplotlib import rcParams  # enable automatic scaling of the plots

rcParams.update({"figure.autolayout": True})  # enable automatic scaling of the plots

# directories where the results are stored
dir: str = "../results/"  # parent directory
dir_lab_1A: str = "lab_1/1A/lab_1A"
dir_lab_1B: str = "lab_1/1B/lab_1B"
dir_lab_2: str = "lab_2/lab_2"
dir_lab_3: str = "lab_3/lab_3"
dir_lab_4: str = "final/final"

# file extension
ext: str = ".csv"

# PNG quality (dpi)
quality: int = 1000

# axis labels
x_label: str = "Keys (n)"
y_label: str = "Time (clock)"

# plots titles
title_lab_1A: str = "Binary Search Trees"
title_lab_1B: str = "Linked Lists, Binary Search Trees"
title_lab_2: str = "Red-Black Trees, Binary Search Trees"
title_lab_3: str = "B-Trees, Red-Black Trees, Binary Search Trees"
title_lab_4: str = "B-Trees (with variable degree t)"

# Lab. 1A - Binary Search Trees
def lab_1A() -> None:
    with open(dir + dir_lab_1A + ext, "r") as file:
        lines: List(str) = [line.strip() for line in file.readlines()]

        keys: List(int) = []
        second_column: List(float) = []

        title: str = ""

        for line in iter(lines):
            # check if line has any letters
            if not any(char.isalpha() for char in line):
                line: List(str) = line.split(",")

                keys.append(int(line[0]))
                second_column.append(float(line[1]))
            else:
                title: str = line.split(",")[1]  # title of the second column
            # end if
        # end for

        plt.xlabel(x_label)
        plt.ylabel(y_label)  # set axis labels
        plt.plot(keys, second_column, "blue", linewidth=2)  # plot the data
        plt.title(title_lab_1A)  # set title
        plt.grid(True)  # show the grid
        plt.legend([title], loc="best")  # show legend, and put it in the best location
        plt.xlim(0)
        plt.ylim(0)  # set the lower limits of the x and y axis
        plt.savefig(dir + dir_lab_1A, dpi=quality)  # save the plot PNG
    # end with

    plt.clf()  # clear the figure
# end lab_1A()

# Lab. 1B - Linked Lists, Binary Search Trees
def lab_1B() -> None:
    with open(dir + dir_lab_1B + ext, "r") as file:
        lines: List(str) = [line.strip() for line in file.readlines()]

        keys: List(int) = []
        second_column: List(float) = []
        thrid_column: List(float) = []

        titles: List(str) = []

        for line in iter(lines):
            # check if line has any letters
            if not any(char.isalpha() for char in line):
                line: List(str) = line.split(",")

                keys.append(int(line[0]))
                second_column.append(float(line[1]))
                thrid_column.append(float(line[2]))
            else:
                line: List(str) = line.split(",")

                titles.append(line[1])  # title of the second column
                titles.append(line[2])  # title of the third column
            # end if
        # end for

        plt.xlabel(x_label)
        plt.ylabel(y_label)  # set axis labels
        plt.plot(
            keys, second_column, "red", keys, thrid_column, "blue", linewidth=2
        )  # plot the data
        plt.title(title_lab_1B)  # set title
        plt.grid(True)  # show the grid
        plt.legend(titles, loc="best")  # show legend, and put it in the best location
        plt.xlim(0)
        plt.ylim(0)  # set the lower limits of the x and y axis
        plt.savefig(dir + dir_lab_1B, dpi=quality)  # save the plot PNG
    # end with

    plt.clf()  # clear the figure
# end lab_1B()

# Lab. 2 - Red-Black Trees, Binary Search Trees
def lab_2() -> None:
    with open(dir + dir_lab_2 + ext, "r") as file:
        lines: List(str) = [line.strip() for line in file.readlines()]

        keys: List(int) = []
        second_column: List(float) = []
        thrid_column: List(float) = []

        titles: List(str) = []

        for line in iter(lines):
            # check if line has any letters
            if not any(char.isalpha() for char in line):
                line: List(str) = line.split(",")

                keys.append(int(line[0]))
                second_column.append(float(line[1]))
                thrid_column.append(float(line[2]))
            else:
                line: List(str) = line.split(",")

                titles.append(line[1])  # title of the second column
                titles.append(line[2])  # title of the third column
            # end if
        # end for

        plt.xlabel(x_label)
        plt.ylabel(y_label)  # set axis labels
        plt.plot(
            keys, second_column, "red", keys, thrid_column, "blue", linewidth=2
        )  # plot the data
        plt.title(title_lab_2)  # set title
        plt.grid(True)  # show the grid
        plt.legend(titles, loc="best")  # show legend, and put it in the best location
        plt.xlim(0)
        plt.ylim(0)  # set the lower limits of the x and y axis
        plt.savefig(dir + dir_lab_2, dpi=quality)  # save the plot PNG
    # end with

    plt.clf()  # clear the figure
# end lab_2()

# Lab. 3 - B-Trees, Red-Black Trees, Binary Search Trees
def lab_3() -> None:
    with open(dir + dir_lab_3 + ext, "r") as file:
        lines: List(str) = [line.strip() for line in file.readlines()]

        keys: List(int) = []
        second_column: List(float) = []
        thrid_column: List(float) = []
        fourth_column: List(float) = []

        titles: List(str) = []

        for line in iter(lines):
            # check if line has any letters
            if not any(char.isalpha() for char in line):
                line: List(str) = line.split(",")

                keys.append(int(line[0]))
                second_column.append(float(line[1]))
                thrid_column.append(float(line[2]))
                fourth_column.append(float(line[3]))
            else:
                line: List(str) = line.split(",")

                titles.append(line[1])  # title of the second column
                titles.append(line[2])  # title of the third column
                titles.append(line[3])  # title of the fourth column
            # end if
        # end for

        plt.xlabel(x_label)
        plt.ylabel(y_label)  # set axis labels
        plt.plot(
            keys,
            second_column,
            "red",
            keys,
            thrid_column,
            "blue",
            keys,
            fourth_column,
            "green",
            linewidth=2,
        )  # plot the data
        plt.title(title_lab_3)  # set title
        plt.grid(True)  # show the grid
        plt.legend(titles, loc="best")  # show legend, and put it in the best location
        plt.xlim(0)
        plt.ylim(0)  # set the lower limits of the x and y axis
        plt.text(
            500000,
            950000,
            "andrea-berardi",
            fontsize=50,
            color="gray",
            alpha=0.06,
            ha="center",
            va="center",
            rotation="30",
        )
        plt.savefig(dir + dir_lab_3, dpi=quality)  # save the plot PNG
    # end with

    plt.clf()  # clear the figure
# end lab_3()

# Lab. 4 - B-Trees
def final() -> None:
    with open(dir + dir_lab_4 + ext, "r") as file:
        lines: List(str) = [line.strip() for line in file.readlines()]

        keys: List(int) = []
        second_column: List(float) = []
        thrid_column: List(float) = []
        fourth_column: List(float) = []

        titles: List(str) = []

        for line in iter(lines):
            # check if line has any letters
            if not any(char.isalpha() for char in line):
                line: List(str) = line.split(",")

                keys.append(int(line[0]))
                second_column.append(float(line[1]))
                thrid_column.append(float(line[2]))
                fourth_column.append(float(line[3]))
                #fifth_column.append(float(line[4]))
            else:
                line: List(str) = line.split(",")

                titles.append(line[1])  # title of the second column
                titles.append(line[2])  # title of the third column
                titles.append(line[3])  # title of the fourth column
            # end if
        # end for

        plt.xlabel(x_label)
        plt.ylabel(y_label)  # set axis labels
        plt.plot(
            keys,
            second_column,
            "red",
            keys,
            thrid_column,
            "blue",
            keys,
            fourth_column,
            "green",
            linewidth=2,
        )  # plot the data
        plt.title(title_lab_4)  # set title
        plt.grid(True)  # show the grid
        plt.legend(titles, loc="best")  # show legend, and put it in the best location
        plt.xlim(0)
        plt.ylim(0)  # set the lower limits of the x and y axis
        plt.savefig(dir + dir_lab_4, dpi=quality)  # save the plot PNG
    # end with

    plt.clf()  # clear the figure
# end final()

# Main function
def main() -> None:
    lab_1A()
    lab_1B()
    lab_2()
    lab_3()
    final()
# end main()

# this specifies what will be run when the script is executed
if __name__ == "__main__":
    main()
# end if
