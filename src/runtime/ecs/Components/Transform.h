#pragma once

//×é¼þÀà
#include "graphic/MeshNode.h"

class Transform
{

public:
	Transform();
	~Transform();

	void Translate(float x,float y,float z);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void Scale(float x, float y, float z);

private:
	Vector3 postion = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
public:
	glm::mat4 model;
};

