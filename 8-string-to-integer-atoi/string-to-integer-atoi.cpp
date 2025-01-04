class Solution {
public:
int myAtoi(string s) {
	
	long long  res = 0;
	int i = 0;
	int sign =1 ; 
	bool ignore = true; 
	while (s[i] == ' ' && i < s.size() ) {
		i++; 
	}
	if ( i< s.size() && s[i] == '+' || s[i] == '-') {
		sign = s[i] == '-' ? -1 : 1 ;
		i++;
	}
	if (i < s.size()) {
		for (int j = i;j < s.size(); j++) {
			cout << j << endl; 
			if (ignore && s[j] == '0') {
				continue; 
			}
			if (s[j] < '0' || s[j] > '9') {
				break;
			}
			else {
                ignore =  false ;
            
				res = long(s[j] - '0') +res*10;
                if (res  * sign >= INT_MAX || res *sign  <=INT_MIN) {
		        return sign >0 ? INT_MAX: INT_MIN;
	}				
			}

		}
	}
	
	return int(res * sign);



}
};
