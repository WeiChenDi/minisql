#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include"Interpter.h"
#include"API.h"
#include"CatalogManager.h"
#include"RecordManager.h"
#include"IndexManager.h"
#include<time.h>

#pragma warning(disable:4996)

using namespace std;

BufferManager bm;
CatalogManager cm;
RecordManager rm;
IndexManager im;
Interpreter Itp;


int main()
{
	API ap;
	ap.cm = &cm;
	ap.rm = &rm;
	ap.InitProgram();
	string str;
	cout << "Welcome to minisql!" << endl;
	cout << "Author: Wei Chendi, Bai Lin, Su Man" << endl;
	cout << endl;

	while (1)
	{
		cout << "minisql>>";
		string str;
		char c;
		c = getchar();
		while (c != ';')
		{
			if (c == '\n')
			{
				c = getchar();
				continue;
			}
			str += c;
			c = getchar();
		}
		str += ';';
		double dur;
		clock_t start, end;
		start = clock();
		Itp.InterpreterFunc(ap, str);
		end = clock();
		dur = (double)(end - start);
		printf("Use Time:%f s\n\n", (dur / CLOCKS_PER_SEC));
		cout << string(100, '=') << endl;
	}
	system("pause");
}

