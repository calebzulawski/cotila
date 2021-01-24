cmake_minimum_required(VERSION 3.14)
project(cotila VERSION 1.2.0 LANGUAGES CXX DESCRIPTION "A compile time linear algebra system")

option(BUILD_TESTING "Build Cotila tests" ON)
option(BUILD_DOCS "Build Doxygen documentation" OFF)

# Interface target
include(GNUInstallDirs)
add_library(cotila INTERFACE)
target_include_directories(cotila INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>	
)
target_compile_features(cotila INTERFACE cxx_std_17)
add_library(cotila::cotila ALIAS cotila)

# Docs build
if (BUILD_DOCS)
	find_package(Doxygen REQUIRED)
	# Options from Doxyfile
	set(DOXYGEN_DOXYFILE_ENCODING "utf-8")
	set(DOXYGEN_PROJECT_LOGO "logo.svg")
	set(DOXYGEN_OUTPUT_DIRECTORY "docs/") # will be in {binary_dir}/docs
	set(DOXYGEN_REPEAT_BRIEF "NO")
	set(DOXYGEN_SEPARATE_MEMBER_PAGES "YES")
	set(DOXYGEN_EXCLUDE_PATTERNS "*/detail/*")
	set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "mainpage.md")
    set(DOXYGEN_LAYOUT_FILE "layout.xml")

	doxygen_add_docs(doc include/ mainpage.md layout.xml COMMENT "Generating documentation")
endif()

# installing
install(DIRECTORY include/cotila DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS cotila EXPORT cotila-config DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT cotila-config NAMESPACE Cmsl:: DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cotila")
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/cotila-configVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)

# testing
if(BUILD_TESTING)
	enable_testing()
	add_subdirectory("test/")
endif()
