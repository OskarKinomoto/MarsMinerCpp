#include "CameraGL2.hpp"

#include <GL/gl.h>

#include "../Robot/Robot.hpp"

CameraGL2::CameraGL2(Event<SizeI> windowSize) : windowSize(windowSize) {}

void CameraGL2::SetPosition(PositionF position, int min, int max) {
  this->position = position;
    if (-position.x - windowSize().width / 2 < -max)
    position.x = -(-max + windowSize().width / 2);

  if (-position.x + windowSize().width / 2 > -min)
    position.x = -(-min - windowSize().width / 2);

  this->position = position;
}

void CameraGL2::Begin() {
  glTranslatef(-windowSize().width / 2, 0, 0);
}

void CameraGL2::Translate() {
  glTranslatef(position.x, position.y, 0);
}

void CameraGL2::TranslateBack() {
  glTranslatef(-position.x, -position.y, 0);
}
