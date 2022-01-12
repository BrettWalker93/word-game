#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <random>
#include <map>

using namespace std;

void menu();
void game(string ans);
void wordSearch(vector<string> &wl);

int main() {

	menu();

	return 0;

}

void menu() {

//compile word list
	vector<string> wordList = {};

	ifstream wordListRead("5letterwords.txt");

	string s = "";

	try {
		if (wordListRead.is_open()) {


			do {
				wordListRead >> s;
				wordList.push_back(s);
			} while (s.compare("zymes") != 0);
		}
	}

	catch (exception e) {
		cout << e.what();
		exit;
	}

//menu loop
	bool done = false;
	do {
		cout << "_ _ _ _ _" << endl;
		cout << "1. New Game" << endl;
		cout << "2. Word Search" << endl;
		cout << "6. Quit" << endl;

		int cmd = 3;

		cin >> cmd;
		
		random_device rd;
		mt19937	 gen(rd());
		uniform_int_distribution<> distr(0, wordList.size() - 1);

		switch (cmd) {
		case 1:
			game(wordList[distr(gen)]);
			break;
		case 6:
			done = true;
			break;
		case 2:
			wordSearch(wordList);
		default:
			break;
		}
	} while (!done);
}

void game(string ans) {

	bool solved = false;
	cout << "_ _ _ _ _" << endl;

	do {
		string guess = "";
		cin >> guess;
		if (guess.compare("exit") == 0) return;
		string check = "";
		int i = 0;
		for (char c : guess) {
			int pos = ans.find(c);

			if (pos == string::npos) {
				check += "X";
			}

			else {				
				if (ans[i] == guess[i]) {
					check += "þ";
				}
				else check += "/";
			}
			i++;
			if (i == 5) i = 0;
		}

		cout << check << endl;

		if (ans.compare(guess) == 0) {
			solved = true;
			cout << "Yay!" << endl;
		}
	} while (!solved);

	return;
}

void wordSearch(vector<string>& wl) {

	string sc;

	cout << "contains: ";

	cin >> sc;
	cout << endl;

	string sd;

	cout << "doesn't contain: ";
	cin >> sd;
	cout << endl;

	cout << "basic search (y/n): ";
	char resp = 'y';
	cin >> resp;

	map<char, vector<int>> sc_map = {};

	if (resp == 'n') {
		for (char c : sc) {
			cout << c << " is yellow(0) or green(1): ";
			int cc;
			cin >> cc;

			cout << "position: ";
			int cpos = 0;
			cin >> cpos;

			sc_map.insert(pair<char, vector<int>>(c, { cc, cpos }));
		}
	}

	vector<string> ws = {};

	for (string ls : wl) {

		bool good = true;

		for (char c : sd) {
			if (ls.find(c) != string::npos) {
				good = false;
				break;
			}
		}

		for (char c : sc) {
			//cout << "looking at char: " << c << endl;
			//cout << "with map element: " << sc_map[c][0] << ", " << sc_map[c][1] << endl;

			if (ls.find(c) == string::npos) {
				good = false;
				break;
			}

			if (resp == 'n') {
				if (((ls[sc_map[c][1]] == c) && (sc_map[c][0] == 1)) || ((ls[sc_map[c][1]] != c) && (sc_map[c][0] == 0))) {}
				else {
					good = false;
					break;
				}
			}
		}
		
		if (good) {
			cout << ls << endl;
			ws.push_back(ls);
		}

	}

	map<char, int> lettercount = {};

	for (string word : ws) {
		for (char c : word) {
			pair<map<char, int>::iterator, bool> cani;
			cani = lettercount.insert(pair<char, int>(c, 1));
			if (!cani.second) lettercount[c]++;
		}
	}
	cout << ws.size() << " words" << endl;
	for (pair<char, int> dap : lettercount) {
		cout << dap.first << ": " << dap.second << endl;
	}

}