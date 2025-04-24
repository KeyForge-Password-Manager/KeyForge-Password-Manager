#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>


#include <chrono>
#include <thread>//	std::this_thread::sleep_for(std::chrono::milliseconds(10000));



using namespace std;

class Color {
public:
	/*Color rr;	cout << rr.magenta("red") << "  " << rr.cyan("blue") <<"  "<<rr.grey("grey")<< endl;*/
	string black(string str) {
		str = "\033[30m" + str + "\033[0m";
		return str;
	}
	string red(string str) {
		str = "\033[31m" + str + "\033[0m";
		return str;
	}
	string green(string str) {
		str = "\033[32m" + str + "\033[0m";
		return str;
	}
	string yellow(string str) {
		str = "\x1b[33m" + str + "\x1b[0m";
		return str;
	}
	string blue(string str) {
		str = "\x1b[34m" + str + "\x1b[0m";
		return str;
	}
	string magenta(string str) {
		str = "\033[35m" + str + "\033[0m";
		return str;
	}
	string cyan(string str) {
		str = "\033[36m" + str + "\033[0m";
		return str;
	}
	/*???*/string grey(string str) {
		str = "\033[37m" + str + "\033[0m";
		return str;
	}
};
Color rr;


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

void norm_string(string& pass) {
	for (int i = 0; i < pass.size(); i += 2) {
		if (pass[i] == pass[i + 1]) {
			pass.insert(i + 1, "X");
		}
	}
	//if (pass.size() % 2 == 1)pass += 'X';
}
void norm_ans(string& s2){
	for (int i = 0; i < s2.size(); i++) {
		if (s2[i] == 'X') {
			if (s2[i - 1] == s2[i + 1]) s2.erase(s2.begin() + i);
		}
	}
}

string read(string company) {
	string ans="";
	string line;
	ifstream in("Storage.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			bool similar = true;
			for (int i = 0; i < company.size(); i++) {
				if (company[i] != line[i])similar = false;
			}
			string p = "";
			for (int i = line.find(' ')+1; i < line.size(); i++)p += line[i];
			if (similar) ans += p+=" ";
		}
	}
	in.close();
	return ans;
}
void addf(string company, string pass) {
	ofstream out;
	out.open("Storage.txt", ios::app);
	if (out.is_open())
	{
		string r = read(company);
		if (r == "") {
			out << company << " " << pass << endl;
		}
		else {
			cout << "этот сайт(приложение) ранее уже был введён. Хотите заменить пароль(введите 1) или создать ещё один(введите 2)?"<<endl;
			int inp; cin >> inp;
			if(inp==2)out << company << " " << pass << endl;
			if(inp==1) {
				
				ofstream out2;
				out2.open("temp.txt");
				string line2;
				ifstream in2("Storage.txt");
				if (in2.is_open())
				{
					while (getline(in2, line2))
					{
						bool similar = true;
						for (int i = 0; i < company.size(); i++) {
							if (company[i] != line2[i])similar = false;
						}
						if (!similar)
							out2 << line2 << endl;
						else {
							cout << line2 << endl;
							cout << "Если хотите оставить этот пароль, нажмите " << rr.blue("1") << endl <<
								    "Если хотите удалить его, нажмите " << rr.red("2") << endl;
							int inp; cin >> inp;
							if (inp == 1)out2 << line2 << endl;
						}
					}
				}
				in2.close();
				out2.close();

				ofstream out3;
				out3.open("Storage.txt");
				string line3;
				ifstream in3("temp.txt");
				if (in3.is_open())
				{
					while (getline(in3, line3))
					{
						out3 <<line3 << endl;
					}
				}
				out3 << company << " " << pass << endl;
				in3.close();
				out3.close();
			}
		}
	}
	out.close();
}

string encryption(string pass, string key){
	string ans;
	ans = Playfer(pass, key);
	ans=Vigenere(ans, key);
	return ans;
}
string decryption(string pass, string key){
	string ans;
	ans = Vigenere_obr(pass, key);
	ans = Playfer_obr(ans, key);
	return ans;
}
void read_all_file(string key) {
	string line;
	ifstream in("Storage.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			string company = ""; string pass = "";
			for (int i = 0; i < line.find(" "); i++)company += line[i];
			for (int i = line.find(" ") + 1; i < line.size(); i++)pass += line[i];
			cout << setw(15)<<left<< company << " "<< decryption(pass,key)<< endl;
		}
	}
	in.close();
}
int count_str_in_file(string key) {
	int n = 0;
	string line;
	ifstream in("Storage.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			string company = ""; string pass = "";
			for (int i = 0; i < line.find(" "); i++)company += line[i];
			for (int i = line.find(" ") + 1; i < line.size(); i++)pass += line[i];
			n++;
		}
	}
	in.close();
	return n;
}
