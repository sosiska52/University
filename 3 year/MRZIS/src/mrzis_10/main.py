import torch
import torch.nn as nn
import torch.optim as optim
import numpy as np
import pandas as pd
from torch.utils.data import DataLoader, TensorDataset, random_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error, explained_variance_score


class AutoEncoder(nn.Module):
    def __init__(self, input_size, hidden_size):
        super(AutoEncoder, self).__init__()
        self.encoder = nn.Sequential(
            nn.Linear(input_size, hidden_size),
            nn.LeakyReLU()
        )
        self.decoder = nn.Sequential(
            nn.Linear(hidden_size, input_size),
            nn.LeakyReLU()
        )

    def forward(self, x):
        x = self.encoder(x)
        x = self.decoder(x)
        return x


def pca(X, num_components, return_error=False):
    X_meaned = X - np.mean(X, axis=0)
    cov_mat = np.cov(X_meaned, rowvar=False)
    eigen_values, eigen_vectors = np.linalg.eigh(cov_mat)

    sorted_index = np.argsort(eigen_values)[::-1]
    eigen_vectors = eigen_vectors[:, sorted_index]

    eigenvector_subset = eigen_vectors[:, 0:num_components]
    X_reduced = np.dot(eigenvector_subset.transpose(), X_meaned.transpose()).transpose()

    if return_error:
        X_restored = np.dot(X_reduced, eigenvector_subset.transpose()) + np.mean(X, axis=0)
        reconstruction_error = np.mean(np.square(X - X_restored))
        explained_var = explained_variance_score(X, X_restored)
        return X_reduced, reconstruction_error, explained_var
    else:
        return X_reduced


def load_and_preprocess_data(filepath, test_ratio=0.2):
    data = pd.read_csv(filepath)
    X = data.iloc[:, :-1].values
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    return X_scaled, scaler


def create_dataloaders(X_scaled, test_ratio=0.2, batch_size=16):
    train_size = int((1 - test_ratio) * len(X_scaled))
    test_size = len(X_scaled) - train_size
    dataset = TensorDataset(torch.tensor(X_scaled, dtype=torch.float32), torch.tensor(X_scaled, dtype=torch.float32))
    train_dataset, test_dataset = random_split(dataset, [train_size, test_size])
    train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)
    return train_loader, test_loader


def train_autoencoder(autoencoder, train_loader, test_loader, num_epochs=100, learning_rate=0.001):
    criterion = nn.MSELoss()
    optimizer = optim.Adam(autoencoder.parameters(), lr=learning_rate)
    test_errors = []

    for epoch in range(num_epochs):
        autoencoder.train()
        total_loss = 0
        for batch_x, _ in train_loader:
            optimizer.zero_grad()
            output = autoencoder(batch_x)
            loss = criterion(output, batch_x)
            loss.backward()
            optimizer.step()
            total_loss += loss.item()

        autoencoder.eval()
        test_loss = 0
        with torch.no_grad():
            for batch_x, _ in test_loader:
                output = autoencoder(batch_x)
                test_loss += criterion(output, batch_x).item()
        test_loss /= len(test_loader)
        test_errors.append(test_loss)

        if (epoch + 1) % 10 == 0:
            print(f'Epoch [{epoch + 1}/{num_epochs}], Train Loss: {total_loss / len(train_loader):.6f}, Test Loss: {test_loss:.6f}')

    return test_errors


def evaluate_reconstruction(autoencoder, test_loader):
    autoencoder.eval()
    reconstructed, original = [], []
    with torch.no_grad():
        for batch_x, _ in test_loader:
            output = autoencoder(batch_x)
            reconstructed.append(output.numpy())
            original.append(batch_x.numpy())
    original = np.vstack(original)
    reconstructed = np.vstack(reconstructed)
    mse = mean_squared_error(original, reconstructed)
    explained_var = explained_variance_score(original, reconstructed)
    return mse, explained_var


def main():
    X_scaled, _ = load_and_preprocess_data('ionosphere_data.csv')
    train_loader, test_loader = create_dataloaders(X_scaled)

    input_size = X_scaled.shape[1]
    hidden_size = 2
    autoencoder = AutoEncoder(input_size, hidden_size)

    test_errors = train_autoencoder(autoencoder, train_loader, test_loader)
    mse_autoencoder, variance_autoencoder = evaluate_reconstruction(autoencoder, test_loader)

    X_pca, mse_pca, variance_pca = pca(X_scaled, hidden_size, return_error=True)

    print(f'Autoencoder - MSE: {mse_autoencoder:.6f}, Explained Variance: {variance_autoencoder:.6f}')
    print(f'PCA - MSE: {mse_pca:.6f}, Explained Variance: {variance_pca:.6f}')


if __name__ == "__main__":
    main()