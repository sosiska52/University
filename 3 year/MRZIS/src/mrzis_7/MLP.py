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
        self.errors_for_chart = []

        self.alp = 0.01
        self.dropout_rate = 0.01
        self.lamb_1 = 0.00001
        self.lamb_2 = 0.0001

        self.in_hid_weight = np.random.uniform(-1, 1, (self.in_size, self.hid_size))
        self.hid_out_weight = np.random.uniform(-1, 1,(self.hid_size, self.out_size))

        self.hid_bias = np.random.rand(self.hid_size)
        self.out_bias = np.random.rand(self.out_size)

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)

    def forward_prop(self, image, dropout_mask):
        self.input_layer = image
        self.hidden_layer = self.sigmoid(np.dot(image, self.in_hid_weight) - self.hid_bias)

        self.hidden_layer *= dropout_mask

        self.output_layer = np.dot(self.hidden_layer, self.hid_out_weight) - self.out_bias
        return self.output_layer

    """def backward_prop(self, error, dropout_mask):
        hidden_error = np.dot(error, self.hid_out_weight.T) * self.sigmoid_derivative(self.hidden_layer)
        hidden_error *= dropout_mask

        self.hid_out_weight -= self.alp * np.dot(self.hidden_layer.reshape(-1, 1), error.reshape(1, -1))
        self.out_bias += self.alp * error

        self.in_hid_weight -= self.alp * np.dot(self.input_layer.reshape(-1, 1), hidden_error.reshape(1, -1))
        self.hid_bias += self.alp * hidden_error"""

    def backward_prop(self, error, dropout_mask):
        hidden_error = np.dot(error, self.hid_out_weight.T) * self.sigmoid_derivative(self.hidden_layer)
        hidden_error *= dropout_mask

        l1_hid_out = self.lamb_1 * np.sign(self.hid_out_weight)
        l2_hid_out = self.lamb_2 * self.hid_out_weight

        self.hid_out_weight -= self.alp * (np.dot(self.hidden_layer.reshape(-1, 1), error.reshape(1, -1)) + l1_hid_out + l2_hid_out)
        self.out_bias += self.alp * error

        l1_in_hid = self.lamb_1 * np.sign(self.in_hid_weight)
        l2_in_hid = self.lamb_2 * self.in_hid_weight

        self.in_hid_weight -= self.alp * (np.dot(self.input_layer.reshape(-1, 1), hidden_error.reshape(1, -1)) + l1_in_hid + l2_in_hid)
        self.hid_bias += self.alp * hidden_error

    def train_online(self, train_data, train_e, test_data, test_e):
        max_epoch = 300

        for epoch in range(max_epoch):
            for ind, image in enumerate(train_data):
                dropout_mask = np.random.binomial(1, 1 - self.dropout_rate, size=self.hid_size)
                self.backward_prop(self.forward_prop(image, dropout_mask) - train_e[ind], dropout_mask)

            if self.test(test_data, test_e):
                break
        print(f"Network trained in {epoch + 1} epochs")

    #MSE
    """def test(self, test_data, test_e) -> bool:
        mse = 0
        dropout_mask = np.ones(self.hid_size)
        for ind, image in enumerate(test_data):
            prediction = self.forward_prop(image, dropout_mask)
            mse += 0.5 * np.sum((prediction - test_e[ind]) ** 2)
            print(f"{test_e[ind]} | {prediction}")
        print(f"MSE_test: {mse}")
        self.errors_for_chart.append(mse)
        return mse < 0.01"""

    #MAE
    def test(self, test_data, test_e) -> bool:
        mae = 0
        dropout_mask = np.ones(self.hid_size)
        for ind, image in enumerate(test_data):
            prediction = self.forward_prop(image, dropout_mask)
            mae += np.sum(np.abs(prediction - test_e[ind]))
            print(f"{test_e[ind]} | {prediction}")
        mae /= len(test_data)
        print(f"MAE_test: {mae}")
        self.errors_for_chart.append(mae)
        return mae < 0.001

    def show_result_plot(self, test_data, test_e):
        x_values = np.arange(0, 48.9, 0.1)
        predicted_values = []
        dropout_mask = np.ones(self.hid_size)
        for image in test_data:
            predicted_values.append(self.forward_prop(image, dropout_mask))

        plt.figure(figsize=(10, 5))
        plt.plot(x_values, test_e, label='Actual Values', color='blue')
        plt.plot(x_values, predicted_values, label='Predicted Values', color='orange', linestyle='dashed')
        plt.title('Actual vs. Predicted Values')
        plt.xlabel('Input')
        plt.ylabel('Output')
        plt.legend()
        plt.grid()
        plt.show()

    def show_error_plot(self):
        x_values = np.arange(len(self.errors_for_chart))

        plt.figure(figsize=(10, 5))
        plt.plot(x_values, self.errors_for_chart, marker='o', linestyle='-', color='b', label='Data')
        plt.title("Error graph")
        plt.xlabel("Time")
        plt.ylabel("Error")
        plt.grid(True)
        plt.show()