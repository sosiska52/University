import random

def func(x) -> float:
    return -2 * x + 12

def makeFile():
    with open("data.txt", 'w') as data:
        with open("reference.txt", 'w') as ref:
            for i in range(150):
                x = random.uniform(-10.0, 10.0)
                y = random.uniform(-10.0, 10.0)
                data.write(str(x) + " " + str(y) + "\n")
                if y > func(x):
                    ref.write("1\n")
                else:
                    ref.write("0\n")