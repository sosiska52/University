import math

def make_file(a, b, d):
    with open('data.txt', 'w') as outfile:
        x = 0.0
        while x < 15:
            print(x)
            outfile.write(str(func(a,b,d,x)) + "\n")
            x += 0.1

def func(a, b, d, x):
    return a * math.sin(b * x) + d