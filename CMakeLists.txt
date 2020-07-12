cmake_minimum_required(VERSION 3.15)
project(readline C)

set(CMAKE_CXX_STANDARD 11)

set(LIB_PATH			./libmx/)
set(SRC_PATH			./src/)
set(INC_PATH			./inc/)

#-----------------------------------libmx------------------------
set(LMX_NAME			mx)
set(LMX_PATH			libmx)
set(LMX_LIB				${LMX_PATH})


aux_source_directory(	${SRC_PATH} PROJECT_SOURCE_FILES)   #src
aux_source_directory(	${LMX_LIB}/src LMX_SRC)                 #libMX src

add_library(			${LMX_NAME} STATIC ${LMX_SRC})      #L MX


include_directories(${INC_PATH})
include_directories(${LMX_PATH}/inc)
include_directories(${LMX_PATH}/)


add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCE_FILES})

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS})

target_link_libraries(${PROJECT_NAME}
        ${LMX_NAME}
        )

