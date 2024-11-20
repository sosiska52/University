from matplotlib import pyplot as plt

import MakeDataSet
from SimpleNN import SimpleNN
import numpy as np
import time

if __name__ == '__main__':
    coordinates, values = MakeDataSet.generate_clusters()
    train_data = coordinates[0:150]
    test_data = coordinates[150:200]
    train_e = values[0:150]
    test_e = values[150:200]

    # Создание графика
    plt.figure(figsize=(8, 8))

    # Отображение всех точек
    plt.scatter(coordinates[:, 0], coordinates[:, 1], color='blue', marker='o')

    # Настройка графика
    plt.axhline(0, color='black', linewidth=0.5, linestyle='--')  # Горизонтальная линия
    plt.axvline(0, color='black', linewidth=0.5, linestyle='--')  # Вертикальная линия
    plt.grid(color='gray', linestyle='--', linewidth=0.5)  # Сетка
    plt.title("Координаты из четырех кластеров")
    plt.xlabel("X координаты")
    plt.ylabel("Y координаты")
    plt.xlim(-0.5, 2)  # Установите пределы осей
    plt.ylim(-0.5, 2)
    # plt.show()

    start_time = time.time()
    network = SimpleNN()
    network.train_online(train_data, train_e, test_data, test_e)
    end_time = time.time()
    print(f"Time: {end_time - start_time}")