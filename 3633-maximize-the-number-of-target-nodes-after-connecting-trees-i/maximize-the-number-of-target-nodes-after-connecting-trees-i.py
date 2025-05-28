from bisect import bisect_right
from typing import List, Tuple

class Solution:
    def maxTargetNodes(self, edges1: List[List[int]],
                       edges2: List[List[int]],
                       k: int) -> List[int]:
        # build adjacency lists
        n = len(edges1) + 1
        m = len(edges2) + 1
        adj1 = [[] for _ in range(n)]
        adj2 = [[] for _ in range(m)]
        for u, v in edges1:
            adj1[u].append(v)
            adj1[v].append(u)
        for u, v in edges2:
            adj2[u].append(v)
            adj2[v].append(u)

        # g1[i] = # nodes in tree1 within distance ≤ k of i
        # g2[j] = # nodes in tree2 within distance ≤ k-1 of j
        g1 = self._withinDist(adj1, k)
        g2 = self._withinDist(adj2, max(0, k-1))
        M  = max(g2) if k > 0 else 0

        # answer[i] = g1[i] + M
        return [g1[i] + M for i in range(n)]

    def _withinDist(self,
                    adj: List[List[int]],
                    R: int
                   ) -> List[int]:
        """
        For each node u, computes the number of nodes within distance ≤ R
        in the tree given by adj, using centroid decomposition in O(N log^2 N).
        """
        self.adj       = adj
        self.R         = R
        N              = len(adj)
        self.blocked   = [False]*N
        self.subSize   = [0]*N
        self.layers    = [[] for _ in range(N)]      # List[List[Tuple[c,dist,comp]]]
        self.allDist   = [[] for _ in range(N)]      # distances from each centroid
        self.childDist = [[] for _ in range(N)]      # per-centroid child-subtree dists

        self._decompose(0)

        # Now answer for each u by walking its centroid-layers
        cnt = [0]*N
        for u in range(N):
            total = 0
            for c, dist, comp in self.layers[u]:
                rem = R - dist
                if rem < 0:
                    continue
                A = self.allDist[c]
                t = bisect_right(A, rem)
                if comp >= 0:
                    B = self.childDist[c][comp]
                    t -= bisect_right(B, rem)
                total += t
            cnt[u] = total
        return cnt

    def _dfsSize(self, u: int, p: int) -> int:
        """Compute subtree sizes ignoring blocked nodes."""
        self.subSize[u] = 1
        for v in self.adj[u]:
            if v != p and not self.blocked[v]:
                self.subSize[u] += self._dfsSize(v, u)
        return self.subSize[u]

    def _findCentroid(self, u: int, p: int, size: int) -> int:
        """Find centroid of the component rooted at u of total size `size`."""
        for v in self.adj[u]:
            if v != p and not self.blocked[v] and self.subSize[v]*2 > size:
                return self._findCentroid(v, u, size)
        return u

    def _dfsDist(self,
                 u: int,
                 p: int,
                 d: int,
                 c: int,
                 comp: int
                ) -> None:
        """
        From centroid c, record distance d for node u (in child-subtree comp)
        and recurse down its unblocked children.
        """
        self.layers[u].append((c, d, comp))
        self.allDist[c].append(d)
        if comp >= 0:
            self.childDist[c][comp].append(d)
        for v in self.adj[u]:
            if v != p and not self.blocked[v]:
                self._dfsDist(v, u, d+1, c, comp)

    def _decompose(self, entry: int) -> None:
        """Recursively build the centroid decomposition from `entry`."""
        size = self._dfsSize(entry, -1)
        c    = self._findCentroid(entry, -1, size)
        self.blocked[c] = True

        # 1) record the centroid itself
        self.layers[c].append((c, 0, -1))
        self.allDist[c].append(0)

        # 2) count how many child-subtrees
        comps = sum(1 for v in self.adj[c] if not self.blocked[v])
        self.childDist[c] = [[] for _ in range(comps)]

        # 3) gather distances in each child-subtree
        idx = 0
        for v in self.adj[c]:
            if not self.blocked[v]:
                self._dfsDist(v, c, 1, c, idx)
                idx += 1

        # 4) sort the collected distances for binary search
        self.allDist[c].sort()
        for sub in self.childDist[c]:
            sub.sort()

        # 5) recurse on each remaining component
        for v in self.adj[c]:
            if not self.blocked[v]:
                self._decompose(v)
