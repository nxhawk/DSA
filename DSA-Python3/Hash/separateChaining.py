class Hash:
    def __init__(self, n):
        self.size = n
        self.table = [[] for _ in range(n)]

    # print hash table
    def display_hash(self):
        for i in range(self.size):
            print('%d:' % i, end=" ")

            for j in self.table[i]:
                print('-->', end=" ")
                print(j, end=" ")

            print()

    # hash func
    def hashing(self, value):
        return value % self.size

    # insert value
    def insert(self, value):
        hash_key = self.hashing(value)
        self.table[hash_key].append(value)


if __name__ == '__main__':
    hash = Hash(7)
    hash.insert(12)
    hash.insert(15)
    hash.insert(3)
    hash.insert(5)
    hash.display_hash()
