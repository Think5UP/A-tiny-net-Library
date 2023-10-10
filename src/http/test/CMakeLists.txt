add_executable(HttpServerTest HttpServerTest.cc)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/src/http/test)

target_link_libraries(HttpServerTest tiny_webserver)