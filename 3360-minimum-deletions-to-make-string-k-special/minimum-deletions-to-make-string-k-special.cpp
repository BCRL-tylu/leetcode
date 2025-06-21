class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> freq(26);
        int ans =INT_MAX,mc=0,mmc=INT_MAX;
        for(auto w:word){
            freq[w-'a']++;
        }
        sort(freq.begin(),freq.end());
        vector<vector<pair<int,int>>> dp(26); // base cost
        dp[0] = {{freq[0],0},{freq[1],freq[0]}};
        for(int i = 1;i<26;i++){
            for(auto [b,c]:dp[i-1]){
                dp[i].push_back({b,c+max(freq[i]-b-k,0)});
            }
            pair<int,int> end = *dp[i-1].rbegin();
            if(i<25) dp[i].push_back({freq[i+1],end.second+freq[i]});
        }
        for(auto [b,c]:dp[25]){
            ans = min(ans,c);
        }
        return ans;
    }
};