
class Solution {
public:
    bool phonePrefix(vector<string>& numbers) {
        sort(numbers.begin(), numbers.end());
        for (size_t i = 0; i + 1 < numbers.size(); i++) {
            if (numbers[i+1].size() >= numbers[i].size() &&
                numbers[i+1].compare(0, numbers[i].size(), numbers[i]) == 0)
                return false;
        }
        return true;
    }
};
