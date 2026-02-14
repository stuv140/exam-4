add_executable(print_ip  print_ip.cpp)

target_include_directories(print_ip PRIVATE ${PROJECT_SOURCE_DIR}/include)

install(TARGETS print_ip RUNTIME DESTINATION bin)
