#include "Triangle.h"
#include <GLFW/glfw3.h>	
	Triangle::Triangle()
	{
	}
	Triangle::~Triangle()
	{
	}
	void Triangle::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// ���ƶ�������
		glColor3f(1, 1, 0);//������ɫ
		glBegin(GL_LINES);
		for (int i = 0; i < 3; i++)
		{
			for (int j = i + 1; j < 4; j++) {
				glVertex3fv(vertex[i]);
				glVertex3fv(vertex[j]);
			}
		}
		glEnd();

		glFlush();
	}
