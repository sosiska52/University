import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
from torchvision import transforms
from torch.utils.data import DataLoader
from tqdm import tqdm
import numpy as np

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

class Autoencoder(nn.Module):
    def __init__(self):
        super().__init__()
        self.encoder = nn.Sequential(
            nn.Conv2d(1, 16, kernel_size=3),
            nn.ELU(),
            nn.Conv2d(16, 32, kernel_size=3),
            nn.ELU()
        )
        self.decoder = nn.Sequential(
            nn.ConvTranspose2d(32, 16, kernel_size=3),
            nn.ELU(),
            nn.ConvTranspose2d(16, 1, kernel_size=3),
            nn.Sigmoid()
        )

    def forward(self, x):
        x = self.encoder(x)
        x = self.decoder(x)
        return x

class MultiAutoencoder:
    def __init__(self):
        self.models = [Autoencoder().to(device) for _ in range(10)]
        self.optimizers = [optim.Adam(model.parameters(), lr=0.001) for model in self.models]
        self.criterion = nn.MSELoss()

    def train_step(self, x, label):
        model = self.models[label]
        optimizer = self.optimizers[label]

        model.train()
        optimizer.zero_grad()
        output = model(x)
        loss = self.criterion(output, x)
        loss.backward()
        optimizer.step()

        return loss.item()

    def test_step(self, x):
        losses = []
        for model in self.models:
            model.eval()
            with torch.no_grad():
                output = model(x)
                loss = self.criterion(output, x)
                losses.append(loss.item())
        return np.argmin(losses)

transform = transforms.Compose([
    transforms.ToTensor()
])

train_dataset = torchvision.datasets.MNIST(root='./data', train=True, download=True, transform=transform)
test_dataset = torchvision.datasets.MNIST(root='./data', train=False, download=True, transform=transform)

train_loader = DataLoader(train_dataset, batch_size=1, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=1, shuffle=False)

model = MultiAutoencoder()

max_epochs = 1
for epoch in range(max_epochs):
    total_loss = 0
    for x, label in tqdm(train_loader, desc=f"Epoch {epoch+1}"):
        x = x.to(device)
        loss = model.train_step(x, label.item())
        total_loss += loss
    print(f"Train loss: {total_loss / len(train_loader):.4f}")

correct = 0
total = 0
for x, label in test_loader:
    x = x.to(device)
    predicted = model.test_step(x)
    if predicted == label.item():
        correct += 1
    total += 1

accuracy = correct / total * 100
print(f"Accuracy: {accuracy:.2f}% ({correct}/{total})")
