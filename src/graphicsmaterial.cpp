#include <QImage>
#include <QOpenGLFunctions_3_3_Core>

#include "graphicscontroller.h"
#include "graphicsmaterial.h"

namespace graphics {

Material::~Material()
{
    glDeleteTextures(1, &m_id);
}

Material::Material(ControllerPtr pController, const std::string& filename) :
    m_pController(pController)
{
    load(QImage(QString::fromStdString(filename)));
}

Material::Material(ControllerPtr pController, const QImage &image) :
    m_pController(pController)
{
    load(image);
}

void Material::load(const QImage &image)
{
	auto funcs = m_pController->functions();

    auto img = image.convertToFormat(QImage::Format_RGB888);

	funcs->glGenTextures(1, &m_id);
	funcs->glBindTexture(GL_TEXTURE_2D, m_id);
	funcs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, img.width(), img.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.bits());
	funcs->glGenerateMipmap(GL_TEXTURE_2D);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	funcs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

}
