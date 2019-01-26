#ifndef __INTERPTER_H__
#define __INTERPTER_H__
#include <string>
#include <vector>
#include "API.h"
using namespace std;



typedef struct attribute *PtrToAttribute;
struct attribute
{
	string name;
	int type;
	int ifPrimary = 0;
	int ifUnique = 0;
}; 
static vector<attribute> attri;

class Interpreter
{
public:
	string getWord(string str, int* index);
	int InterpreterFunc(API ap, string str);
};


#endif // !__INTERPTER_H__

