class Hash:
    def __init__(self, n):
        self.size = n
        self.table = [-1 for _ in range(n)]

    def display_hash(self):
        for i in range(self.size):
            print("%d: %d" % (i, self.table[i]))

    def hashFunc1(self, value):
        return value % self.size

    def hashFunc2(self, value, index):
        return (value + index*index) % self.size

    def h2(self, value):
        return 5 - value % 5

    def hashFuncDouble(self, k1, k2, i):
        return (k1 + i*k2) % self.size

    def insertFunc(self, value):
        k1 = self.hashFunc1(value)
        count = 0
        tk1 = k1
        while self.table[tk1] != -1:
            count += 1
            tk1 = self.hashFunc2(k1, count)
            if tk1 == k1:
                print("Hash Table full")
                return
        self.table[tk1] = value

    def insertFuncDouble(self, value):
        k1 = self.hashFunc1(value)
        k2 = self.h2(value)

        tk = k1
        count = 0
        while self.table[tk] != -1:
            count += 1
            tk = self.hashFuncDouble(k1, k2, count)
            if tk == k1:
                print('Hash table full')
                return
        self.table[tk] = value


if __name__ == '__main__':
    hash = Hash(7)
    hash.insertFuncDouble(5)
    hash.insertFuncDouble(12)
    hash.insertFuncDouble(20)
    hash.insertFuncDouble(15)
    hash.display_hash()
