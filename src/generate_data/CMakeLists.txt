set(SOURCES clock.cpp random.cpp)
add_library(generate_lib STATIC ${SOURCES})


add_executable(gen_data generate_data_file.cpp)
target_link_libraries(gen_data generate_lib) 
