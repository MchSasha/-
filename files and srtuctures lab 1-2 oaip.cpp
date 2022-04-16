#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct student {
    string fio;
    int year;
    int group;
    int marks[4];
    double average_score;
};


void read(string name_of_file, vector <student> &file);
void rerecord(string name_of_file, vector <student> &file);
void show_list(vector <student>& file);
void menu(int &n);
double score(vector<student>& file);



int main()
{
    //считать ил  создать новый
    //добавить ошибки 
    setlocale(LC_ALL, "rus");
    vector <student> file;
    int n = 0;
    cout << "1. Cчитать с имеющегося файла" << '\n' <<"2. Создать новый файл"<<'\n'<<"Выьрано: ";
    cin >> n; cout << '\n';
    string file_name;
    if (n == 1)
    {
        cout << endl;
        cout << "Введите полное имя файла: ";
        cin >> file_name;

    }
    if (n == 2) {
        cout << endl;
        cout << "Введите имя нового файла: ";
        cin >> file_name;
    }
    while(n!=1&&n!=2) {
        cout << "ERROR!" << '\n' << "Выберите действие еще раз: ";
        cin >> n; cout << '\n';
    }
    read(file_name, file);
    menu(n);
    while (n != 0) {
        switch (n)
        {
        case 1:
        {
            student new_student;
            cout << "...Добавление новой записи...";
            cout << endl;
            cout << "Введите ФИО студента: ";
            cin >> new_student.fio;
            cout << "Введите год рождения студента: ";
            cin >> new_student.year;
            cout << "Введите номер группы студента: ";
            cin >> new_student.group;
            cout << "Введите отметки студента по физике, математике, информатике, химии соответсвенно: ";
            cout << endl;
            for (int i = 0; i < 4; i++)
                cin >> new_student.marks[i];
            cout << endl;
            new_student.average_score =
                (new_student.marks[0] + new_student.marks[1]
                    + new_student.marks[2] + new_student.marks[3]) / 4.0;

            file.push_back(new_student);
            break;
        }
        case 2:
        {
            cout << "...Просмотр всех записей..." << endl;
            if (file.size() == 0) {
                cout << endl;
                cout << "Список записей пуст";
                break;
            }
            else {
                show_list(file);
                break;
            }
        }
        case 3:
        {
            cout << "...Коррекция записей..." << endl;
            if (file.size() == 0) {
                cout << endl;
                cout << "Список записей пуст";
                break;
            }
            else {
                show_list(file);
                cout << "Введите ФИО студента, чью запись хотите скорректировать: ";
                string fio;
                cin >> fio;
                cout << "Введите номер группы студента, чью запись хотите скорректировать: ";
                int num;
                cin >> num;
                int m;
                cout << "Выберите соответсвующее поле для корректировки: " << '\n' << "1. ФИО" << '\n' << "2. Год рождения" << '\n' << "3. Номер группы"
                    << '\n' << "4. Отметки" << '\n' << "Будет выполнено: ";
                cin >> m; cout << endl;
                int match = 0;
                for (int i = 0; i < file.size(); i++)
                    if (file[i].fio == fio && file[i].group == num) {
                        match++;
                        cout << "Введите новые данные: " << endl;
                        string change;

                        if (m == 1)
                        {
                            cin >> change; file[i].fio = change;
                        }
                        if (m == 2)
                        {
                            cin >> change; file[i].year = stoi(change);
                        }
                        if (m == 3)
                        {
                            cin >> change; file[i].group = stoi(change);
                        }
                        if (m == 4) {
                            for (int j = 0; j < 4; j++) {
                                cin >> change;
                                file[i].marks[j] = stoi(change);

                            }
                            file[i].average_score =
                                (file[i].marks[0] + file[i].marks[1]
                                    + file[i].marks[2] + file[i].marks[3]) / 4.0;
                        }
                        
                        cout << endl;
                        cout << "Выбранная запись будет заменена на: " << file[i].fio << " " << file[i].year << " " << file[i].group << " "
                            << file[i].marks[0] << " " << file[i].marks[1] << " " << file[i].marks[2]
                            << " " << file[i].marks[3]
                            << " " << file[i].average_score << endl;
                    }
                if (match == 0)
                {
                    cout << "ERROR!" << '\n' << "Такого студента нет ";
                }
                break;
            }
        }
        case 4:
        {
            cout << "...Вычислить общий средний балл всех студентов и приготовить к печати список студентов со средним баллом выше общего среднего балла..." << '\n';
            if (file.size() == 0) {
                cout << "Список записей пуст";
                break;
            }
            double general_score = score(file);
            cout << "Общий средний балл всех студентов: " << general_score << '\n';
            cout << "Готов к печати список студентов со средним баллом выше общего среднего балла: " << endl;
            for (student i : file) {
                if (i.average_score > general_score)
                    cout << i.fio << endl;
            }
            break;
        }
        }
        menu(n);
    }
    if (n == 0) {
        rerecord(file_name, file);
        return 0;
    }
    
}

void show_list(vector <student>& file) 
{
    for (student i : file) {
        cout << i.fio << " " << i.year << " " << i.group << " "
            << i.marks[0] << " " << i.marks[1] << " " << i.marks[2]
            << " " << i.marks[3]
            << " " << i.average_score << endl;
    }
}
void read(string name_of_file, vector <student> &file ) {

    ifstream record;
    record.open(name_of_file);
    string student_inf;
    while (getline(record, student_inf))
    {
        stringstream inf(student_inf);
        string data;
        student temporary;
        int i = 0;
        while (getline(inf, data, ' ')) {
            if (i == 0)
                temporary.fio = data;
            if (i == 1)
                temporary.year = stoi(data);
            if (i == 2)
                temporary.group = stoi(data);
            if (i == 3)
                temporary.marks[0] = stoi(data);
            if (i == 4)
                temporary.marks[1] = stoi(data);
            if (i == 5)
                temporary.marks[2] = stoi(data);
            if (i == 6) {
                temporary.marks[3] = stoi(data);
                temporary.average_score =
                    (temporary.marks[0] + temporary.marks[1]
                    + temporary.marks[2] + temporary.marks[3]) / 4.0;
            }

            i++;
        }
        file.push_back(temporary);
    }
}
void rerecord(string name_of_file, vector <student>& file) 
{
    ofstream RErecord;
    RErecord.open(name_of_file);
    for (student i : file) {
    RErecord << i.fio << " " << i.year << " " << i.group << " "
        << i.marks[0] << " " << i.marks[1] << " " << i.marks[2]
        << " " << i.marks[3] << " " << i.average_score << endl;
    }
    RErecord.close();

    RErecord.open("List_of_students.txt");
    double general_score = score(file);
    RErecord << "Студенты попавшие в список: " << endl;
    for (student i : file) {
        if (i.average_score > general_score)
            RErecord << i.fio << endl;
    }
    RErecord.close();
}
void menu(int &n ) 
{
    cout <<'\n'<< "МЕНЮ" << endl << "1. Добавление новой записи " << "\n" << "2. Просмотр всех записей" << "\n"
        << "3. Коррекция записи " << "\n" << "4. Вычислить общий средний балл всех студентов и приготовить к печати список студентов со средним баллом выше общего среднего балла"<<'\n'<<
        "0. Сохранить все изменения и распечатать список студентов со средним баллом выше общего реднего "<<'\n'
        <<"Вы выбрали: ";
    cin >> n;
    cout << endl;
    while (n != 0 && n != 1 && n != 2 && n != 3 && n != 4) {
        cout << "ERROR!" << '\n' << "Выберите дейсвтие еще раз: ";
        cin >> n;
    }
    
}
double score(vector<student>& file) {
    double number_of_students = 0;
    double general_score = 0;
    for (student i : file) {
        general_score += i.average_score;
        number_of_students++;
    }
    general_score /= number_of_students;
    return general_score;
}