class NumberContainers {
private:
    unordered_map<int, int> c; // Maps index -> number
    unordered_map<int, set<int>> n_i; // Maps number -> sorted indices

public:
    void change(int index, int number) {
        if (auto it = c.find(index); it != c.end()) {
            int prev = it->second;
            auto& indexSet = n_i[prev];
            indexSet.erase(index);
            if (indexSet.empty()) n_i.erase(prev); // Erase only if necessary
        }
        c[index] = number;
        n_i[number].insert(index); // Store index in set
    }

    int find(int number) {
        auto it = n_i.find(number);
        return (it == n_i.end() || it->second.empty()) ? -1 : *it->second.begin();
    }
};
