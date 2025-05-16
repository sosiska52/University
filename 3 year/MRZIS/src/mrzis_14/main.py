import numpy as np
from scipy import signal
from tqdm import tqdm
import torchvision
import random

class Layer:
    def __init__(self):
        self.input = None
        self.output = None

    def __call__(self, *args, **kwargs):
        return self.forward(*args, **kwargs)

    def forward(self, *args, **kwargs):
        raise NotImplementedError

    def backward(self, output_gradient, learning_rate):
        raise NotImplementedError


class Conv2D(Layer):
    def __init__(self, input_shape, kernel_size, depth, transposed=False):
        super().__init__()
        self.transposed = transposed
        self.input_depth, self.input_height, self.input_width = input_shape
        self.depth = depth
        self.kernel_size = kernel_size

        if not transposed:
            self.output_shape = (depth, input_shape[1] - kernel_size + 1, input_shape[2] - kernel_size + 1)
        else:
            self.output_shape = (depth, input_shape[1] + kernel_size - 1, input_shape[2] + kernel_size - 1)

        self.kernels_shape = (depth, self.input_depth, kernel_size, kernel_size)
        he_std = np.sqrt(2.0 / (self.input_depth * kernel_size**2))
        self.kernels = np.random.randn(*self.kernels_shape) * he_std
        self.biases = np.zeros(self.output_shape)

    def forward(self, input):
        self.input = input.copy()
        self.output = self.biases.copy()

        if not self.transposed:
            for i in range(self.depth):
                for j in range(self.input_depth):
                    self.output[i] += signal.correlate2d(self.input[j], self.kernels[i, j], mode='valid')
        else:
            for i in range(self.depth):
                for j in range(self.input_depth):
                    self.output[i] += signal.convolve2d(self.input[j], self.kernels[i, j], mode='full')

        return self.output

    def backward(self, output_gradient, learning_rate):
        kernels_gradient = np.zeros(self.kernels_shape)
        input_gradient = np.zeros((self.input_depth, self.input_height, self.input_width))

        if not self.transposed:
            for i in range(self.depth):
                for j in range(self.input_depth):
                    kernels_gradient[i, j] = signal.correlate2d(self.input[j], output_gradient[i], mode='valid')
                    input_gradient[j] += signal.convolve2d(output_gradient[i], self.kernels[i, j], mode='full')
        else:
            for i in range(self.depth):
                for j in range(self.input_depth):
                    kernels_gradient[i, j] = signal.correlate2d(self.input[j], output_gradient[i], mode='valid')
                    input_gradient[j] += signal.correlate2d(output_gradient[i], self.kernels[i, j], mode='valid')

        self.kernels -= learning_rate * kernels_gradient
        self.biases -= learning_rate * output_gradient
        return input_gradient


class ELU(Layer):
    def __init__(self, alpha=1.0):
        super().__init__()
        self.alpha = alpha

    def forward(self, x):
        self.input = x
        return np.where(x > 0, x, self.alpha * (np.exp(x) - 1))

    def backward(self, output_gradient, learning_rate):
        grad_input = np.where(self.input > 0, 1, self.alpha * np.exp(self.input))
        return output_gradient * grad_input


class MeanSquaredErrorLoss(Layer):
    def forward(self, target, predict):
        self.target = target
        self.predict = predict
        return np.mean((predict - target) ** 2) / 2

    def backward(self, target, predict):
        return (predict - target) / predict.size


class Autoencoder(Layer):
    def __init__(self):
        super().__init__()
        self.encoder = [
            Conv2D((1, 28, 28), 3, 16),
            ELU(),
            Conv2D((16, 26, 26), 3, 32)
        ]
        self.decoder = [
            Conv2D((32, 24, 24), 3, 16, transposed=True),
            ELU(),
            Conv2D((16, 26, 26), 3, 1, transposed=True)
        ]

    def forward(self, x):
        for layer in self.encoder:
            x = layer.forward(x)
        for layer in self.decoder:
            x = layer.forward(x)
        return x

    def backward(self, grad, learning_rate):
        for layer in reversed(self.decoder):
            grad = layer.backward(grad, learning_rate)
        for layer in reversed(self.encoder):
            grad = layer.backward(grad, learning_rate)
        return grad


def get_class_dict(train=True):
    transform = torchvision.transforms.Compose([
        lambda img: np.expand_dims(np.array(img).astype(np.float32) / 255.0, axis=0)
    ])

    dataset = torchvision.datasets.MNIST(
        root='./data',
        train=train,
        download=True,
        transform=transform
    )

    class_dict = {}
    for image, target in dataset:
        if target not in class_dict:
            class_dict[target] = []
        class_dict[target].append(image)

    return class_dict


class AutoencoderModel:
    def __init__(self):
        self.autoencoders = [Autoencoder() for _ in range(10)]

    def forward(self, x, model_idx):
        return self.autoencoders[model_idx].forward(x)

    def backward(self, grad, learning_rate, model_idx):
        return self.autoencoders[model_idx].backward(grad, learning_rate)


def train_loop(dataset, model, criterion, learning_rate):
    total_loss = 0
    random.shuffle(dataset)
    for image, label in tqdm(dataset, desc="Training", leave=False):
        pred = model.forward(image, label)
        loss = criterion.forward(image, pred)
        total_loss += loss

        dL_dx = criterion.backward(image, pred)
        model.backward(dL_dx, learning_rate, label)

    return total_loss / len(dataset)



def test(models, test_dataset):
    true, false = 0, 0
    total_loss = 0

    for image, cls in test_dataset:
        losses = []
        for idx in range(10):
            pred = models.forward(image, idx)
            losses.append(MeanSquaredErrorLoss().forward(image, pred))
        predicted_class = np.argmin(losses)
        total_loss += losses[cls]
        if predicted_class == cls:
            true += 1
        else:
            false += 1

    accuracy = true / (true + false) * 100
    avg_loss = total_loss / (true + false)
    print(f"Accuracy: {accuracy:.2f}% ({true}/{true + false}), Avg Loss: {avg_loss:.4f}")
    return accuracy, avg_loss



def main():
    learning_rate = 0.001
    max_epochs = 100
    target_loss = 0.005

    train_class_dict = get_class_dict(train=True)
    test_class_dict = get_class_dict(train=False)

    train_dataset = [(img, cls) for cls, imgs in train_class_dict.items() for img in imgs]
    test_dataset = [(img, cls) for cls, imgs in test_class_dict.items() for img in imgs]

    model = AutoencoderModel()
    criterion = MeanSquaredErrorLoss()
    print("Training started...")

    for epoch in range(1, max_epochs + 1):
        avg_loss = train_loop(train_dataset, model, criterion, learning_rate)
        print(f"Epoch {epoch} - Train Loss: {avg_loss:.4f}")

        accuracy, test_loss = test(model, test_dataset)

        if test_loss < target_loss:
            print(f"\nTarget loss reached: {test_loss:.4f} < {target_loss}")
            break


if __name__ == "__main__":
    main()