#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <math.h>
#include <string>
#define MAXS 10000
template <class T>
struct Node {
    T data; //значение узла
    Node* next; // указатель на некст узел
};
template <class T>
class TStack {
private:
    Node<T>* top; // указатель на верхний элемент стека
    size_t maxSize; // максимальный размкер стека
    size_t currentSize; // текущее кол-во элементов
public:
    TStack(size_t size = MAXS);
    ~TStack();
    TStack(const TStack& s);
    TStack& operator=(const TStack<T>& s);
    bool operator==(const TStack& s) const;
    bool operator!=(const TStack& s) const;
    void Push(T val);
    T Pop();
    bool Empty() const;
    bool Full() const;
    T Top() const;
    void Clear(); // тот же деструктор
    bool Check(const std::string& str);
};
template <class T>
TStack<T>::TStack(size_t size) : maxSize(size), currentSize(0), top(nullptr) {
    if (size <= 0)
        throw - 1;
    if (size > MAXS)
        throw - 1;
}
template <class T>
TStack<T>::~TStack() {
    while (!Empty()) {
        Pop();
    }
}
template <class T>
TStack<T>::TStack(const TStack<T>& s) : maxSize(s.maxSize), currentSize(s.currentSize), top(nullptr) {
    if (s.top == nullptr) {
        top = nullptr;
    }
    else {
        Node<T>* current = s.top;
        Node<T>* last = nullptr;
        while (current != nullptr) {
            Node<T>* newNode = new Node<T>;
            newNode->data = current->data;
            newNode->next = nullptr;

            if (last == nullptr) {
                top = newNode;
            }
            else {
                last->next = newNode;
            }
            last = newNode;
            current = current->next;
        }
    }
}
template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& s) {
    if (this == &s)
        return *this;
    Clear();
    maxSize = s.maxSize;
    currentSize = s.currentSize;
    if (s.top == nullptr) {
        top = nullptr;
    }
    else {
        Node<T>* current = s.top;
        Node<T>* last = nullptr;
        while (current != nullptr) {
            Node<T>* newNode = new Node<T>;
            newNode->data = current->data;
            newNode->next = nullptr;

            if (last == nullptr) {
                top = newNode;
            }
            else {
                last->next = newNode;
            }

            last = newNode;
            current = current->next;
        }
    }
    return *this;
}
template <class T>
bool TStack<T>::operator==(const TStack<T>& s) const {
    if (maxSize != s.maxSize) {
        return false;
    }
    if (currentSize != s.currentSize) {
        return false;
    }
    Node<T>* current1 = top;
    Node<T>* current2 = s.top;
    while (current1 != nullptr) {
        if (current1->data != current2->data) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return true;
}
template <class T>
bool TStack<T>::operator!=(const TStack<T>& s) const {
    return !(*this == s);
}
template <class T>
void TStack<T>::Push(T val) {
    if (Full())
        throw - 1;
    Node<T>* newNode = new Node<T>;
    newNode->data = val;
    newNode->next = top;
    top = newNode;
    currentSize++;
}
template <class T>
T TStack<T>::Pop() {
    if (Empty())
        throw - 1;
    Node<T>* temp = top;
    T value = top->data;
    top = top->next;
    delete temp;
    currentSize--;
    return value;
}
template <class T>
bool TStack<T>::Empty() const {
    return top == nullptr;
}
template <class T>
bool TStack<T>::Full() const {
    return currentSize >= maxSize;
}
template <class T>
T TStack<T>::Top() const {
    if (Empty())
        throw - 1;
    return top->data;
}
template <class T>
void TStack<T>::Clear() {
    while (!Empty()) {
        Pop();
    }
}
template <class T>
bool TStack<T>::Check(const std::string& str) {
    TStack<char> s;
    for (char ch : str) {
        if (ch == '(') {
            s.Push('(');
        }
        else if (ch == ')') {
            if (s.Empty()) {
                return false;
            }
            s.Pop();
        }
    }
    return s.Empty();
}

class TCalc {
    std::string infix;
    std::string postfix;
    TStack<double> StNum;
    TStack<char> StChar;

public:
    TCalc();
    void SetInfix(std::string _infix) { infix = _infix; }
    void SetPostfix(std::string _postfix) { postfix = _postfix; }
    std::string GetInfix() { return infix; }
    std::string GetPostfix() { return postfix; }
    void ToPostfix();
    double CalcPostfix();
    double Calc();
    int Prior(char op);
};
TCalc::TCalc() : StNum(MAXS), StChar(MAXS) {}
int TCalc::Prior(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^')
        return 3;
    return 0;
}
double TCalc::CalcPostfix() {
    StNum.Clear();
    std::string number = "";
    for (int i = 0; i < postfix.length(); i++) {
        if (postfix[i] >= '0' && postfix[i] <= '9' || postfix[i] == '.' || postfix[i] == '_') {
            if (postfix[i] == '_') {
                number += '-';
            }
            else {
                number += postfix[i];
            }
        }
        else if (postfix[i] == ' ' && !number.empty()) {
            StNum.Push(stod(number));
            number = "";
        }
        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
            double Num2 = StNum.Pop();
            double Num1 = StNum.Pop();
            if (postfix[i] == '+') {
                StNum.Push(Num1 + Num2);
            }
            else if (postfix[i] == '-') {
                StNum.Push(Num1 - Num2);
            }
            else if (postfix[i] == '*') {
                StNum.Push(Num1 * Num2);
            }
            else if (postfix[i] == '/') {
                if (Num2 == 0) throw - 1;
                StNum.Push(Num1 / Num2);
            }
            else if (postfix[i] == '^') {
                StNum.Push(pow(Num1, Num2));
            }
        }
    }
    if (!number.empty()) {
        StNum.Push(stod(number));
    }
    double a = StNum.Pop();
    if (!StNum.Empty()) {
        throw - 1;
    }
    return a;
}
void TCalc::ToPostfix() {
    postfix = "";
    StChar.Clear();
    std::string s = "(" + infix + ")";
    if (!StChar.Check(infix)) {
        throw - 1;
    }

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            StChar.Push(s[i]);
        }
        else if (s[i - 1] == '(' && s[i] == '-') {
            postfix += "_";
        }
        else if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
            while (i < s.length() && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) {
                postfix += s[i];
                i++;
            }
            i--;
            postfix += ' ';
        }
        else if (s[i] == ')') {
            while (!StChar.Empty() && StChar.Top() != '(') {
                postfix += StChar.Pop();
                postfix += ' ';
            }
            if (!StChar.Empty()) {
                StChar.Pop();
            }
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
            while (!StChar.Empty() && Prior(StChar.Top()) >= Prior(s[i])) {
                postfix += StChar.Pop();
                postfix += ' ';
            }
            StChar.Push(s[i]);
        }
    }
    if (!StChar.Empty()) {
        throw - 1;
    }
}
double TCalc::Calc() {
    std::string str = "(" + infix + ")";
    StNum.Clear();
    StChar.Clear();
    if (!StChar.Check(infix)) {
        throw - 1;
    }
    for (int i = 0; i < str.size(); i++)
    {
        char tmp = str[i];
        if (tmp == '(')
            StChar.Push(tmp);
        else if (str[i - 1] == '(' && tmp == '-')
            str[i] = '_';
        else if (i > 0 && tmp >= '0' && tmp <= '9' && str[i - 1] == '_')
        {
            size_t idx;
            double num = std::stod(&tmp, &idx);
            StNum.Push(num * (-1.0));
            i += idx - 1;
        }
        else if (tmp >= '0' && tmp <= '9' || tmp == '.') {
            size_t idx;
            double num = std::stod(&tmp, &idx);
            StNum.Push(num);
            i += idx - 1;
        }
        else if (tmp == ')')
        {
            char a = StChar.Pop();
            while (a != '(')
            {
                double Num2 = StNum.Pop();
                double Num1 = StNum.Pop();
                if (a == '+')
                    StNum.Push(Num1 + Num2);
                if (a == '-')
                    StNum.Push(Num1 - Num2);
                if (a == '*')
                    StNum.Push(Num1 * Num2);
                if (a == '/')
                {
                    if (Num2 == 0)
                        throw - 1;
                    StNum.Push(Num1 / Num2);
                }
                if (a == '^')
                {
                    int p = pow(Num2, -1);
                    if (p % 2 == 0 && Num1 < 0)
                        throw - 1;
                    StNum.Push(pow(Num1, Num2));
                }
                a = StChar.Pop();
            }
        }
        else if (tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/' || tmp == '^')
        {
            while (Prior(StChar.Top()) >= Prior(tmp)) {
                double Num2 = StNum.Pop();
                double Num1 = StNum.Pop();
                char a = StChar.Pop();
                if (a == '+')
                    StNum.Push(Num1 + Num2);
                if (a == '-')
                    StNum.Push(Num1 - Num2);
                if (a == '*')
                    StNum.Push(Num1 * Num2);
                if (a == '/')
                {
                    if (Num2 == 0)
                        throw - 1;
                    StNum.Push(Num1 / Num2);
                }
                if (a == '^')
                {
                    int p = pow(Num2, -1);
                    if (p % 2 == 0 && Num1 < 0)
                        throw - 1;
                    StNum.Push(pow(Num1, Num2));
                }
            }
            StChar.Push(tmp);
        }
    }
    double a = StNum.Pop();
    if (StNum.Empty() == 0)
        throw - 1;
    return a;
}

