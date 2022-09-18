cmake_minimum_required (VERSION 3.8)
add_executable (ChessGame  "main.cpp" "Engine.h" "Engine.cpp" "GameBoard.h" "GameBoard.cpp" "GUI.h" "GUI.cpp" "Macros.h" "Piece.h" "Piece.cpp" "Player.h" "Player.cpp")

# set SFML_DIR here :
# Example : set(SFML_DIR "../../SFML-2.5.1/lib/cmake/SFML")

set(SFML_DIR "../../../SFML/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics system window REQUIRED)
target_link_libraries(ChessGame sfml-graphics sfml-window sfml-system)
