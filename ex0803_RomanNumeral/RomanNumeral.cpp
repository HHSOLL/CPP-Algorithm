#include <iostream>
#include <string>
#include <unordered_map>

class Solution {
 public:
  int romanToInt(std::string s) {
    std::unordered_map<char, int> m;
    m['I'] = 1;
    m['V'] = 5;
    m['X'] = 10;
    m['L'] = 50;
    m['C'] = 100;
    m['D'] = 500;
    m['M'] = 1000;

    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
      auto val = m.find(s[i]);

      if (i + 1 < s.length() && val != m.end() && m.find(s[i + 1]) != m.end() &&
          m.find(s[i + 1])->second > val->second) {
        ans += (m.find(s[i + 1])->second - val->second);
        i++;
      } else
        ans += val->second;
    }

    return ans;
  }
};

int main(void) {
  Solution s;
  std::string str;

  std::cin >> str;
  std::cout << s.romanToInt(str) << '\n';

  return 0;
}