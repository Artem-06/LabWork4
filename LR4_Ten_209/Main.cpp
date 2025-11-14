#include <iostream>
#include "Windows.h"
#include "Header.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const string FILENAME = "mails.json";

    // ----------------- МЕНЮ -----------------
    while (true) {
        cout << "Оберіть завдання:" << endl;
        cout << "1) Загальна кількість листів" << endl;
        cout << "2) Кількість унікальних відправників" << endl;
        cout << "3) Кількість листів, надісланих на ebass@enron.com (загалом та по днях)" << endl;
        cout << "4) Аналіз переписки Shanna Husser і Eric Bass" << endl;
        cout << "5) Кількість разів використання теми листів у 2000 році (топ)" << endl;
        cout << "6) Найбільш навантажений день тижня" << endl;
        cout << "0) Вихід" << endl;
        cout << "Вибір: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cout << "Невірне введення.\n";
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
        case 1: task1_TotalMails(FILENAME); break;
        case 2: task2_UniqueSenders(FILENAME); break;
        case 3: task3_ToEbass(FILENAME); break;
        case 4: task4_ShannaEric(FILENAME); break;
        case 5: task5_Subjects2000(FILENAME); break;
        case 6: task6_BusyWeekday(FILENAME); break;
        default:
            cout << "Невідомий вибір.\n";
        }
    }

    cout << "Кінець.\n";
    return 0;
}