#pragma once
class PointStack
{
	int x, y;
	PointStack *next;
public:
	PointStack();
	PointStack(PointStack &S);
	~PointStack();
	void Stackin(int X, int Y);
	void Stackout(int &X, int &Y);
	bool Isnull();
};

