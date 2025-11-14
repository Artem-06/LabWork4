#include "Header.h"

using namespace std;

Mail parseMailLine(const string& LINE) {
    Mail mail;
    mail.from       = getField(LINE, "From");
    mail.to         = getField(LINE, "To");
    mail.subject    = getField(LINE, "Subject");
    mail.date       = getField(LINE, "Date");
    return mail;
}

bool parseYMD(const string& DATE_FIELD, string& out) {
    if (DATE_FIELD.size() < 8) return false;

    // 1) «найдемо позиц≥ю початку дн€ (перша цифрова посл≥довн≥сть)
    int posDay = -1;
    for (int i = 0; i < (int)DATE_FIELD.size(); ++i) {
        if (isdigit((unsigned char)DATE_FIELD[i])) { posDay = i; break; }
    }
    if (posDay == -1) return false;

    // ѕрочитаЇмо день (може бути 1 або 2 цифри)
    int pos = posDay;
    while (pos < (int)DATE_FIELD.size() && isdigit((unsigned char)DATE_FIELD[pos])) ++pos;
    int day = atoi(DATE_FIELD.substr(posDay, pos - posDay).c_str());

    // 2) «найдемо м≥с€ць - трибуквену абрев≥атуру (jan..dec)
    string mons[12] = { "jan","feb","mar","apr","may","jun",
                        "jul","aug","sep","oct","nov","dec" };
    int month = -1;
    int posMonth = -1;
    for (int i = 0; i + 2 < (int)DATE_FIELD.size(); ++i) {
        string temp = DATE_FIELD.substr(i, 3);
        for (char& c : temp) c = tolower((unsigned char)c);
        for (int mon = 0; mon < 12; ++mon) {
            if (temp == mons[mon]) {
                month = mon + 1;
                posMonth = i;
                break;
            }
        }
        if (month != -1) break;
    }
    if (month == -1) return false;

    // 3) «найдемо р≥к Ч перша 4-значна посл≥довн≥сть **п≥сл€** posMonth
    int year = -1;
    for (int i = posMonth + 3; i + 3 < (int)DATE_FIELD.size(); ++i) {
        if (isdigit((unsigned char)DATE_FIELD[i]) &&
            isdigit((unsigned char)DATE_FIELD[i + 1]) &&
            isdigit((unsigned char)DATE_FIELD[i + 2]) &&
            isdigit((unsigned char)DATE_FIELD[i + 3])) {

            // додаткова перев≥рка: р≥к маЇ бути в розумних межах, наприклад 1900..2100
            int cand = atoi(DATE_FIELD.substr(i, 4).c_str());
            if (cand >= 1900 && cand <= 2100) {
                year = cand;
                break;
            }
        }
    }
    if (year == -1) return false;

    // 4) ‘ормуЇмо р€док YYYY-MM-DD
    char buf[16];
    sprintf_s(buf, "%04d-%02d-%02d", year, month, day);
    out = buf;

    return true;
}

bool parseWeekday(const string& DATE_FIELD, string& out) {
    for (int i = 0; i < (int)DATE_FIELD.size() - 2; i++) {
        if (isalpha(DATE_FIELD[i]) &&
            isalpha(DATE_FIELD[i + 1]) &&
            isalpha(DATE_FIELD[i + 2])) {

            out = DATE_FIELD.substr(i, 3);
            for (char& c : out) c = tolower(c);
            return true;
        }
    }
    return false;
}