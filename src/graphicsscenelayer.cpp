#include <QOpenGLFunctions_3_3_Core>
#include <QImage>

#include "glm/mat3x3.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_inverse.hpp"

#include "graphicscontroller.h"
#include "graphicsscenelayer.h"
#include "graphicsmodel.h"
#include "graphicsmesh.h"
#include "graphicsmaterial.h"

namespace graphics {

SceneLayer::~SceneLayer()
{

}

void SceneLayer::clear()
{
	m_models.clear();
}

void SceneLayer::setViewMatrix(const glm::mat4x4& val)
{
	m_viewMatrix = val;
}

void SceneLayer::setProjMatrix(const glm::mat4x4& val)
{
	m_projMatrix = val;
}

void SceneLayer::enableDepthTest(bool state)
{
	m_depthTestState = state;
}

ModelPtr SceneLayer::addModel(MaterialPtr pMaterial, MeshPtr pMesh)
{
	auto pModel = ModelPtr(new Model(pMaterial, pMesh));
	m_models.push_back(pModel);
	return pModel;
}

ModelPtr SceneLayer::selectModel(int32_t x, int32_t y)
{
	auto viewport = m_pController->viewport();
	auto funcs = m_pController->functions();

	funcs->glBindFramebuffer(GL_FRAMEBUFFER, m_pController->selectFramebuffer());
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	funcs->glDrawBuffers(1, DrawBuffers);

	funcs->glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	funcs->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	funcs->glClearDepth(1.0f);
	funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	funcs->glUseProgram(m_selectProgram);
	funcs->glUniformMatrix4fv(m_selectProjMatrixLoc, 1, GL_FALSE, glm::value_ptr(m_projMatrix));
	funcs->glUniformMatrix4fv(m_selectViewMatrixLoc, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));

	if (m_depthTestState) {
		funcs->glEnable(GL_DEPTH_TEST);
		funcs->glDepthMask(GL_TRUE);
	}
	else {
		funcs->glDisable(GL_DEPTH_TEST);
	}

	uint32_t objectId = 0;
	for (auto pModel: m_models) {
		float a = ((objectId & 0xFF000000) >> 24) / 255.0;
		float b = ((objectId & 0x00FF0000) >> 16) / 255.0;
		float g = ((objectId & 0x0000FF00) >> 8) / 255.0;
		float r = (objectId & 0x000000FF) / 255.0;
		++objectId;

		funcs->glUniform4f(m_selectColorLoc, r,g,b,a);
		funcs->glUniformMatrix4fv(m_selectModelMatrixLoc, 1, GL_FALSE, glm::value_ptr(pModel->transformMatrix()));

		funcs->glBindVertexArray(pModel->m_pMesh->m_vertexArray);
		funcs->glDrawElements(GL_TRIANGLES, pModel->m_pMesh->m_numIndices, GL_UNSIGNED_INT, 0);
	}
	funcs->glBindVertexArray(0);

	objectId = -1;
	funcs->glReadBuffer(GL_COLOR_ATTACHMENT0);
	funcs->glReadPixels(x, viewport[3]-y-1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &objectId);

	funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (objectId != -1) {
		auto iter = m_models.begin();
		std::advance(iter, objectId);
		return *iter;
	}
	return nullptr;
}

void SceneLayer::setParam(const std::string& name, const glm::vec4& value)
{
	m_params[name] = value;
}

SceneLayer::SceneLayer(ControllerPtr pController, ProgramId programId) :
	m_pController(pController),
	m_models(),
	m_params(),
	m_projMatrix(),
	m_viewMatrix()
{
	auto funcs = m_pController->functions();

	m_program = m_pController->program(programId);
	m_modelMatrixLoc = funcs->glGetUniformLocation(m_program, "u_modelMatrix");
	m_normalMatrixLoc = funcs->glGetUniformLocation(m_program, "u_normalMatrix");
	m_viewMatrixLoc = funcs->glGetUniformLocation(m_program, "u_viewMatrix");
	m_projMatrixLoc = funcs->glGetUniformLocation(m_program, "u_projMatrix");
	m_textureLoc = funcs->glGetUniformLocation(m_program, "u_texture");

	m_selectProgram = m_pController->program(ProgramId::Select);
	m_selectModelMatrixLoc = funcs->glGetUniformLocation(m_selectProgram, "u_modelMatrix");
	m_selectViewMatrixLoc = funcs->glGetUniformLocation(m_selectProgram, "u_viewMatrix");
	m_selectProjMatrixLoc = funcs->glGetUniformLocation(m_selectProgram, "u_projMatrix");
	m_selectColorLoc = funcs->glGetUniformLocation(m_selectProgram, "u_color");
}

void SceneLayer::render() const
{
	auto funcs = m_pController->functions();

	funcs->glUseProgram(m_program);

	funcs->glUniformMatrix4fv(m_projMatrixLoc, 1, GL_FALSE, glm::value_ptr(m_projMatrix));
	funcs->glUniformMatrix4fv(m_viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
	funcs->glUniform1i(m_textureLoc, 0);

	for (auto& param: m_params)
		funcs->glUniform4fv(funcs->glGetUniformLocation(m_program, param.first.c_str()), 1, glm::value_ptr(param.second));

	if (m_depthTestState) {
		funcs->glEnable(GL_DEPTH_TEST);
		funcs->glDepthMask(GL_TRUE);
	}
	else {
		funcs->glDisable(GL_DEPTH_TEST);
	}

	funcs->glActiveTexture(GL_TEXTURE0);

	for (auto pModel: m_models) {
		auto modelMatrix = pModel->transformMatrix();
		auto normalMatrix = glm::inverseTranspose(glm::mat3x3(modelMatrix));
		funcs->glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		funcs->glUniformMatrix3fv(m_normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

		funcs->glBindTexture(GL_TEXTURE_2D, pModel->m_pMaterial->m_id);

		funcs->glBindVertexArray(pModel->m_pMesh->m_vertexArray);
		funcs->glDrawElements(GL_TRIANGLES, pModel->m_pMesh->m_numIndices, GL_UNSIGNED_INT, 0);
	}
	funcs->glBindVertexArray(0);
}


}
