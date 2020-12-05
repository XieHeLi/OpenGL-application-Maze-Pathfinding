#include "MazeMap.h"
#include<fstream>
#include<iostream>
#include<gl/glut.h>
#include<time.h>
using namespace std;

MazeMap::MazeMap()
{
	int i, j;
	if (N % 2 == 0) 
	{
		for (i = 0; i < N; i++)
		{
			Map[0][i] = 1;
			Map[i][0] = 1;
			Map[i][N] = 1;
			Map[N][i] = 1;
		}
		for (i = 1; i < N - 1; i++)
		{
			for (j = 1; j < N - 1; j++)
			{
				Map[i][j] = 0;
			}
		}
		Map[N - 2][N - 1] = 0;
	}
	else 
	{
		for (i = 0; i < N; i++)
			for (j = 0; j <= N; j++)
			{
				if (i % 2 != 0 && j % 2 != 0)
					Map[i][j] = 3;
				else
					Map[i][j] = 1;
			}
	}
	Map[1][1] = 0;
	
	xin = 1;
	yin = 1;
	xout = N - 2;
	yout = N - 2;
	playerX = xin;
	playerY = yin;
}
MazeMap::MazeMap(MazeMap &M)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			Map[i][j] = M.Map[i][j];
		}
	}
	xin = M.xin;
	yin = M.yin;
	xout = M.xout;
	yout = M.yout;
	playerX = xin;
	playerY = yin;
}
MazeMap::MazeMap(const char *s) {
	int n, i, j;
	fstream f(s, ios::in);
	f >> n >> xin >> xout >> yin >> yout;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			f >> Map[i][j];
		}
	}
	f.close();
	playerX = xin;
	playerY = yin;
}
MazeMap::~MazeMap()
{
}
int MazeMap::Getxin()
{
	return xin;
}
int MazeMap::Getxout() {
	return xout;
}
int MazeMap::Getyin() {
	return yin;
}
int MazeMap::Getyout() {
	return yout;
}
int MazeMap::GetplayerX() {
	return playerX;
}
int MazeMap::GetplayerY() {
	return playerY;
}
void MazeMap::ReadFile(const char *s)
{
	int n,i,j;
	fstream f(s, ios::in);
	f >> n >> xin >> yin >> xout >> yout;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			f >> Map[i][j];
		}
	}
	f.close();
	playerX = xin;
	playerY = yin;
}
bool MazeMap::FindPath(int x,int y)
{
	if (x<0 || x>N - 1 || y<0 || y>N - 1)return false;
	if (x==xout&&y== yout)
	{
		Map[x][y] = 2;
		return true;
	}
	else
	{
		if (Map[x][y] == 0)//当前点可以走
		{
			Map[x][y] = 2;//先标记为通路
			if (FindPath(x, y + 1) || FindPath(x + 1, y) || FindPath(x - 1, y) || FindPath(x, y - 1))//如果能递归找到出口
				return true;
			else
			{
				Map[x][y] = 0;//否则当前路口不可走
				return false;
			}
		}
		else return false;

	}
}
bool MazeMap::IsPlayerFound()
{
	if (playerX == xout && playerY == yout)return true;
	else return false;
}
void MazeMap::DrawMyself()
{
	float x0, y0, x1, y1;
	int i,j;
	
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++) {
			if (Map[i][j] == 1)
			{
				glColor3f(0.0, 0.0, 0.0);
				x0 = ((float)j - (float)N / 2) * 2 / (float)N;
				y0 = ((float)N / 2 - (float)i - 1) * 2 / (float)N;
				x1 = ((float)j - (float)N / 2 + 1) * 2 / (float)N;
				y1 = ((float)N / 2 - (float)i) * 2 / (float)N;
				glRectf(x0, y0, x1, y1);
			}
			else if (Map[i][j] == 2)
			{
				glColor3f(0.41, 0.36, 0.22);
				x0 = ((float)j - (float)N / 2) * 2 / (float)N;
				y0 = ((float)N / 2 - (float)i - 1) * 2 / (float)N;
				x1 = ((float)j - (float)N / 2 + 1) * 2 / (float)N;
				y1 = ((float)N / 2 - (float)i) * 2 / (float)N;
				glRectf(x0, y0, x1, y1);
			}
			else continue;
		}
	}
	glColor3f(0.8,0.14,0.19);
	x0 = ((float)playerY - (float)N / 2) * 2 / (float)N;
	y0 = ((float)N / 2 - (float)playerX - 1) * 2 / (float)N;
	x1 = ((float)playerY - (float)N / 2 + 1) * 2 / (float)N;
	y1 = ((float)N / 2 - (float)playerX) * 2 / (float)N;
	glRectf(x0, y0, x1, y1);
	glFlush();
}
void MazeMap::PlayerEvent(int key, int X, int Y) 
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (playerY-1<0)break;
		if (Map[playerX][playerY - 1] == 1)break;
		playerY --;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		if (playerY + 1 > N-1)break;
		if (Map[playerX][playerY + 1] == 1)break;
		playerY++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		if (playerX - 1 <0)break;
		if (Map[playerX-1][playerY] == 1)break;
		playerX--;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		if (playerX + 1 > N - 1)break;
		if (Map[playerX+1][playerY] == 1)break;
		playerX++;
		glutPostRedisplay();
		glutPostRedisplay();
		break;
	}
}
void MazeMap::ClearPath()
{
	int i, j;
	for (i = 0; i < N; i++) 
	{
		for (j = 0; j < N; j++)
			if (Map[i][j] != 1)Map[i][j] = 0;
	}
}
bool  MazeMap::IsNoMark()
{
	int i, j;
	for (i = 1; i < N - 1; i += 2)
		for (j = 1; j < N - 1; j += 2)
		{
			if (Map[i][j] == 3)return true;
		}
	return false;
}
bool  MazeMap::IsOtherNotVisit(int currentx, int currenty, int &neighborx, int &neighbory)
{
	if ((currenty + 2) < (N - 1) && Map[currentx][currenty + 2] == 3)//右边不是墙而且没访问过
	{
		neighborx = currentx;
		neighbory = currenty + 2;
		return true;
	}
	else if ((currentx + 2) < (N - 1) && Map[currentx + 2][currenty] == 3)//下边
	{
		neighborx = currentx + 2;
		neighbory = currenty;
		return true;
	}
	else if ((currentx - 2) > 0 && Map[currentx - 2][currenty] == 3)//左
	{
		neighborx = currentx - 2;
		neighbory = currenty;
		return true;
	}
	else if ((currenty - 2) > 0 && Map[currentx][currenty - 2] == 3)//上
	{
		neighborx = currentx;
		neighbory = currenty - 2;
		return true;
	}
	else return false;
}
bool  MazeMap::IsNotVisit(int currentx, int currenty, int &neighborx, int &neighbory)
{
	int direction = 0;//0123分别代表右下左上
	bool result = false;
	srand((unsigned)time(NULL));
	direction = rand() % 4;
	switch (direction)
	{
	case 0:
		if ((currenty + 2) < (N - 1) && Map[currentx][currenty + 2] == 3)//右边不是墙而且没访问过
		{
			neighborx = currentx;
			neighbory = currenty + 2;
			result = true;
		}
		else result = IsOtherNotVisit(currentx, currenty, neighborx, neighbory);
		break;
	case 1:
		if ((currentx + 2) < (N - 1) && Map[currentx + 2][currenty] == 3)//下边
		{
			neighborx = currentx + 2;
			neighbory = currenty;
			result = true;
		}
		else result = IsOtherNotVisit(currentx, currenty, neighborx, neighbory);
		break;
	case 2:
		if ((currentx - 2) > 0 && Map[currentx - 2][currenty] == 3)//左
		{
			neighborx = currentx - 2;
			neighbory = currenty;
			result = true;
		}
		else result = IsOtherNotVisit(currentx, currenty, neighborx, neighbory);
		break;
	case 3:
		if ((currenty - 2) > 0 && Map[currentx][currenty - 2] == 3)//上
		{
			neighborx = currentx;
			neighbory = currenty - 2;
			result = true;
		}
		else result = IsOtherNotVisit(currentx, currenty, neighborx, neighbory);
		break;
	default:
		result = IsOtherNotVisit(currentx, currenty, neighborx, neighbory);
		break;
	}
	return result;
}
void  MazeMap::RemoveWall(int x0, int y0, int x1, int y1)
{
	if (x0 % 2 == 0 || y0 % 2 == 0 || x1 % 2 == 0 || y1 % 2 == 0)return;
	else
	{
		if (x0 == x1 && y0 + 2 == y1)//在右侧
			Map[x0][y0 + 1] = 0;
		if (y0 == y1 && x0 + 2 == x1)//在下侧
			Map[x0 + 1][y0] = 0;
		if (x0 == x1 && y0 - 2 == y1)//在上侧
			Map[x0][y0 - 1] = 0;
		if (y0 == y1 && x0 - 2 == x1)//在左侧
			Map[x0 - 1][y0] = 0;
	}
}
void  MazeMap::Creatmap_Recursive_backtracker()
{
	if (N % 2 == 0)return;
	int currentx = 1, currenty = 1, neighborx, neighbory,i;
	Map[currentx][currenty] = 4;//将起点标记为已访问
	PointStack stack;
	while (IsNoMark())
	{
		if (IsNotVisit(currentx, currenty, neighborx, neighbory))
		{
			stack.Stackin(currentx, currenty);//当前位置入栈
			RemoveWall(currentx, currenty, neighborx, neighbory);
			currentx = neighborx;
			currenty = neighbory;
			Map[currentx][currenty] = 4;//将当前点标记为已访问
		}
		else if (!stack.Isnull())
		{
			stack.Stackout(currentx, currenty);
		}
	}
	ClearPath();
	yout = N - 2;
	for (i = N - 2; i > 0; i--)
	{
		xout = i;
		if (FindPath(xin, yin))
		{
			xout = i + 1;
			Map[xout][yout] = 0;
			yin -= yin;
			Map[xin][yin] = 0;
			ClearPath();
			return;
		}
		ClearPath();
	}
}