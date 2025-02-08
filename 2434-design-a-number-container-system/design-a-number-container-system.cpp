class NumberContainers {
private:
    unordered_map<int, int> c; // Maps index -> number
    unordered_map<int, map<int, int>> n_i; // Maps number -> {index, dummy_value}

public:
    void change(int index, int number) {
        if (auto it = c.find(index); it != c.end()) {
            int prev = it->second;
            n_i[prev].erase(index);
            if (n_i[prev].empty()) n_i.erase(prev);
        }
        c[index] = number;
        n_i[number][index] = 1; // Store index as key (dummy value = 1)
    }

    int find(int number) {
        auto it = n_i.find(number);  // Declare `it` separately
        if (it == n_i.end() || it->second.empty()) return -1;
        return it->second.begin()->first; // Return smallest index
    }
};
