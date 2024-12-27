import numpy as np
import matplotlib.pyplot as plt
from tensorflow.keras import datasets, layers, models

# MNIST veri setini yükleme
(train_images, train_labels), (test_images, test_labels) = datasets.mnist.load_data()

# Veri ön işleme
train_images = train_images.reshape((60000, 28, 28, 1))
test_images = test_images.reshape((10000, 28, 28, 1))

# Normalize etme
train_images, test_images = train_images / 255.0, test_images / 255.0

# CNN Modelini Kurma
model = models.Sequential([
    layers.Conv2D(32, (3, 3), activation='relu', input_shape=(28, 28, 1)),
    layers.MaxPooling2D((2, 2)),
    layers.Conv2D(64, (3, 3), activation='relu'),
    layers.MaxPooling2D((2, 2)),
    layers.Conv2D(64, (3, 3), activation='relu'),
    layers.Flatten(),
    layers.Dense(64, activation='relu'),
    layers.Dense(10, activation='softmax')
])

# Modeli Derleme
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# Modeli Eğitme
model.fit(train_images, train_labels, epochs=20, validation_data=(test_images, test_labels))

# Modeli Kaydetme
model.save('mnist_digit_recognizer.h5')