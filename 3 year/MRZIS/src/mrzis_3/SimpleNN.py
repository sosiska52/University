import math

import numpy as np
import matplotlib.pyplot as plt

class SimpleNN:
    def __init__(self, x_len, y_len):
        self.X = np.zeros(x_len)
        self.Y = np.zeros(y_len)
        self.W = np.random.rand(x_len, y_len)
        self.T = np.zeros(y_len)
        self.alp: float = 0.5
        self.adaptive_flag: bool = False
        self.errors_for_chart = np.array([])

    def forward_prop(self, image):
        self.X = image
        return np.dot(image, self.W) - self.T

    def activation_func(self, weighted_sum):
        return 1 / (1 +  math.exp(-weighted_sum))

    def activation_derivative(self, weighted_sum):
        sig = self.activation_func(weighted_sum)
        return sig * (1 - sig)

    def adjust(self, error, weighted_sum):
        for i in range(self.W.shape[0]):
            for j in range(self.W.shape[1]):
                self.W[i, j] -= self.alp * error * self.X[i] * self.activation_derivative(weighted_sum)
                self.T[j] += self.alp * error * self.activation_derivative(weighted_sum)

    """def adaptive_online(self, image):
        self.alp = 1 / (1 + np.sum(image ** 2))"""

    def adaptive_online(self, image):
        self.alp = self.activation_derivative(self.forward_prop(image)) / (1 + np.sum(image ** 2))

    """def adaptive_batch(self, batch_data, batch_e):
        dividend: float = 0
        divider: float = 0
        a = self.helper_a(batch_data, batch_e)
        for ind, image in enumerate(batch_data):
            dividend += (self.activation_func(self.forward_prop(image)) - batch_e[ind]) * a
            divider += a ** 2
        self.alp = 2 * dividend / divider

    def helper_a(self, batch_data, batch_e) -> float:
        a: float = 0
        for ind, image in enumerate(batch_data):
            a += (self.forward_prop(image) - batch_e[ind]) * (1 + np.sum(image ** 2))
        return a"""

    def adaptive_batch(self, batch_data, batch_e):
        dividend = 0
        divider = 0
        a = self.helper_a(batch_data, batch_e)
        for ind, image in enumerate(batch_data):
            activation = self.activation_func(self.forward_prop(image))
            delta = activation - batch_e[ind]
            dividend += delta * activation * (1 - activation) * a
            divider += a ** 2
        self.alp = 3 * dividend / divider
        return self.alp

    def helper_a(self, batch_data, batch_e):
        a = 0
        for ind, image in enumerate(batch_data):
            activation = self.activation_func(self.forward_prop(image))
            a += (activation - batch_e[ind]) * (1 + np.sum(image ** 2))
        return a

    def train_online(self, train_data, train_e, test_data, test_e):
        max_epoch: int = 100

        for epoch in range(max_epoch):
            ind: int = 0
            for image in train_data:
                Y = self.forward_prop(image)
                prediction = self.activation_func(Y)
                error = prediction - train_e[ind]
                if self.adaptive_flag:
                    self.adaptive_online(image)
                self.adjust(error, Y)
                ind += 1
            if self.test(test_data, test_e):
                print(f"Network trained in {epoch} epoches")
                #self.drawErrorGraph()
                break

    def test(self, test_data, test_e) -> bool:
        counter: float = 0
        for ind, image in enumerate(test_data):
            Y = self.activation_func(self.forward_prop(image))
            if (Y >= 0.5 and test_e[ind] == 1) or (Y < 0.5 and test_e[ind] == 0):
                counter+=1
        right_percent = counter / len(test_e) * 100
        print(f"Percentage: {right_percent}")
        self.errors_for_chart = np.append(self.errors_for_chart, right_percent)
        return right_percent > 95

    def train_batch(self, train_data, train_e, test_data, test_e, batch_size):
        max_epoch: int = 100
        num_of_batches = len(train_data) / batch_size

        for epoch in range(max_epoch):
            start: int = 0
            while start < num_of_batches:
                batch_data = train_data[start: start + batch_size]
                batch_e = train_e[start: start + batch_size]
                weight_updater = np.zeros(2)
                batch_error: float = 0
                for ind, image in enumerate(batch_data):
                    Y = self.forward_prop(image)
                    prediction = self.activation_func(Y)
                    error = prediction - batch_e[ind]
                    batch_error += error * self.activation_derivative(Y)
                    weight_updater += error
                    weight_updater = weight_updater * image
                    weight_updater *= self.activation_derivative(Y)
                if self.adaptive_flag:
                    self.adaptive_batch(batch_data, batch_e)
                # self.adjust(batch_error)

                for i in range(self.W.shape[0]):
                    for j in range(self.W.shape[1]):
                        # self.W[i, j] -= self.alp * error * self.X[i]
                        self.W[i, j] -= self.alp * weight_updater[i]
                        self.T[j] += self.alp * batch_error

                start += batch_size
                if self.test(test_data, test_e):
                    print(f"Network trained in {epoch} epoches")
                    #self.drawErrorGraph()
                    return

    def drawErrorGraph(self):
        x = np.arange(len(self.errors_for_chart))
        plt.figure(figsize=(len(self.errors_for_chart), 5))
        plt.plot(x, self.errors_for_chart)
        plt.xlabel('Epoch')
        plt.ylabel('Errors')
        plt.grid()
        plt.show()