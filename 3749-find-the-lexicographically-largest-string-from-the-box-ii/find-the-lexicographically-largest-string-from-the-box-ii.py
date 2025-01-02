class Solution:
    def answerString(self, word: str, numFriends: int) -> str:
        if numFriends == 1:
            return word
        
        n = len(word)
        maxSize = n - numFriends + 1

        pq = []
        
        for idx, c in enumerate(word):
            heapq.heappush(pq, (-ord(c), idx))
        
        max_char = -pq[0][0]

        ans = ""
        while pq and -pq[0][0] == max_char:
            _, idx = heapq.heappop(pq)
            ans = max(ans, word[idx:min(idx + maxSize, n + 1)])
        
        return ans