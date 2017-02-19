SET(MAIN_SOURCES
  main.cpp
  Controler/Controler.cpp
  Controler/Keyboard.cpp
  Controler/Mouse.cpp
  Painter/PainterGL2.cpp
  Painter/CameraGL2.cpp
  Painter/Sprite.cpp
  Painter/Texture.cpp
  SDL/SDL_OpenGL.cpp
  Utils/Color.cpp
  Utils/Layer.cpp
  Utils/Vector2.cpp
  Utils/Tools.cpp
  Utils/Exception.cpp
  Utils/OpenglVersion.cpp
  Objects/Background.cpp
  Objects/BreakingTile.cpp
  Objects/Clouds.cpp
  Objects/Grass.cpp
  Objects/Model.cpp
  Objects/Mineral.cpp
  Objects/Tile.cpp
  Objects/Tiles.cpp
  Objects/CollisionTile.cpp
  Robot/Robot.cpp
  Robot/Cargo.cpp
  Robot/Drill.cpp
  Robot/Engine.cpp
  Robot/Fuel.cpp
  Robot/Hull.cpp
  Robot/MainSystem.cpp
  Robot/Money.cpp
  Robot/Physics.cpp
  )

SET(MAIN_HEADERS
    Painter/Painter.hpp
    Painter/Camera.hpp
    Utils/Action.hpp
    Utils/Log.hpp
    Interfaces/LoadInterface.hpp
    Interfaces/MouseInterface.hpp
    Interfaces/PaintInterface.hpp
    Interfaces/TickInterface.hpp
    Interfaces/FuelUseInterface.hpp
    Robot/Enums.hpp
    Utils/Utils.hpp
    )

INCLUDE_DIRECTORIES(.)

ADD_EXECUTABLE(${PROJECT_NAME} ${MAIN_SOURCES} ${MAIN_HEADERS})

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${PNG_LIBRARIES}
    )
