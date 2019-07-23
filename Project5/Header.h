#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <vector>
#include <windows.h>
#include <GL/glut.h>

#define RED		1
#define BLUE	2
#define GREEN	3
#define ORANGE	4
#define YELLOW	5
#define VIOLET	6
#define BLACK	7
#define WHITE	8
#define WIDTH_0_5	1
#define WIDTH_1		2
#define WIDTH_1_5	3
#define WIDTH_2		4
#define WIDTH_2_5	5
#define WIDTH_3		6
#define WIDTH_3_5	7
#define WIDTH_4		8

using namespace std;
GLint widht, height;
int current_group;
bool drawing_mode;		//true - режим отрисовки
int max_group;
bool prev_space;

class point
{
public: 
	GLint x, y;
	point(GLint p1, GLint p2);

};

class colour
{
public:
	GLint red=255, blue=0, green=0;
	int group;
	colour(GLint r, GLint b, GLint g, int gr);
};

struct triangle
{
public:
	vector<point> coordinates;
	int group;
};

class triangletype
{
public:
	float widht;
	unsigned short type;
	int group;
	triangletype(float _widht, unsigned short _type, int _group);
};

point::point(GLint p1, GLint p2)
{
	x = p1;
	y = p2;
}

colour::colour(GLint r, GLint b, GLint g, int gr)
{
	red = r;
	blue = b;
	green = g;
	group = gr;
}

triangletype::triangletype(float _widht, unsigned short _type, int _gr)
{
	type = _type;
	group = _gr;
	widht = _widht;
}

vector <triangle> v; // треугольники
triangle l; // рисующийся треугольник
vector <colour> colours;
vector <triangletype> triangletypeVec;


void Up_key() {
	char str[50];
	current_group++;
	current_group = current_group % (max_group + 1);

	sprintf(str, "Текущая группа: %i", current_group + 1);
	glutSetWindowTitle(str);
}

void Down_key(){
	char str[50];
	current_group--;
	if (current_group < 0) current_group = max_group;
	sprintf(str, "Текущяя группа :  %i", current_group + 1);
	glutSetWindowTitle(str);
}

void Delete_group() {
	char str[50];
	int i, j;
	j = v.size();
	for (i = 0; i < j; i++) {
		if (v[i].group == current_group)
		{
			v.erase(v.begin() + i);
			j = v.size();
			i--;
		}
	}

	for (i = 0; i < v.size(); i++)
	{
		if (v[i].group > current_group)
		{
			v[i].group--;
		}
	}

	colours.erase(colours.begin() + current_group);

	for (i = 0; i < colours.size(); i++)
	{
		if (colours[i].group > current_group)
		{
			colours[i].group--;
		}
	}

	if (max_group) max_group--;
	current_group = current_group % (max_group + 1);
	if (colours.size() == 0)
	{
		colours.push_back(colour(150, 150, 150, current_group));
		triangletypeVec.push_back(triangletype(1.0, 0xFFFF, current_group));
	}

	sprintf(str, "%i Групп ", max_group + 1);
	glutSetWindowTitle(str);
}
void Increase_Red()
{
	if (colours[current_group].red + 10 < 255) colours[current_group].red += 10;
}

void Increase_Green()
{
	if (colours[current_group].green + 10 < 255) colours[current_group].green += 10;
}
void Increase_Blue()
{
	if (colours[current_group].blue + 10 < 255) colours[current_group].blue += 10;
}
void DIncrease_Red()
{
	if (colours[current_group].red - 10 > 0) colours[current_group].red -= 10;
}

void DIncrease_Green()
{
	if (colours[current_group].green - 10 > 0) colours[current_group].green -= 10;
}
void DIncrease_Blue()
{
	if (colours[current_group].blue - 10 > 0) colours[current_group].blue -= 10;
}

void Create()
{
	int i, j;
	v.push_back(l);
	drawing_mode = false;
	i = l.coordinates.size();
	for (j = 0; j < i; j++) l.coordinates.pop_back();
}
void On_Space_Key()
{
	char str[50];
	if (!prev_space)	
	{
		prev_space = true;	
		max_group++;		
		current_group = max_group;	
		colours.push_back(colour(150, 150, 150, current_group));	
		triangletypeVec.push_back(triangletype(1.0, 0xFFFF, current_group));

		sprintf(str, "%i groups", max_group + 1);
		glutSetWindowTitle(str);
	}
}

void Delete_primitive() {
	int k;
	bool found=false, one_in=true;
	k = v.size();
	k--;
	for (k; k >= 0 && one_in; k--) {
		if (!found)
		{
			v.erase(v.begin() + k);
			found = true;
		}
		else one_in = false;
	}
	if (one_in) Delete_group;
}

void MoveUp()
{
	int j, k;
	int jj, l;
	k = v.size();
	for (j = 0; j < k; j++)
	{
		if (v[j].group == current_group)
		{
			l = v[j].coordinates.size();
			for (jj = 0; jj < l; jj++)
				v[j].coordinates[jj].y += 3;
		
		}
	}

}

void MoveDown()
{
	int j, k;
	int jj, l;
	k = v.size();
	for (j = 0; j < k; j++)
	{
		if (v[j].group == current_group)
		{
			l = v[j].coordinates.size();
			for (jj = 0; jj < l; jj++)
				v[j].coordinates[jj].y -= 3;
		}
	}
}

void MoveLeft()
{
	int j, k;
	int jj, l;
	k = v.size();
	for (j = 0; j < k; j++)
	{
		if (v[j].group == current_group)
		{
			l = v[j].coordinates.size();
			for (jj = 0; jj < l; jj++)
				v[j].coordinates[jj].x -= 3;
		}
	}
}

void MoveRight()
{
	int j, k;
	int jj, l;
	k = v.size();
	for (j = 0; j < k; j++)
	{
		if (v[j].group == current_group)
		{
			l = v[j].coordinates.size();
			for (jj = 0; jj < l; jj++)
				v[j].coordinates[jj].x += 3;
		}
	}
}
void processMainMenu(int option)
{

};
void processWidthMenu(int option)//обработчик подменю толщины линии
{
	switch (option)
	{
	case WIDTH_0_5:
		triangletypeVec[current_group].widht = 0.5; break;
	case WIDTH_1:
		triangletypeVec[current_group].widht = 1.0; break;
	case WIDTH_1_5:
		triangletypeVec[current_group].widht = 1.5; break;
	case WIDTH_2:
		triangletypeVec[current_group].widht = 2.0; break;
	case WIDTH_2_5:
		triangletypeVec[current_group].widht = 2.5; break;
	case WIDTH_3:
		triangletypeVec[current_group].widht = 3.0; break;
	case WIDTH_3_5:
		triangletypeVec[current_group].widht = 3.5; break;
	case WIDTH_4:
		triangletypeVec[current_group].widht = 4.0; break;
	}
}
void ColorMenu(int option)//обработчик подменю цветов
{
	switch (option)
	{
	case RED:
		colours[current_group].red = 252;
		colours[current_group].green = 48;
		colours[current_group].blue = 58; break;
	case GREEN:
		colours[current_group].red = 105;
		colours[current_group].green = 197;
		colours[current_group].blue = 22; break;
	case BLUE:
		colours[current_group].red = 42;
		colours[current_group].green = 128;
		colours[current_group].blue = 245; break;
	case ORANGE:
		colours[current_group].red = 246;
		colours[current_group].green = 138;
		colours[current_group].blue = 42; break;
	case YELLOW:
		colours[current_group].red = 246;
		colours[current_group].green = 224;
		colours[current_group].blue = 42; break;
	case VIOLET:
		colours[current_group].red = 182;
		colours[current_group].green = 97;
		colours[current_group].blue = 183; break;
	case BLACK:
		colours[current_group].red = 0;
		colours[current_group].green = 0;
		colours[current_group].blue = 0; break;
	case WHITE:
		colours[current_group].red = 255;
		colours[current_group].green = 255;
		colours[current_group].blue = 255; break;
	}
	glutPostRedisplay();
}

void Menu()
{
	int mainm, colorm, widhtm;
	colorm = glutCreateMenu(ColorMenu);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Orange", ORANGE);
	glutAddMenuEntry("Yellow", YELLOW);
	glutAddMenuEntry("Violet", VIOLET);
	glutAddMenuEntry("Black", BLACK);
	glutAddMenuEntry("White", WHITE);
	widhtm = glutCreateMenu(processWidthMenu);
	glutAddMenuEntry("0.5", WIDTH_0_5);
	glutAddMenuEntry("1.0", WIDTH_1);
	glutAddMenuEntry("1.5", WIDTH_1_5);
	glutAddMenuEntry("2.0", WIDTH_2);
	glutAddMenuEntry("2.5", WIDTH_2_5);
	glutAddMenuEntry("3.0", WIDTH_3);
	glutAddMenuEntry("3.5", WIDTH_3_5);
	glutAddMenuEntry("4.0", WIDTH_4);
	mainm = glutCreateMenu(processMainMenu);
	glutAddSubMenu("Толщина линии", widhtm);
	glutAddSubMenu("Цвет треугольника", colorm);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

