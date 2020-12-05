#include<iostream>
#include<gl\glut.h>
#include<Windows.h>
#include"MazeMap.h"
#include<iostream>
using namespace std;
MazeMap maze;
//�Թ���ͼ�Ĵ洢·��
const char *s = "E://Program Files (x86)/Microsoft Visual Studio/frusits/data_and_struct/Maze/map.txt";
bool looper = true;
bool jugpath = false;
void DrawString(void *font, const char s[], float x = -0.4, float y = 0.1, float r = 0, float g = 0, float b = 0)//���ַ���ʾ	
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
	glutSwapBuffers();//˫�����½�������������ָ��
}
void myReshape(int w, int h)//�����ڸı�ʱ
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
void timer(int p)//ʱ��ص�����
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
void special(int key, int x, int y)//��Ӧ���������
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
	cout << "ѡ���Թ�����ģʽ��" << endl<<"��1���Զ�����"<<endl<<"��2���ļ�����"<<endl;
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
	glutInit(&argc, argv);//��GLUT���г�ʼ��
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//ʹ��RGB��ɫ
	glutInitWindowPosition(200, 100);//���ô�������Ļ�е�λ��
	glutInitWindowSize(600, 600);//���ô��ڵĴ�С��
	glutCreateWindow("��   ��   ��   ��");//����ǰ�����õ���Ϣ�������ڡ�����������Ϊ���ڵı��⡣

	glutReshapeFunc(&myReshape);//���ڴ�С�ı�ʱ��Ҫ��ȡ����Ϊ
	glutDisplayFunc(&display);//����һ������������Ҫ���л�ͼʱ����������ͻᱻ���á�
	glutTimerFunc(150, timer, 0);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(special);//��Ӧ�����ϵ����ⰴ��
	glutMainLoop();//����һ����Ϣѭ����
	return 0;
}