#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <thread>//	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
#include <Windows.h>
#include <random>
#include <algorithm>
using namespace std;
int columns = 0;
int rows = 0;
vector<string> bad_pass = { "123123","qwerty", "qwerty123", "password", "12345678", "1q2w3e", "111111"," 1234", "12345"};

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
					num1 = (num1 + 1) % 9;
					num2 = (num2 + 1) % 9;
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
	if (pass.size() % 2 == 1)ans += pass[pass.size() - 1];

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
					num1 = (num1 - 1 + 9) % 9;
					num2 = (num2 - 1 + 9) % 9;
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

string read(string company) {
	string ans = "";
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
			for (int i = line.find(' ') + 1; i < line.size(); i++)p += line[i];
			if (similar) ans += p += " ";
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
			cout << "этот сайт(приложение) ранее уже был введён. Хотите заменить пароль(введите 1) или создать ещё один(введите 2)?" << endl;
			string inp; cin >> inp;
			if (inp == "2")out << company << " " << pass << endl;
			if (inp == "1") {

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
							out2 << comp << " " << p << endl;
						else {
							cout << comp << " " << decryption(p, key) << endl;
							cout << "Если хотите оставить этот пароль, нажмите " << rr.blue("1") << endl <<
								"Если хотите удалить его, нажмите " << rr.red("2") << endl;
							string inp; cin >> inp;
							if (inp == "1")out2 << comp << " " << p << endl;
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
						out3 << line3 << endl;
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

string encryption(string pass, string key) {
	string ans;
	if (key.size() < 5) {
		ans = Playfer(pass, key);
		ans = Vigenere(ans, key);
	}
	else if (key.size() < 10) {
		ans = Playfer(pass, key);
		ans = Vigenere(ans, key);
		ans = Vigenere(ans, key);
	}
	else {
		ans = Playfer(pass, key);
		ans = Vigenere(ans, key);
		ans = Vigenere(ans, key);
		ans = Vigenere(ans, key);
	}
	return ans;
}
string decryption(string pass, string key) {
	string ans;
	if (key.size() < 5) {
		ans = Vigenere_obr(pass, key);
		ans = Playfer_obr(ans, key);
	}
	else if (key.size() < 10) {
		ans = Vigenere_obr(pass, key);
		ans = Vigenere_obr(ans, key);
		ans = Playfer_obr(ans, key);
	}
	else {
		ans = Vigenere_obr(pass, key);
		ans = Vigenere_obr(ans, key);
		ans = Vigenere_obr(ans, key);
		ans = Playfer_obr(ans, key);
	}
	return ans;
}
void read_all_file(string key, bool flag) {
	string line;
	ifstream in("Storage.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			string company = ""; string pass = "";
			for (int i = 0; i < line.find(" "); i++)company += line[i];
			for (int i = line.find(" ") + 1; i < line.size(); i++)pass += line[i];
			string pass2 = "";
			for (int i = 0; i < pass.size(); i++)pass2 += "*";
			//cout << setw(15)<<left<< company << " "<< decryption(pass,key)<< endl;
			if (flag)
				cout << setw(15) << left << company << " " << pass2 << endl;
			else { cout << setw(15) << left << company << " " << decryption(pass, key) << endl; }
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

bool is_number(const std::string& s)
{
	return !s.empty() && (s.find_first_not_of("0123456789") == s.npos);
}
string is_user(string user_key) {
	if (rows > 6) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD savedCursorPos;

		// Получаем текущую позицию курсора
		if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
			savedCursorPos = csbi.dwCursorPosition;
		}
		else {
			std::cerr << "Ошибка получения позиции курсора.\n";
			return "0";
		}

		COORD lastRow = { 0, csbi.srWindow.Bottom };
		SetConsoleCursorPosition(hConsole, lastRow);
		std::cout << rr.black("       Made by 0_Mega_Team");

		// Возвращаем курсор обратно
		SetConsoleCursorPosition(hConsole, savedCursorPos);
		//std::cout << "\nВернулись обратно!" << std::endl;
	}
	cout <<
		"Если хотите посмотреть пароли, введите " << rr.magenta("1") << "." << endl <<
		"Если хотите добавить пароль, введите " << rr.cyan("2") << "." << endl <<
		"Чтобы проверить пароли на надёжность, нажмите " << rr.green("3") << endl <<
		"Если хотите сгенерировать надежный пароль, нажмите "<<rr.yellow("4")<<endl<<
		"Для выхода из приложения введите " << rr.red("0") << endl;
	string inp;
	cin >> inp;
	system("cls");
	if ((inp) == "1") {
		string line;
		string user = "";
		ifstream in("Storage.txt");
		if (in.is_open()) {
			while (getline(in, line)) { user += line; }
		}
		in.close();
		if (!user.empty()) {
			read_all_file(user_key, true);
			cout << "чтобы получить доступ к паролям, введите мастер-пароль " << endl;
			string exit1; cin >> exit1;
			if ((exit1) == user_key) {
				read_all_file(user_key, false);

				cout << "если хотите запустить поиск, нажмите " << rr.green("1") << endl;
				cout << "если хотите скопировать пароль в буфер обмена, нажмите " << rr.yellow("2") << " а затем введите номер строки с нужным аккаунтом и паролем" << endl;
				cout << "для выхода в меню нажмите " << rr.red("0") << endl;
				string exit2; cin >> exit2;
				if ((exit2) == "0")system("cls");
				else if ((exit2) == "1") {
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
					string exit2; cin >> exit2; system("cls");
				}
				else if ((exit2) == "2") {
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
							cout << rr.cyan(to_string(n)) << "  " << setw(15) << left << company << " " << decryption(pass, user_key) << endl;
							n++;
						}
					}
					in.close();
					string input_num1; cin >> input_num1;
					int input_num;
					if (is_number(input_num1)) {
						input_num = stoi(input_num1);
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
			}
		}
		else { cout << "Паролей пока нет, чтобы создать нажмите 2 в меню" << endl; }
	}
	else if ((inp) == "2") {
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
	else if ((inp) == "3") {
		bool ok = true;
		int worth_pass=-1;
		long worth_val = 1215752191;
		int n = count_str_in_file(user_key);
		vector<string> list(n);

		cout << "Слабые пароли, которые желательно заменить:" << endl;
		string line;
		n = 0;
		ifstream in("Storage.txt");
		if (in.is_open()) {
			while (getline(in, line)) {
				string company = ""; string pass = "";
				for (int i = 0; i < line.find(" "); i++)company += line[i];
				for (int i = line.find(" ") + 1; i < line.size(); i++)pass += line[i];
				list[n] = decryption(pass, user_key);
				for (int i = 0; i < list[n].size(); i++)list[n][i] = (char)std::tolower(list[n][i]);

				long ans_pass = 0;
				string s = list[n];
				vector<char> all = { 'a', 'b','c','d','e','f','g','h','i','j','k','l','m','n', 'o', 'p' , 'q', 'r', 's', 't','u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '_','!', '@', '#', '$', '%', '^', '&', '*', '-', '+', '=', '.', ':', '?', '№', '~', '<', '>' };
				for (int i = 0; i < s.size(); i++) {
					for (int j = 0; j < 36; j++)
						if (s[i] == all[j]) ans_pass += (j + 1) * pow(36, i);
				}
				//cout << list[n] << " " << ans_pass << endl;
				if (ans_pass < worth_val) { worth_pass = n; worth_val = ans_pass; }
				if (ans_pass < 1500 || std::find(bad_pass.begin(), bad_pass.end(), list[n]) != bad_pass.end()) cout << list[n] << endl;

				n++;
			}
		}
		in.close();
		cout << endl;


		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (list[i].find(list[j]) != std::string::npos) {
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
							if (n == i || n == j)cout << company2 << " " << pass2 << endl;
							n++;
						}
					}
					in2.close();
				}
			}
		}
		if (worth_pass != -1)
			cout << endl << "Cлабейшим паролем является " << rr.red(list[worth_pass]) << endl;
		cout << "чтобы продолжить, нажмите любую цифру" << endl;
		string qq1; cin >> qq1;

		system("cls");
		if (ok) {
			cout << "Всё в порядке. (одинаковых паролей не найдено)" << endl;
			cout << "чтобы продолжить, нажмите любую цифру" << endl;
			string qq; cin >> qq;
			system("cls");
		}
	}
	else if (inp == "4") {
		vector<char> data = {// {} [] \|/ ' " ` ; 
		'Q', 'q', 'W', 'w', 'E', 'e', 'R', 'r', 'T',
		't', 'Y', 'y', 'U', 'u', 'I', 'i', 'O', 'o',
		'P', 'p', 'A', 'a', 'S', 's', 'D', 'd', 'F',
		'f', 'G', 'g', 'H', 'h', 'J', 'j', 'K', 'k',
		'L', 'l', 'Z', 'z', 'X', 'x', 'C', 'c', 'V',
		'v', 'B', 'b', 'N', 'n', 'M', 'm', '0', '1',
		'2', '3', '4', '5', '6', '7', '8', '9', '_',
		'!', '@', '#', '$', '%', '^', '&', '*', '-',
		'+', '=', '.', ':', '?', '№', '~', '<', '>',
		};
		int n = 12;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(data.begin(), data.end(), gen);

		// Берем первые n элементов
		cout << "Ваш пароль: ";
		string pass = "";
		for (int i = 0; i < n && i < data.size(); ++i) {
			pass+=data[i];
		}
		cout << pass << endl;
		cout << "Чтобы скопировать его в буфер обмена, нажмите " << rr.green("1") << endl;
		string inpp = "";
		cin >> inpp;
		if (inpp=="1")
			CopyToClipboard(pass);
	}
	else if ((inp) == "5") {
		cout << "введите слово, например FLEX" << endl;
		string word; cin >> word;

		//string str = "FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  FLEX  ";
		//str = str + str + str + str + str + str + str + str + str + str;
		for (int i = 0; i < 9; i++)word = word + "   " + word;
		vector<string>vect = { "31","32","33","34","35","36","37" };
		for (int i = 0; i < 100; i++) {
			cout << "\033[" + vect[i % 7] + "m" + word + "\033[0m";
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
			system("cls");
		}
	}
	else { return "0"; }
	
	return inp;
}
void welcome() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
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
	//включение ANSI для работы Color
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	setlocale(LC_ALL, "Russian");
	welcome();

	string line;
	string user = "";
	ifstream in("Storage.txt");
	if (in.is_open()) {
		while (getline(in, line)) { user += line; }
	}
	in.close();

	string stop = "1";
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
	while (stop != "0") {
		stop = is_user(user_key);
	}
}
