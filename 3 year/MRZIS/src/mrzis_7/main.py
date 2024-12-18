import numpy as np
from make_dataset import make_datafile, make_data
from MLP import Network
import time

if __name__ == "__main__":
    make_datafile(0.3, 0.2, 0.06, 0.2)
    train_data, train_e, test_data, test_e = make_data()

    start_time = time.time()
    network = Network(10,6,1)
    network.train_online(train_data, train_e, test_data, test_e)
    end_time = time.time()
    print(f"Time: {end_time - start_time}")
    network.show_result_plot(test_data, test_e)
    network.show_error_plot()