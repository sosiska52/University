import torch
import torch.nn as nn
import torch.optim as optim
import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from torch.utils.data import DataLoader, TensorDataset


data = pd.read_csv("Seed_Data.csv", header=None)
X = data.iloc[:, :-1].values
scaler = StandardScaler()
X = scaler.fit_transform(X)

# Разделение на train/test
X_train, X_test = train_test_split(X, test_size=0.2, random_state=42)


X_train_tensor = torch.FloatTensor(X_train)
X_test_tensor = torch.FloatTensor(X_test)

# Создание DataLoader
train_dataset = TensorDataset(X_train_tensor, X_train_tensor)
train_loader = DataLoader(train_dataset, batch_size=2, shuffle=True)

class LinearAutoencoder(nn.Module):
    def __init__(self, input_dim, encoding_dim):
        super(LinearAutoencoder, self).__init__()
        self.encoder = nn.Linear(input_dim, encoding_dim, bias=False)
        self.decoder = nn.Linear(encoding_dim, input_dim, bias=False)

        nn.init.normal_(self.encoder.weight, mean=0.0, std=0.01)
        nn.init.normal_(self.decoder.weight, mean=0.0, std=0.01)

    def forward(self, x):
        encoded = self.encoder(x)
        decoded = self.decoder(encoded)
        return encoded, decoded

class OjaOptimizer(optim.Optimizer):
    def __init__(self, params, lr=0.01):
        defaults = dict(lr=lr)
        super(OjaOptimizer, self).__init__(params, defaults)

    def step(self, closure=None):
        loss = None
        if closure is not None:
            loss = closure()

        for group in self.param_groups:
            for p in group['params']:
                if p.grad is None:
                    continue

                if not hasattr(p, '_x') or not hasattr(p, '_y'):
                    continue

                x = p._x
                y = p._y

                if hasattr(p, '_is_decoder') and p._is_decoder:
                    x_recon = torch.mm(y, p.data.t())
                    delta = group['lr'] * torch.mm((x - x_recon).t(), y)
                    p.data.add_(delta)

                    for q in group['params']:
                        if hasattr(q, '_is_encoder') and q._is_encoder:
                            q.data = p.data.t()

        return loss

class AutoencoderTrainer:
    def __init__(self, model, optimizer_type, lr=0.01):
        self.model = model
        self.optimizer_type = optimizer_type

        if optimizer_type == "Oja":
            for name, param in model.named_parameters():
                if 'encoder' in name:
                    param._is_encoder = True
                elif 'decoder' in name:
                    param._is_decoder = True

            self.optimizer = OjaOptimizer(model.parameters(), lr=lr)
        elif optimizer_type == "SGD":
            self.optimizer = optim.SGD(model.parameters(), lr=lr)
        elif optimizer_type == "Adam":
            self.optimizer = optim.Adam(model.parameters(), lr=lr)

        self.criterion = nn.MSELoss()

    def train_step(self, x):
        y, x_recon = self.model(x)

        if self.optimizer_type == "Oja":
            for name, param in self.model.named_parameters():
                if 'decoder' in name:
                    param._x = x
                    param._y = y

        loss = self.criterion(x_recon, x)

        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

        return loss.item()

# Параметры
input_dim = X.shape[1]
encoding_dim = 4
epochs = 100

# Создание моделей
models = {
    "Oja": LinearAutoencoder(input_dim, encoding_dim),
    "SGD": LinearAutoencoder(input_dim, encoding_dim),
    "Adam": LinearAutoencoder(input_dim, encoding_dim)
}

trainers = {
    "Oja": AutoencoderTrainer(models["Oja"], "Oja", lr=0.01),
    "SGD": AutoencoderTrainer(models["SGD"], "SGD", lr=0.01),
    "Adam": AutoencoderTrainer(models["Adam"], "Adam", lr=0.01)
}

# Обучение
results = {name: {'train_losses': [], 'test_losses': []} for name in models}

for epoch in range(epochs):
    for name, trainer in trainers.items():
        models[name].train()
        train_loss = 0
        for batch_x, _ in train_loader:
            train_loss += trainer.train_step(batch_x)
        train_loss /= len(train_loader)
        results[name]['train_losses'].append(train_loss)

        models[name].eval()
        with torch.no_grad():
            _, decoded_test = models[name](X_test_tensor)
            test_loss = trainer.criterion(decoded_test, X_test_tensor).item()
            results[name]['test_losses'].append(test_loss)

    if (epoch + 1) % 10 == 0:
        print(f"Epoch {epoch + 1}/{epochs}")
        for name in models:
            print(f"{name}: Train Loss = {results[name]['train_losses'][-1]:.4f}, Test Loss = {results[name]['test_losses'][-1]:.4f}")
        print()


plt.figure(figsize=(12, 8))
for name in models:
    plt.plot(results[name]['train_losses'], label=f'{name} (train)')
    plt.plot(results[name]['test_losses'], '--', label=f'{name} (test)')

plt.xlabel('Epoch')
plt.ylabel('MSE Loss')
plt.title('Autoencoder Training with Different Optimizers')
plt.legend()
plt.grid(True)
plt.show()

# Итоговые ошибки
print("\nFinal Test Losses:")
for name in models:
    print(f"{name}: {results[name]['test_losses'][-1]:.4f}")