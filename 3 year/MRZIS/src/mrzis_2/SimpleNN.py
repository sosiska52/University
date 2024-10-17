import numpy as np
import matplotlib.pyplot as plt

class SimpleNN:
    def __init__(self, x_len, y_len):
        #self.X = np.array(x_len)
        self.X = np.array([1,2,3,4,5])
        self.Y = np.array(y_len)
        self.W = np.random.rand(x_len, y_len)
        self.T = np.array(y_len)
        self.alp: float = 0.1

    def forward_prop(self, image):
        self.X = np.zeros_like(image)
        return np.dot(image, self.W) - self.T

    def adjust(self, error):
        for t in self.T:
            t += self.alp * error
        for i in range(self.W.shape[0]):
            for j in range(self.W.shape[1]):
                self.W[i, j] -= self.alp * error * self.X[i]

    def train(self, train_data, train_e, test_data, test_e):
        epoch: int = 0
        max_epoch: int = 100
        error: float = 100
        is_trained: bool = False
        ind: int = 0

        while epoch < max_epoch:
            while not is_trained:
                Y = self.forward_prop(train_data[ind:ind + len(self.X)])
                error = Y - train_e[ind + len(self.X) - 1]
                self.adjust(error)
            is_trained = self.test(test_data, test_e)
            epoch += 1

    def test(self, test_data, test_e) -> bool:
        mse: float = 0.0
        ind: int = 0
        while ind + len(self.X) - 1 < len(test_data):
            Y = self.forward_prop(test_data[ind:ind + len(self.X)])
            mse += (Y - test_e[ind + len(self.X) - 1]) **2
            ind += 1
        mse = 0.5 * mse
        print(mse)
        return mse < 0.001

    def drawErrorGraph(self, errors):
        x = np.arange(len(errors))
        plt.figure(figsize=(10, 5))
        plt.plot(x, errors)
        plt.xlabel('Epoch')
        plt.ylabel('Errors')
        plt.grid()
        plt.show()