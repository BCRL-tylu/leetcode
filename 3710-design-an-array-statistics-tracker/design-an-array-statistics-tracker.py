from sortedcontainers import SortedList as bst

class StatisticsTracker:

    def __init__(self):
        self.a = deque()
        self.n = 0
        self.s = 0
        self.count = Counter()
        self.pq = []
        self.ss = bst()

    def addNumber(self, v) -> None:
        self.ss.add(v)
        self.count[v] += 1
        heappush(self.pq, (-self.count[v], v))
        self.s += v
        self.a.append(v)
        self.n += 1
        
    def removeFirstAddedNumber(self) -> None:
        v = self.a.popleft()
        self.ss.remove(v)
        self.count[v] -= 1
        self.s -= v
        self.n -= 1

    def getMean(self) -> int:
        return self.s // self.n

    def getMedian(self) -> int:
        return self.ss[self.n // 2]

    def getMode(self) -> int:
        while self.pq and -self.pq[0][0] != self.count[self.pq[0][1]]: heappop(self.pq)
        return self.pq[0][1]