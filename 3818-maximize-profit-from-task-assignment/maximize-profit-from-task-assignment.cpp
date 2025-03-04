class Solution 
{
	public:
    long long maxProfit(vector<int>& workers, vector<vector<int>>& tasks) 
	{
		long long result=0,maximum=0,m=workers.size(),n=tasks.size();
		unordered_map<int,int> total;
		sort(tasks.begin(),tasks.end(),[](vector<int>& a,vector<int>& b){
			if(a[0]!=b[0]) return a[0]<b[0];
			return a[1]>b[1];
		});
		for(int i=0;i<m;i++) total[workers[i]]++;
		for(int i=0;i<n;i++)
		{
			if(total.count(tasks[i][0]))
			{
				result+=tasks[i][1];
				total[tasks[i][0]]--;
				if(total[tasks[i][0]]==0) total.erase(tasks[i][0]);
			}
			else maximum=max(maximum,1ll*tasks[i][1]);
		}
		return result+maximum;
    }
};