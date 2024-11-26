#include <iostream>
#include "TSack.h"
using namespace std;
int main()
{
	TStack<int> s(9);
	s.Push(8);
	s.Push(7);
	s.Push(6);
	TCalc c;
	c.SetInfix("3+2-1");
	c.ToPostfix();
	cout << c.GetPostfix() << endl;
	c.SetInfix("6.2+4");
	c.ToPostfix();
	cout << c.CalcPostfix() << endl;
	c.SetInfix("1-3+(5-3)^2+5/2+9*2");
	cout << c.Calc() << endl;
	return 0;
}