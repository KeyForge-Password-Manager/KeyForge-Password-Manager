#include <iostream>
#include <string>
#include <vector>
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


bool is_elem_in(char a, vector<vector<char>>& finall) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (finall[i][j] == a)return true;
		}
	}
	return false;
}

string Playfer(string pass, string key) {
	string ans = "";
	vector<vector<char>> all = {// {} [] \|/ ' " ` ; 
		{'Q', 'q', 'W', 'w', 'E', 'e', 'R', 'r', 'T'},
		{'t', 'Y', 'y', 'U', 'u', 'I', 'i', 'O', 'o'},
		{'P', 'p', 'A', 'a', 'S', 's', 'D', 'd', 'F'},
		{'f', 'G', 'g', 'H', 'h', 'J', 'j', 'K', 'k'},
		{'L', 'l', 'Z', 'z', 'X', 'x', 'C', 'c', 'V'},
		{'v', 'B', 'b', 'N', 'n', 'M', 'm', '0', '1'},
		{'2', '3', '4', '5', '6', '7', '8', '9', '_'},
		{'!', '@', '#', '$', '%', '^', '&', '*', '-'},
		{'+', '=', '.', ':', '?', '№', '~', '<', '>'}
	};
	vector<vector<char>> all2 = {
		{'Q', 'q', 'W', 'w', 'E', 'e', 'R', 'r', 'T'},
		{'t', 'Y', 'y', 'U', 'u', 'I', 'i', 'O', 'o'},
		{'P', 'p', 'A', 'a', 'S', 's', 'D', 'd', 'F'},
		{'f', 'G', 'g', 'H', 'h', 'J', 'j', 'K', 'k'},
		{'L', 'l', 'Z', 'z', 'X', 'x', 'C', 'c', 'V'},
		{'v', 'B', 'b', 'N', 'n', 'M', 'm', '0', '1'},
		{'2', '3', '4', '5', '6', '7', '8', '9', '_'},
		{'!', '@', '#', '$', '%', '^', '&', '*', '-'},
		{'+', '=', '.', ':', '?', '№', '~', '<', '>'}
	};
	vector<vector<char>> finall = {
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	};
	

	int jj = 0; int ii = 0;
	for (int i = 0; i < key.size(); i++) {
		if (!is_elem_in(key[i], finall)) {
			finall[jj][ii % 9] = key[i];
			ii++;
			if (ii % 9 == 0)jj++;
			for (int all2i = 0; all2i < 9; all2i++) {
				for (int all2j = 0; all2j < 9; all2j++) {
					if (all2[all2i][all2j] == key[i]) all2[all2i][all2j] = ' ';
				}
			}
		}
	}
	

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (all2[i][j] != ' ') {
				finall[jj][ii % 9] = all2[i][j];
				ii++;
				if (ii % 9 == 0)jj++;
			}
		}
	}


	//таблица из пароля создана, нужно шифровать
	for (int i = 0; i < (pass.size()/2)*2; i=i+2) {
		bool done = false;
		//в одной строке
		if (!done) {
			for (int str = 0; str < 9; str++) {
				int num1 = -1; int num2 = -1;
				for (int j = 0; j < 9; j++) {
					if (pass[i] == finall[str][j]) num1 = j;
					if (pass[i + 1] == finall[str][j]) num2 = j;
				}
				if (num1 != -1 && num2 != -1) {
					num1 = (num1 + 1) % 9;
					num2 = (num2 + 1) % 9;
					ans += finall[str][num1];
					ans += finall[str][num2];
					done=true;
				}
			}
		}

		//в одном столбце
		if (!done) {
			for (int stol = 0; stol < 9; stol++) {
				int num1 = -1; int num2 = -1;
				for (int j = 0; j < 9; j++) {
					if (pass[i] == finall[j][stol]) num1 = j;
					if (pass[i + 1] == finall[j][stol]) num2 = j;
				}
				if (num1 != -1 && num2 != -1) {
					num1 = (num1 + 1) % 9;
					num2 = (num2 + 1) % 9;
					ans += finall[num1][stol];
					ans += finall[num2][stol];
					done = true;
				}
			}
		}

		//разные строки и столбцы
		if (!done) {
			int el1_i = -1; int el1_j = -1;
			int el2_i = -1; int el2_j = -1;
			for (int ipr = 0; ipr < 9; ipr++) {
				for (int jpr = 0; jpr < 9; jpr++) {
					if (finall[ipr][jpr] == pass[i]) {
						el1_i = ipr;
						el1_j = jpr;
					}
					if (finall[ipr][jpr] == pass[i + 1]) {
						el2_i = ipr;
						el2_j = jpr;
					}
				}
			}
			if (el1_i != -1 && el1_j != -1 && el2_i != -1 && el2_j != -1) {
				swap(el1_j, el2_j);
				ans += finall[el1_i][el1_j];
				ans += finall[el2_i][el2_j];
				done = true;
			}
		}
	}
	if (pass.size() % 2 == 1)ans += pass[pass.size()-1];

	return ans;
}
string Playfer_obr(string pass, string key) {
	string ans = "";
	vector<vector<char>> all = {// {} [] \|/ ' " ` ; 
		{'Q', 'q', 'W', 'w', 'E', 'e', 'R', 'r', 'T'},
		{'t', 'Y', 'y', 'U', 'u', 'I', 'i', 'O', 'o'},
		{'P', 'p', 'A', 'a', 'S', 's', 'D', 'd', 'F'},
		{'f', 'G', 'g', 'H', 'h', 'J', 'j', 'K', 'k'},
		{'L', 'l', 'Z', 'z', 'X', 'x', 'C', 'c', 'V'},
		{'v', 'B', 'b', 'N', 'n', 'M', 'm', '0', '1'},
		{'2', '3', '4', '5', '6', '7', '8', '9', '_'},
		{'!', '@', '#', '$', '%', '^', '&', '*', '-'},
		{'+', '=', '.', ':', '?', '№', '~', '<', '>'}
	};
	vector<vector<char>> all2 = {
		{'Q', 'q', 'W', 'w', 'E', 'e', 'R', 'r', 'T'},
		{'t', 'Y', 'y', 'U', 'u', 'I', 'i', 'O', 'o'},
		{'P', 'p', 'A', 'a', 'S', 's', 'D', 'd', 'F'},
		{'f', 'G', 'g', 'H', 'h', 'J', 'j', 'K', 'k'},
		{'L', 'l', 'Z', 'z', 'X', 'x', 'C', 'c', 'V'},
		{'v', 'B', 'b', 'N', 'n', 'M', 'm', '0', '1'},
		{'2', '3', '4', '5', '6', '7', '8', '9', '_'},
		{'!', '@', '#', '$', '%', '^', '&', '*', '-'},
		{'+', '=', '.', ':', '?', '№', '~', '<', '>'}
	};
	vector<vector<char>> finall = {
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	};


	int jj = 0; int ii = 0;
	for (int i = 0; i < key.size(); i++) {
		if (!is_elem_in(key[i], finall)) {
			finall[jj][ii % 9] = key[i];
			ii++;
			if (ii % 9 == 0)jj++;
			for (int all2i = 0; all2i < 9; all2i++) {
				for (int all2j = 0; all2j < 9; all2j++) {
					if (all2[all2i][all2j] == key[i]) all2[all2i][all2j] = ' ';
				}
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (all2[i][j] != ' ') {
				finall[jj][ii % 9] = all2[i][j];
				ii++;
				if (ii % 9 == 0)jj++;
			}
		}
	}


	//таблица из пароля создана, нужно шифровать
	for (int i = 0; i < (pass.size() / 2) * 2; i = i + 2) {
		bool done = false;
		//в одной строке
		if (!done) {
			for (int str = 0; str < 9; str++) {
				int num1 = -1; int num2 = -1;
				for (int j = 0; j < 9; j++) {
					if (pass[i] == finall[str][j]) num1 = j;
					if (pass[i + 1] == finall[str][j]) num2 = j;
				}
				if (num1 != -1 && num2 != -1) {
					num1 = (num1 - 1 +9) % 9;
					num2 = (num2 - 1 +9) % 9;
					ans += finall[str][num1];
					ans += finall[str][num2];
					done = true;
				}
			}
		}

		//в одном столбце
		if (!done) {
			for (int stol = 0; stol < 9; stol++) {
				int num1 = -1; int num2 = -1;
				for (int j = 0; j < 9; j++) {
					if (pass[i] == finall[j][stol]) num1 = j;
					if (pass[i + 1] == finall[j][stol]) num2 = j;
				}
				if (num1 != -1 && num2 != -1) {
					num1 = (num1 - 1) % 9;
					num2 = (num2 - 1) % 9;
					ans += finall[num1][stol];
					ans += finall[num2][stol];
					done = true;
				}
			}
		}

		//разные строки и столбцы
		if (!done) {
			int el1_i = -1; int el1_j = -1;
			int el2_i = -1; int el2_j = -1;
			for (int ipr = 0; ipr < 9; ipr++) {
				for (int jpr = 0; jpr < 9; jpr++) {
					if (finall[ipr][jpr] == pass[i]) {
						el1_i = ipr;
						el1_j = jpr;
					}
					if (finall[ipr][jpr] == pass[i + 1]) {
						el2_i = ipr;
						el2_j = jpr;
					}
				}
			}
			if (el1_i != -1 && el1_j != -1 && el2_i != -1 && el2_j != -1) {
				swap(el1_j, el2_j);
				ans += finall[el1_i][el1_j];
				ans += finall[el2_i][el2_j];
				done = true;
			}
		}
	}
	if (pass.size() % 2 == 1)ans += pass[pass.size() - 1];

	return ans;
}

int main(){
  return 0;
}
