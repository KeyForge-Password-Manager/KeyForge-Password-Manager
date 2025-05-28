#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <thread>//	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

#include <Windows.h>
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
void CopyToClipboard(const std::string& text) {
	// Открываем буфер обмена
	if (OpenClipboard(nullptr)) {
		// Очищаем буфер
		EmptyClipboard();

		// Выделяем память под текст (включая нулевой символ)
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
		if (hMem != nullptr) {
			// Копируем текст в выделенную память
			char* pMem = static_cast<char*>(GlobalLock(hMem));
			strcpy_s(pMem, text.size() + 1, text.c_str());
			GlobalUnlock(hMem);

			// Помещаем текст в буфер обмена
			SetClipboardData(CF_TEXT, hMem);
		}

		// Закрываем буфер обмена
		CloseClipboard();
	}
}


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

/*void norm_string(string& pass) {
	for (int i = 0; i < pass.size(); i += 2) {
		if (pass[i] == pass[i + 1]) {
			pass.insert(i + 1, "X");
		}
	}
	//if (pass.size() % 2 == 1)pass += 'X';
}*/
/*void norm_ans(string& s2) {
	for (int i = 0; i < s2.size(); i++) {
		if (s2[i] == 'X') {
			if (s2[i - 1] == s2[i + 1]) s2.erase(s2.begin() + i);
		}
	}
}*/

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
string encryption(string pass, string key);
string decryption(string pass, string key);
void addf(string company, string pass, string key) {
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
						string comp = "";
						for (int i = 0; i < line2.find(' '); i++)comp += line2[i];
						string p = "";
						for (int i = line2.find(' ') + 1; i < line2.size(); i++)p += line2[i];
						if (!similar)
							out2 << comp<<" "<<p << endl;
						else {
							cout << comp << " " << decryption(p, key) << endl;
							cout << "Если хотите оставить этот пароль, нажмите " << rr.blue("1") << endl <<
								    "Если хотите удалить его, нажмите " << rr.red("2") << endl;
							int inp; cin >> inp;
							if (inp == 1)out2 << comp << " " << p << endl;
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

int is_user(string user_key) {
	cout <<
		"Если хотите посмотреть пароли, введите " << rr.magenta("1") << "." << endl <<
		"Если хотите добавить пароль, введите " << rr.cyan("2") << "." << endl <<
		"Чтобы проверить пароли на надёжность, нажмите " << rr.green("3") << endl<<
		"Для выхода из приложения введите " << rr.red("0")<<endl;
	int inp;
	cin >> inp;
	system("cls");
	if (inp == 1) { 
		read_all_file(user_key); 
		cout << "если хотите запустить поиск, нажмите "<<rr.green("1") << endl;
		cout << "если хотите скопировать пароль в буфер обмена, нажмите " << rr.yellow("2") <<" а затем введите номер строки с нужным аккаунтом и паролем" << endl;
		cout << "для выхода в меню нажмите " << rr.red("0") << endl;
		int exit1; cin >> exit1;
		if(exit1==0)system("cls");
		else if(exit1==1){
			system("cls");
			string input_f = "";
			cout << "Введите букву или слово, которое хотите найти" << endl;
			cin >> input_f;
			string line;
			ifstream in("Storage.txt");
			if (in.is_open())
			{
				while (getline(in, line))
				{
					string company = ""; string pass = "";
					for (int i = 0; i < line.find(" "); i++)company += line[i];
					for (int i = line.find(" ") + 1; i < line.size(); i++)pass += line[i];
					if (company.find(input_f) != string::npos) {
						cout << setw(15) << left << company << " " << decryption(pass, user_key) << endl;
					}
				}
			}
			in.close();
			cout << "для выхода в меню нажмите " << rr.red("0") << endl;
			int exit1; cin >> exit1; system("cls");
		}
		else {
			system("cls");
			int n = 1;
			string line;
			ifstream in("Storage.txt");
			if (in.is_open())
			{
				while (getline(in, line))
				{
					string company = ""; string pass = "";
					for (int i = 0; i < line.find(" "); i++)company += line[i];
					for (int i = line.find(" ") + 1; i < line.size(); i++)pass += line[i];
					cout << rr.cyan(to_string(n))<<"  "<<setw(15) << left << company << " " << decryption(pass, user_key) << endl;
					n++;
				}
			}
			in.close();
			int input_num; cin >> input_num;

			n = 1;
			string line1;
			ifstream in1("Storage.txt");
			if (in1.is_open())
			{
				while (getline(in1, line1))
				{
					string company = ""; string pass = "";
					for (int i = 0; i < line1.find(" "); i++)company += line1[i];
					for (int i = line1.find(" ") + 1; i < line1.size(); i++)pass += line1[i];
					if (n == input_num) CopyToClipboard(decryption(pass, user_key));
					//cout << rr.cyan(n) << "  " << setw(15) << left << company << " " << decryption(pass, key) << endl;
					n++;
				}
			}
			in1.close();
		}
	}
	else if (inp == 2) {
		cout << "Введите название сайта/приложения латиницей" << endl;
		string company = "";
		getline(cin, company);
		if (company == "")getline(cin, company);
		while (company.find(" ") != string::npos)
			company[company.find(" ")] = '_';

		cout << "введите пароль" << endl;
		string pass = ""; cin >> pass;
		pass = encryption(pass, user_key);
		addf(company, pass, user_key);
		system("cls");
	}
	else if (inp == 3) {
		bool ok = true;
		int worth_pass;
		long worth_val = 1215752191;
		int n = count_str_in_file(user_key);
		vector<string> list(n);

		string line;
		n = 0;
		ifstream in("Storage.txt");
		if (in.is_open()){
			while (getline(in, line)) {
				string company = ""; string pass = "";
				for (int i = 0; i < line.find(" "); i++)company += line[i];
				for (int i = line.find(" ") + 1; i < line.size(); i++)pass += line[i];
				list[n] = decryption(pass, user_key); 

				long ans_pass = 0;
				string s = list[n];
				vector<char> all = {'a', 'b','c','d','e','f','g','h','i','j','k','l','m','n', 'o', 'p' , 'q', 'r', 's', 't','u', 'v', 'w', 'x', 'y', 'z'};
				for (int i = 0; i < s.size(); i++) {
					for (int j = 0; j < 26; j++)
						if (s[i] == all[j]) ans_pass += (j + 1) * pow(26, i);
				}
				//cout << list[n] << " " << ans_pass << endl;
				if (ans_pass < worth_val) worth_pass = n;

				for(int i=0; i<list[n].size(); i++)list[n][i]= (char)std::tolower(list[n][i]);
				n++;
			}
		}
		in.close();

		
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				if (list[i].find(list[j]) != std::string::npos ) {
					ok = false;
					cout << "Эти пароли похожи, лучше заменить один из них:" << endl;
					
					string line2;
					n = 0;
					ifstream in2("Storage.txt");
					if (in2.is_open()) {
						while (getline(in2, line2)) {
							string company2 = ""; string pass2 = "";
							for (int i = 0; i < line2.find(" "); i++)company2 += line2[i];
							for (int i = line2.find(" ") + 1; i < line2.size(); i++)pass2 += line2[i];
							pass2 = decryption(pass2, user_key);
							if (n == i || n==j)cout << company2<<" "<< pass2<< endl;
							n++;
						}
					}
					in2.close();

					cout <<endl<< "А так же слабейшим паролем является " << list[worth_pass]<<endl;
					cout << "чтобы продолжить, нажмите любую цифру" << endl;
					int qq; cin >> qq;
					system("cls");
				}
			}
		}
		if (ok) {
			cout << "Всё в порядке." << endl;
			cout << "чтобы продолжить, нажмите любую цифру" << endl;
			int qq; cin >> qq;
			system("cls");
		}
	}
	else if (inp == 4) {
		cout << "введите слово, например FLEX" << endl;
		string word; cin >> word;

		//string str = "FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  ";
		//str = str + str + str + str + str + str + str + str + str + str;
		for (int i = 0; i < 9; i++)word =word + "   " + word;
		vector<string>vect = { "31","32","33","34","35","36","37" };
		for (int i = 0; i < 100; i++) {
			cout << "\033[" + vect[i % 7] + "m" + word + "\033[0m";
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
			system("cls");
		}
	}
	return inp;
}
void welcome() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	if (columns >= 100) {
		cout << " __          __  _ _                             _           _  __          ______                   " << endl <<
			" \\ \\        / / | | |                           | |         | |/ /         |  ____|                  " << endl <<
			"  \\ \\  /\\  / /__| | | ___ ___  _ __ ___   ___   | |_ ___    | ' / ___ _   _| |__ ___  _ __ __ _  ___ " << endl <<
			"   \\ \\/  \\/ / _ \\ | |/ __/ _ \\| '_ ` _ \\ / _ \\  | __/ _ \\   |  < / _ \\ | | |  __/ _ \\| '__/ _` |/ _ \\" << endl <<
			"    \\  /\\  /  __/ | | (_| (_) | | | | | |  __/  | || (_) |  | . \\  __/ |_| | | | (_) | | | (_| |  __/" << endl <<
			"     \\/  \\/ \\___|_|_|\\___\\___/|_| |_| |_|\\___|   \\__\\___/   |_|\\_\\___|\\__, |_|  \\___/|_|  \\__, |\\___|" << endl <<
			"                                                                       __/ |               __/ |     " << endl <<
			"                                                                      |___/               |___/      " << endl;
	}
}
int main() {
	setlocale(LC_ALL, "Russian");
	welcome();
	
	string line;
	string user = "";
	ifstream in("Storage.txt");
	if (in.is_open()){
		while (getline(in, line)){user += line;}
	}
	in.close();

	int stop = 1;
	string user_key = "";
	if (!user.empty()) {
		cout << "введите мастер-пароль для входа в приложение(1 слово без русских букв)" << endl;
		cin >> user_key;
		//is_user(user_key);
	}
	else {
		cout << "для создания аккаутна нужно придумать Мастер-Пароль(1 слово без русских букв). Далее этот же Мастер-Пароль понадобится для получения доступа к паролям" << endl;
		cout << "введите мастер-пароль" << endl;
		cin >> user_key;
		//is_user(user_key);
	}
	while (stop != 0) {
		stop=is_user(user_key);
	}
}
