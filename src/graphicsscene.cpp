#include <QGLContext>
#include <QGLFunctions>
#include <QImage>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsmodel.h"
#include "graphicsmesh.h"
#include "graphicsmaterial.h"

namespace graphics {

Scene::~Scene()
{
	int i = 123;
}

void Scene::clear()
{
	for (auto& list: m_objects)
		list.clear();
}

ModelPtr Scene::addModel(SceneLayer layer, MaterialPtr pMaterial, MeshPtr pMesh)
{
	auto pModel = ModelPtr(new Model(shared_from_this(), pMaterial, pMesh));
	m_objects[static_cast<size_t>(layer)].push_back(pModel);
	return pModel;
}

void Scene::setViewMatrix(const glm::mat4x4& value)
{
	m_viewMatrix = value;
}

ModelPtr Scene::selectObject(SceneLayer layer, int32_t x, int32_t y)
{
	auto viewport = m_pController->viewport();
	auto funcs = m_pController->context()->functions();
	GLuint framebuffer, depthRenderbuffer, colorTexture;

	funcs->glGenRenderbuffers(1, &depthRenderbuffer);
	funcs->glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
	funcs->glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, viewport[2], viewport[3]);

	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewport[2], viewport[3], 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	funcs->glGenFramebuffers(1, &framebuffer);
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
	funcs->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);

	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDepthMask(GL_TRUE);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(glm::perspective(glm::half_pi<float>(), (float)viewport[2]/(float)viewport[3], 0.5f, 1000.0f)));

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(m_viewMatrix));

	auto& objectsList = m_objects[static_cast<size_t>(layer)];
	uint32_t objectId = 0;
	for (auto pModel: objectsList) {
		funcs->glBindBuffer(GL_ARRAY_BUFFER, pModel->m_pMesh->m_vertexBuffer);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 8*sizeof(float), (const GLvoid*)(0*sizeof(float)));
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pModel->m_pMesh->m_indexBuffer);

		uint8_t r = (objectId & 0x00FF0000) >> 16;
		uint8_t g = (objectId & 0x0000FF00) >> 8;
		uint8_t b = (objectId & 0x000000FF);
		++objectId;
		glColor3ub(r,g,b);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(glm::value_ptr(pModel->transformMatrix()));
		glDrawElements(GL_TRIANGLES, pModel->m_pMesh->m_numIndices, GL_UNSIGNED_INT, 0);
		glPopMatrix();
	}

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glReadPixels(x, viewport[3]-y-1, 1, 1, GL_BGR, GL_UNSIGNED_BYTE, &objectId);

	uint8_t r = (objectId & 0x00FF0000) >> 16;
	uint8_t g = (objectId & 0x0000FF00) >> 8;
	uint8_t b = (objectId & 0x000000FF);

	funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
	funcs->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);
	funcs->glDeleteFramebuffers(1, &framebuffer);

	glBindTexture(GL_TEXTURE_2D, 0);
	glGenTextures(1, &colorTexture);

	funcs->glBindRenderbuffer(GL_RENDERBUFFER, 0);
	funcs->glGenRenderbuffers(1, &depthRenderbuffer);

	return nullptr;
}

Scene::Scene(ControllerPtr pController) :
	m_pController(pController),
	m_objects(),
	m_viewMatrix()
{

}

void Scene::render() const
{
	using RenderFunc = void (Scene::*)(const std::list<ModelPtr>&) const;
	static const RenderFunc funcs[] = {
		&Scene::renderBackground,
		&Scene::renderObjects
	};

	for (size_t i = 0; i < static_cast<size_t>(SceneLayer::Count); ++i)
		(this->*funcs[i])(m_objects[i]);
}

void Scene::renderBackground(const std::list<ModelPtr>& listModels) const
{
	glDepthMask(GL_FALSE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (auto pModel: listModels)
		renderModel(pModel);
}

void Scene::renderObjects(const std::list<ModelPtr>& listModels) const
{
	auto viewport = m_pController->viewport();

	glDepthMask(GL_TRUE);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(glm::perspective(glm::half_pi<float>(), (float)viewport[2]/(float)viewport[3], 0.5f, 1000.0f)));

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(m_viewMatrix));

	for (auto pModel: listModels)
		renderModel(pModel);

}

void Scene::renderModel(ModelPtr pModel) const
{
	auto funcs = m_pController->context()->functions();

	funcs->glBindBuffer(GL_ARRAY_BUFFER, pModel->m_pMesh->m_vertexBuffer);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 8*sizeof(float), (const GLvoid*)(0*sizeof(float)));
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 8*sizeof(float), (const GLvoid*)(3*sizeof(float)));
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 8*sizeof(float), (const GLvoid*)(6*sizeof(float)));
	funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pModel->m_pMesh->m_indexBuffer);

	glBindTexture(GL_TEXTURE_2D, pModel->m_pMaterial->m_id);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(pModel->transformMatrix()));

	glDrawElements(GL_TRIANGLES, pModel->m_pMesh->m_numIndices, GL_UNSIGNED_INT, 0);

	glPopMatrix();
}

}
