add_executable(printer_ip  printer_ip.cpp)

target_include_directories(printer_ip PRIVATE ${PROJECT_SOURCE_DIR}/include)

install(TARGETS printer_ip RUNTIME DESTINATION bin)
