#pragma once

#include <string>
#include <vector>

using namespace std;

// ----------------- СТРУКТУРА -----------------

struct Mail {
	string from;
	string to;
	string date;
	string subject;
};

// ----------------- ЗАВАНТАЖЕННЯ -----------------

vector<Mail> loadMails(const string& FILENAME);

// ----------------- ДОПОМІЖНІ УТИЛІТИ -----------------

string getField(const string& LINE, const string& FIELD);
string fullWeekday(const string& SHORT_WD);

// ----------------- ПАРСИНГ -----------------

Mail parseMailLine(const string& LINE);
bool parseYMD(const string& DATE_FIELD, string& out);
bool parseWeekday(const string& DATE_FIELD, string& out);

// ----------------- ЗАВДАННЯ -----------------

void task1_TotalMails(const string& FILENAME);
void task2_UniqueSenders(const string& FILENAME);
void task3_ToEbass(const string& FILENAME);
void task4_ShannaEric(const string& FILENAME);
void task5_Subjects2000(const string& FILENAME);
void task6_BusyWeekday(const string& FILENAME);