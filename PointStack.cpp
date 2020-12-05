#include "PointStack.h"
#include<iostream>
using namespace std;

PointStack::PointStack()
{
	x = 0;
	y = 0;
	next = NULL;
}
PointStack::PointStack(PointStack &S) 
{
	x = 0;
	y = 0;
	next = NULL;
	if (S.next == NULL)return;
	PointStack *p, *q, *L;
	L = this;
	q = S.next;
	while (q != NULL)
	{
		p = new PointStack;
		if (p == NULL) {
			cout << "¿½±´Òç³ö" << endl;
			return;
		}
		p->x = q->x;
		p->y = q->y;
		p->next = NULL;
		L->next = p;
		L = L->next;
		q = q->next;
	}
	p = NULL;
	q = NULL;
	L = NULL;
}

PointStack::~PointStack()
{
	PointStack *p, *q;
	q = next;
	while (q != NULL)
	{
		p = q;
		q = q->next;
		p->next = NULL;
		delete p;
	}
	p = NULL;
	q = NULL;
}
void PointStack::Stackin(int X, int Y)
{
	PointStack *p, *q;
	p = next;
	q = new PointStack;
	if (q == NULL) {
		cout << "Õ»Òç³ö" << endl;
		return;
	}
	q->x = X;
	q->y = Y;
	next = q;
	q->next = p;
	p = NULL;
	q = NULL;
}
void PointStack::Stackout(int &X, int &Y)
{
	if (next == NULL)
	{
		cout << "Õ»¿Õ" << endl;
		return;
	}
	PointStack *p, *q;
	p = next;
	q = p->next;
	next = q;
	p->next = NULL;
	X = p->x;
	Y = p->y;
	delete p;
	p = NULL;
	q = NULL;
}
bool PointStack::Isnull() {
	if (next == NULL)return true;
	else return false;
}