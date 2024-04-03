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

# --------------------------------------------------------------------------------------------------
# INTERFACE lib for specifying C++ standard
# --------------------------------------------------------------------------------------------------
add_library(ia_app_compiler_flags INTERFACE)
target_compile_features(ia_app_compiler_flags INTERFACE cxx_std_17)

# --------------------------------------------------------------------------------------------------
# Set compile options for compiling C++ with GNU compiler
# --------------------------------------------------------------------------------------------------
set(gcc_like_cxx $<COMPILE_LANG_AND_ID:CXX,GNU>)

# Since ia_app_compiler_flags is used by the target IA_App in the same build-system, the generator-
# expression $<BUILD_INTERFACE:...> evaluates to its content, which in this case is a set of
# warnings.
target_compile_options(ia_app_compiler_flags
	# We can only set INTERFACE properties since the ia_app_compiler_flags is an INTERFACE target
	INTERFACE
		$<${gcc_like_cxx}:
			$<BUILD_INTERFACE:
				-ggdb;-pedantic-errors;-Wall;-Weffc++;-Wextra;-Wconversion;-Wsign-conversion;-Werror>>)


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
		${PROJECT_BINARY_DIR}) # For IA_AppConfig.h

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		IA_Metric	
		ia_app_compiler_flags)
