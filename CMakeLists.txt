project( IMAGE_PROCESSING )

add_executable( image_processing *.cpp )

install (TARGETS image_processing DESTINATION bin)

file(COPY resources/*.txt DESTINATION bin/*.txt)
