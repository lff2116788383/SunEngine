#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGLRenderer.h"
#include "window/Window.h"
#include "graphic/MeshNode.h"


bool OpenGLRenderer::Init(Window* window)
{
	///* ���õ�ǰ�Ĵ��������� *///�������Ĵ�����ΪOpenGL��ǰ�������� ����
	//glfwMakeContextCurrent(window->m_pGLFWWindow);//������ɶ��˼����̫��⣿��

	return true;
}
void OpenGLRenderer::display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// ���ƶ�������
	glColor3f(1, 1, 0);//������ɫ
	glBegin(GL_LINES);
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 4; j++) {
			glVertex3fv(testvertex[i]);
			glVertex3fv(testvertex[j]);
		}
	}
	glEnd();

	glFlush();
}

void OpenGLRenderer::InitMesh(MeshNode* mesh)
{
	glGenVertexArrays(1, &mesh->VAO);
	glGenBuffers(1, &mesh->VBO);
	glGenBuffers(1, &mesh->EBO);

	glBindVertexArray(mesh->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(SEVertex), &mesh->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int),
		&mesh->indices[0], GL_STATIC_DRAW);

	//����λ��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SEVertex), (void*)0);

	//���㷨��
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SEVertex), (void*)offsetof(SEVertex, Normal));

	//��������
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SEVertex), (void*)offsetof(SEVertex, TexCoords));

	//�ָ�Ĭ�ϵ�VAO����
	glBindVertexArray(0);
}

void OpenGLRenderer::BeginRender()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::Render(Window* window, MeshNode* mesh,Shader* shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < mesh->textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = mesh->textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader->setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
	}

	//��Ⱦ
	glBindVertexArray(mesh->VAO);
	glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}