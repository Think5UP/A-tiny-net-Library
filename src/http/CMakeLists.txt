set(HTTP_SRCS
    HttpContext.cc
    HttpResponse.cc
    HttpServer.cc
)

add_executable(HttpServer ${HTTP_SRCS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/src/http)

target_link_libraries(HttpServer tiny_webserver)