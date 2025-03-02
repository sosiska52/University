import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def make_linear_graph(data):
    if isinstance(data, list) and all(isinstance(d, pd.Series) for d in data):
        df = pd.concat(data, axis=1)

        if df.apply(lambda x: pd.to_numeric(x, errors='coerce').notnull().all()).all():
            plt.figure(figsize=(10, 6))

            for column in df.columns:
                plt.plot(df.index, df[column], label=column)

            plt.title('Линейный график')
            plt.xlabel('Индекс')
            plt.ylabel('Значение')
            plt.legend()
            plt.grid()
            plt.show()
        else:
            print("Ошибка: Все значения должны быть числовыми.")
    else:
        print("Ошибка: data должен быть списком pandas.Series.")

def make_scatter_diagram(data):
    pass

def make_circle_diagram(data):
    pass

def make_hist(data):
    pass

def clean_data(data):
    pass