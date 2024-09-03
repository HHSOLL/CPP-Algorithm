#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
  // 문제 1. 10진수 -> 2진수
  {
    int decimal = 105;
    string binary = ("");

    while (decimal > 0) {
      int tmp = decimal % 2;
      decimal /= 2;

      if (tmp == 1)
        binary.push_back('1');
      else
        binary.push_back('0');
    }
    std::reverse(binary.begin(), binary.end());
    cout << binary << endl;  // 1101001
  }

  // 문제 2. 문자열 뒤집기
  {
    string input = "Hello, World!";

    string result;

    for (int i = input.length() - 1; i >= 0; i--) {
      result += input[i];
    }
    cout << result << endl;  // !dlroW ,olleH
  }

  // 문제 3. 모든 자리 다 더하기
  {
    string n = "789789";

    int tmp = stoi(n);
    int sum = 0;
    while (tmp > 0) {
      sum += tmp % 10;
      tmp /= 10;
    }

    cout << sum << endl;
  }

  return 0;
}