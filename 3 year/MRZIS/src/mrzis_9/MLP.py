import torch
import torch.nn as nn
import torch.optim as optim


class MLP(nn.Module):
    def __init__(self, in_size, hid1_size, hid2_size, out_size):
        super(MLP, self).__init__()
        self.layer1 = nn.Linear(in_size, hid1_size)
        self.layer2 = nn.Linear(hid1_size, hid2_size)
        self.layer3 = nn.Linear(hid2_size, out_size)
        self.drop = nn.Dropout(0.1)

    def forward(self, x):
        x = nn.ReLU()(self.layer1(x))
        x = self.drop(nn.ReLU()(self.layer2(x)))
        x = self.layer3(x)
        return x

    def train_step(self, optimizer, criterion, inputs, targets):
        optimizer.zero_grad()
        outputs = self(inputs)
        loss = criterion(outputs, targets)
        loss.backward()
        optimizer.step()
        return loss.item()

    def train_model(self, train_loader, optimizer, criterion, num_epochs):
        self.train()
        epoch_losses = []
        for epoch in range(num_epochs):
            epoch_loss = 0
            for inputs, targets in train_loader:
                loss = self.train_step(optimizer, criterion, inputs, targets)
                epoch_loss += loss
            avg_epoch_loss = epoch_loss / len(train_loader)
            epoch_losses.append(avg_epoch_loss)
            print(f"Epoch {epoch + 1}/{num_epochs}, Loss: {avg_epoch_loss:.4f}")

        return epoch_losses

    def test_model(self, test_loader, criterion):
        self.eval()
        test_loss = 0
        correct = 0
        total = 0

        with torch.no_grad():
            for inputs, targets in test_loader:
                outputs = self(inputs)
                loss = criterion(outputs, targets)
                test_loss += loss.item()

                _, predicted = torch.max(outputs, 1)
                mismatch = predicted == targets
                print(predicted, " - ", targets, " - ", mismatch.sum())
                correct += mismatch.sum().item()
                total += targets.size(0)

        accuracy = correct / total
        print(f"Test Loss: {test_loss / len(test_loader):.4f}, Accuracy: {accuracy:.2%}")