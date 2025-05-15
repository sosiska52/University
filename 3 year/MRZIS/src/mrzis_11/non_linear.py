import torch
import torch.nn as nn
import torch.optim as optim
import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from torch.utils.data import DataLoader, TensorDataset

# Загрузка данных
data = pd.read_csv("Seed_Data.csv", header=None)
X = data.iloc[:, :-1].values
scaler = StandardScaler()
X = scaler.fit_transform(X)

# Разделение на train/test
X_train, X_test = train_test_split(X, test_size=0.2, random_state=42)

# Конвертация в тензоры PyTorch
X_train_tensor = torch.FloatTensor(X_train)
X_test_tensor = torch.FloatTensor(X_test)

# Создание DataLoader
train_dataset = TensorDataset(X_train_tensor, X_train_tensor)
train_loader = DataLoader(train_dataset, batch_size=2, shuffle=True)


class NonlinearAutoencoder(nn.Module):
    def __init__(self, input_dim, encoding_dim):
        super(NonlinearAutoencoder, self).__init__()
        self.encoder = nn.Linear(input_dim, encoding_dim)
        self.decoder = nn.Linear(encoding_dim, input_dim)
        self.activation = nn.Tanh()

    def forward(self, x, return_all=False):

        y0 = self.activation(self.encoder(x))

        x1 = self.activation(self.decoder(y0))

        if return_all:
            y1 = self.activation(self.encoder(x1))
            return y0, x1, y1
        return y0, x1


class CumulativeDeltaOptimizer(optim.Optimizer):
    def __init__(self, params, lr=0.01):
        defaults = dict(lr=lr)
        super(CumulativeDeltaOptimizer, self).__init__(params, defaults)

        # Инициализация состояний для хранения накопленных градиентов
        for group in self.param_groups:
            for p in group['params']:
                self.state[p]['cumulative_grad'] = torch.zeros_like(p.data)

    def step(self, closure=None):
        loss = None
        if closure is not None:
            loss = closure()

        for group in self.param_groups:
            for p in group['params']:
                if p.grad is None:
                    continue

                # Накопление градиентов
                self.state[p]['cumulative_grad'] += p.grad.data

        return loss

    def apply_accumulated_gradients(self):
        for group in self.param_groups:
            lr = group['lr']
            for p in group['params']:
                if p.grad is None:
                    continue

                # Применение накопленных градиентов
                p.data.add_(-lr * self.state[p]['cumulative_grad'])
                # Сброс накопленных градиентов
                self.state[p]['cumulative_grad'].zero_()


class AutoencoderTrainer:
    def __init__(self, model, lr=0.01):
        self.model = model
        self.optimizer = CumulativeDeltaOptimizer(model.parameters(), lr=lr)
        self.criterion = nn.MSELoss()

    def train_step(self, x):
        y0, x1, y1 = self.model(x, return_all=True)
        reconstruction_loss = self.criterion(x1, x)
        compression_loss = self.criterion(y1, y0)
        total_loss = reconstruction_loss + compression_loss

        self.optimizer.zero_grad()
        total_loss.backward()
        self.optimizer.step()  # Накопление градиентов

        return total_loss.item()

    def apply_gradients(self):
        self.optimizer.apply_accumulated_gradients()


# Параметры
input_dim = X.shape[1]
encoding_dim = 4
epochs = 100

# Создание и обучение модели
model = NonlinearAutoencoder(input_dim, encoding_dim)
trainer = AutoencoderTrainer(model, lr=0.01)

# Обучение
train_losses = []
test_losses = []

for epoch in range(epochs):
    model.train()
    train_loss = 0
    for batch_x, _ in train_loader:
        train_loss += trainer.train_step(batch_x)

    trainer.apply_gradients()

    train_loss /= len(train_loader)
    train_losses.append(train_loss)

    model.eval()
    with torch.no_grad():
        _, decoded = model(X_test_tensor)
        test_loss = trainer.criterion(decoded, X_test_tensor).item()
        test_losses.append(test_loss)

plt.figure(figsize=(12, 8))
plt.plot(train_losses, label='Train Loss')
plt.plot(test_losses, '--', label='Test Loss')
plt.xlabel('Epoch')
plt.ylabel('MSE Loss')
plt.title('Autoencoder Training with Cumulative Delta Rule')
plt.legend()
plt.grid(True)
plt.show()

# Итоговая ошибка
print(f"\nFinal Test Loss: {test_losses[-1]:.4f}")