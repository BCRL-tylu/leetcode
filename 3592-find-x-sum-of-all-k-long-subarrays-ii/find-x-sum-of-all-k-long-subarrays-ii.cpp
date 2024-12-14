class Solution {
public:
  vector<long long> findXSum(vector<int>& nums, int k, int x)
  {
    auto res = vector<long long>{};
    auto top = set<array<int, 2>, std::greater<array<int, 2>>>{};
    auto bot = set<array<int, 2>, std::greater<array<int, 2>>>{};
    
    auto sum = 0ll;
    auto index = 0;
    auto table = unordered_map<int, int>{};
    for(; index < k; ++index) ++table[nums[index]];
    for(const auto& [k, f] : table) 
    {
      top.insert({f, k});
      sum += 1ll * f * k;
    }
    while(size(top) > x)
    {
      auto it = end(top);
      it = prev(it);
      sum -= 1ll * (*it)[0] * (*it)[1];
      bot.insert(*it);
      top.erase(it);
    }
    res.push_back(sum);
    
    for(; index < size(nums); ++index)
    {
      auto ori = array{table[nums[index - k]], nums[index - k]};
      if(auto it = top.find(ori); it != cend(top))
      {
        top.erase(ori);
        sum -= 1ll * ori[0] * ori[1];
      }
      if(auto it = bot.find(ori); it != cend(bot)) bot.erase(ori);
      
      ori = array{table[nums[index]], nums[index]};
      if(auto it = top.find(ori); it != cend(top))
      {
        top.erase(ori);
        sum -= 1ll * ori[0] * ori[1];
      }
      if(auto it = bot.find(ori); it != cend(bot)) bot.erase(ori);
      
      if(--table[nums[index - k]] > 0)
      {
        auto val = array{table[nums[index - k]], nums[index - k]};
        top.insert(val);
        sum += 1ll * val[0] * val[1];
      }
      
      if(++table[nums[index]] > 0)
      {
        if(nums[index - k] == nums[index])
        {
          auto val = array{table[nums[index]] - 1, nums[index]};
          top.erase(val);
          sum -= 1ll * val[0] * val[1];
        }
        auto val = array{table[nums[index]], nums[index]};
        top.insert(val);
        sum += 1ll * val[0] * val[1];
      }
      
      while(size(top) < x && size(bot) > 0)
      {
        auto it = begin(bot);
        sum += 1ll * (*it)[0] * (*it)[1];
        top.insert(*it);
        bot.erase(it);
      }
      
      while(size(top) > x)
      {
        auto it = end(top);
        it = prev(it);
        sum -= 1ll * (*it)[0] * (*it)[1];
        bot.insert(*it);
        top.erase(it);
      }
      
      auto tIt = end(top);
      tIt = prev(tIt);
      while(size(bot) > 0 && *(cbegin(bot)) > *tIt)
      {
        auto it = begin(bot);
        sum -= 1ll * (*tIt)[0] * (*tIt)[1];
        sum += 1ll * (*it)[0] * (*it)[1];
        top.insert(*it);
        bot.insert(*tIt);
        top.erase(tIt);
        bot.erase(it);
        tIt = end(top);
        tIt = prev(tIt);
      }
      res.push_back(sum);
    }
    return res;
  }
};