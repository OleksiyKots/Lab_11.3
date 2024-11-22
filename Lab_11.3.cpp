#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
using namespace std;

struct Friend {
    string surname;
    string name;
    string zodiacSign;
    int birthDate[3];
};

void displayMenu();
string getFileName();
void createList(const string& filename);
void viewList(const string& filename);
void addFriend(const string& filename);
void findFriendBySurname(const string& filename, const string& surname);
bool parseDate(const string& dateStr, int birthDate[3]);
bool isValidDate(int day, int month, int year);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string filename = getFileName(); // Отримання імені файлу
    int choice;
    do {
        displayMenu();
        cout << "Оберіть опцію: ";
        cin >> choice;
        switch (choice) {
        case 1:
            createList(filename);
            break;
        case 2:
            viewList(filename);
            break;
        case 3:
            addFriend(filename);
            break;
        case 4: {
            string surname;
            cout << "Введіть прізвище для пошуку: ";
            cin >> surname;
            findFriendBySurname(filename, surname);
            break;
        }
        case 0:
            cout << "Вихід з програми." << endl;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 0);
    return 0;
}

void displayMenu() {
    cout << "\n--- Меню ---" << endl;
    cout << "1. Створити новий список" << endl;
    cout << "2. Переглянути список" << endl;
    cout << "3. Додати друга до списку" << endl;
    cout << "4. Знайти друга за прізвищем" << endl;
    cout << "0. Вихід" << endl;
}

string getFileName() {
    string filename;
    cout << "Введіть ім'я файлу: ";
    cin >> filename;
    return filename;
}

void createList(const string& filename) {
    ofstream file(filename);
    if (file) {
        cout << "Новий список створено." << endl;
    }
    else {
        cerr << "Помилка створення файлу." << endl;
    }
}

void viewList(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не вдалося відкрити файл." << endl;
        return;
    }
    string line;
    cout << "\nСписок друзів:\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
}

void addFriend(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Не вдалося відкрити файл для запису." << endl;
        return;
    }
    Friend newFriend;
    cout << "Введіть прізвище: ";
    cin >> newFriend.surname;
    cout << "Введіть ім'я: ";
    cin >> newFriend.name;
    cout << "Введіть знак зодіаку: ";
    cin >> newFriend.zodiacSign;
    string dateStr;
    cout << "Введіть дату народження (дд.мм.рррр): ";
    cin >> dateStr;
    if (!parseDate(dateStr, newFriend.birthDate)) {
        cerr << "Невірний формат дати. Друг не доданий." << endl;
        return;
    }
    file << newFriend.surname << " " << newFriend.name << " "
        << newFriend.zodiacSign << " "
        << newFriend.birthDate[0] << "." << newFriend.birthDate[1] << "." << newFriend.birthDate[2] << endl;
    cout << "Друг доданий до списку." << endl;
}

void findFriendBySurname(const string& filename, const string& surname) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не вдалося відкрити файл." << endl;
        return;
    }
    string line;
    bool found = false;
    while (getline(file, line)) {
        istringstream iss(line);
        Friend friendData;
        iss >> friendData.surname >> friendData.name >> friendData.zodiacSign;
        string dateStr;
        iss >> dateStr;
        if (friendData.surname == surname) {
            if (parseDate(dateStr, friendData.birthDate)) {
                cout << friendData.surname << " " << friendData.name << " "
                    << friendData.zodiacSign << " " << friendData.birthDate[0] << "." << friendData.birthDate[1] << "." << friendData.birthDate[2] << endl;
                found = true;
            }
        }
    }
    if (!found) {
        cout << "Друга з прізвищем \"" << surname << "\" не знайдено." << endl;
    }
}

bool parseDate(const string& dateStr, int birthDate[3]) {
    char dot1, dot2;
    istringstream iss(dateStr);
    if (iss >> birthDate[0] >> dot1 >> birthDate[1] >> dot2 >> birthDate[2] &&
        dot1 == '.' && dot2 == '.' &&
        isValidDate(birthDate[0], birthDate[1], birthDate[2])) {
        return true;
    }
    return false;
}

bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        return day <= (isLeap ? 29 : 28);
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    }
    return true;
}
