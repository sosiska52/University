import numpy as np
import matplotlib.pyplot as plt

class SimpleNN:
    def __init__(self, x_len, y_len):
        self.X = np.zeros(x_len)
        self.Y = np.zeros(y_len)
        self.W = np.random.rand(x_len, y_len)
        self.T = np.zeros(y_len)
        self.alp: float = 0.01
        self.adaptive_flag: bool = False
        self.errors_for_chart = np.array([])

    def forward_prop(self, image):
        self.X = image
        return np.dot(image, self.W) - self.T

    def adjust(self, error):
        for i in range(self.W.shape[0]):
            for j in range(self.W.shape[1]):
                self.W[i, j] -= self.alp * error * self.X[i]
                self.T[j] += self.alp * error

    def adaptive_online(self, image):
        self.alp = 1 / (1 + np.sum(image ** 2))

    def adaptive_batch(self, batch_data, batch_e):
        dividend: float = 0
        divider: float = 0
        a = self.helper_a(batch_data, batch_e)
        for ind, image in enumerate(batch_data):
            dividend += (self.forward_prop(image) - batch_e[ind]) * a
            divider += a ** 2
        self.alp = dividend / divider

    def helper_a(self, batch_data, batch_e) -> float:
        a: float = 0
        for ind, image in enumerate(batch_data):
            a += (self.forward_prop(image) - batch_e[ind]) * (1 + np.sum(image ** 2))
        return a

    def train_online(self, train_data, train_e, test_data, test_e):
        max_epoch: int = 100

        for epoch in range(max_epoch):
            ind: int = 0
            for image in train_data:
                Y = self.forward_prop(image)
                error = Y - train_e[ind]
                if self.adaptive_flag:
                    self.adaptive_online(image)
                self.adjust(error)
                ind += 1
            if self.test(test_data, test_e):
                print(f"Network trained in {epoch} epoches")
                self.drawErrorGraph()
                break

    def test(self, test_data, test_e) -> bool:
        mse: float = 0.0
        ind: int = 0
        for image in test_data:
            Y = self.forward_prop(image)
            mse += 0.5 * (Y - test_e[ind]) **2
            ind += 1
        print(f"MSE: {mse}")
        self.errors_for_chart = np.append(self.errors_for_chart, mse)
        return mse < 0.000_000_000_000_01

    def train_batch(self, train_data, train_e, test_data, test_e, batch_size):
        max_epoch: int = 100
        num_of_batches = len(train_data) / batch_size

        for epoch in range(max_epoch):
            start: int = 0
            while start < num_of_batches:
                batch_data = train_data[start: start + batch_size]
                batch_e = train_e[start: start + batch_size]
                weight_updater = np.zeros(5)
                batch_error: float = 0
                for ind, image in enumerate(batch_data):
                    Y = self.forward_prop(image)
                    error = Y - batch_e[ind]
                    batch_error += error
                    weight_updater += error
                    weight_updater = weight_updater * image
                if self.adaptive_flag:
                    self.adaptive_batch(batch_data, batch_e)
                #self.adjust(batch_error)

                for i in range(self.W.shape[0]):
                    for j in range(self.W.shape[1]):
                        #self.W[i, j] -= self.alp * error * self.X[i]
                        self.W[i, j] -= self.alp * weight_updater[i]
                        self.T[j] += self.alp * batch_error

                start += batch_size
                if self.test(test_data, test_e):
                    print(f"Network trained in {epoch} epoches")
                    self.drawErrorGraph()
                    return

    def drawErrorGraph(self):
        x = np.arange(len(self.errors_for_chart))
        plt.figure(figsize=(len(self.errors_for_chart), 5))
        plt.plot(x, self.errors_for_chart)
        plt.xlabel('Epoch')
        plt.ylabel('Errors')
        plt.grid()
        plt.show()