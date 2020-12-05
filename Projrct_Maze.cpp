#include<iostream>
#include<gl\glut.h>
#include<Windows.h>
#include"MazeMap.h"
#include<iostream>
using namespace std;
MazeMap maze;
//迷宫地图的存储路径
const char *s = "E://Program Files (x86)/Microsoft Visual Studio/frusits/data_and_struct/Maze/map.txt";
bool looper = true;
bool jugpath = false;
void DrawString(void *font, const char s[], float x = -0.4, float y = 0.1, float r = 0, float g = 0, float b = 0)//画字符提示	
{
	float sum;
	sum = r + g + b;
	r = r / sum;
	g = g / sum;
	b = b / sum;
	glColor3f(r, g, b);
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i < strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]);
	}
}
void display() 
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();//双缓冲下交换两个缓冲区指针
}
void myReshape(int w, int h)//当窗口改变时
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.0, 1.0, -1.0*(GLfloat)h / (GLfloat)w, 1.0*(GLfloat)h / (GLfloat)w, -1.0, 1.0);
	else
		glOrtho(-1.0*(GLfloat)w / (GLfloat)h, 1.0*(GLfloat)w / (GLfloat)h, -1.0, 1.0, -1.0, 1.0);
}
void timer(int p)//时间回调函数
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	maze.DrawMyself();
	
	if (maze.IsPlayerFound())
	{
		looper = false;
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24, "Found!You are so clever!!!", -0.4,0.1,0.8, 0.14, 0.19);
		glFlush();
	}
	else 
	{
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24, "Press any letter for help", -0.4, 0.8, 1, 0, 0);
		glFlush();
	}
	glutSwapBuffers();
	if (looper)
	{
		glutTimerFunc(150, timer, 0);
	}
}
void special(int key, int x, int y)//响应方向键输入
{
	maze.PlayerEvent(key,x,y);
}
void KeyBoard(unsigned char key, int x, int y)
{
	if ((key >= 65 || key<=90) ||( key >= 97 && key<=122))
	{
		jugpath = (!jugpath);
		if (jugpath)
		{
			if (!maze.FindPath(maze.GetplayerX(), maze.GetplayerY()))
			{
				DrawString(GLUT_BITMAP_TIMES_ROMAN_24, "No Path,Bad End!", -0.4, 0.1, 0, 0, 0);
				glFlush();
				looper = false;
			}
			else glutPostRedisplay();
		}
		else
		{
			maze.ClearPath();
			glutPostRedisplay();
		}
	}
}
int main(int argc, char *argv[])
{
	char key;
	cout << "选择迷宫生成模式：" << endl<<"【1】自动生成"<<endl<<"【2】文件读入"<<endl;
	cin >> key;
	switch (key)
	{
	case '1':
		maze.Creatmap_Recursive_backtracker();
		break;
	case'3':
		break;
	default:
		maze.ReadFile(s);
		break;
	}
	glutInit(&argc, argv);//对GLUT进行初始化
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//使用RGB颜色
	glutInitWindowPosition(200, 100);//设置窗口在屏幕中的位置
	glutInitWindowSize(600, 600);//设置窗口的大小。
	glutCreateWindow("东   海   迷   宫");//根据前面设置的信息创建窗口。参数将被作为窗口的标题。

	glutReshapeFunc(&myReshape);//窗口大小改变时需要采取的行为
	glutDisplayFunc(&display);//设置一个函数，当需要进行画图时，这个函数就会被调用。
	glutTimerFunc(150, timer, 0);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(special);//相应键盘上的特殊按键
	glutMainLoop();//进行一个消息循环。
	return 0;
}