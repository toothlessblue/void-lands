cmake_minimum_required(VERSION 3.21)
project(GameClient)

include_directories("../include")

set(CMAKE_EXE_LINKER_FLAGS "-s USE_GLFW=3 -s LLD_REPORT_UNDEFINED --preload-file ../../../assets@/ -O0 -s WASM=1 -s MAX_WEBGL_VERSION=2 --post-js ../../../GameClient/postFix.js -lwebsocket.js -s SAFE_HEAP=1 -s FETCH --memoryprofiler")

add_executable(GameClient main-gameClient.cpp ../GameLibrary/Logger/Logger.cpp ../GameLibrary/Logger/Logger.h Window/Window.cpp Window/Window.h Renderer/VertexArrayObject/VertexArrayObject.cpp Renderer/VertexArrayObject/VertexArrayObject.h Renderer/VertexArrayBuffer/VertexArrayBuffer.cpp Renderer/VertexArrayBuffer/VertexArrayBuffer.h Time/Time.cpp Time/Time.h Renderer/ShaderHelper/ShaderHelper.cpp Renderer/ShaderHelper/ShaderHelper.h Transform/Transform.cpp Transform/Transform.h ../GameLibrary/Utils/VectorUtils.cpp ../GameLibrary/Utils/VectorUtils.h Camera/Camera.cpp Camera/Camera.h TextureLoader/TextureLoader.cpp TextureLoader/TextureLoader.h ControlledPlayer/ControlledPlayer.cpp ControlledPlayer/ControlledPlayer.h EmscriptenInputManager/EmscriptenInputManager.cpp EmscriptenInputManager/EmscriptenInputManager.h Floor/Floor.cpp Floor/Floor.h Networking/Networking.cpp Networking/Networking.h Config/Config.cpp Config/Config.h CommunicationManager/CommunicationManager.cpp CommunicationManager/CommunicationManager.h ../GameLibrary/Utils/MathUtils.cpp ../GameLibrary/Utils/MathUtils.h ../GameLibrary/Utils/Utils.h Renderer/EntityRenderer/EntityRenderer.cpp Renderer/EntityRenderer/EntityRenderer.h GameData/GameData.cpp GameData/GameData.h ResourceFetcher/ResourceFetcher.cpp ResourceFetcher/ResourceFetcher.h)

target_link_libraries(GameClient PRIVATE GameLibrary)