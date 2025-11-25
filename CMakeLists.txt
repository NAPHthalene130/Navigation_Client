cmake_minimum_required(VERSION 3.19)
project(Navigation LANGUAGES CXX)

set(BOOST_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/boost_1_89_0")

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Boost 1.80 REQUIRED COMPONENTS system HINTS ${BOOST_ROOT_DIR})
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost at the path: ${BOOST_ROOT_DIR}! Please check the folder name.")
endif()

qt_standard_project_setup()

qt_add_executable(Navigation
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
        MapDataNetReader.cpp
        MapDataNetReader.h
)

target_link_libraries(Navigation
    PRIVATE
        Qt::Core
        Qt::Widgets
        ${Boost_LIBRARIES}
        ws2_32
)

target_include_directories(Navigation PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(Navigation PRIVATE ${Boost_LIBRARIES})

include(GNUInstallDirs)

install(TARGETS Navigation
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Navigation
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
