import numpy as np
from matplotlib import pyplot as plt


class Network:
    def __init__(self, input_neurons, hidden_neurons, output_neurons=1):
        self.in_size = input_neurons
        self.hid_size = hidden_neurons
        self.out_size = output_neurons
        self.input_layer = np.zeros(self.in_size)
        self.hidden_layer = np.zeros(self.hid_size)
        self.output_layer = np.zeros(self.out_size)

        self.alp = 0.5

        self.in_hid_weight = np.random.rand(self.in_size, self.hid_size)
        self.hid_out_weight = np.random.rand(self.hid_size, self.out_size)

        self.hid_bias = np.random.rand(self.hid_size)
        self.out_bias = np.random.rand(self.out_size)

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)

    """def sigmoid_derivative(self, weighted_sum):
        sig = self.sigmoid(weighted_sum)
        return sig * (1 - sig)"""

    def forward_prop(self, image):
        self.input_layer = image
        self.hidden_layer = self.sigmoid(np.dot(image, self.in_hid_weight) + self.hid_bias)
        self.output_layer = self.sigmoid(np.dot(self.hidden_layer, self.hid_out_weight) + self.out_bias)
        return self.output_layer

    def backward_prop(self, prediction, expected_value):
        error = (prediction - expected_value) * self.sigmoid_derivative(self.output_layer)
        hidden_error = np.dot(error, self.hid_out_weight.T) * self.sigmoid_derivative(self.hidden_layer)

        self.hid_out_weight -= self.alp * np.dot(self.hidden_layer.reshape(-1, 1), error.reshape(1, -1))
        self.out_bias -= self.alp * error

        self.in_hid_weight -= self.alp * np.dot(self.input_layer.reshape(-1, 1), hidden_error.reshape(1, -1))
        self.hid_bias -= self.alp * hidden_error

    def train(self, train_data, train_e, test_data, test_e):
        max_epoch = 100

        for epoch in range(max_epoch):
            for ind, image in enumerate(train_data):
                prediction = self.forward_prop(image)
                self.backward_prop(prediction, train_e[ind])

            if self.test(test_data, test_e):
                print(f"Network trained in {epoch + 1} epochs")
                break

        print("Final weights and biases:")
        print("Input-Hidden Weights:\n", self.in_hid_weight)
        print("Hidden Biases:\n", self.hid_bias)
        print("Hidden-Output Weights:\n", self.hid_out_weight)
        print("Output Biases:\n", self.out_bias)

    def test(self, test_data, test_e) -> bool:
        mse = 0
        for ind, image in enumerate(test_data):
            prediction = self.forward_prop(image)
            mse += 0.5 * np.sum((prediction - test_e[ind]) ** 2)
            print(f"{image} - {test_e[ind]} | {prediction}")
        print(f"MSE: {mse}")
        return mse < 0.01

    def visualize_decision_boundary(self, test_data, test_e):
        x_min, x_max = test_data[:, 0].min() - 1, test_data[:, 0].max() + 1
        y_min, y_max = test_data[:, 1].min() - 1, test_data[:, 1].max() + 1
        xx, yy = np.meshgrid(np.linspace(x_min, x_max, 200), np.linspace(y_min, y_max, 200))
        grid = np.c_[xx.ravel(), yy.ravel()]

        predictions = np.array([self.forward_prop(point) for point in grid])
        predictions = predictions.reshape(xx.shape)

        plt.contourf(xx, yy, predictions, levels=[0, 0.5, 1], colors=["red", "blue"], alpha=0.3)

        plt.scatter(test_data[:, 0], test_data[:, 1], c=test_e.flatten(), cmap="bwr", edgecolors="k", s=50)
        plt.title("Decision Boundary and Test Data")
        plt.xlabel("Feature 1")
        plt.ylabel("Feature 2")
        plt.show()