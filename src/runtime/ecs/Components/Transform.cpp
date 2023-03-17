#include "Transform.h"


	Transform::Transform()
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it dow
	}

	Transform::~Transform()
	{
	}

	void Transform::Translate(float x, float y, float z)
	{
		model = glm::translate(model, glm::vec3(x, y, z));
	}

	void Transform::RotateX(float angle)
	{
		model = glm::rotate(model, glm::radians(angle),glm::vec3(1.0, 0.0, 0.0));
	}

	void Transform::RotateY(float angle)
	{
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
	}

	void Transform::RotateZ(float angle)
	{
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
	}

	void Transform::Scale(float x, float y, float z)
	{
		model = glm::scale(model, glm::vec3(x, y, z));
	}

