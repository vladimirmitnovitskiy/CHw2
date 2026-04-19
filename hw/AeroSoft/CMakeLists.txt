add_library(AVL AVLtree.c)

add_executable(AeroSoft AeroSoft.c)

target_link_libraries(AeroSoft PRIVATE AVL)