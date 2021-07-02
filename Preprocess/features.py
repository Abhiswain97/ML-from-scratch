from typing import Dict, List


class features:
    def __init__(self, labels: List[str]):
        self.labels: List[str] = labels

    def one_hot_encode(self) -> Dict[str, List[str]]:
        encoded_dict: Dict[str, List[str]] = {}

        for i, label in enumerate(self.labels):
            vec = [0 for _ in range(len(self.labels))]
            vec[i] = 1
            encoded_dict[label] = vec

        return encoded_dict


if __name__ == "__main__":
    vec = ["Red", "Green", "Blue"]

    print(features(labels=vec).one_hot_encode())
