#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::string Add(std::string str1, std::string str2) {
  int digit_1 = str1.length(), digit_2 = str2.length();
  if (digit_1 > digit_2) {
    int digit = digit_1 - digit_2;
    for (int i = 0; i < digit; i++) str2.insert(0, "0");
  } else if (digit_1 < digit_2) {
    int digit = digit_2 - digit_1;
    for (int i = 0; i < digit; i++) str1.insert(0, "0");
  }

  int index = max(str1.size(), str2.size()) - 1;

  std::string result(index + 1, '0');
  int carry = 0;

  cout << '\n' << str1 << '\n' << str2 << '\n';
  cout << "--------------------";
  cout << '\n';

  for (int i = index; i >= 0; i--) {
    int n1 = int(str1[i] - '0');
    int n2 = int(str2[i] - '0');

    result[i] = (n1 + n2 + carry) % 10 + '0';

    if (n1 + n2 + carry >= 10)
      carry = 1;
    else
      carry = 0;

    cout << result << '\n';
  }
  if (carry == 1) result.insert(0, "1");

  return result;
}

int main(void) {
  vector<vector<string>> tests = {{"12", "34", to_string(12 + 34)},
                                  {"123", "45", to_string(123 + 45)},
                                  {"54544", "44545", to_string(54544 + 44545)},
                                  {"5555", "55", to_string(5555 + 55)},
                                  {"5555", "5555", to_string(5555 + 5555)},
                                  {"9823471235421415454545454545454544",
                                   "1714546546546545454544548544544545",
                                   "11538017781967960909090003089999089"}};

  for (const auto& t : tests) {
    const string str1 = t[0];      // "12"
    const string str2 = t[1];      // "34"
    const string expected = t[2];  // "46"

    cout << str1 << " + " << str2 << " = " << expected << endl;

    const string result = Add(str1, str2);

    cout << result << " " << expected << " ";

    if (result == expected)
      cout << "OK" << endl;
    else {
      cout << "Not OK" << endl;
      exit(-1);
    }
    cout << endl << endl;
  }

  cout << "Congratulations. All OK!" << endl;

  return 0;
}