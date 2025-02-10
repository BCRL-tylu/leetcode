class Solution {
public:
    string clearDigits(string s) {
        stack<char> c_s,d_s; //char stack, digit stack

        for(int i=0; i<(int)s.size();i++){
            if(s[i]<='9'){//number
            c_s.pop();
            }else{
               c_s.push(s[i]);
            }
        }
        string ans;
        while(!c_s.empty()){
            ans = ans+c_s.top();
            c_s.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};