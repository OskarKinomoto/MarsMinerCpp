#include "PainterGL2.hpp"

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace {

inline void glTexCoord2f(Vector2 v) {
    ::glTexCoord2f(v.x, v.y);
}

}

void PainterGL2::SetUp()
{
    glEnable(GL_DEPTH_TEST | GL_TEXTURE_2D | GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PainterGL2::CleanView()
{
    glClearColor(0.f, 1.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PainterGL2::BeginQuads()
{
    glBegin(GL_QUADS);
}

void PainterGL2::Square(Position position, Size size, Layer layer)
{
    glTexCoord3f(position.x, position.y, static_cast<float>(layer));
    glTexCoord3f(position.x + size.x, position.y + size.y, static_cast<float>(layer));
    glTexCoord3f(position.x + size.x, position.y, static_cast<float>(layer));
    glTexCoord3f(position.x, position.y + size.y, static_cast<float>(layer));
}

void PainterGL2::Sprite(Position position, Size size, Layer layer, Sprite::Name sprite)
{
    glTexCoord2f(Sprite::Coordinates(sprite, Sprite::VertexPosition::LeftBottom));
    glTexCoord3f(position.x, position.y, static_cast<float>(layer));
    glTexCoord2f(Sprite::Coordinates(sprite, Sprite::VertexPosition::LeftTop));
    glTexCoord3f(position.x + size.x, position.y + size.y, static_cast<float>(layer));
    glTexCoord2f(Sprite::Coordinates(sprite, Sprite::VertexPosition::RightBottom));
    glTexCoord3f(position.x + size.x, position.y, static_cast<float>(layer));
    glTexCoord2f(Sprite::Coordinates(sprite, Sprite::VertexPosition::RightTop));
    glTexCoord3f(position.x, position.y + size.y, static_cast<float>(layer));
}

void PainterGL2::EndQuads()
{
    glEnd();
}

void PainterGL2::Translate(Vector2 v)
{
    glTranslatef(v.x, v.y, 0);
}

void PainterGL2::Color(::Color color)
{
    glColor3f(color.r, color.g, color.b);
}

void PainterGL2::Textures(bool enable)
{
    if (enable == texturesEnabled)
        return;

    if (enable)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);

    texturesEnabled = enable;
}

void PainterGL2::Resize(int width, int height)
{
    this->width = width;
    this->height = height;

    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION_MATRIX);


    // TODO ortho view matrix

    glm::mat4x4 projection_matrix = glm::ortho(0, width, 0, height, -11, 11);

    glLoadMatrixf(&projection_matrix[0][0]);
}

float PainterGL2::Width() const
{
    return width;
}

float PainterGL2::Height() const
{
    return height;
}

void PainterGL2::Gradient(Position start, ::Color c1, Position end, ::Color c2, Layer layer)
{
    Color(c1);
    glTexCoord3f(start.x, start.y, static_cast<float>(layer));
    glTexCoord3f(end.x, start.y, static_cast<float>(layer));

    Color(c2);
    glTexCoord3f(end.x, end.y, static_cast<float>(layer));
    glTexCoord3f(start.x, end.y, static_cast<float>(layer));
}
