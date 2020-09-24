import json
import random

data = dict()
for i in range(100):
    test = {
        "numOfWorkers": 2,
        "jobs": random.sample(range(1, 100000), 10),
        "learningFactor": round(random.random() * -1, 5)
    }
    data[i] = test


with open('test/resources/testsPayload.json', 'w+') as file:
     file.write(json.dumps(data))