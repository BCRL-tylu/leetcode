class Solution:
    def maximumMatchingIndices(self, a, b):
        return max(sum(a[(i+d) % len(a)] == b[i] for i in range(len(a))) for d in range(len(a)))        