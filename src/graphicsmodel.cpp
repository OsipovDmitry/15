#include "glm/gtc/matrix_transform.hpp"

#include "graphicsmodel.h"

namespace graphics {

Model::~Model()
{
	int i = 123;
}

glm::vec3 Model::position() const
{
	return m_position;
}

glm::vec3 Model::angles() const
{
	return m_angles;
}

glm::vec3 Model::scale() const
{
	return m_scale;
}

glm::mat4x4 Model::transformMatrix() const
{
	return
			glm::translate(glm::mat4x4(), m_position) *
			glm::rotate(glm::mat4x4(), m_angles.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4x4(), m_angles.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4x4(), m_angles.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4x4(), m_scale);
}

int32_t Model::userData() const
{
	return m_userData;
}

void Model::setPosition(const glm::vec3& val)
{
	m_position = val;
}

void Model::setAngles(const glm::vec3& val)
{
	m_angles = val;
}

void Model::setScale(const glm::vec3& val)
{
	m_scale = val;
}

void Model::setUserData(int32_t val)
{
	m_userData = val;
}

Model::Model(ScenePtr pScene, MaterialPtr pMaterial, MeshPtr pMesh) :
	m_pScene(pScene),
	m_pMaterial(pMaterial),
	m_pMesh(pMesh),
	m_position(),
	m_angles(),
	m_scale(1.0f, 1.0f, 1.0f),
	m_userData(-1)
{
}

}
