import numpy as np
import matplotlib.pyplot as plt

class SimpleNN:
    def __init__(self):
        self.X1 = np.zeros(2)
        self.X2 = np.zeros(2)
        self.W1 = np.random.randn(2, 2) * 0.01
        self.W2 = np.random.randn(2, 1) * 0.01
        self.weighted1 = np.zeros((2, 2))
        self.weighted2 = np.zeros((2, 1))
        self.T1 = np.random.rand(2)
        self.T2 = np.random.rand(1)
        self.alp: float = 0.05
        self.errors_for_chart = np.array([])

    def forward_prop(self, image):
        self.X1 = image
        self.weighted1 = np.dot(image, self.W1) - self.T1
        self.X2 = self.sigmoid_func(self.weighted1)
        self.weighted2 = np.dot(self.X2, self.W2) - self.T2
        return self.sigmoid_func(self.weighted2)

    def sigmoid_func(self, weighted_sum):
        return 1 / (1 +  np.exp(-weighted_sum))

    def sigmoid_derivative(self, weighted_sum):
        sig = self.sigmoid_func(weighted_sum)
        return sig * (1 - sig)

    def back_prop(self,prediction, expected_output):
        output_error = prediction - expected_output
        d_output = output_error * self.sigmoid_derivative(self.weighted2)
        self.W2 -= self.alp * np.dot(self.X2.reshape(-1,1), d_output.reshape(1,-1))
        self.T2 += self.alp * d_output

        hidden_error = np.dot(d_output, self.W2.T) * self.sigmoid_derivative(self.weighted1)
        self.W1 -= self.alp * np.dot(self.X1.reshape(-1, 1), hidden_error.reshape(1, -1))
        self.T1 += self.alp * hidden_error

    def train_online(self, train_data, train_e, test_data, test_e):
        max_epoch: int = 1000

        self.W1 = ([1,-1], [1,-1])
        self.W2 = ([1], [1])
        self.T1 = ([0.5,-1.5])
        self.T2 = ([1.5])

        for epoch in range(max_epoch):
            for ind, image in enumerate(train_data):
                prediction = self.forward_prop(image)
                #self.back_prop(prediction, train_e[ind])
            if self.test(test_data, test_e):
                print(f"Network trained in {epoch + 1} epoches")
                self.draw_error_graph()
                break
        print(self.W1)
        print(self.T1)
        print(self.W2)
        print(self.T2)
        self.draw_error_graph()

    def test(self, test_data, test_e) -> bool:
        mse: float = 0
        for ind, image in enumerate(test_data):
            prediction = self.forward_prop(image)
            mse += 0.5 * (prediction - test_e[ind]) ** 2
            print(str(image) + " - " + str(test_e[ind]) + " | " + str(prediction))
        print(f"MSE: {mse}")
        self.errors_for_chart = np.append(self.errors_for_chart, mse)
        return mse == 0

    def draw_error_graph(self):
        x = np.arange(len(self.errors_for_chart))
        plt.figure(figsize=(len(self.errors_for_chart), 5))
        plt.plot(x, self.errors_for_chart)
        plt.xlabel('Epoch')
        plt.ylabel('Errors')
        plt.grid()
        plt.show()