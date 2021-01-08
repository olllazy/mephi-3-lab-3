#pragma once
#ifndef G_INTERFACE_H
#define G_INTERFACE_H 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <conio.h> 
#include <Windows.h>

#include "graph.h"
#include "tests.h"

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::cin;


//ofstream fout; //����



Graph* printmenu12() {
	while (true)
	{
		fout.open(PATH_FILE);
		//fout << "������ � ������� � �++";
		
		cout << "		(1.1)������ ���� ��������������." << endl;
		cout << "	����������, ����������� ������� �� ��������� ������� - �������� �� ����� ������." << endl;
		cout << "	||������� ���������� ������ � �����: ";
		int length = readInt(1, INT_MAX);
		fout << length << ' ';
		
		cout << "	||���� ���������������? " << endl;
		cout << "	||1 - ���;" << endl;
		cout << "	||2 - ��." << endl;
		cout << "	||������� ��� �����: ";
		int choice = readInt(1, 2);
		fout << choice - 1 << ' ';

		cout << "	||���� ����������? " << endl;
		cout << "	||1 - ���;" << endl;
		cout << "	||2 - ��." << endl;
		cout << "	||������� ��� �����: ";
		int weight = readInt(1, 2);
		fout << weight - 1 << endl;

		cout << "	����������, ������� ���� ����� �������� ��������." << endl;
		cout << "	> ������� ���������� � 1;" << endl;
		cout << "	> ���� ���� �� ���������������, �� ��������� ���� �� �����." << endl << endl;
		
		while (true) {
			cout << "	||������� ��������� �������: ";
			choice = readInt(1, length);
			fout << choice - 1 << ' ';

			cout << "	||������� �������� �������: ";
			choice = readInt(1, length);
			fout << choice - 1;

			if (weight == 2) {
				cout << "	||������� ��� �����: ";
				int choice = readInt(1,INT_MAX);
				fout <<' '<< choice;
			}
			fout << endl;
			cout << "	��� ���������� ����� ���� ������� '�����': ";
			string line;
			std::getline(cin, line);
			cout << "	__________" << endl << endl;
			if (line == "�����" || line == "�����")
				break;
		}		
		fout.close();
		return makeGraph(PATH_FILE);
		//return nullptr;
	}
}
Graph* printmenu11() {
	while (true)
	{
		cout << "		(1.1)������ ���� �������������." << endl;
		cout << "	||1 - �� ���������������, �� ����������;" << endl;
		cout << "	||2 - �� ���������������, ����������;" << endl;
		cout << "	||3 - ���������������, �� ����������;" << endl;
		cout << "	||4 - ���������������, ����������;" << endl;
		cout << "	||" << endl;
		cout << "	||5 - ����� � ���� (1)������� ����." << endl;
		cout << "	||������� ����� ���������� ���� ��������: ";
		int choice = readInt(1, 5);
		switch (choice)
		{
		case 1:
			return makeGraph(PATH_FILE1);
			break;
		case 2:
			return makeGraph(PATH_FILE2);
			break;
		case 3:
			return makeGraph(PATH_FILE3);
			break;
		case 4:
			return makeGraph(PATH_FILE4);
			break;
		case 5:
			return nullptr;
			break;
		}
	}
}
Graph* printmenu1() {
	while (true)
	{
		cout << "		(1)������� ����." << endl;
		cout << "	|1 - ������ �������������;" << endl;
		cout << "	|2 - ������ ��������������;" << endl;
		cout << "	|" << endl;
		cout << "	|3 - ����� � ������� ����." << endl;
		cout << "	|������� ����� ���������� ���� ��������: ";
		int choice = readInt(1, 3);
		switch (choice)
		{
		case 1:
			return printmenu11();
			break;
		case 2:
			return printmenu12();
			break;
		case 3:
			return nullptr;
			break;
		}
	}
}
void printmenu32(Graph* graph) {
	while (true)
	{
		cout << "		(3.2)����� ������������� �����." << endl;
		cout << "	||1 - ��� ����� ����;" << endl;
		cout << "	||2 - � ������ ���� (��� �� ���������� ��� ������� ����� ����� 1);" << endl;
		cout << "	||3 - ��� ��������;" << endl;
		cout << "	||" << endl;
		cout << "	||4 - ����� � ���� (3)������� ��� ������." << endl;
		cout << "	||������� ����� ���������� ���� ��������: ";
		int choice = readInt(1, 4);
		switch (choice)
		{
		case 1:
			//return printmenu31(Graph * graph);
			t_graph_shortestPathBFS(graph);
			break;
		case 2:
			t_graph_dijkstra(graph);
			break;
		case 3:
			t_graph_paths(graph);
			break;
		case 4:
			return;
			break;
		}
	}
}

void printmenu3(Graph* graph) {
	while (true)
	{
		cout << "		(3)�������� ��� ������." << endl;
		cout << "	|1 - ���������� ����;" << endl;
		cout << "	|2 - ����� ������������� ����;" << endl;
		cout << "	|" << endl;
		cout << "	|3 - ����� � ������� ����." << endl;
		cout << "	|������� ����� ���������� ���� ��������: ";
		int choice = readInt(1, 3);
		switch (choice)
		{
		case 1:
			//return printmenu31(Graph * graph);
			t_graph_painting(graph);
			break;
		case 2:
			printmenu32(graph);
			break;
		case 3:
			return;
			break;
		}
	}
}

void printmenu0() {
	Graph* graph = nullptr;
	while (true)
	{
		cout << "	������� ����." << endl;
		cout << "1 - ������� ����;" << endl;
		cout << "2 - �������� ���������� � ��������� �����;" << endl;
		//cout << "2 - ������ ���������� �������� (� ������);" << endl;
		cout << "3 - �������� ��� ������;" << endl;
		//cout << "4 - ������ �������� (�����������, ��� ��, ��� �����);" << endl;
		//cout << "6 - ������ ������� �� �����������;" << endl;
		//cout << "7 - ������ ������� ����� �����������;" << endl;
		cout << endl;
		cout << "4 - �����." << endl;
		cout << "5 - TESTS" << endl;
		cout << "������� ����� ���������� ���� ��������: ";
		int choice = readInt(1, 5);
		switch (choice)
		{
		case 1:			
			graph = printmenu1();
			cout << endl;
			break;		
		case 2:
			if (graph == nullptr) {
				cout << "���� �� ��� ������." << endl;
				break;
			}
			else {
				print(graph);
				break;
			}
		case 3:
			if (graph == nullptr) {
				cout << "���� �� ��� ������." << endl;
				break;
			}
			else {
				printmenu3(graph);
				break;
			}
		case 4:
			return;
			break;
		case 5:
			tests();
			break;
		}
	}
}

void program() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	printmenu0();
	return;
}


#endif // !G_INTERFACE_H
