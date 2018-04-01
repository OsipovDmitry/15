#include <QGLContext>
#include <QGLFunctions>

#include "graphicscontroller.h"
#include "graphicsmesh.h"

namespace graphics {

Mesh::~Mesh()
{
	auto funcs = m_pController->context()->functions();
	funcs->glDeleteBuffers(1, &m_vertexBuffer);
	funcs->glDeleteBuffers(1, &m_indexBuffer);
}

Mesh::Mesh(ControllerPtr pController, const std::vector<float>& vertices, const std::vector<uint32_t> indices) :
	m_pController(pController)
{
	auto funcs = m_pController->context()->functions();

	funcs->glGenBuffers(1, &m_vertexBuffer);
	funcs->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	funcs->glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

	funcs->glGenBuffers(1, &m_indexBuffer);
	funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	funcs->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

	m_numIndices = indices.size();
}

}
