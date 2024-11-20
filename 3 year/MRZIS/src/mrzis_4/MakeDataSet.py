import random
import numpy as np

def generate_random_coordinates(x1, x2, y1, y2):
    return (random.normalvariate(x1, x2), random.normalvariate(y1, y2))

def make_arrays():
    data_array = []
    reference_array = []

    for i in range(50):
        x, y = generate_random_coordinates(0.35, 0.75, 0.35, 0.75)
        data_array.append([x, y])
        reference_array.append(0)

    for i in range(50):
        x, y = generate_random_coordinates(0.35, 0.75, 0.35, -0.75)
        data_array.append([x, y])
        reference_array.append(1)

    for i in range(50):
        x, y = generate_random_coordinates(0.35, -0.75, 0.35, -0.75)
        data_array.append([x, y])
        reference_array.append(0)

    for i in range(50):
        x, y = generate_random_coordinates(0.35, -0.75, 0.35, 0.75)
        data_array.append([x, y])
        reference_array.append(1)

    # Перемешивание индексов
    indices = list(range(len(data_array)))
    random.shuffle(indices)

    # Создание перемешанных NumPy массивов
    shuffled_data = np.array([data_array[i] for i in indices])
    shuffled_reference = np.array([reference_array[i] for i in indices])

    return shuffled_data, shuffled_reference

def generate_clusters(n=50):
    # Генерация кластеров
    cluster_1 = np.random.normal(loc=(1, 1), scale=0.1, size=(n, 2))  # 1-я четверть
    cluster_2 = np.random.normal(loc=(0, 1), scale=0.1, size=(n, 2))  # 2-я четверть
    cluster_3 = np.random.normal(loc=(0, 0), scale=0.1, size=(n, 2))  # 3-я четверть
    cluster_4 = np.random.normal(loc=(1, 0), scale=0.1, size=(n, 2))  # 4-я четверть

    # Объединение всех кластеров в один массив координат
    all_coordinates = np.vstack((cluster_1, cluster_2, cluster_3, cluster_4))

    # Создание массива значений
    values = np.array([0] * n + [1] * n + [0] * n + [1] * n)  # 0 для 1-й и 3-й, 1 для 2-й и 4-й

    # Перемешивание массивов
    indices = np.arange(len(all_coordinates))
    np.random.shuffle(indices)

    shuffled_coordinates = all_coordinates[indices]
    shuffled_values = values[indices]

    return shuffled_coordinates, shuffled_values