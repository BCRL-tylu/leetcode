class Solution:
    def maxCoins(self, lane1: List[int], lane2: List[int]) -> int:
        ans = max(max(lane1), max(lane2))
        n = len(lane1)
        record = collections.defaultdict(int)
        for i in range(n):
            ans = max(ans, self.dp(i, lane1, lane2, record, n, 1, 2))
        return ans

    def dp(self, index, lane1, lane2, record, n, curr, switch):
        if (index, curr, switch) in record:
            return record[(index, curr, switch)]
        elif index == n:
            return 0
        pre = lane1[index] if curr == 1 else lane2[index]
        temp = pre

        if switch > 0:
            if curr == 1:
                temp = max(temp, \
                    self.dp(index, lane1, lane2, record, n, 2, switch - 1))
            else:
                temp = max(temp, \
                    self.dp(index, lane1, lane2, record, n, 1, switch - 1))
        
        temp = max(temp, pre + \
            self.dp(index + 1, lane1, lane2, record, n, curr, switch))
        if switch > 0:
            if curr == 1:
                temp = max(temp, \
                    pre + self.dp(index + 1, lane1, lane2, record, n, 2, switch - 1))
            else:
                temp = max(temp, \
                    pre + self.dp(index + 1, lane1, lane2, record, n, 1, switch - 1))
        
        record[(index, curr, switch)] = temp
        
        return record[(index, curr, switch)]
            