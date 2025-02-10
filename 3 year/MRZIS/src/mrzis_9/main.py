import pandas as pd
from matplotlib import pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA
import torch
from torch import optim, nn
from torch.utils.data import DataLoader, TensorDataset
from MLP import MLP

if __name__ == "__main__":
    file_path = "WineQT.csv"
    data = pd.read_csv(file_path)

    X = data.iloc[:, :-2].values
    y = data.iloc[:, -2].values
    y = y - 3

    pca = PCA(n_components=7)
    X_reduced = pca.fit_transform(X)

    X_train, X_test, y_train, y_test = train_test_split(X_reduced, y, test_size=0.2, random_state=42)

    X_train = torch.tensor(X_train, dtype=torch.float32)
    X_test = torch.tensor(X_test, dtype=torch.float32)
    y_train = torch.tensor(y_train, dtype=torch.long)
    y_test = torch.tensor(y_test, dtype=torch.long)

    train_dataset = TensorDataset(X_train, y_train)
    test_dataset = TensorDataset(X_test, y_test)

    train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=64)

    print("Данные успешно загружены и подготовлены:")
    print(f"Размер тренировочного набора: {len(train_dataset)}")
    print(f"Размер тестового набора: {len(test_dataset)}")

    ##################################################################################################3

    model = MLP(in_size=X_train.shape[1], hid1_size=64, hid2_size=32, out_size=6)

    optimizer = optim.AdamW(model.parameters(), lr=0.01)
    criterion = nn.CrossEntropyLoss()

    num_epochs = 200
    epoch_losses = model.train_model(train_loader, optimizer, criterion, num_epochs)

    model.test_model(test_loader, criterion)

    plt.plot(range(1, num_epochs + 1), epoch_losses, marker='o')
    plt.xlabel("Epochs")
    plt.ylabel("Loss")
    plt.title("Training Loss per Epoch")
    plt.grid(True)
    plt.show()