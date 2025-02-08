class NumberContainers {
public:
    unordered_map<int,priority_queue<int,vector<int>,greater<int>>>m;
    unordered_map<int,int>m1;
    NumberContainers() {
        
    }
    
    void change(int i, int n) {
        m1[i]=n;
        m[n].push(i);
    }
    
    int find(int n) {
        while(!m[n].empty() && m1[m[n].top()]!=n){
            m[n].pop();
        }
        if(m[n].empty()) return -1;
        return m[n].top();
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */