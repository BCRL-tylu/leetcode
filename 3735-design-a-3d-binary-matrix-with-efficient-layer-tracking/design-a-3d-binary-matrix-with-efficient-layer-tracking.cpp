#include <unordered_map>
#include <map>
#include <set>
using namespace std;

class matrix3D {
private:
    unordered_map<int, int> layer_count; // Count of 1's in each layer
    map<int, set<int>> count_content; // counts of layers with their indices
    int size;

public:
    bool*** matrix;

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

    ~matrix3D() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                delete[] matrix[i][j];
            }
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void setCell(int x, int y, int z) {
        if (!matrix[x][y][z]) { // Only increment if it was previously 0
            matrix[x][y][z] = true;
            int k = layer_count[x];
            if (k > 0) {
                count_content[k].erase(x);
                if(count_content[k].empty()){
                count_content.erase(k);
                }
            }
            count_content[++layer_count[x]].insert(x);
        }
    }

    void unsetCell(int x, int y, int z) {
        if (matrix[x][y][z]) { // Only decrement if it was previously 1
            matrix[x][y][z] = false;
            int k = layer_count[x];
            count_content[k].erase(x);
            if(count_content[k].empty()){
                count_content.erase(k);
            }
            layer_count[x]--;
            if (layer_count[x] > 0) {
                count_content[layer_count[x]].insert(x);
            }
        }
    }

    int largestMatrix() {
        if (count_content.empty()) return size-1; //
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
