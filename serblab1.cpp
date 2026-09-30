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


void addTruba(Truba &t) 
{
    cout << "Введите название трубы: ";
    cin.ignore();
    getline(cin, t.name);
    
    cout << "Введите длину (км): ";
    while (!checkInput(t.dlina)) 
    {
        cout << "Ошибка! Введите положительное число: ";
    }
    
    cout << "Введите диаметр (мм): ";
    while (!checkInput(t.diametr)) 
    {
        cout << "Ошибка! Введите положительное число: ";
    }
    
    t.remont = false;
    cout << "Труба добавлена!\n";
}

void addKS(KS &k) 
{
    cout << "Введите название КС: ";
    cin.ignore();
    getline(cin, k.name);
    
    cout << "Введите количество цехов всего: ";
    int temp;
    double temp1;
    while (!checkInput(temp1))
    {
        cout << "Ошибка! Введите положительное число: ";
    }
    k.cehov_vsego = int(temp1);
    
    cout << "Введите количество цехов в работе: ";
    while (true)
    {
        while (!checkInputt(temp)) 
        {
            cout << "Ошибка! Введите положительное число: ";
        }
        if (temp <= k.cehov_vsego)
        {
            k.cehov_rabot = temp;
            break;
        }
        else
        {
            cout << "Цехов в работе должно быть не больше чем цехов всего: ";
        }
    }         
    
    cout << "Введите класс станции: ";
    while (!checkInputt(temp)) 
    {
        cout << "Ошибка! Введите положительное число: ";
    }
    k.klass = temp;
    cout << "КС добавлена!\n";
}

void showAll(Truba t, KS k) 
{
    cout << "\n Труба \n";
    if (t.name == "")
    {
        cout << "Не существует\n";
    }
    else
    {
        cout << "Название: " << t.name << endl;
        cout << "Длина: " << t.dlina << " км" << endl;
        cout << "Диаметр: " << t.diametr << " мм" << endl;
        if (t.remont) cout << "Статус: В ремонте\n";
        else cout << "Статус: Работает\n";
    }
    
    cout << "\n КС \n";
    if (k.name == "")
    {
        cout << "Не существует\n";
    }
    else
    {            
        cout << "Название: " << k.name << endl;
        cout << "Цехов всего: " << k.cehov_vsego << endl;
        cout << "Цехов в работе: " << k.cehov_rabot << endl;
        cout << "Класс: " << k.klass << endl;
    }
}

void editTruba(Truba &t) 
{
    if (t.name == "") 
    {
        cout << "Сначала добавьте трубу!\n";
        return;
    }
    t.remont = !t.remont;
    cout << "Статус трубы изменен.\n";
}

void editKS(KS &k) 
{
    if (k.name == "") 
    {
        cout << "Сначала добавьте КС!\n";
        return;
    }
    
    int deistvie;
    cout << "1. Запустить цех\n2. Остановить цех\nВаш выбор: ";
    if (!(cin >> deistvie) || cin.peek() != '\n') 
    {
        cout << "Ошибка ввода.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } 
    else 
    {
        if (deistvie == 1 && k.cehov_rabot < k.cehov_vsego) 
        {
            k.cehov_rabot++;
            cout << "Цех запущен.\n";
        } 
        else if (deistvie == 2 && k.cehov_rabot > 0) 
        {
            k.cehov_rabot--;
            cout << "Цех остановлен.\n";
        }
         else 
        {
            cout << "Действие невозможно.\n";
        }
    }
}

void saveTruba(Truba t, ofstream &fout) 
{
    fout << t.name << endl;
    fout << t.dlina << endl;
    fout << t.diametr << endl;
    fout << t.remont << endl;
}

void saveKS(KS k, ofstream &fout) 
{
    fout << k.name << endl;
    fout << k.cehov_vsego << endl;
    fout << k.cehov_rabot << endl;
    fout << k.klass << endl;
}

void loadTruba(Truba &t, ifstream &fin) 
{
    getline(fin, t.name);
    fin >> t.dlina;
    fin >> t.diametr;
    fin >> t.remont;
    fin.ignore(); 
}

void loadKS(KS &k, ifstream &fin) 
{
    getline(fin, k.name);
    fin >> k.cehov_vsego;
    fin >> k.cehov_rabot;
    fin >> k.klass;
}

int main() 
{
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
            addTruba(mojaTruba);
        }
        else if (menu == 2) 
        {
            addKS(mojaKS);
        }
        else if (menu == 3) 
        {
            showAll(mojaTruba, mojaKS);
        }
        else if (menu == 4) 
        {
            editTruba(mojaTruba);
        }
        else if (menu == 5) 
        {
            editKS(mojaKS);
        }
       else if (menu == 6) 
        {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
    
            ofstream fout(filename); 
            if (!fout.is_open()) {
                cout << "Ошибка открытия файла!\n";
            } else {
                saveTruba(mojaTruba, fout); 
                saveKS(mojaKS, fout);       
                fout.close();              
                cout << "Сохранено.\n";
            }
        }
        else if (menu == 7) 
        {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            
            ifstream fin(filename);
            if (!fin.is_open()) 
            {
                cout << "Файл не найден.\n";
            } else 
            {
                loadTruba(mojaTruba, fin); 
                loadKS(mojaKS, fin);       
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