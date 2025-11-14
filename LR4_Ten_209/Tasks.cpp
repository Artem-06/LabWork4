#include "Header.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// 1) Загальна кількість листів
void task1_TotalMails(const string& FILENAME) {
    vector<Mail> mails = loadMails(FILENAME);
    cout << "Кількість листів: " << mails.size() << "\n";
}

// 2) Кількість унікальних відправників
void task2_UniqueSenders(const string& FILENAME) {
    vector<Mail> mails = loadMails(FILENAME);

    vector<string> unique; // список унікальних адрес

    for (const Mail& MAIL : mails) {
        string str = MAIL.from;
        for (char& c : str) c = tolower(c);

        bool found = false;
        for (const string& U : unique)
            if (U == str) found = true;

        if (!found && str != "") unique.push_back(str);
    }

    cout << "Унікальних відправників: " << unique.size() << "\n";
}

// 3) Кількість листів, надісланих на ebass@enron.com
struct DayCount {
    string day;
    int count;
};

void task3_ToEbass(const string& FILENAME) {
    const string TARGET = "ebass@enron.com";
    vector<Mail> mails = loadMails(FILENAME);

    vector<DayCount> dayList;
    int total = 0;

    for (auto& mail : mails) {
        string target = mail.to;
        for (char& c : target) c = tolower(c);

        if (target.find(TARGET) != string::npos) {
            total++;

            string ymd;
            if (!parseYMD(mail.date, ymd))
                ymd = "(unknown)";

            bool found = false;
            for (auto& dayCount : dayList)
                if (dayCount.day == ymd) {
                    dayCount.count++;
                    found = true;
                }

            if (!found) {
                DayCount date;
                date.day = ymd;
                date.count = 1;
                dayList.push_back(date);
            }
        }
    }

    // Сортування по даті (бабл-сорт)
    for (int i = 0; i < (int)dayList.size(); i++)
        for (int j = i + 1; j < (int)dayList.size(); j++)
            if (dayList[j].day < dayList[i].day)
                swap(dayList[i], dayList[j]);

    cout << "Всього листів: " << total << "\n";
    cout << "По днях:\n";
    for (auto& dayCount : dayList)
        cout << dayCount.day << " : " << dayCount.count << "\n";
}

// 4) Аналіз переписки Shanna Husser і Eric Bass
void task4_ShannaEric(const string& FILENAME) {
    const string SHANNA = "shanna.husser@enron.com";
    const string ERIC = "eric.bass@enron.com";

    vector<Mail> mails = loadMails(FILENAME);

    int sh_to_er = 0;
    int er_to_sh = 0;

    for (auto& mail : mails) {
        string from = mail.from;
        string to = mail.to;
        for (char& c : from) c = tolower(c);
        for (char& c : to) c = tolower(c);

        if (from.find(SHANNA) != string::npos && to.find(ERIC) != string::npos) sh_to_er++;
        if (from.find(ERIC) != string::npos && to.find(SHANNA) != string::npos) er_to_sh++;
    }

    cout << "Shanna → Eric: " << sh_to_er << "\n";
    cout << "Eric → Shanna: " << er_to_sh << "\n";
    cout << "Всього листів між ними: " << sh_to_er + er_to_sh << "\n";
}

// 5) Кількість разів використання теми листів у 2000 році
struct SubjCount {
    string subject;
    int count;
};

void task5_Subjects2000(const string& FILENAME) {
    const string TARGET_YEAR = "2000";

    vector<Mail> mails = loadMails(FILENAME);
    vector<SubjCount> subjects;

    for (auto& mail : mails) {
        if (mail.date.find(TARGET_YEAR) != string::npos) {
            string subj = mail.subject;
            if (subj == "") subj = "(no subject)";

            bool found = false;
            for (auto& p : subjects)
                if (p.subject == subj) { p.count++; found = true; }

            if (!found) {
                SubjCount subjCount;
                subjCount.subject = subj;
                subjCount.count = 1;
                subjects.push_back(subjCount);
            }
        }
    }

    // Сортування за спаданням count (бабл-сорт)
    for (int i = 0; i < (int)subjects.size(); i++)
        for (int j = i + 1; j < (int)subjects.size(); j++)
            if (subjects[j].count > subjects[i].count)
                swap(subjects[i], subjects[j]);

    cout << "Топ тем у 2000 році:\n";

    int limit = subjects.size();
    if (limit > 10) limit = 10;

    for (int i = 0; i < limit; i++)
        cout << subjects[i].subject << " : " << subjects[i].count << "\n";

    if (subjects.size() == 0)
        cout << "(немає листів 2000 року)\n";
}

// 6) Найбільш навантажений день тижня
void task6_BusyWeekday(const string& FILENAME) {
    vector<Mail> mails = loadMails(FILENAME);

    const int DAYS = 8;
    string names[DAYS] = {
        "Monday","Tuesday","Wednesday","Thursday",
        "Friday","Saturday","Sunday","(unknown)"
    };
    int cnt[DAYS] = { 0 };

    for (auto& mail : mails) {
        string w3;
        if (!parseWeekday(mail.date, w3)) {
            cnt[7]++;
        }
        else {
            string full = fullWeekday(w3);

            int id = 7;
            for (int i = 0; i < 7; i++)
                if (full == names[i]) id = i;

            cnt[id]++;
        }
    }

    cout << "Розподіл за днями тижня:\n";
    for (int i = 0; i < DAYS; i++)
        cout << names[i] << " : " << cnt[i] << "\n";

    // Пошук максимального вручну
    int best = 0;
    for (int i = 1; i < DAYS; i++)
        if (cnt[i] > cnt[best]) best = i;

    cout << "Найбільш навантажений день: "
        << names[best]
        << " (" << cnt[best] << ")\n";
}