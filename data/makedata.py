import random
import uuid
import os

DATA_LOAD = 2_000_0000
VALUE_LIMIT = 10 ** 12

def makedata_1(filename):
    with open(filename, "w", encoding='utf-8') as out_f:
        for i in range(0, DATA_LOAD):
            a = random.randint(1, VALUE_LIMIT)
            b = uuid.uuid4()
            r = '{},{}\n'.format(a, b)
            out_f.write(r)

def main():
    makedata_1("data2.csv")

if __name__ == "__main__":
    main()