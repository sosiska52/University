from SimpleNN import SimpleNN
import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    #network = SimpleNN()
    trainMatrix = np.array([[-1, -1], [-1, 1], [1, 1], [1, -1]])
    eArr = np.array([1, 0, 0, 0])
    #network.trainNN(trainMatrix, eArr)
    # Задаем координаты углов квадрата
    corners = [(-1, -1), (-1, 1), (1, 1), (1, -1)]

    # Разделяем координаты на x и y
    x, y = zip(*corners)

    # Добавляем первую точку в конец, чтобы закрыть квадрат
    x += (x[0],)
    y += (y[0],)

    # Создание графика
    plt.figure()
    plt.plot(x, y, marker='o')  # Рисуем квадрат с маркерами в углах
    plt.title('Квадрат по заданным координатам')
    plt.xlim(-3, 3)  # Устанавливаем пределы по оси x
    plt.ylim(-3, 3)  # Устанавливаем пределы по оси y
    plt.grid()
    plt.xlabel('X')
    plt.ylabel('Y')

    # Добавляем значения на углах
    for i in range(len(eArr)):
        plt.text(x[i], y[i], str(eArr[i]), fontsize=12, ha='right', va='bottom')

    # Отображение графика
    plt.show()