#include <iostream>
#include <string>

using namespace std;

bool isRealNumber(string& str) {
  // Check if the string is empty.
  if (str.empty()) {
    return false;
  }

  string tempStr = str;

  // Check if the first character is a plus or minus sign.
  if (tempStr[0] == '+' || tempStr[0] == '-') {
    tempStr = tempStr.substr(1);
  }

  // Check if the string contains only digits and a decimal point.
  bool hasDecimal = false;
  for (int i = 0; i < tempStr.length(); i++) {
    if (!isdigit(tempStr[i]) && tempStr[i] != '.') {
      return false;
    }
    if (tempStr[i] == '.') {
      // Check for more than one decimal point.
      if (hasDecimal) {
        return false;
      }
      hasDecimal = true;
    }
  }

  return true;
}

int main() {
  string str = "+5";
  bool isReal = isRealNumber(str);

  if (isReal) {
    cout << "The string is a real number." << endl;
  } else {
    cout << "The string is not a real number." << endl;
  }

  return 0;
}
