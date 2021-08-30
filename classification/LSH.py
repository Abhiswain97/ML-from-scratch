from typing import Dict
import numpy as np
import random
import pandas as pd
from tqdm import tqdm
from collections import Counter, OrderedDict


class LSH:
    def __init__(self, X: np.array, y, num_hps: int = 5, k: int = 11):

        self.set_seed()

        self.X: np.array = X
        self.y = y
        self.hash_table: Dict = {}
        self.num_hps: int = num_hps
        self.k = k

        # Generate hyperplanes
        self.hps: np.array = np.array(
            [np.random.normal(0, 1, X.shape[1]) for _ in range(self.num_hps)]
        )

    def set_seed(self):
        """
        Setting the random seed for better interpretability
        """
        np.random.seed(0)
        random.seed(0)

    def _hash_func(self, vec):
        """
        Hash function to generate keys
        """
        return tuple(np.sign(np.dot(self.hps, vec)))

    def _create_hash_table(self):
        """
        Generate hash table putting points in various buckets
        """
        for idx, vec in tqdm(enumerate(self.X), total=self.X.shape[0]):
            key = self._hash_func(vec)

            if key not in self.hash_table.keys():
                self.hash_table[key] = []
            else:
                self.hash_table[key].append(idx)

    def _cos_sim(self, v1, v2):
        """
        Compute the cosine similarity between 2 vectors
        """
        return np.dot(v1, v2) / (np.linalg.norm(v1) * np.linalg.norm(v2))

    def fit_transform(self):
        """
        The training phase for generating hash table
        """
        self._create_hash_table()

    def _majority_voting(self, classes):
        """
        Does majority voting among nearest neighbor 
        predicted classes to get the final prediction
        """
        max_count = max(list(classes.values()))

        preds = []

        for k, v in classes.items():
            if v == max_count:
                preds.append(k)

        return sorted(preds)[0]

    def transform(self, X_test):
        """
        Make predictions on the test data
        """
        preds = []

        for idx, vec in tqdm(enumerate(X_test), total=X_test.shape[0]):
            key = self._hash_func(vec)

            # Getting all the neighbors from hash table
            neigh_idxs = self.hash_table[key]

            # Computing cosine similarity for each vector
            cos_sims = {}

            for idx in tqdm(neigh_idxs):
                v = self.X[idx]
                cos_sims[idx] = self._cos_sim(v, vec)

            # Getting the nearest neighbours
            nearest_nn_idxs = np.array(
                list(
                    OrderedDict(
                        sorted(cos_sims.items(),
                               key=lambda x: x[1], reverse=True)
                    ).keys()
                )[:12]
            )

            preds.append(self._majority_voting(
                Counter(self.y[nearest_nn_idxs])))

        return preds
