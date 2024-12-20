import torch
import torch.nn as nn
import torch.optim as optim


class MLP(nn.Module):
    def __init__(self, in_size, hid1_size, hid2_size, out_size):
        super(MLP, self).__init__()
        self.layer1 = nn.Linear(in_size, hid1_size)
        self.layer2 = nn.Linear(hid1_size, hid2_size)
        self.layer3 = nn.Linear(hid2_size, out_size)
        self.dropout = nn.Dropout(0.01)

    def forward(self, x):
        x = nn.ReLU()(self.layer1(x))
        x = self.dropout(nn.ReLU()(self.layer2(x)))
        x = nn.Sigmoid()(self.layer3(x))  # Сигмоида для вероятностей
        return x

    def train_step(self, optimizer, criterion, inputs, targets):
        """
        Выполняет один шаг обучения (обратное распространение + обновление весов).
        """
        # Обнуляем градиенты
        optimizer.zero_grad()

        # Прямой проход
        outputs = self(inputs)

        # Вычисляем ошибку
        loss = criterion(outputs, targets)

        # Обратное распространение
        loss.backward()

        # Обновляем веса
        optimizer.step()

        return loss.item()

    def train_model(self, train_loader, optimizer, criterion, num_epochs):
        self.train()  # Переводим модель в режим обучения
        epoch_losses = []  # Список для хранения значений потерь на каждой эпохе
        for epoch in range(num_epochs):
            epoch_loss = 0
            for inputs, targets in train_loader:
                loss = self.train_step(optimizer, criterion, inputs, targets)
                epoch_loss += loss
            avg_epoch_loss = epoch_loss / len(train_loader)
            epoch_losses.append(avg_epoch_loss)
            print(f"Epoch {epoch + 1}/{num_epochs}, Loss: {avg_epoch_loss:.4f}")

        # Возвращаем список потерь для визуализации
        return epoch_losses

    def test_model(self, test_loader, criterion):
        """
        Оценивает модель на тестовом наборе данных.
        """
        self.eval()  # Переводим модель в режим оценки
        test_loss = 0
        correct = 0
        total = 0

        with torch.no_grad():  # Отключаем расчет градиентов
            for inputs, targets in test_loader:
                outputs = self(inputs)
                loss = criterion(outputs, targets)
                test_loss += loss.item()

                # Предсказание классов
                predicted = (outputs > 0.5).float()
                correct += (predicted == targets).sum().item()
                total += targets.size(0)

        accuracy = correct / total
        print(f"Test Loss: {test_loss / len(test_loader):.4f}, Accuracy: {accuracy:.2%}")
