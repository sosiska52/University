from SimpleNN import SimpleNN
from MakeDataSet import makeFile
import numpy as np
import time

def make_matrix(start = 0, end = None):
    matrix = []
    with open("data.txt", 'r') as file:
        for ind, line in enumerate(file):
            if ind < start:
                continue
            if end is not None and ind >= end:
                break

            numbers = list(map(float, line.split()))
            if len(numbers) == 2:
                matrix.append(numbers)
            else:
                print(f"Пропущена строка: {line.strip()} (должно быть 2 числа)")

        return np.array(matrix)

def make_array(start = 0, end = None):
    with open("reference.txt", 'r') as file:
        data = [float(line.strip()) for line in file if line.strip()]
    return data[start: end]

if __name__ == '__main__':
    makeFile()
    train_data = make_matrix(0, 100)
    test_data = make_matrix(100, 150)
    train_e = make_array(0, 100)
    test_e = make_array(100, 150)
    print(train_e)

    start_time = time.time()
    network = SimpleNN(2,1)
    network.adaptive_flag = True
    #network.train_online(train_data,train_e, test_data, test_e)
    #network.train_batch(train_data, train_e, test_data, test_e, 2)
    end_time = time.time()
    print(f"Time: {end_time - start_time}")