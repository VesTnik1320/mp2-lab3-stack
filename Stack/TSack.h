#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;
const int MAXS = 10000;
template <class T>
class TStack
{
	T* pMem;
	int MaxSize, Num;
public:
	TStack(int _MaxSize = 10); //����������� �������������
	~TStack(); //����������
	TStack(const TStack& s); //����������� �����������
	int GetSize() { return MaxSize; } // ������ �����
	int GetStartIndex() { return Num; } // ������ Num
	TStack& operator=(const TStack<T> s); //�������� ������������
	bool operator==(const TStack& s) const; //��������� �����
	bool operator!=(const TStack& s) const; //��������� �� �����
	T Pop(); //���������� �������� �� �����
	void Push(T val); //���������� �������� � ����
	bool Empty() const; // �������� �� ������� Num = -1
	bool Full() const; // �������� �� ������� Nun = MaxSize-1
	T Top() const; //���������� �� �������� �����
	void Clear(); //������� ����� Clear
	bool Check(string str);
	friend istream& operator>>(istream& in, TStack& s) //���� ��������
	{
		if (this->isFull())
			throw - 1;
		Num++;
		in >> s.pMem[Num];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TStack& s) //????? ????????
	{
		if (this->isEmpty())
			throw - 1;
		out << s.pMem[Num];
		return out;
	}
};
template <class T>
TStack<T>::TStack(int _MaxSize)
{
	if (_MaxSize < 0 || _MaxSize > MAXS)
		throw - 1;
	MaxSize = _MaxSize;
	Num = -1;
	pMem = new T[MaxSize];
}
template <class T>
TStack<T>::TStack(const TStack<T>& s)
{
	if (s.MaxSize < 0 || s.MaxSize > MAXS || s.Num < -1 || s.Num >= s.MaxSize)
		throw - 1;
	MaxSize = s.MaxSize;
	Num = s.Num;
	pMem = new T[MaxSize];
	for (int i = 0; i <= Num; i++)
		pMem[i] = s.pMem[i];
}
template <class T>
TStack<T>::~TStack()
{
	delete[] pMem;
}
template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T> s)
{
	if (this == &s)
		return *this;
	if (MaxSize != s.MaxSize)
	{
		MaxSize = s.MaxSize;
		delete[] pMem;
		pMem = new T[MaxSize];
	}
	Num = s.Num;
	for (int i = 0; i <= Num; i++)
		pMem[i] = s.pMem[i];
	return *this;
}
template <class T>
bool TStack<T>::operator==(const TStack& s) const
{
	if (this == &s)
		return true;
	if (MaxSize != s.MaxSize)
		return false;
	if (Num != s.Num)
		return false;
	for (int i = 0; i <= Num; i++) {
		if (pMem[i] != s.pMem[i])
			return false;
	}
	return true;
}
template <class T> // ���������
bool TStack<T>::operator!=(const TStack& s) const
{
	return !(*this == s);
}
template <class T>
bool TStack<T>::Empty() const
{
	if (Num == -1)
		return true;
	return false;
}
template <class T>
bool TStack<T>::Full() const
{
	if (Num == MaxSize - 1)
		return true;
	return false;
}
template <class T>
T TStack<T>::Pop()
{
	if (this->Empty())
		throw - 1;
	T tmp = pMem[Num];
	Num--;
	return tmp;
}
template <class T>
void TStack<T>::Push(T val)
{
	if (this->Full())
		throw - 1;
	Num++;
	pMem[Num] = val;
}
template <class T>
T TStack<T>::Top() const
{
	if (this->Empty())
		throw - 1;
	return pMem[Num];
}
template <class T>
void TStack<T>::Clear() {
	Num = -1;
}
template <class T>
bool TStack<T>::Check(string str)
{
	TStack<char> s;
	bool res = true;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
			s.Push('(');
		if (str[i] == ')')
		{
			if (s.Empty())
				return false;
			s.Pop();
		}
	}
	if (!s.Empty())
		return false;
	return true;
}
class TCalc
{
	string infix;
	string postfix;
	TStack<double> StNum;
	TStack<char> StChar;
public:
	TCalc();//����������� ����� ���� ������
	void SetInfix(string _infix) {
		infix = _infix;
	}
	void SetPostfix(string _postfix) {
		postfix = _postfix;
	}
	string GetInfix() {
		return infix;
	}
	string GetPostfix() {
		return postfix;
	}
	void ToPostfix(); //������������� �� infix � postfix
	double CalcPostfix();
	double Calc();
	int Prior(char op);
};
TCalc::TCalc()
{

}
void TCalc::ToPostfix()
{

}
double TCalc::CalcPostfix() {
	StNum.Clear();
	StChar.Clear();
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] >= '0' && postfix[i] <= '9')
			StNum.Push(postfix[i] - '0');
		if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/')
		{
			double Num2 = StNum.Pop();
			double Num1 = StNum.Pop();
			if (postfix[i] == '+')
				StNum.Push(Num1 + Num2);
			if (postfix[i] == '-')
				StNum.Push(Num1 - Num2);
			if (postfix[i] == '*')
				StNum.Push(Num1 * Num2);
			if (postfix[i] == '/')
			{
				if (Num2 == 0)
					throw - 1;
				StNum.Push(Num1 / Num2);
			}
		}
		//������� �������, �������� ����� �� ������� - ���� ���� - ������, ����� ����������
		return StNum.Pop();
	}
}
void TCalc::ToPostfix() {
	postfix = "";
	StChar.Clear();
	string s = "(" + infix + ")";
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(')
			StChar.Push(s[i]);
		else if (s[i] <= '9' && s[i] >= '0')
			postfix += s[i];
		else if (s[i] == ')')
		{
			char a = StChar.Pop();
			while (a != '(')
			{
				postfix += a;
				a = StChar.Pop();
			}
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
		{
			while (Prior(StChar.Top()) >= Prior(s[i]))
				postfix += StChar.Pop();
			StChar.Push(s[i]);
		}
	}
}
