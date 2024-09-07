#include <assert.h>

#include <iostream>
#include <string>
#include <vector>

std::string Add(std::string str1, std::string str2) {
  if (!str1.size() && !str2.size()) return "0";

  int dig_1 = str1.size();
  int dig_2 = str2.size();
  int N = std::max(dig_1, dig_2);

  if (dig_1 > dig_2) {
    for (int i = 0; i < dig_1 - dig_2; i++) {
      str2.insert(0, "0");
    }
  } else if (dig_1 < dig_2) {
    for (int i = 0; i < dig_2 - dig_1; i++) {
      str1.insert(0, "0");
    }
  }

  std::string result(N, '0');
  int carry = 0;
  for (int i = N - 1; i >= 0; i--) {
    int n1 = str1[i] - '0';
    int n2 = str2[i] - '0';
    int sum = n1 + n2 + carry;
    carry = sum / 10;
    result[i] = sum % 10 + '0';
  }
  if (carry > 0) {
    result.insert(0, "1");
  }

  return result;
}

std::string Subtract(std::string str1, std::string str2) {
  if (str1 == str2) return "0";

  int dig_1 = str1.size();
  int dig_2 = str2.size();
  int N = std::max(dig_1, dig_2);

  if (dig_1 > dig_2) {
    for (int i = 0; i < dig_1 - dig_2; i++) {
      str2.insert(0, "0");
    }
  } else if (dig_1 < dig_2) {
    for (int i = 0; i < dig_2 - dig_1; i++) {
      str1.insert(0, "0");
    }
  }

  std::string result(N, '0');
  int carry = 0;
  for (int i = N - 1; i >= 0; i--) {
    int n1 = str1[i] - '0';
    int n2 = str2[i] - '0';
    int sum = n1 - n2 + carry + 10;
    carry = sum / 10 - 1;
    result[i] = sum % 10 + '0';
  }
  int idx = 0;
  while (result[idx] == '0') idx++;
  result = result.substr(idx, N - idx);

  return result;
}

std::string KaratsubaHelper(std::string str1, std::string str2, int level) {
  std::cout << "Level " << level << " : " << str1 << " x " << str2 << '\n';

  int dig_1 = str1.size();
  int dig_2 = str2.size();
  int N = std::max(dig_1, dig_2);

  if (dig_1 > dig_2) {
    for (int i = 0; i < dig_1 - dig_2; i++) {
      str2.insert(0, "0");
    }
  } else if (dig_1 < dig_2) {
    for (int i = 0; i < dig_2 - dig_1; i++) {
      str1.insert(0, "0");
    }
  }

  if (N == 1) {
    std::string result = std::to_string(stoi(str1) * stoi(str2));
    return result;
  }

  int mid = N / 2;

  std::string a = str1.substr(0, mid);
  std::string b = str1.substr(mid, N - mid);

  std::string c = str2.substr(0, mid);
  std::string d = str2.substr(mid, N - mid);

  std::string ac = KaratsubaHelper(a, c, level + 1);
  std::string bd = KaratsubaHelper(b, d, level + 1);
  std::string abcd =
      KaratsubaHelper(std::to_string(stoi(a) + stoi(b)),
                      std::to_string(stoi(c) + stoi(d)), level + 1);
  abcd = Subtract(abcd, Add(ac, bd));

  ac.append(std::string((N - mid) * 2, '0'));
  abcd.append(std::string((N - mid), '0'));
  std::string result = Add(Add(ac, bd), abcd);

  return result;
}

std::string Karatsuba(std::string str1, std::string str2) {
  if (!str1.size() && !str2.size()) return "0";

  std::string result = KaratsubaHelper(str1, str2, 0);

  int idx = 0;
  while (result[idx] == '0') idx++;
  result = result.substr(idx, result.size() - idx);

  return result;
}

int main(void) {
  std::vector<std::vector<std::string>> tests = {
      {"1234", "5678", std::to_string(1234 * 5678)},
      {"12", "34", std::to_string(12 * 34)},
      {"123", "2", std::to_string(123 * 2)},
      {"123", "45", std::to_string(123 * 45)},
      {"110", "110", std::to_string(110 * 110)},
      {"5555", "55", std::to_string(5555 * 55)},
      {"5555", "5555", std::to_string(5555 * 5555)},
      {"98234712354214154", "171454654654655",
       "16842798681791158832220782986870"}
      // , {"9823471235421415454545454545454544",
      // "1714546546546545454544548544544545",
      // "16842798681791114273590624445460185389471221520083884298838480662480"}
  };

  for (const auto& t : tests) {
    const std::string str1 = t[0];
    const std::string str2 = t[1];
    const std::string expected = t[2];

    std::cout << str1 << " * " << str2 << " = " << expected << '\n';

    const std::string result = Karatsuba(str1, str2);

    std::cout << result << " " << expected << " ";

    if (result == expected)
      std::cout << "OK";
    else {
      std::cout << "Not Ok";
      exit(-1);
    }
    std::cout << '\n' << '\n';
  }
  std::cout << "All OK!" << '\n';

  return 0;
}