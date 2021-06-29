import random
import math


class Metrics:
    def __init__(self):
        self.metrics = {"accuracy": self.accuracy, "log_loss": self.log_loss}

    def __call__(self, y_true, y_pred, y_probs=None, metric="accuracy"):
        if metric not in self.metrics:
            raise Exception("Metric not implemented")
        else:
            if metric == "log_loss":
                return self.metrics[metric](y_true, y_probs)
            else:
                return self.metrics[metric](y_true, y_pred)

    @staticmethod
    def accuracy(y_true, y_pred):
        return sum(
            [
                1 if label == pred_label else 0
                for label, pred_label in zip(y_true, y_pred)
            ]
        ) / len(y_true)

    @staticmethod
    def log_loss(y_true, y_probs):
        return (
            -1
            * (1 / len(y_true))
            * sum(
                [
                    (
                        (y_true[i] * math.log(y_probs[i]))
                        + ((1 - y_true[i]) * math.log(1 - y_probs[i]))
                    )
                    for i in range(len(y_true))
                ]
            )
        )


if __name__ == "__main__":
    y_true = [random.randint(0, 1) for _ in range(10)]
    y_pred = [random.randint(0, 1) for _ in range(10)]

    y_probs = [random.uniform(0, 1) for _ in range(10)]

    metrics = Metrics()

    print(metrics(y_true, y_pred, metric="accuracy"))
    print(metrics(y_true, y_pred=None, y_probs=y_probs, metric="log_loss"))
