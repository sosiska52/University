import numpy as np

import MakeDataSet


class NeuralNetwork:
    def __init__(self):
        # Инициализация весов
        self.input_size = 2
        self.hidden_size = 2
        self.output_size = 1

        self.weights_input_hidden = np.random.rand(self.input_size, self.hidden_size)
        self.weights_hidden_output = np.random.rand(self.hidden_size, self.output_size)

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)

    def sigmoid_derivative1(self, weighted_sum):
        sig = self.sigmoid(weighted_sum)
        return sig * (1 - sig)

    def forward(self, X):
        # Прямое распространение
        self.hidden_input = np.dot(X, self.weights_input_hidden)
        self.hidden_output = self.sigmoid(self.hidden_input)

        self.final_input = np.dot(self.hidden_output, self.weights_hidden_output)
        self.final_output = self.sigmoid(self.final_input)

        return self.final_output

    def backward(self, X, y, output):
        # Обратное распространение
        output_error = y - output
        output_delta = output_error * self.sigmoid_derivative(output)

        hidden_error = output_delta.dot(self.weights_hidden_output.T)
        hidden_delta = hidden_error * self.sigmoid_derivative(self.hidden_output)

        # Обновление весов
        self.weights_hidden_output += self.hidden_output.T.dot(output_delta)
        self.weights_input_hidden += X.T.dot(hidden_delta)

    def train(self, X, y, epochs=1000):
        for _ in range(epochs):
            output = self.forward(X)
            self.backward(X, y, output)



coordinates, values = MakeDataSet.generate_clusters()
train_data = coordinates[0:150]
test_data = coordinates[150:200]
train_e = values[0:150]

X = np.array([[0, 0],
              [0, 1],
              [1, 0],
              [1, 1]])

y = np.array([[0], [1], [1], [0]])

# Создание и обучение нейронной сети
nn = NeuralNetwork()
temp = 0
print(nn.sigmoid_derivative(temp))
print(nn.sigmoid_derivative1(temp))
nn.train(X, y)

# Проверка результатов
for i in range(len(X)):
    print(f"Input: {X[i]} - Predicted Output: {nn.forward(X[i].reshape(1, -1))}")