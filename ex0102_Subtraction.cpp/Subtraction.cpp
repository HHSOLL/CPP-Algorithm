#include <iostream>
#include <string>
#include <vector>

using namespace std;

string Subtract(string str1, string str2) {
  if (str1 == str2) return "0";

  int digit_1 = str1.size(), digit_2 = str2.size();
  if (digit_1 > digit_2) {
    for (int i = 0; i < digit_1 - digit_2; i++) str2.insert(0, "0");
  } else if (digit_1 < digit_2) {
    for (int i = 0; i < digit_2 - digit_1; i++) str1.insert(0, "0");
  }

  string result(str1.size(), '0');
  int carry = 0;

  cout << '\n' << str1 << '\n' << str2 << '\n';
  cout << "--------------------";
  cout << '\n';

  for (int i = str1.size() - 1; i >= 0; i--) {
    int n1 = int(str1[i] - '0');
    int n2 = int(str2[i] - '0');

    int tmp = 0;
    if (n1 - n2 - carry < 0) {
      tmp = 10 + n1 - n2;
      result[i] = (tmp - carry) % 10 + '0';
      carry = 1;
    } else if (n1 - n2 - carry >= 0) {
      tmp = n1 - n2;
      result[i] = (tmp - carry) % 10 + '0';
      carry = 0;
    }
  }
  //   if (carry == 1) {
  //     result.erase(0, 1);
  //   }
  if (result[0] == '0') result.erase(0, 1);
  return result;
}

int main(void) {
  // 항상 큰 수에서 작은 수를 빼는 경우(결과가 음수가 되지 않는 경우)를 가정
  vector<vector<string>> tests = {
      //   {"34", "12", std::to_string(34 - 12)},
      {"123", "45", std::to_string(123 - 45)},
      {"54544", "44545", std::to_string(54544 - 44545)},
      {"5555", "55", std::to_string(5555 - 55)},
      {"5555", "5555", std::to_string(5555 - 5555)},
      {"9823471235421415454545454545454544",
       "1714546546546545454544548544544545",
       "8108924688874870000000906000909999"}};

  for (const auto& t : tests) {
    const string str1 = t[0];
    const string str2 = t[1];
    const string expected = t[2];

    cout << str1 << " - " << str2 << " = " << expected << endl;

    const string result = Subtract(str1, str2);

    cout << result << " " << expected << " ";

    if (result == expected)
      cout << "OK";
    else {
      cout << "Not OK" << endl;
      exit(-1);
    }
    cout << endl << endl;
  }

  cout << "Congratulations. All OK!" << endl;

  return 0;
}