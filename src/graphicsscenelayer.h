#ifndef GRAPHICSSCENELAYER_H
#define GRAPHICSSCENELAYER_H

#include <memory>
#include <list>
#include <unordered_map>

#include <QGL>

#include "glm/mat4x4.hpp"

namespace graphics {

class Controller;
using ControllerPtr = std::shared_ptr<Controller>;

enum class ProgramId : int32_t;

class Material;
using MaterialPtr = std::shared_ptr<Material>;

class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;

class Model;
using ModelPtr = std::shared_ptr<Model>;

class SceneLayer
{
public:
	~SceneLayer();

	void clear();
	ModelPtr addModel(MaterialPtr pMaterial, MeshPtr pMesh);
	ModelPtr selectModel(int32_t x, int32_t y);
	void setParam(const std::string& name, const glm::vec4& value);

private:
	SceneLayer(ControllerPtr pController, ProgramId programId);

	void setViewMatrix(const glm::mat4x4& val);
	void setProjMatrix(const glm::mat4x4& val);
	void enableDepthTest(bool state);

	void render() const;

	ControllerPtr m_pController;
	std::list<ModelPtr> m_models;
	glm::mat4x4 m_viewMatrix, m_projMatrix;
	std::unordered_map<std::string, glm::vec4> m_params;
	GLuint m_program, m_selectProgram;
	GLint m_modelMatrixLoc, m_viewMatrixLoc, m_projMatrixLoc, m_textureLoc;
	GLint m_selectModelMatrixLoc, m_selectViewMatrixLoc, m_selectProjMatrixLoc, m_selectColorLoc;
	bool m_depthTestState;


	friend class Scene;
};

}

#endif // GRAPHICSSCENELAYER_H
