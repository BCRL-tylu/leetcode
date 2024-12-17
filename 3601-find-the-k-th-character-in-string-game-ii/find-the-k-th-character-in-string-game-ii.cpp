class Solution {
public:
    std::string shiftString(const std::string& input) {
        std::string result = input;
        for (char& ch : result) {
            ch = (ch == 'z') ? 'a' : ch + 1; // Wrap lowercase z to a
            // Non-alphabet characters remain unchanged
        }
        return result;
    }
 
    char kthCharacter(long long k, vector<int>& operations) {
        int n = operations.size();
        n = min(n,47);
        long long cp = std::pow(2, n);
        long long k_pos = k;
        string cs = "a";
        int set = std::min(n,5);
        for (int i = 0; i < set; i++) {
            if (operations[i]) {
                cs += shiftString(cs);
            } else {
                cs += cs;
            }
        }

         std::stack<int> do_operations;
        long long k_prev = k_pos;
        while (cp > 32) {
            cp /= 2;
            k_pos %= cp;
            if(k_pos ==0){
                k_pos = cp;
            }
            if(k_pos!=k_prev){
                k_prev = k_pos;
                do_operations.push(1);// meaning this operation requires to do
            }else{
                do_operations.push(0);
            }
        }

        char rt = cs[k_pos-1];
        
        for (int i = set; i < n; i++) {
            int do_oper = do_operations.top();
            do_operations.pop();
            if (operations[i] && do_oper) {
                rt = (rt == 'z') ? 'a' : rt + 1;
            } else {
                rt = rt;
            }
        }
        return rt;
    }
};