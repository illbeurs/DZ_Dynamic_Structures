#include <iostream>
#include "queue.h"
#include <fstream>
#include <string>
using namespace std;
void show_content();
void load_data(const char* filename, queue& dep, queue& cred);
void show_queue(queue& q);
queue deposit;
queue credit;
void main()
{
	setlocale(LC_ALL, "Russian");

	load_data("people.txt", deposit, credit);

	cout << "Content-type: text/html; charset=Windows-1251\n\n";
	ifstream f("Queue");
	if (f.is_open())
	{
		auto sz = 65536;
		auto buf = new char[sz];
		while (!f.eof())
		{
			f.getline(buf, sz);
			if (strcmp(buf, "<!--#TITLE#-->") == 0)
			{
				cout << "<h1 class='title'>Очередь</h1>";
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
		cout << "Ошибка Загрузки Файла";
	}
}

void show_content() {
	setlocale(LC_ALL, "Russian");

#ifndef _DEBUG
	char* data = nullptr;
	get_form_data(data);
#else
	const char* data = "imya=Sergey&";
#endif
	char* value = nullptr;
	get_param_value(value, "imya", data);
	cout << "<form method='post' action='queue.cgi'>";
	cout << "<textarea type='text' class='enter' name='imya'>";
	if (!(data && strlen(data) > 0)) {
		ifstream text("people.txt");
		auto sz = 65536;
		auto buf = new char[sz];
		while (!text.eof()) {
			text.getline(buf, sz);
			cout << buf << "\n";
		}
		text.close();
	}
	else {
		cout << "Вкладчики:\n";
		show_queue(deposit);
		cout << "Кредиторы:\n";
		show_queue(credit);
	}
	cout << "</textarea>";
	cout << "<input type='submit' value='Распределить по кредитам и вкладам' class='button'>";
	cout << "</form>";

	delete[] data;
}

void load_data(const char* filename, queue& dep, queue& cred)
{
	ifstream f(filename);
	if (f.is_open())
	{
		while (!f.eof())
		{
			char* man = new char[200];
			f.getline(man, 200);
			char* lastname = new char[50];
			char* sex = new char[50];
			int age;
			char* job = new char[50];
			int payment;
			char* goal = new char[50];
			sscanf_s(man, "%s %s %d %s %d %s", lastname, 50, sex, 50, &age, job, 50, &payment, goal, 50);
			if (string(goal) == "Кредит") enqueue(cred, lastname, sex, age, job, payment, goal);
			else enqueue(dep, lastname, sex, age, job, payment, goal);
		}
		f.close();
	}
	else
		cout << "Файл не открылся";
}

void show_queue(queue& q)
{
	int i = 0;
	while (true)
	{
		man m;
		if (dequeue(q, m))
		{
			cout << ++i << ")\t" << m.lastname << " " << m.sex << " " << m.age << " " << m.job << " " << m.payment << " " << m.goal << "\n";
		}
		else
		{
			break;
		}
	}
}
