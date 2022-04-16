#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;
void show_content();
void resh(char* s) {
    char opn[4] = { '(', '[', '{', '<' }; // открывающие скобки
    char cls[4] = { ')', ']', '}', '>' }; // закрывающие скобки
    char open; //open - временный char для сравнения открывающих скобок
    int i, k, order;
    elem* stack{ 0 };  // стек символов
    bool flag = 1;
    for (i = 0; s[i] != '\0'; i++) {
        for (k = 0; k < 4; k++) // проверить 4 вида скобок
        {
            if (s[i] == opn[k]) { // открывающая скобка
                push(stack, s[i], i);
                break;
            }
            if (s[i] == cls[k] && stack) { // закрывающая скобка
                pop(stack, open, order); // вынимаем последнюю записанную в стек открывающую скобку для сравнения
                if (open != opn[k]) {
                    cout << i << " ";
                    flag = 0;
                }
                break;
            }
            if (!stack && k == 3) { //если все открывающие закрылись, но в строке остались лишние скобки
                cout << i << " ";
                flag = 0;
                break;
            }
        }
    }
    if (stack) { //если остались лишние открывающие скобки 
        while (stack) {
            pop(stack, open, order);
            cout << order << " ";
        }
        flag = 0;
    }
    if (flag) {
        cout <<"Введенное выражение верно";
    }
    else {
        cout << "- Индексы ошибок";
    }
}
void main() {
    setlocale(LC_ALL, "rus");
    cout << "Content-type: text/html; charset=Windows-1251\n\n";
    ifstream f("stack");
    if (f.is_open())
    {
        auto sz = 65536;
        auto buf = new char[sz];
        while (!f.eof())
        {
            f.getline(buf, sz);
            if (strcmp(buf, "<!--#TITLE#-->") == 0)
            {    
                cout << "<div class = 'wrap'>";
                cout << "<h1 class = 'title'>Стеки</h1>";  
            }
            if (strcmp(buf, "<!--#CONTENT#-->") == 0)
            {
                show_content();
            }
            cout << buf;
        }
        delete[] buf;
        f.close();
    }
    else
    {
        cout << "Сайт не открылся";
    }
}
void show_content()
{
    cout << "<form method='get' action='stack.cgi'>";
    cout << "<input type='text' class='enter' name='skobki' placeholder='Введите скобочную последовательность'>";
    cout << "<input type='submit' value='Отправить' class='button'></input>";
    cout << "</form>";
    cout << "<h2 class = 'result'>Результат</h2>";
    cout << "<div class = 'output'>";
    char* data = nullptr;
    get_form_data(data);
    if (data && strlen(data) > 0)
    {
        char* value = nullptr;
        get_param_value(value, "skobki", data);
        cout << "Введенное выражение : " << value<<"<br>";
        resh(value);
  
    }
    cout << "</div>";
    delete[] data;
}
