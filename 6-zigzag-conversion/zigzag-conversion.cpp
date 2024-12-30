class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1){
            return s;
        }
        
        std::vector<string> vec(numRows);
        int n = s.size();
        int k =numRows-1;
        int series = 2*k;

        for(int i = 0; i<n;i++){
            int cp = i % series;
            if(cp<= k){
                vec[cp]+=s[i];
            }else{
                vec[series-cp]+=s[i];
            }
        }

        std::string result;
        for (const auto& str : vec) {
            result += str; // Append each string to the result
        }
        return result;
    }
};