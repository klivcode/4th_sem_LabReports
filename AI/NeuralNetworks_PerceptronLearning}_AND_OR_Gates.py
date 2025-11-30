
# Lab 9: Neural Network - Logic Gates using Perceptron Learning
# =============================================================
# Objective: Implement basic logic gates (AND, OR) using a single-layer Perceptron.
# Key concepts:
# ✔ Perceptron: basic unit of neural network
# ✔ Weights & bias
# ✔ Activation function
# ✔ Perceptron learning rule (weight update)
# ✔ Epochs: number of passes over training data
# =============================================================

import numpy as np

# -------------------------------------------------------------
# Perceptron Class
# -------------------------------------------------------------
class Perceptron:
    def __init__(self, input_size, lr=0.1, epochs=10):
        """
        Initialize Perceptron
        input_size: number of input features
        lr: learning rate
        epochs: number of times to iterate over the dataset
        """
        self.lr = lr
        self.epochs = epochs
        self.weights = np.zeros(input_size + 1)  # +1 for bias term

    def activation(self, x):
        """
        Step activation function:
        Returns 1 if input >= 0 else 0
        """
        return 1 if x >= 0 else 0

    def predict(self, x):
        """
        Predict output for a given input x
        z = weighted sum + bias
        """
        z = np.dot(x, self.weights[1:]) + self.weights[0]  # weights[0] is bias
        return self.activation(z)

    def train(self, X, y):
        """
        Train perceptron using Perceptron Learning Rule
        For each epoch and each sample:
        1. Predict output
        2. Calculate error = target - prediction
        3. Update weights and bias
        """
        for _ in range(self.epochs):
            for xi, yi in zip(X, y):
                y_pred = self.predict(xi)
                error = yi - y_pred
                # Update weights
                self.weights[1:] += self.lr * error * xi
                # Update bias
                self.weights[0] += self.lr * error

# =============================================================
# Training AND Gate
# =============================================================
X_and = np.array([[0,0],[0,1],[1,0],[1,1]])  # Input combinations
y_and = np.array([0,0,0,1])                  # AND gate outputs

perceptron_and = Perceptron(input_size=2)
perceptron_and.train(X_and, y_and)

print("AND Gate Results:")
for xi in X_and:
    print(f"Input: {xi} => Output: {perceptron_and.predict(xi)}")

# =============================================================
# Training OR Gate
# =============================================================
y_or = np.array([0,1,1,1])  # OR gate outputs

perceptron_or = Perceptron(input_size=2)
perceptron_or.train(X_and, y_or)

print("\nOR Gate Results:")
for xi in X_and:
    print(f"Input: {xi} => Output: {perceptron_or.predict(xi)}")
