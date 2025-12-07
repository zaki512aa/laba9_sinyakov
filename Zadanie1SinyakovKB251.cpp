#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// перечисления для предметов и статуса
enum Predmet { MATEMATIKA, FIZIKA, ISTORIYA, LITERATURA };
enum Status { OTLICHNIK, HOROSHIST, TROECHNIK, DVOECHNIK };

// описание структуры ученикаS
struct Uchenik {
    string fio;
    string klass;
    Predmet lubimiy_predmet;
    Status status_ucheby;
    double sredniy_ball;
};

// прототипы функций
string getPredmetName(Predmet p);
string getStatusName(Status s);
void printUchenik(const Uchenik& u);
void loadFromFile(vector<Uchenik>& spisok, const string& imyaFayla);
void printAll(const vector<Uchenik>& spisok);
void filterByClass(const vector<Uchenik>& spisok);
void filterByBall(const vector<Uchenik>& spisok);
void menu(const vector<Uchenik>& spisok);

int main() {
    vector<Uchenik> ucheniki;
    string imyaFayla = "students.txt";

    // загрузка данных и запуск меню
    loadFromFile(ucheniki, imyaFayla);
    printAll(ucheniki);
    menu(ucheniki);

    return 0;
}

// получение названия предмета
string getPredmetName(Predmet p) {
    switch (p) {
        case MATEMATIKA: return "Matematika";
        case FIZIKA: return "Fizika";
        case ISTORIYA: return "Istoriya";
        case LITERATURA: return "Literatura";
        default: return "Neizvestno";
    }
}

// получение названия статуса
string getStatusName(Status s) {
    switch (s) {
        case OTLICHNIK: return "Otlichnik";
        case HOROSHIST: return "Horoshist";
        case TROECHNIK: return "Troechnik";
        case DVOECHNIK: return "Dvoechnik";
        default: return "Neizvestno";
    }
}

// вывод одного ученика
void printUchenik(const Uchenik& u) {
    cout << u.fio << " \t "
         << u.klass << " \t "
         << getPredmetName(u.lubimiy_predmet) << " \t "
         << getStatusName(u.status_ucheby) << " \t "
         << u.sredniy_ball << endl;
}

// чтение из файла
void loadFromFile(vector<Uchenik>& spisok, const string& imyaFayla) {
    ifstream file(imyaFayla);
    if (!file.is_open()) {
        cout << "oshibka: fayl ne nayden" << endl;
        return;
    }

    string f, k;
    int p, s;
    double b;

    // цикл чтения
    while (file >> f >> k >> p >> s >> b) {
        Uchenik u;
        u.fio = f;
        u.klass = k;
        u.lubimiy_predmet = static_cast<Predmet>(p);
        u.status_ucheby = static_cast<Status>(s);
        u.sredniy_ball = b;
        spisok.push_back(u);
    }
    file.close();
}

// вывод всего списка
void printAll(const vector<Uchenik>& spisok) {
    cout << "--- vse ucheniki ---" << endl;
    for (const auto& u : spisok) {
        printUchenik(u);
    }
    cout << "--------------------" << endl;
}

// выборка по классу
void filterByClass(const vector<Uchenik>& spisok) {
    string nuzhnyKlass;
    cout << "vvedite klass dlya poiska (naprimer 10A): ";
    cin >> nuzhnyKlass;

    cout << "--- rezultaty ---" << endl;
    bool naydeno = false;
    for (const auto& u : spisok) {
        if (u.klass == nuzhnyKlass) {
            printUchenik(u);
            naydeno = true;
        }
    }
    if (!naydeno) cout << "ucheniki ne naydeny" << endl;
}

// выборка по среднему баллу
void filterByBall(const vector<Uchenik>& spisok) {
    double nuzhnyBall;
    cout << "vvedite minimalniy sredniy ball: ";
    cin >> nuzhnyBall;

    cout << "--- rezultaty ---" << endl;
    bool naydeno = false;
    for (const auto& u : spisok) {
        if (u.sredniy_ball >= nuzhnyBall) {
            printUchenik(u);
            naydeno = true;
        }
    }
    if (!naydeno) cout << "ucheniki ne naydeny" << endl;
}

// меню пользователя
void menu(const vector<Uchenik>& spisok) {
    int vybor;
    do {
        cout << endl;
        cout << "1. iskat po klassu" << endl;
        cout << "2. iskat po srednemu ballu" << endl;
        cout << "0. vyhod" << endl;
        cout << "vash vybor: ";
        cin >> vybor;

        switch (vybor) {
            case 1:
                filterByClass(spisok);
                break;
            case 2:
                filterByBall(spisok);
                break;
            case 0:
                cout << "do svidaniya" << endl;
                break;
            default:
                cout << "nepravilniy vvod" << endl;
        }
    } while (vybor != 0);
}