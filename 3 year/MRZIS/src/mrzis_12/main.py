import torch
import torch.nn as nn
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from torch.utils.data import DataLoader, TensorDataset


def generate_data():
    x = np.linspace(0, 10, 100)
    y = np.cos(4 * x) + 2 * np.sin(3 * x)
    return x, y


def create_sequences(data, seq_length):
    xs, ys = [], []
    for i in range(len(data) - seq_length):
        x = data[i:(i + seq_length)]
        y = data[i + seq_length]
        xs.append(x)
        ys.append(y)
    return np.array(xs), np.array(ys)


SEQ_LENGTH = 5
HIDDEN_SIZE = 32
EPOCHS = 200
BATCH_SIZE = 8
LEARNING_RATE = 0.01


x, y = generate_data()
X, Y = create_sequences(y, SEQ_LENGTH)
X = X.reshape(-1, SEQ_LENGTH, 1)
Y = Y.reshape(-1, 1)


X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, shuffle=False)


X_train = torch.FloatTensor(X_train)
Y_train = torch.FloatTensor(Y_train)
X_test = torch.FloatTensor(X_test)
Y_test = torch.FloatTensor(Y_test)

# DataLoader
train_data = TensorDataset(X_train, Y_train)
train_loader = DataLoader(train_data, batch_size=BATCH_SIZE, shuffle=False)


class ManualRNN(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(ManualRNN, self).__init__()
        self.hidden_size = hidden_size

        # Веса для входного слоя
        self.Wxh = nn.Parameter(torch.randn(input_size, hidden_size) * 0.01)
        # Веса для скрытого состояния
        self.Whh = nn.Parameter(torch.randn(hidden_size, hidden_size) * 0.01)
        # Веса для выходного слоя
        self.Why = nn.Parameter(torch.randn(hidden_size, output_size) * 0.01)

        # Смещения
        self.bh = nn.Parameter(torch.zeros(hidden_size))
        self.by = nn.Parameter(torch.zeros(output_size))

    def forward(self, x):

        h = torch.zeros(x.size(0), self.hidden_size).to(x.device)

        for t in range(x.size(1)):
            xt = x[:, t, :]
            h = torch.tanh(xt @ self.Wxh + h @ self.Whh + self.bh)

        output = h @ self.Why + self.by
        return output


class PyTorchRNN(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(PyTorchRNN, self).__init__()
        self.rnn = nn.RNN(input_size, hidden_size, batch_first=True)
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        out, _ = self.rnn(x)
        out = self.fc(out[:, -1, :])
        return out


class GRUModel(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(GRUModel, self).__init__()
        self.gru = nn.GRU(input_size, hidden_size, batch_first=True)
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        out, _ = self.gru(x)
        out = self.fc(out[:, -1, :])
        return out


class LSTMModel(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(LSTMModel, self).__init__()
        self.lstm = nn.LSTM(input_size, hidden_size, batch_first=True)
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        out, _ = self.lstm(x)
        out = self.fc(out[:, -1, :])
        return out


# Функция для обучения модели
def train_model(model, train_loader, criterion, optimizer, epochs):
    train_loss = []
    test_loss = []

    for epoch in range(epochs):
        model.train()
        total_loss = 0

        for batch_x, batch_y in train_loader:
            optimizer.zero_grad()
            output = model(batch_x)
            loss = criterion(output, batch_y)
            loss.backward()
            optimizer.step()
            total_loss += loss.item()

        avg_train_loss = total_loss / len(train_loader)
        train_loss.append(avg_train_loss)

        # Оценка на тестовых данных
        model.eval()
        with torch.no_grad():
            test_output = model(X_test)
            test_loss_val = criterion(test_output, Y_test).item()
            test_loss.append(test_loss_val)

        if (epoch + 1) % 50 == 0:
            print(f'Epoch {epoch + 1}, Train Loss: {avg_train_loss:.4f}, Test Loss: {test_loss_val:.4f}')

    return train_loss, test_loss


manual_rnn = ManualRNN(1, HIDDEN_SIZE, 1)
pytorch_rnn = PyTorchRNN(1, HIDDEN_SIZE, 1)
gru = GRUModel(1, HIDDEN_SIZE, 1)
lstm = LSTMModel(1, HIDDEN_SIZE, 1)

# Критерий и оптимизаторы
criterion = nn.MSELoss()
manual_optimizer = torch.optim.Adam(manual_rnn.parameters(), lr=LEARNING_RATE)
rnn_optimizer = torch.optim.Adam(pytorch_rnn.parameters(), lr=LEARNING_RATE)
gru_optimizer = torch.optim.Adam(gru.parameters(), lr=LEARNING_RATE)
lstm_optimizer = torch.optim.Adam(lstm.parameters(), lr=LEARNING_RATE)


print("Training Manual RNN...")
manual_train_loss, manual_test_loss = train_model(manual_rnn, train_loader, criterion, manual_optimizer, EPOCHS)

print("\nTraining PyTorch RNN...")
rnn_train_loss, rnn_test_loss = train_model(pytorch_rnn, train_loader, criterion, rnn_optimizer, EPOCHS)

print("\nTraining GRU...")
gru_train_loss, gru_test_loss = train_model(gru, train_loader, criterion, gru_optimizer, EPOCHS)

print("\nTraining LSTM...")
lstm_train_loss, lstm_test_loss = train_model(lstm, train_loader, criterion, lstm_optimizer, EPOCHS)


def predict(model, X):
    model.eval()
    with torch.no_grad():
        predictions = model(X)
    return predictions.numpy()


manual_pred = predict(manual_rnn, X_test)
rnn_pred = predict(pytorch_rnn, X_test)
gru_pred = predict(gru, X_test)
lstm_pred = predict(lstm, X_test)

# Визуализация
plt.figure(figsize=(12, 8))


plt.subplot(2, 2, 1)
plt.plot(manual_train_loss, label='Manual RNN Train')
plt.plot(manual_test_loss, label='Manual RNN Test')
plt.title('Manual RNN Loss')
plt.legend()

plt.subplot(2, 2, 2)
plt.plot(rnn_train_loss, label='RNN Train')
plt.plot(rnn_test_loss, label='RNN Test')
plt.title('PyTorch RNN Loss')
plt.legend()

plt.subplot(2, 2, 3)
plt.plot(gru_train_loss, label='GRU Train')
plt.plot(gru_test_loss, label='GRU Test')
plt.title('GRU Loss')
plt.legend()

plt.subplot(2, 2, 4)
plt.plot(lstm_train_loss, label='LSTM Train')
plt.plot(lstm_test_loss, label='LSTM Test')
plt.title('LSTM Loss')
plt.legend()

plt.tight_layout()
plt.show()


test_indices = range(len(Y_test))

plt.figure(figsize=(12, 8))
plt.plot(test_indices, Y_test.numpy(), label='True', linewidth=2)
plt.plot(test_indices, manual_pred, label='Manual RNN')
plt.plot(test_indices, rnn_pred, label='PyTorch RNN')
plt.plot(test_indices, gru_pred, label='GRU')
plt.plot(test_indices, lstm_pred, label='LSTM')
plt.title('Predictions on Test Data')
plt.legend()
plt.show()