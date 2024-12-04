from SimpleNN import SimpleNN
import numpy as np

if __name__ == '__main__':
    network = SimpleNN()
    trainMatrix = np.array([[-1, -1], [-1, 1], [1, 1], [1, -1]])
    e = np.array([1, 0, 0, 0])
    network.trainNN(trainMatrix, e)
    network.draw(trainMatrix, e)