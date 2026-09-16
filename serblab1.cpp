#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Описываем трубу
struct Truba {
    string name;
    double dlina;
    double diametr;
    bool remont; // true = в ремонте, false = работает
};

// Описываем компрессорную станцию (КС)
struct KS {
    string name;
    int cehov_vsego;
    int cehov_rabot;
    int klass;
};

// Функция для добавления трубы
void addTruba(Truba &t) {
    cout << "Введите название трубы: ";
    cin >> t.name;
    cout << "Введите длину (км): ";
    cin >> t.dlina;
    cout << "Введите диаметр (мм): ";
    cin >> t.diametr;
    t.remont = false; // Новая труба всегда исправна
}

// Функция для добавления КС
void addKS(KS &k) {
    cout << "Введите название КС: ";
    cin >> k.name;
    cout << "Введите количество цехов всего: ";
    cin >> k.cehov_vsego;
    cout << "Введите количество цехов в работе: ";
    cin >> k.cehov_rabot;
    cout << "Введите класс станции: ";
    cin >> k.klass;
}

// Функция для вывода
void show(Truba t, KS k) {
    cout << "\n--- Труба ---\n";
    cout << "Название: " << t.name << endl;
    cout << "Длина: " << t.dlina << " км" << endl;
    cout << "Диаметр: " << t.diametr << " мм" << endl;
    if (t.remont == true) 
    {
        cout << "Статус: В ремонте" << endl;
    } else {
        cout << "Статус: Работает" << endl;
    }

    cout << "\n--- КС ---\n";
    cout << "Название: " << k.name << endl;
    cout << "Цехов всего: " << k.cehov_vsego << endl;
    cout << "Цехов в работе: " << k.cehov_rabot << endl;
    cout << "Класс: " << k.klass << endl;
}

// Функция изменения ремонта трубы
void editTruba(Truba &t) {
    if (t.remont == true) 
    {
        t.remont = false;
        cout << "Труба теперь работает.\n";
    } 
    else 
    {
        t.remont = true;
        cout << "Труба теперь в ремонте.\n";
    }
}

// Функция изменения КС
void editKS(KS &k) {
    int vibor;
    cout << "1. Запустить цех\n";
    cout << "2. Остановить цех\n";
    cout << "Ваш выбор: ";
    cin >> vibor;

    if (vibor == 1) {
        if (k.cehov_rabot < k.cehov_vsego) {
            k.cehov_rabot = k.cehov_rabot + 1;
            cout << "Цех запущен.\n";
        } else {
            cout << "Все цеха уже работают.\n";
        }
    }
    else if (vibor == 2) {
        if (k.cehov_rabot > 0) {
            k.cehov_rabot = k.cehov_rabot - 1;
            cout << "Цех остановлен.\n";
        } else {
            cout << "Все цеха уже остановлены.\n";
        }
    }
    else {
        cout << "Неверный выбор.\n";
    }
}

// Сохранение в файл
void save(Truba t, KS k) {
    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;

    ofstream fout(filename);
    fout << t.name << endl;
    fout << t.dlina << endl;
    fout << t.diametr << endl;
    fout << t.remont << endl;
    
    fout << k.name << endl;
    fout << k.cehov_vsego << endl;
    fout << k.cehov_rabot << endl;
    fout << k.klass << endl;
    
    fout.close();
    cout << "Данные сохранены.\n";
}

// Загрузка из файла
void load(Truba &t, KS &k) {
    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;

    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Ошибка! Файл не найден.\n";
        return;
    }

    fin >> t.name >> t.dlina >> t.diametr >> t.remont;
    fin >> k.name >> k.cehov_vsego >> k.cehov_rabot >> k.klass;
    
    fin.close();
    cout << "Данные загружены.\n";
}

int main() {
    Truba mojaTruba;
    KS mojaKS;
    int menu = -1;

    while (menu != 0) {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить КС\n";
        cout << "3. Просмотр\n";
        cout << "4. Ремонт трубы\n";
        cout << "5. Изменить КС\n";
        cout << "6. Сохранить\n";
        cout << "7. Загрузить\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";
        cin >> menu;

        if (menu == 1) {
            addTruba(mojaTruba);
        }
        else if (menu == 2) {
            addKS(mojaKS);
        }
        else if (menu == 3) {
            show(mojaTruba, mojaKS);
        }
        else if (menu == 4) {
            editTruba(mojaTruba);
        }
        else if (menu == 5) {
            editKS(mojaKS);
        }
        else if (menu == 6) {
            save(mojaTruba, mojaKS);
        }
        else if (menu == 7) {
            load(mojaTruba, mojaKS);
        }
        else if (menu == 0) {
            cout << "Выход из программы.\n";
        }
        else {
            cout << "Нет такого пункта меню.\n";
        }
    }

    return 0;
}