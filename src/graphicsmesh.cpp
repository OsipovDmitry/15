#include <QOpenGLFunctions_3_3_Core>

#include "graphicscontroller.h"
#include "graphicsmesh.h"

namespace graphics {

Mesh::~Mesh()
{
	auto funcs = m_pController->functions();
	funcs->glDeleteBuffers(1, &m_vertexBuffer);
	funcs->glDeleteBuffers(1, &m_indexBuffer);
	funcs->glDeleteVertexArrays(1, &m_vertexArray);
}

Mesh::Mesh(ControllerPtr pController, const std::vector<float>& vertices, const std::vector<uint32_t> indices) :
	m_pController(pController)
{
	auto funcs = m_pController->functions();

	funcs->glGenBuffers(1, &m_vertexBuffer);
	funcs->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	funcs->glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

	funcs->glGenBuffers(1, &m_indexBuffer);
	funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	funcs->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

	funcs->glGenVertexArrays(1, &m_vertexArray);
	funcs->glBindVertexArray(m_vertexArray);

	funcs->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid*)(0*sizeof(float)));
	funcs->glEnableVertexAttribArray(0);
	funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid*)(3*sizeof(float)));
	funcs->glEnableVertexAttribArray(1);
	funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid*)(6*sizeof(float)));
	funcs->glEnableVertexAttribArray(2);

	funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	funcs->glBindVertexArray(0);

	m_numIndices = indices.size();
}

}
