#include <iostream>
#include <string>
#include <vector>

using namespace std;

string Multiply(string str1, string str2) {
  int digit_1 = str1.size();
  int digit_2 = str2.size();
  int M = max(digit_1, digit_2);

  if (digit_1 > digit_2) {
    for (int i = 0; i < digit_1 - digit_2; i++) {
      str2.insert(0, "0");
    }
  } else if (digit_1 < digit_2) {
    for (int i = 0; i < digit_2 - digit_1; i++) {
      str1.insert(0, "0");
    }
  }

  string result(2 * M, '0');

  for (int i = M - 1; i >= 0; i--) {
    int carry = 0;
    int n1 = str1[i] - '0';
    int k = M + i;
    for (int j = M - 1; j >= 0; j--) {
      int n2 = str2[j] - '0';

      int val = (n1 * n2 + carry);
      int tmp = val % 10;

      if ((val + (result[k] - '0')) >= 10)
        carry = (val + (result[k] - '0')) / 10;
      else
        carry = 0;

      result[k] = ((tmp + (result[k] - '0')) % 10) + '0';

      k--;
    }
    result[k] = carry + '0';
  }
  for (int i = 0; i < M * 2; i++) {
    if (result[0] == '0') {
      result.erase(0, 1);
      continue;
    }
    if (result[0] != '0') break;
  }
  return result;
}

int main() {
  vector<vector<string>> tests = {
      {"12", "34", std::to_string(12 * 34)},
      {"123", "45", std::to_string(123 * 45)},
      {"5555", "55", std::to_string(5555 * 55)},
      {"5555", "5555", std::to_string(5555 * 5555)},
      {"98234712354214154", "171454654654655",
       "16842798681791158832220782986870"},
      {"9823471235421415454545454545454544",
       "1714546546546545454544548544544545",
       "16842798681791114273590624445460185389471221520083884298838480662480"}};

  for (const auto& t : tests) {
    const string str1 = t[0];
    const string str2 = t[1];
    const string expected = t[2];

    cout << str1 << " * " << str2 << " = " << expected << endl;

    const string result = Multiply(str1, str2);

    cout << result << " " << expected << " ";

    if (result == expected)
      cout << "OK";
    else {
      cout << "Not OK";
      exit(-1);
    }
    cout << endl << endl;
  }

  cout << "Congratulations. All OK!" << endl;

  return 0;
}