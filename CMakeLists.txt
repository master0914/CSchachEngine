cmake_minimum_required(VERSION 4.0)
project(SchachEngine)

set(CMAKE_CXX_STANDARD 20)

#find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
#
#message(STATUS "Python3 interpreter: ${Python3_EXECUTABLE}")
#message(STATUS "Python3 include dirs: ${Python3_INCLUDE_DIRS}")
#message(STATUS "Python3 libraries:   ${Python3_LIBRARIES}")


add_subdirectory(lib/3DEngine "${CMAKE_BINARY_DIR}/3DEngine")

add_executable(SchachEngine
        src/core/Bitboard.cpp
        src/core/Bitboard.h
        src/core/ChessBoard.cpp
        src/core/ChessBoard.h
        src/core/Move.cpp
        src/core/Move.h
        src/core/ChessGame.cpp
        src/core/ChessGame.h
        src/util/Helper.h
        src/players/IPlayer.h
        src/main.cpp
        src/ChessApp.cpp
        src/ChessApp.h
        src/core/UIManager.h
        src/core/UIManager.cpp
        src/core/Piece.cpp
        src/core/Piece.h
        src/util/Logger.h
        src/core/MoveGenerator.cpp
        src/core/MoveGenerator.h
        src/core/Movelist.h
)



target_link_libraries(SchachEngine 3DEngineLib)

