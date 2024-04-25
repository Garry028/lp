from sklearn.metrics import accuracy_score, precision_score, recall_score
from keras.layers import Dense
from keras.models import Sequential
import numpy as np
from keras.datasets import imdb

(train_data, train_label), (test_data, test_label) = imdb.load_data(num_words=10000)


def vectorize_sequences(sequences, dimensions=10000):
    results = np.zeros((len(sequences), dimensions))
    for i, sequence in enumerate(sequences):
        results[i, sequence] = 1

    return results


x_train = vectorize_sequences(train_data)
x_test = vectorize_sequences(test_data)

y_train = np.asarray(train_label).astype('float32')
y_test = np.asarray(test_label).astype('float32')


model = Sequential()

model.add(Dense(16, input_shape=(10000,), activation='relu'))
model.add(Dense(16, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

model.compile(optimizer='adam', loss='mse', metrics=['accuracy'])

model.summary()

history = model.fit(x_train, y_train, validation_split=0.2,
                    epochs=20, verbose=1, batch_size=512)

mse, mae = model.evaluate(x_test, y_test)

print('MSE ', mse)
print('MAE ', mae)

y_preds = model.predict(x_test)

y_preds
y_test

tests = []
for i in y_test:
    tests.append(int(i))

preds = []
for i in y_preds:
    if i[0] > 0.5:
        preds.append(1)
    else:
        preds.append(0)


print(accuracy_score(tests, preds))
print(precision_score(tests, preds))
print(recall_score(tests, preds))

# word_index is a dictionary mapping words to an integer index
word_index = imdb.get_word_index()


def return_token(tid):
    for k, v in word_index.items():
        # We decode the review; note that our indices were offset by 3
        # because 0, 1 and 2 are reserved indices for "padding", "start of sequence", and "unknown".
        if v == tid-3:
            return k
    return '?'


def print_review(id_):
    sentence = ' '.join(return_token(i) for i in train_data[id_])
    return sentence


print_review(0)
train_label[0]  # Positive
print_review(1)
train_label[1]  # Negaive
print_review(2)
train_label[2]  # Negaive
