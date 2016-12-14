cmake_minimum_required(VERSION 2.8)
project( IMAGE_PROCESSING )

file(GLOB SRC "*.cpp")
add_executable( image_processing ${SRC} )

install (TARGETS image_processing DESTINATION bin)

file(GLOB my_resources "resources/*.txt")

file(COPY ${my_resources} DESTINATION .)
