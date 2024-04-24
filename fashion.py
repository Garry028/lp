import matplotlib.pyplot as plt
import numpy as np

from keras.datasets import fashion_mnist
(train_x, train_y), (test_x, test_y) = fashion_mnist.load_data()

model.fit(train_x.astype(np.float32), train_y.astype(
    np.float32), epochs=5, validation_split=0.2)

loss, acc = model.evaluate(test_x, test_y)
print(loss)
print(acc)


# To know the labels list
def check_label(id_, labels):
    label = train_y[id_]
    if label not in labels:
        plt.imshow(train_x[id_])
        print(label)
        plt.show()
    return label


# To know unqiue Labels
labels = []
i = 0
while len(labels) < 10:
    label = check_label(i, labels)
    if label not in labels:
        labels.append(label)
    i += 1


def predict(id_):
    labels = ['t_shirt', 'trouser', 'pullover', 'dress', 'coat', 'sandal',
              'shirt', 'sneaker', 'bag', 'ankle_boots']  # Insert After Running Above Code
    predictions = model.predict(test_x[id_:id_+1])
    label = labels[np.argmax(predictions)]
    print(label)
    plt.imshow(test_x[id_])
    plt.show()


predict(5)

for i in range(10, 20):
    predict(i)
