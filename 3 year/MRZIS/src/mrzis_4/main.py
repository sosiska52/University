from matplotlib import pyplot as plt

import MakeDataSet
#from SimpleNN import SimpleNN
import numpy as np
import time

if __name__ == '__main__':
    coordinates, values = MakeDataSet.generate_clusters()
    train_data = coordinates[0:150]
    test_data = coordinates[150:200]
    train_e = values[0:150]
    test_e = values[150:200]
    start_time = time.time()
    #network = SimpleNN()
    #network.train_online(train_data, train_e, test_data, test_e)
    #network.back_prop(0.5,1)

    end_time = time.time()
    print(f"Time: {end_time - start_time}")