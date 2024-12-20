import pandas as pd
from matplotlib import pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
import torch
from torch import optim, nn
from torch.utils.data import DataLoader, TensorDataset
from MLP import MLP

file_path = "mushrooms.csv"
data = pd.read_csv(file_path)

# Шаг 2: Преобразование категориальных данных в числовые
label_encoders = {}
for column in data.columns:
    le = LabelEncoder()
    data[column] = le.fit_transform(data[column])
    label_encoders[column] = le

# Шаг 3: Разделение данных на признаки (X) и целевые метки (y)
X = data.iloc[:, 1:].values  # Все столбцы, кроме первого (класса)
y = data.iloc[:, 0].values   # Первый столбец - целевая метка

# Шаг 4: Разделение на тренировочный и тестовый наборы
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Шаг 5: Преобразование в тензоры PyTorch
X_train = torch.tensor(X_train, dtype=torch.float32)
X_test = torch.tensor(X_test, dtype=torch.float32)
y_train = torch.tensor(y_train, dtype=torch.float32).unsqueeze(1)  # Добавляем размерность для совместимости
y_test = torch.tensor(y_test, dtype=torch.float32).unsqueeze(1)

# Шаг 6: Создание DataLoader для тренировки и тестирования
train_dataset = TensorDataset(X_train, y_train)
test_dataset = TensorDataset(X_test, y_test)

train_loader = DataLoader(train_dataset, batch_size=32, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=32)

print("Данные успешно загружены и подготовлены:")
print(f"Размер тренировочного набора: {len(train_dataset)}")
print(f"Размер тестового набора: {len(test_dataset)}")

model = MLP(in_size=X_train.shape[1], hid1_size=64, hid2_size=32, out_size=1)

optimizer = optim.Adam(model.parameters(), lr=0.001)
criterion = nn.BCELoss()

num_epochs = 10
epoch_losses = model.train_model(train_loader, optimizer, criterion, num_epochs)

model.test_model(test_loader, criterion)

plt.plot(range(1, num_epochs + 1), epoch_losses, marker='o')
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.title("Training Loss per Epoch")
plt.grid(True)
plt.show()