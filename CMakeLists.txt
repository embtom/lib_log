project(lib_log)

#However, the file(GLOB...) allows for wildcard additions:
SET(SOURCES src/lib_log.c)

######################################################
#Build target settings
######################################################
add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} lib_ttyportmux ) 
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_options(${PROJECT_NAME} PUBLIC -DTRACE)
