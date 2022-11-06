#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string getDecimal(double number);
string eraseDecimal0(string number);
string eraseInteger0(string number);
string eraseLast0(string number);
bool findDecimal(string number);
string suffixWithUnit(double number);

string getDecimal(double number) {
  string result = "";
  number = floor(number);
  if(number < 10) {
    result = "00" + to_string(number);
  }
  else if(number < 100) {
    result = "0" + to_string(number);
  }
  else {
    result = to_string(number);
  }
  result = eraseDecimal0(result);
  return result;
}

string eraseDecimal0(string number) {
  int i = number.size() - 1;
  while(i >= 0) {
    if(number[number.size() -1] != '0') {
      i = -1;
      break;
    }
    if(number[i] != '0') break;
    if(number[i] == '0') i--;
  }
  if(i != -1) number.erase(i, number.size() - 1);
  return number;
}

string eraseInteger0(string number) {
  int i = number.size() - 1;
  while(i >= 0) {
    if(number[number.size() -1] != '0') {
      i = -1;
      break;
    }
    if(number[i] != '0') {
      i++;
      break;
    }
    if(number[i] == '0') i--;
  }
  if(i != -1) number.erase(i, number.size() - 1);
  return number;
}

string eraseLast0(string number) {
  if(findDecimal(number)) {
    int i = number.size() - 1;
    while(i >= 0) {
      if(number[number.size() -1] != '0') {
        i = -1;
        break;
      }
      if(number[i] == '.') break;
      if(number[i] != '0') {
        i++;
        break;
      } 
      if(number[i] == '0') i--;
    }
    if(i != -1) number.erase(i, number.size() - 1);
  }
  return number;
}

bool findDecimal(string number) {
  for(int i = 0; i < number.size(); i++) {
    if(number[i] == '.') return 1;
  }
  return 0;
}

string suffixWithUnit(double number) {
  int index = 0;
  double res = number;
  string decimal = "";
  double decimal_num = res - floor(res);
  decimal_num = decimal_num * 1000000;
  decimal = getDecimal(decimal_num) + decimal;
  res = floor(res);
  while(res >= 1000) {
    res = res / 1000;
    decimal_num = res - floor(res);
    decimal_num = decimal_num * 1000;
    decimal = getDecimal(decimal_num) + decimal;
    res = floor(res);
    index++;
    if(res < 1000) break;
  }
  string result = to_string(res);
  result = eraseInteger0(result);
  if(decimal != "") result += decimal;
  else result.pop_back();
  result = eraseLast0(result);
  if(index == 1) result += " Kilo";
  else if(index == 2) result += " Mega";
  else if(index == 3) result += " Giga";
  else if(index == 4) result += " Tera";
  else if(index == 5) result += " Peta";
  else if(index == 6) result += " Exa";
  return result;
}

int main() {
  cout << suffixWithUnit(123) << endl;
  cout << suffixWithUnit(1234) << endl;
  cout << suffixWithUnit(12345) << endl;
  cout << suffixWithUnit(1234567) << endl;
  cout << suffixWithUnit(12345678) << endl;
  return 0;
}