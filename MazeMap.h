#pragma once
#include"PointStack.h"
const int N = 25;
class MazeMap
{
	int Map[N][N];
	int xin,yin,xout, yout;//�Թ���ںͳ��ڵ�����
	int playerX, playerY;//���λ��
	friend class PointStack;
	bool IsNoMark();
	bool IsOtherNotVisit(int currentx, int currenty, int &neighborx, int &neighbory);
	bool IsNotVisit(int currentx, int currenty, int &neighborx, int &neighbory);
	void RemoveWall(int x0, int y0, int x1, int y1);
public:
	MazeMap();
	MazeMap(MazeMap &M);
	MazeMap(const char *s);
	~MazeMap();
	int Getxin();
	int Getxout();
	int Getyin();
	int Getyout();
	int GetplayerX();
	int GetplayerY();
	void ReadFile(const char *s);
	bool FindPath(int x = 1, int y = 1);
	void PlayerEvent(int key, int X, int Y);
	void DrawMyself();
	bool IsPlayerFound();//����ҵ�ͨ·����
	void ClearPath();//����Ѿ��ҵ���ͨ·
	void Creatmap_Recursive_backtracker();//�ݹ���ݷ������Թ�
};



