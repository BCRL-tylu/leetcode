class NumberContainers {
private:
    unordered_map<int,int> c;
    unordered_map<int, set<int>> n_i;
    
public:
    NumberContainers() {} // Properly initialize vector 'c'
    
    void change(int index, int number) {
        if (!c.count(index)) {
            n_i[number].insert(index);
            c[index] = number;
            return;
        }
        n_i[c[index]].erase(index);
        if (n_i[c[index]].empty()) { // Fix: use .empty() instead of size() == 0
            n_i.erase(c[index]);
        }
        c[index] = number;
        n_i[number].insert(index);
    }
    
    int find(int number) {
        if (!n_i.count(number)) {
            return -1;
        }
        return *n_i[number].begin();
    }
};
