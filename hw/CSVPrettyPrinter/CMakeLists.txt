add_library(Table Table.c)
add_library(draw draw.c)

add_executable(CSVPrettyPrinter CSVPrettyPrinter.c)

target_link_libraries(draw PRIVATE Table)
target_link_libraries(CSVPrettyPrinter PRIVATE draw)
target_link_libraries(CSVPrettyPrinter PRIVATE Table)