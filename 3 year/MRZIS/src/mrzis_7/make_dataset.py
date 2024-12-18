from math import cos, sin
import numpy as np
from PIL.ImagePalette import random
import random

step = 0.1
all_data_len = 2500
train_len = 2000
test_len = 500
input_layer_len = 10

def func(a,b,c,d, x):
    return a * cos(b * x) + c * sin(d * x) + random.uniform(-0.01, 0.01)

def make_datafile(a,b,c,d):
    with open("data.txt", "w") as fout:
        x = 0
        while x < (all_data_len * step):
            fout.write(str(func(a,b,c,d,x)) + "\n")
            x += step

def create_matrix_from_file(start ,end):
    with open("data.txt", 'r') as file:
        data = [float(line.strip()) for line in file if line.strip()]

    size = end - start - input_layer_len
    matrix = np.zeros((size, input_layer_len))

    for i in range(size):
        matrix[i, :] = data[i + start:i + start + input_layer_len]

    return matrix

def create_array_from_file(start ,end):
    with open("data.txt", 'r') as file:
        data = [float(line.strip()) for line in file if line.strip()]

    return data[start: end]

def make_data():
    train_data = create_matrix_from_file(0, train_len - 1)
    test_data = create_matrix_from_file(train_len, train_len + test_len - 1)
    train_e = create_array_from_file(input_layer_len, train_len - 1)
    test_e = create_array_from_file(train_len + input_layer_len, train_len + test_len - 1)

    return train_data, train_e, test_data, test_e