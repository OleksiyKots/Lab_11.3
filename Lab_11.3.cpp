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
    string filename = getFileName(); // ��������� ���� �����
    int choice;
    do {
        displayMenu();
        cout << "������ �����: ";
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
            cout << "������ ������� ��� ������: ";
            cin >> surname;
            findFriendBySurname(filename, surname);
            break;
        }
        case 0:
            cout << "����� � ��������." << endl;
            break;
        default:
            cout << "������� ����. ��������� �� ���." << endl;
        }
    } while (choice != 0);
    return 0;
}

void displayMenu() {
    cout << "\n--- ���� ---" << endl;
    cout << "1. �������� ����� ������" << endl;
    cout << "2. ����������� ������" << endl;
    cout << "3. ������ ����� �� ������" << endl;
    cout << "4. ������ ����� �� ��������" << endl;
    cout << "0. �����" << endl;
}

string getFileName() {
    string filename;
    cout << "������ ��'� �����: ";
    cin >> filename;
    return filename;
}

void createList(const string& filename) {
    ofstream file(filename);
    if (file) {
        cout << "����� ������ ��������." << endl;
    }
    else {
        cerr << "������� ��������� �����." << endl;
    }
}

void viewList(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "�� ������� ������� ����." << endl;
        return;
    }
    string line;
    cout << "\n������ �����:\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
}

void addFriend(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "�� ������� ������� ���� ��� ������." << endl;
        return;
    }
    Friend newFriend;
    cout << "������ �������: ";
    cin >> newFriend.surname;
    cout << "������ ��'�: ";
    cin >> newFriend.name;
    cout << "������ ���� ������: ";
    cin >> newFriend.zodiacSign;
    string dateStr;
    cout << "������ ���� ���������� (��.��.����): ";
    cin >> dateStr;
    if (!parseDate(dateStr, newFriend.birthDate)) {
        cerr << "������� ������ ����. ���� �� �������." << endl;
        return;
    }
    file << newFriend.surname << " " << newFriend.name << " "
        << newFriend.zodiacSign << " "
        << newFriend.birthDate[0] << "." << newFriend.birthDate[1] << "." << newFriend.birthDate[2] << endl;
    cout << "���� ������� �� ������." << endl;
}

void findFriendBySurname(const string& filename, const string& surname) {
    ifstream file(filename);
    if (!file) {
        cerr << "�� ������� ������� ����." << endl;
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
        cout << "����� � �������� \"" << surname << "\" �� ��������." << endl;
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
