from sklearn.datasets import make_classification

import showcase

num_samples = 2**10
num_features = 2**8
samples, labels = make_classification(n_samples=num_samples, n_features=num_features, n_redundant=0,
                                      n_informative=2, n_clusters_per_class=1)


m = showcase.Matrix(samples, labels)
print(m.get_data()[0][:5])
print(m.get_labels()[:5])

print(type(m.get_data()))
print(type(m.get_labels()))
