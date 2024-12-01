class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        short k = arr.size();
        short f,s;
        for(short i=0;i<k;i++){
            f = arr[i];
            for(short j=i+1;j<k;j++){
                s = arr[j];
                if(s==2*f||f==2*s){
                    return true;
                }
            }
        }
        return false;
    }
};