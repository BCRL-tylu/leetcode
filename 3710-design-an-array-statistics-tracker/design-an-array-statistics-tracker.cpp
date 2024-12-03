class cmp {
public:
    bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
        if (a.first != b.first) {
            return a.first < b.first;
        } else {
            return a.second > b.second;
        }
    }
};

class StatisticsTracker {
private:
    long long sum;
    deque<int> nums;
    multiset<int, greater<>> upper;             // min heap (for bigger nums)
    multiset<int> lower;                        // max heap (for smaller nums)
    unordered_map<int, int> numFreq;            // {num, freq}
    set<pair<int, int>, cmp> freqNum;           // {freq, num}

    void balanceHeaps() {
        if (upper.size() == lower.size() - 1) { // if upper over erase
            upper.insert(*prev(lower.end()));
            lower.erase(prev(lower.end()));
        }
        if (lower.size() == upper.size() - 2) { // if lower over erase
            lower.insert(*prev(upper.end()));
            upper.erase(prev(upper.end()));
        }
    }

public:
    StatisticsTracker() : sum(0) {}
    
    void addNumber(int number) {
        // maintain sum and deque
        sum += number;
        nums.push_back(number);

        // maintain freq
        int prevFreq = numFreq[number]++;
        int currFreq = prevFreq + 1;
        if (prevFreq != 0) {
            freqNum.erase({prevFreq, number});
        }
        freqNum.insert({currFreq, number});

        // maintain two heap
        upper.insert(number);
        lower.insert(*prev(upper.end()));
        upper.erase(prev(upper.end()));
        if (upper.size() < lower.size()) {
            upper.insert(*prev(lower.end()));
            lower.erase(prev(lower.end()));
        }
    }
    
    void removeFirstAddedNumber() {
        // maintain sum and deque
        int number = nums.front(); // the number to remove
        nums.pop_front();
        sum -= number;
        
        // maintain freq
        int prevFreq = numFreq[number]--;
        int currFreq = prevFreq - 1;
        freqNum.erase({prevFreq, number});
        if (currFreq != 0) {
            freqNum.insert({currFreq, number});
        } else {
            numFreq.erase(number);
        }

        // maintain two heap
        if (number >= *prev(upper.end())) {
            upper.erase(upper.find(number));
        } else {
            lower.erase(lower.find(number));
        }
        balanceHeaps();
    }
    
    int getMean() {
        return sum / nums.size();
    }
    
    int getMedian() {
        return *prev(upper.end());
    }
    
    int getMode() {
        return prev(freqNum.end())->second;
    }
};