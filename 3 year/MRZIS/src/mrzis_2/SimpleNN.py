import numpy as np
import matplotlib.pyplot as plt

class SimpleNN:
    def __init__(self, x_len):
        self.X = self.X = np.zeros(x_len)
        self.W = np.random.uniform(0.1,0.9, x_len)
        self.T = np.random.uniform(0.1, 1)
        self.alp = 0.3

    def forwardProp(self, image):
        self.X = np.zeros_like(image)
        for i in range(len(image)):
            self.X[i] = image[i]

        sum_val = self.X[0] * self.W[0] + self.X[1] * self.W[1] - self.T
        return self.activationF(sum_val)

    def activationF(self, num):
        return 0 if num <= 0 else 1

    def adjust(self, error):
        for i in range(len(self.W)):
            self.W[i] -= self.alp * error * self.X[i]
        self.T += self.alp * error

    def trainNN(self, trainMatrix, e, maxEpoch=100):
        epoch = 0
        allErrors = []
        while epoch < maxEpoch:
            total_error = 0
            for i in range(len(trainMatrix)):
                Y = self.forwardProp(trainMatrix[i])
                error = (Y - e[i])
                total_error += error
                self.adjust(error)

            average_error = total_error / len(trainMatrix)
            allErrors.append(average_error)
            print(f"Epoch: {epoch}, Average Error: {average_error}")

            if average_error == 0:
                self.drawErrorGraph(allErrors)
                break
            epoch += 1

    def draw(self, trainMatrinx, e):
         x, y = zip(*trainMatrinx)
         x += (x[0],)
         y += (y[0],)

         plt.figure()
         plt.plot(x, y, marker='o')
         k = -1 * self.W[0] / self.W[1]
         b = self.T / self.W[1]

         x_line = np.linspace(-3, 3, 5)
         y_line = k * x_line + b

         plt.plot(x_line, y_line, color='red')

         plt.title('Visualization')
         plt.xlim(-3, 3)  # Устанавливаем пределы по оси x
         plt.ylim(-3, 3)  # Устанавливаем пределы по оси y
         plt.grid()
         plt.xlabel('X1')
         plt.ylabel('X2')

         # Добавляем значения на углах
         for i in range(len(e)):
             plt.text(x[i], y[i], str(e[i]), fontsize=12, ha='right', va='bottom')

         plt.show()

    def drawErrorGraph(self, errors):
        x = np.arange(len(errors))
        plt.figure(figsize=(10, 5))
        plt.plot(x, errors)
        plt.xlabel('Epoch')
        plt.ylabel('Errors')
        plt.grid()
        plt.show()