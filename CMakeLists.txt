cmake_minimum_required(VERSION 3.28)

project(IA_App
	VERSION 1.0.0
	DESCRIPTION "Main application for project Investment Analysis."
	LANGUAGES CXX)

# Default build type is release unless in development mode.
set(DEFAULT_BUILD_TYPE "Release")

if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
	set(DEFAULT_BUILD_TYPE "Debug")
endif()

set(CMAKE_CXX_STANDARD 17) # Desired c++ standard
set(CMAKE_CXX_STANDARD_REQUIRED true) # Require the compiler work with the designated standard

# Variables in format @SOME_VAR@ are replaced by the variables in this CMakeLists.txt when the
# output file is produced. The output file will be written to the project binary directory, so the
# directory must be added to the list of include directories.
configure_file(IA_AppConfig.h.in IA_AppConfig.h)

# --------------------------------------------------------------------------------------------------
# IA_Metric library
# --------------------------------------------------------------------------------------------------
add_subdirectory(lib/ia_metric-main)

# --------------------------------------------------------------------------------------------------
# main exe
# --------------------------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} main.cpp)

# No need to add `PUBLIC ${PROJECT_SOURCE_DIR}/lib/ia_metric-main/include` here since the ia_metric
# repo's own CMakeLists.txt makes the include directory public for client.
target_include_directories(${PROJECT_NAME}
	PRIVATE
		${PROJECT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		IA_Metric)
