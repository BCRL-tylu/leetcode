class Solution {
    unordered_map<string, vector<string>> reping;  // maps a recipe to its list of ingredients
    unordered_map<string, bool> sp;                  // tracks supplies and recipes that can be made
    unordered_map<string, int> state;                // 0: not visited, 1: visiting, 2: visited
    
private:
    bool dfs(const string &ing) {

        if (state[ing] == 2) return sp[ing];
        if (state[ing] == 1) return false;
        
        if (sp[ing]) {
            state[ing] = 2;
            return true;
        }
        if (reping.find(ing) == reping.end()) {
            state[ing] = 2;
            return false;
        }
        
        // Mark this ingredient as currently being visited
        state[ing] = 1;
        bool canMake = true;
        for (const auto &subIng : reping[ing]) {
            if (!dfs(subIng)) {
                canMake = false;
                break;
            }
        }
        sp[ing] = canMake;
        state[ing] = 2;
        return canMake;
    }
    
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        vector<string> ans;
        // Mark all initial supplies as available.
        for (const auto &s : supplies) {
            sp[s] = true;
        }
        // Build the dependency graph: map each recipe to its list of ingredients.
        for (int i = 0; i < recipes.size(); i++) {
            reping[recipes[i]] = ingredients[i];
        }
        for (const auto &r : recipes) {
            if (dfs(r)) {
                ans.push_back(r);
            }
        }
        return ans;
    }
};
