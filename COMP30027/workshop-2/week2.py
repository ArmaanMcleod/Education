import numpy as np
import matplotlib as mpl
import sklearn
import math

a = np.arange(5)
b = np.array([1, 3, -2, 0, 0])

a_hamming = np.array([0, "cat", 800, "??"])
b_hamming = np.array([1, "dog", -266, "??"])

check_len = lambda x, y: len(x) != len(y)

def euclidean1(a, b):
    if check_len(a, b):
        return 'Lists are different dimensions'

    return math.sqrt(sum((x-y)**2 for x, y in zip(a, b)))

def euclidean2(a, b):
    if check_len(a, b):
        return 'Lists are different dimensions'

    return np.linalg.norm(a - b)

def hamming1(a, b):
    if check_len(a, b):
        return 'Lists are different dimensions'

    return len([(x, y) for x, y in zip(a, b) if x != y])

print("Questions 1 - 3:")
print(euclidean1(a, b))
print(euclidean2(a, b))

print(hamming1(a_hamming, b_hamming))

def dot_product(a, b):
    if check_len(a, b):
        return 'Lists are different lengths'

    return sum(x * y for x, y in zip(a, b))

def magnitude(a):
    return math.sqrt(sum(x**2 for x in a))

def cosine(a, b):
    if check_len(a, b):
        return 'Lists are different lengths'

    return dot_product(a, b) / (magnitude(a) * magnitude(b))

def my_cosine_numpy(a, b):
    if check_len(a, b):
        return 'Lists are different lengths'
        s
    return np.dot(a, b) / (np.linalg.norm(a) * np.linalg.norm(b))

print("Questions 4")
print(dot_product(np.array([1, 2]), np.array([1, 1])))
print(dot_product(np.array([1, 2]), np.array([2, 2])))
print(dot_product(np.array([1, 2]), np.array([3, 3])))
print(dot_product(np.array([0, 0, 1]), np.array([1, 0, 0])))

print(cosine(np.array([1, 2]), np.array([1, 1])))

print(my_cosine_numpy(np.array([1, 2]), np.array([1, 1])))

M = np.array([[1, 2, 3], [4, 2, 1], [6, 2, 0]])
N = np.array([[0, 3, 1], [1, 1, 4], [2, 0, 3]])

print("Question 5")
print(M + N)
print(M - N)




