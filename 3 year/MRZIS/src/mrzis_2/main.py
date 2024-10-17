import SimpleNN as slp
import numpy as np

if __name__ == '__main__':
    train_len = 100
    test_len = 50

    with open("data.txt", "r") as file:
        values = [float(line.strip()) for line in file]

    train_e = np.array(values[:train_len])
    test_e = np.array(values[train_len:train_len + test_len])
    train_data = np.arange(0, 10, 0.1)
    test_data = np.arange(10, 15, 0.1)

    network = slp.SimpleNN(5, 1)
    network.test(test_data, test_e)