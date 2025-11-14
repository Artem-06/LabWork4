#include "Header.h"
#include <iostream>
#include <fstream>

vector<Mail> loadMails(const string& FILENAME) {
    ifstream fin(FILENAME);
    vector<Mail> mails;

    if (!fin.is_open()) {
        cout << "Не вдалося відкрити файл.\n";
        return mails;
    }

    string line;
    while (getline(fin, line)) {
        bool empty = true;
        for (char c : line)
            if (!isspace((unsigned char)c)) empty = false;

        if (!empty)
            mails.push_back(parseMailLine(line));
    }

    return mails;
}