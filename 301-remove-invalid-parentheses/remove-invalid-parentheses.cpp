class Solution {
public:
vector<string> ans;
unordered_map<string,int> map;//Just to prevent by taking duplicate string in ans
void solve(string s,int minimum_removal_allowed)
{
    if(map[s]!=0)//for checking that string is already exist in map or not
        return;
    else
        map[s]++;//when current string is not present than insert that on map
    
    if(minimum_removal_allowed==0)//when minimum removal removal that is required in given string is 0
    {
        int minimum_removal_now=getminimuminvalid(s);//here we are checking that the current string even after removal of required number of brackets is valid or not
        if(minimum_removal_now==0)//it means that the string after removal is valid, then insert that in ans
        {   
            ans.push_back(s);
        }
        return;
    }
    for(int i=0;i<s.size();i++)
    {
        string left=s.substr(0,i);//taken as it runs till (i-1) and we are skipping ith bracket
        string right=s.substr(i+1);//from i+1 to end or s.size()
        
        solve(left+right,minimum_removal_allowed-1);//calling again by combining left and right
    }
    return;
}
int getminimuminvalid(string s)
{
    stack<char>stack;
    int i=0;
    
    while(i<s.size())
    {
        if(s[i]=='(')//when "(" simply insert that on stack
            stack.push('(');
        else if(s[i]==')')//2 cases when bracket is ")"
        {
            if(stack.empty()==false && stack.top()=='(')//if top of stack is "(" then pop
            {
                stack.pop();
            }
            else
                 stack.push(')');//otherwise push on stack
        }
        i++;
    }
    return stack.size();
}
vector<string> removeInvalidParentheses(string s) 
{
    int minimum_removals=getminimuminvalid(s);
    
    solve(s,minimum_removals);
    return ans;
}
};