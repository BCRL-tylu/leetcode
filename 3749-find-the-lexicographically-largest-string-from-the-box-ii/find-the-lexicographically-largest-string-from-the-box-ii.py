class Solution:
    def answerString(self, word: str, numFriends: int) -> str:
        if numFriends==1:
            return word
        n = len(word)
        mx_i,offset = 0,0
        for i in range(1,n):
            v,mx_v = word[i],word[mx_i+offset]
            if v==mx_v:
                offset+=1
            elif v<mx_v:
                offset = 0
            elif v>mx_v:
                if word[i-offset]>=word[i]:
                    mx_i = i-offset
                else:
                    mx_i = i
                offset = 0
        extra = max(0,numFriends - mx_i - 1)
        if extra:
            return word[mx_i:-extra]
        return word[mx_i:]
        