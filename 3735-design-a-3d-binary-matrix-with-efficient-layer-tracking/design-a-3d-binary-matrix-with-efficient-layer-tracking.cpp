class matrix3D {
    vector<vector<vector<int>>> v;
    vector<int> c;
    map<int, set<int>> f;
public:
    matrix3D(int n) : v(vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(n)))),
    c(vector<int>(n)) {
        for (int i = 0; i < n; ++i) {
            f[0].insert(i);
        }
    }
    
    void setCell(int x, int y, int z) {
        if (v[x][y][z] == 1) return;;
        v[x][y][z] = 1;
        f[c[x]].erase(x);
        if (f[c[x]].empty()) {
            f.erase(c[x]);
        }
        f[++c[x]].insert(x);
    }
    
    void unsetCell(int x, int y, int z) {
        if (v[x][y][z] == 0) return;
        v[x][y][z] = 0;
        f[c[x]].erase(x);
        if (f[c[x]].empty()) {
            f.erase(c[x]);
        }
        f[--c[x]].insert(x);
    }
    
    int largestMatrix() {
        return *f.rbegin()->second.rbegin();
    }
};

/**
 * Your matrix3D object will be instantiated and called as such:
 * matrix3D* obj = new matrix3D(n);
 * obj->setCell(x,y,z);
 * obj->unsetCell(x,y,z);
 * int param_3 = obj->largestMatrix();
 */