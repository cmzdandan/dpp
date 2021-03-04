import time

import numpy as np
import math


def dpp(kernel_matrix, max_length, epsilon=1E-10):
    """
    fast implementation of the greedy algorithm
    :param kernel_matrix: 2-d array
    :param max_length: positive int
    :param epsilon: small positive scalar
    :return: list
    """
    item_size = kernel_matrix.shape[0]
    cis = np.zeros((max_length, item_size))
    di2s = np.copy(np.diag(kernel_matrix))
    selected_items = list()
    selected_item = np.argmax(di2s)
    selected_items.append(selected_item)
    while len(selected_items) < max_length:
        k = len(selected_items) - 1
        ci_optimal = cis[:k, selected_item]
        di_optimal = math.sqrt(di2s[selected_item])
        elements = kernel_matrix[selected_item, :]
        eis = (elements - np.dot(ci_optimal, cis[:k, :])) / di_optimal
        cis[k, :] = eis
        di2s -= np.square(eis)
        selected_item = np.argmax(di2s)
        if di2s[selected_item] < epsilon:
            break
        selected_items.append(selected_item)
    return selected_items


if __name__ == '__main__':
    item_size = 100
    feature_dimension = 8
    max_length = 10

    scores = np.exp(0.01 * np.random.randn(item_size) + 0.2)
    feature_vectors = np.random.randn(item_size, feature_dimension)

    feature_vectors /= np.linalg.norm(feature_vectors, axis=1, keepdims=True)
    similarities = np.dot(feature_vectors, feature_vectors.T)
    kernel_matrix = scores.reshape((item_size, 1)) * similarities * scores.reshape((1, item_size))

    t = time.time()
    result = dpp(kernel_matrix, max_length)
    print('algorithm running time: ' + '\t' + "{0:.4e}".format(time.time() - t))
    print(result)
