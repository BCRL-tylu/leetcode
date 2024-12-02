#define _int64 long long
_int64 d[110000][2];
vector<pair<int,int> > a[110000];
int p[110000];

class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int i,j,x,y,z,n;
        _int64 sum;
        vector<int> q;
        vector<_int64> aa;
        n=edges.size()+1;
        for (i=0;i<n;i++)
        {
            a[i].clear();
            p[i]=-1;
        }
        for (i=0;i+1<n;i++)
        {
            x=edges[i][0];
            y=edges[i][1];
            z=edges[i][2];
            a[x].push_back(make_pair(y,z));
            a[y].push_back(make_pair(x,z));
        }
        q.clear();
        q.push_back(0);
        for (i=0;i<q.size();i++)
        {
            x=q[i];
            for (j=0;j<a[x].size();j++)
            {
                y=a[x][j].first;
                if (y==p[x]) continue;
                q.push_back(y);
                p[y]=x;
            }
        }
        for (i=q.size()-1;i>=0;i--)
        {
            x=q[i];
            aa.clear();
            sum=0;
            for (j=0;j<a[x].size();j++)
            {
                y=a[x][j].first;
                if (y==p[x]) continue;
                sum+=d[y][0];
                if (d[y][1]+a[x][j].second>d[y][0])
                {
                    aa.push_back(d[y][1]+a[x][j].second-d[y][0]);
                }
            }
            sort(aa.rbegin(),aa.rend());
            for (j=0;(j+1<k)&&(j<aa.size());j++)
            {
                sum+=aa[j];
            }
            d[x][1]=sum;
            if (k-1<aa.size())
            {
                sum+=aa[k-1];
            }
            d[x][0]=sum;
        }
        return max(d[0][0],d[0][1]);
    }
};