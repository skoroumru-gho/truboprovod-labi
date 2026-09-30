#include <iostream>
#include <string>
#include <fstream>
#include <limits> 

using namespace std;

struct Truba 
{
    string name;
    double dlina;
    double diametr;
    bool remont;
};

struct KS 
{
    string name;
    int cehov_vsego;
    int cehov_rabot;
    int klass;
};

bool checkInput(double &x) 
{
    if (cin >> x && cin.peek() == '\n' && x > 0) 
    {
        return true;
    } else 
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        return false;
    }
}
bool checkInputt(int &x) 
{
    if (cin >> x && cin.peek() == '\n' && x >= 0) 
    {
        return true;
    } else 
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
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
        
        if (!(cin >> menu) || cin.peek() != '\n') 
        {
            cout << "Ошибка! Введите число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (menu == 1) 
        {
            cout << "Введите название трубы: ";
            cin.ignore();
            getline(cin, mojaTruba.name);
            
            cout << "Введите длину (км): ";
            while (!checkInput(mojaTruba.dlina)) 
            {
                cout << "Ошибка! Введите положительное число: ";
            }
            
            cout << "Введите диаметр (мм): ";
            while (!checkInput(mojaTruba.diametr)) 
            {
                cout << "Ошибка! Введите положительное число: ";
            }
            
            mojaTruba.remont = false;
        }
        else if (menu == 2) 
        {
            cout << "Введите название КС: ";
            cin.ignore();
            getline(cin,mojaKS.name);
            
            cout << "Введите количество цехов всего: ";
            int temp;
            double temp1;
            while (!checkInput(temp1))
            {
                cout << "Ошибка! Введите положительное число: ";
            }
            mojaKS.cehov_vsego = int(temp1);
            
            cout << "Введите количество цехов в работе: ";
            while (true)
            {
                while (!checkInputt(temp)) 
                {
                cout << "Ошибка! Введите положительное число: ";
                }
                if (temp<=mojaKS.cehov_vsego)
                {
                    mojaKS.cehov_rabot = temp;
                    break;
                }
                else
                {
                cout<<"Цехов в работе должно быть не больше чем цехов всего:";
                }
            }         
            
            
            cout << "Введите класс станции: ";
            while (!checkInputt(temp)) 
            {
                cout << "Ошибка! Введите положительное число: ";
            }
            mojaKS.klass = temp;
        }
        else if (menu == 3) 
        {
            cout << "\n--- Труба ---\n";
            if (mojaTruba.name=="")
            {
                cout << "Не существует\n";
            }
            else
            {
                cout << "Название: " << mojaTruba.name << endl;
                cout << "Длина: " << mojaTruba.dlina << " км" << endl;
                cout << "Диаметр: " << mojaTruba.diametr << " мм" << endl;
                if (mojaTruba.remont) cout << "Статус: В ремонте\n";
                else cout << "Статус: Работает\n";
            }
            cout << "\n--- КС ---\n";
            if(mojaKS.name=="")
            {
                cout<<"Не существует\n";
            }
            else
            {            
                cout << "Название: " << mojaKS.name << endl;
                cout << "Цехов всего: " << mojaKS.cehov_vsego << endl;
                cout << "Цехов в работе: " << mojaKS.cehov_rabot << endl;
                cout << "Класс: " << mojaKS.klass << endl;
            }
        }
        else if (menu == 4) 
        {
            mojaTruba.remont = !mojaTruba.remont;
            cout << "Статус трубы изменен.\n";
        }
        else if (menu == 5) 
        {
            int deistvie;
            cout << "1. Запустить цех\n2. Остановить цех\nВаш выбор: ";
            if (!(cin >> deistvie) || cin.peek() != '\n') 
            {
                cout << "Ошибка ввода.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else 
            {
                if (deistvie == 1 && mojaKS.cehov_rabot < mojaKS.cehov_vsego) {
                    mojaKS.cehov_rabot++;
                    cout << "Цех запущен.\n";
                } else if (deistvie == 2 && mojaKS.cehov_rabot > 0) {
                    mojaKS.cehov_rabot--;
                    cout << "Цех остановлен.\n";
                } else {
                    cout << "Действие невозможно.\n";
                }
            }
        }
        else if (menu == 6) 
        {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            ofstream fout(filename);
            fout << mojaTruba.name << endl;
            fout << mojaTruba.dlina << endl;
            fout << mojaTruba.diametr << endl;
            fout << mojaTruba.remont << endl;
            fout << mojaKS.name << endl;
            fout << mojaKS.cehov_vsego << endl;
            fout << mojaKS.cehov_rabot << endl;
            fout << mojaKS.klass << endl;
            fout.close();
            cout << "Сохранено.\n";
        }
        else if (menu == 7) 
        {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            ifstream fin(filename);
            if (!fin.is_open()) {
                cout << "Файл не найден.\n";
            } else 
            {
                getline(fin, mojaTruba.name);
                fin >> mojaTruba.dlina >> mojaTruba.diametr >> mojaTruba.remont;
                fin.ignore();
                getline(fin, mojaKS.name);
                fin >> mojaKS.cehov_vsego >> mojaKS.cehov_rabot >> mojaKS.klass;
                fin.close();
                cout << "Загружено.\n";
            }
        }
        else if (menu == 0) 
        {
            cout << "Выход.\n";
        }
        else 
        {
            cout << "Нет такого пункта.\n";
        }
    }
    return 0;
}