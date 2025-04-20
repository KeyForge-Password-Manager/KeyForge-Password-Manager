#include <iostream>
using namespace std;

string Vigenere(string pass, string key) {
	string ans = "";
	for (int i = 0; i < pass.size(); i++) {
		ans += pass[i] + (int)key[i % key.size()];
	}

	return ans;
}
string Vigenere_obr(string pass, string key) {
	string ans = "";
	for (int i = 0; i < pass.size(); i++) {
		ans += pass[i] - (int)key[i % key.size()];
	}

	return ans;
}

int main(){
  return 0;
}
