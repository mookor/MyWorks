#include "Header.h"
#include <windows.h>
#include <GL/glut.h>
float angle=0;
void  Process_Mouse(int button, int state, int x, int y)
{
	char str[50];
	if (state != GLUT_DOWN) return;		//если кнопка мыши не была отпущена

	if (button == GLUT_LEFT_BUTTON)
	{
		if (!drawing_mode)
		{
			//включить режим отрисовки
			drawing_mode = true;
			//новая ломаная принадлежит текущему набору
			l.group = current_group;
			sprintf(str, "%i groups", max_group + 1);
			glutSetWindowTitle(str);
		}

		//получить координаты точки
		point p = point((GLint)x, height - (GLint)y);
		//добавить их в ломаную
		l.coordinates.push_back(p);
		//указать, что набор не пуст
		prev_space = false;
	}

	glutPostRedisplay();
}

void Display(void) {
	int i, j;
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glPushMatrix();
 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (i = 0; i < v.size(); i++)
	{
		if (v[i].group == current_group)
		{
			glLineWidth(2);

		}
		else {
			
			glLineWidth(triangletypeVec[v[i].group].widht); }
		
		glLineStipple(3, triangletypeVec[v[i].group].type);
		

		glBegin(GL_TRIANGLES);
		for (j = 0; j < v[i].coordinates.size(); j++)
		{
			glColor3ub(colours[v[i].group].red, colours[v[i].group].green, colours[v[i].group].blue);
		
			glVertex2i(v[i].coordinates[j].x, v[i].coordinates[j].y);
		}
		glEnd();
		glDisable(GL_LINE_STIPPLE);

		if (drawing_mode)
		{

			glLineWidth(3.0);

			//установить цвет набора и отрисовать ломаную
			glColor3ub(colours[l.group].red, colours[l.group].green, colours[l.group].blue);
			
			for (j = 0; j < l.coordinates.size(); j++)
			{
				glVertex2i(l.coordinates[j].x, l.coordinates[j].y);
			}
			glEnd();
		}
		char str[50];
		glRotatef(angle, 1, 1, 0);
		sprintf(str, "%i groups", max_group + 1);
		glPopMatrix();
		glutSetWindowTitle(str);
		glFinish();
	}
}

void Process_Normal_Keys(unsigned char key, int x, int y)
{
	if (!drawing_mode)
	{
		if (key == 32)		//пробел
		{
			On_Space_Key();
		}

		if (key == 127)		//delete
		{
			Delete_group();
		}

		if (key == 8)		//backspace
		{
			Delete_primitive();
		}

	
}
		if (key == ',' || key == '.')   
		{
			Create();
		}
		if (key == 'r' || key == 'R')    // Изменение цвета
		{
			Increase_Red();
		}

		if (key == 'g' || key == 'G')
		{
			Increase_Green();
		}
		if (key == 'b' || key == 'B')
		{
			Increase_Blue();
		}
		if (key == 't' || key == 'T')
		{
			DIncrease_Red();
		}

		if (key == 'h' || key == 'H')
		{
			DIncrease_Green();
		}
		if (key == 'n' || key == 'N')
		{
			DIncrease_Blue();
			
		}
	
		                               // движение
		if (key == 'w' || key == 'W')
		{
			MoveUp();
		}
		if (key == 's' || key == 'S')
		{
			MoveDown();
		}
		if (key == 'a' || key == 'A')
		{
			MoveLeft();
		}
		if (key == 'd' || key == 'D')
		{
			MoveRight();
		}
		if (key == '=')
		{
			angle += 0.1;
		}
		if (key == '-')
		{
			angle -= 0.1;
		}
		glutPostRedisplay();
	
}
void SKeyboard(int key, int x, int y){
	switch (key) {
	case GLUT_KEY_DOWN: Down_key();	
		break;
	
	case GLUT_KEY_UP: Up_key();
		break;
}
	glutPostRedisplay();
}

void Initialize() {
	glClearColor(0.1, 0.1, 0.1, 1);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glViewport(0, 0, widht, height);
	 glOrtho(0.0, widht, 0.0, height,-512,512);

	 drawing_mode = false;
	 max_group = 0;
	 current_group = 0;
	 prev_space = false;

	 colours.push_back(colour(150, 150, 150, current_group));
	 triangletypeVec.push_back(triangletype(1.0, 0xFFFF, current_group));
	
}

void Reshape(GLint w, GLint h)
{
	widht = w;
	height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, widht, height);
	gluOrtho2D(0.0, widht, 0.0, height);
}
void timer(int)
{

	glutPostRedisplay();
	glutTimerFunc(50, timer, 0);
}

void main(int argc, char *argv[])
{
	widht = 500;
	height = 500;								//уставить начальные размеры окна
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	
	glutInitWindowSize(widht, height);
	glutCreateWindow("Первая лаба");
	Initialize();		
	Menu();
	glutKeyboardFunc(Process_Normal_Keys);
	glutTimerFunc(50, timer, 0);

	glutSpecialFunc(SKeyboard);
	glutDisplayFunc(Display);
	glutMouseFunc(Process_Mouse);
	glutMainLoop();
}
