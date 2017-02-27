#include "PainterGL2.hpp"

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Utils/Exception.hpp"

namespace {

void glError()
{
    auto ret = glGetError();
    if (ret != GL_NO_ERROR) {
        switch(ret) {
        case GL_INVALID_ENUM:
            throw Exception("GL_INVALID_ENUM");
        case GL_INVALID_VALUE:
            throw Exception("GL_INVALID_VALUE");
        case GL_INVALID_OPERATION:
            throw Exception("GL_INVALID_OPERATION");
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            throw Exception("GL_INVALID_FRAMEBUFFER_OPERATION");
        default:
            throw Exception("GL_UNKNOWN");
        }
    }
}

inline void glTexCoord2f(VectorF v) {
    ::glTexCoord2f(v.x, v.y);
}

}

void PainterGL2::SetUp()
{
    glError();
    glEnable(GL_DEPTH_TEST);
    glError();
    glEnable(GL_BLEND);
    glError();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glError();
}

void PainterGL2::CleanView()
{
    glClearColor(0.5f, 0.5f, 1.f, 0.f);
    glError();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glError();

    glm::mat4x4 modelView = glm::lookAt(glm::vec3{0.0f, 0.0f, 0.0f},
                                        glm::vec3{0.0f, 0.0f, -1.0f},
                                        glm::vec3{0.0f, 1.0f, 0.0f});
    glMatrixMode(GL_MODELVIEW);
    glError();
    glLoadMatrixf(&modelView[0][0]);
    glError();
}

void PainterGL2::BeginQuads()
{
    glError();
    glBegin(GL_QUADS);
}

void PainterGL2::Square(PositionF position, SizeI size, Layer layer)
{
    glTexCoord2f(0,0);
    glVertex3f(position.x, position.y, static_cast<float>(layer));
    glTexCoord2f(1,0);
    glVertex3f(position.x + size.x, position.y, static_cast<float>(layer));
    glTexCoord2f(1,1);
    glVertex3f(position.x + size.x, position.y + size.y, static_cast<float>(layer));
    glTexCoord2f(0,1);
    glVertex3f(position.x, position.y + size.y, static_cast<float>(layer));
}

void PainterGL2::Sprite(PositionF position, SizeI size, Layer layer, Sprite::Name sprite, int offset)
{
    glTexCoord2f(Sprite::Coordinates(sprite, Sprite::VertexPosition::LeftBottom, offset));
    glVertex3f(position.x, position.y, static_cast<float>(layer));

    glTexCoord2f(Sprite::Coordinates(sprite, Sprite::VertexPosition::LeftTop, offset));
    glVertex3f(position.x + size.x, position.y, static_cast<float>(layer));

    glTexCoord2f(Sprite::Coordinates(sprite, Sprite::VertexPosition::RightBottom, offset));
    glVertex3f(position.x + size.x, position.y + size.y, static_cast<float>(layer));

    glTexCoord2f(Sprite::Coordinates(sprite, Sprite::VertexPosition::RightTop, offset));
    glVertex3f(position.x, position.y + size.y, static_cast<float>(layer));
}

void PainterGL2::EndQuads()
{
    glEnd();
    glError();
}

void PainterGL2::Translate(VectorF v)
{
    glTranslatef(v.x, v.y, 0);
    glError();
}

void PainterGL2::Color(::Color color)
{
    glColor3f(color.r, color.g, color.b);
}

void PainterGL2::Textures(bool enable)
{
    if (enable == texturesEnabled)
        return;

    if (enable) {
        Color(Color::White);
        glEnable(GL_TEXTURE_2D);
    } else {
        glDisable(GL_TEXTURE_2D);
    }

    glError();

    texturesEnabled = enable;
}

void PainterGL2::Resize(int width, int height)
{
    this->width = width;
    this->height = height;

    glViewport(0, 0, width, height);
    glError();
    glMatrixMode(GL_PROJECTION);
    glError();
    glm::mat4 mat = glm::ortho<float>(-width, 0, -height/2.0f, height /2.0f, -11.0f, 11.0f);
    glLoadMatrixf(&mat[0][0]);
    glError();
}

float PainterGL2::Width() const
{
    return width;
}

float PainterGL2::Height() const
{
    return height;
}

void PainterGL2::Gradient(PositionF start, ::Color c1, PositionF end, ::Color c2, Layer layer)
{
    Color(c1);
    glVertex3f(start.x, start.y, static_cast<float>(layer));
    glVertex3f(end.x, start.y, static_cast<float>(layer));

    Color(c2);
    glVertex3f(end.x, end.y, static_cast<float>(layer));
    glVertex3f(start.x, end.y, static_cast<float>(layer));
}
