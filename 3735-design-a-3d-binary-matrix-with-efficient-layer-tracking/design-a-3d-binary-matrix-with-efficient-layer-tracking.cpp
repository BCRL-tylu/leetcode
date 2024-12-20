class matrix3D {
private:
    unordered_map<int, int> layer_count; // Count of 1's in each layer
    map<int, set<int>> count_content; // Counts of layers with their indices
    int size;
    bool*** matrix;

public:
    matrix3D(int n) {
        size = n;
        matrix = new bool**[size];
        for (int i = 0; i < size; ++i) {
            matrix[i] = new bool*[size];
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = new bool[size](); 
            }
        }
    }
    //~matrix3D() = default;
    void setCell(int x, int y, int z) {
        if (!matrix[x][y][z]) { // Only increment if it was previously 0
            matrix[x][y][z] = true;
            int k = layer_count[x];

            // Remove old count entry only if k > 0
            if (k > 0) {
                count_content[k].erase(x);
                if (count_content[k].empty()) {
                    count_content.erase(k);
                }
            }

            // Increment layer count and insert into count_content
            int new_k = ++layer_count[x];
            count_content[new_k].insert(x);
        }
    }

    void unsetCell(int x, int y, int z) {
        if (matrix[x][y][z]) { // Only decrement if it was previously 1
            matrix[x][y][z] = false;
            int k = layer_count[x];
            
            // Remove current count entry
            count_content[k].erase(x);
            if (count_content[k].empty()) {
                count_content.erase(k);
            }
            // Decrement layer count and check if needs to be added to count_content
            layer_count[x]--;
            if (layer_count[x] > 0) {
                count_content[layer_count[x]].insert(x);
            }
        }
    }

    int largestMatrix() {
        if (count_content.empty()) return size - 1; // if all 0 count just return the largest layer number
        auto last = count_content.rbegin();
        return *last->second.rbegin(); 
    }
};

/**
 * Your matrix3D object will be instantiated and called as such:
 * matrix3D* obj = new matrix3D(n);
 * obj->setCell(x,y,z);
 * obj->unsetCell(x,y,z);
 * int param_3 = obj->largestMatrix();
 */
