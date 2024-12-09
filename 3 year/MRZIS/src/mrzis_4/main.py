import MakeDataSet
from MLP import Network
from SimpleNN import SimpleNN
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

    network = Network(2,2)
    network.train(train_data, train_e, test_data, test_e)

    end_time = time.time()
    network.visualize_decision_boundary(train_data, train_e)
    print(f"Time: {end_time - start_time}")