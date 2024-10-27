import SimpleNN as slp
import numpy as np
import time

def create_matrix_from_file(start ,end):
    with open("data.txt", 'r') as file:
        data = [float(line.strip()) for line in file if line.strip()]

    size = end - start - 5
    matrix = np.zeros((size, 5))

    for i in range(size):
        matrix[i, :] = data[i + start:i + start + 5]

    return matrix

def create_array_from_file(start ,end):
    with open("data.txt", 'r') as file:
        data = [float(line.strip()) for line in file if line.strip()]

    return data[start: end]

if __name__ == '__main__':
    train_len = 100
    test_len = 50

    train_data = create_matrix_from_file(0, train_len - 1)
    test_data = create_matrix_from_file(train_len, train_len + test_len - 1)
    train_e = create_array_from_file(5, train_len - 1)
    test_e = create_array_from_file(train_len + 5, train_len + test_len - 1)

    start_time = time.time()
    network = slp.SimpleNN(5, 1)
    network.adaptive_flag = False
    network.train_online(train_data, train_e, test_data, test_e)
    #network.train_batch(train_data, train_e, test_data, test_e, 2)
    end_time = time.time()
    print(f"Time: {end_time - start_time}")