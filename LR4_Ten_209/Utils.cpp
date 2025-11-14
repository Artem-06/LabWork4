#include "Header.h"

using namespace std;

string getField(const string& LINE, const string& FIELD) {
    string key = "\"" + FIELD + "\"";
    size_t p = LINE.find(key);
    if (p == string::npos) return "";

    size_t colon = LINE.find(":", p);
    if (colon == string::npos) return "";

    size_t q1 = LINE.find("\"", colon + 1);
    if (q1 == string::npos) return "";

    size_t q2 = LINE.find("\"", q1 + 1);
    if (q2 == string::npos) return "";

    return LINE.substr(q1 + 1, q2 - q1 - 1);
}

string fullWeekday(const string& SHORT_WD) {
    string str = SHORT_WD;
    for (char& c : str) c = tolower(c);

    if (str == "mon") return "Monday";
    if (str == "tue") return "Tuesday";
    if (str == "wed") return "Wednesday";
    if (str == "thu") return "Thursday";
    if (str == "fri") return "Friday";
    if (str == "sat") return "Saturday";
    if (str == "sun") return "Sunday";

    return "(unknown)";
}