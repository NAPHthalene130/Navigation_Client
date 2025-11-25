cmake_minimum_required(VERSION 3.30)
project(Navigation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(_qt_root "H:/Qt")
    if (EXISTS "${_qt_root}")
        file(GLOB _qt_mingw_candidates "${_qt_root}/*/mingw_64")
        list(SORT _qt_mingw_candidates)
        list(REVERSE _qt_mingw_candidates)
        list(GET _qt_mingw_candidates 0 _qt_mingw_path)
        if (EXISTS "${_qt_mingw_path}")
            set(CMAKE_PREFIX_PATH "${_qt_mingw_path}")
        endif()
    endif()
endif()
if (DEFINED CMAKE_PREFIX_PATH AND NOT DEFINED Qt6_DIR)
    set(Qt6_DIR "${CMAKE_PREFIX_PATH}/lib/cmake/Qt6")
endif()

find_package(Qt6 6.6 REQUIRED COMPONENTS Core Widgets)



find_package(Boost 1.80 CONFIG REQUIRED COMPONENTS system)
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
        Boost::system
        ws2_32
)

target_include_directories(Navigation PRIVATE ${Boost_INCLUDE_DIRS})

 

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

if (DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED VCPKG_TARGET_TRIPLET)
    get_filename_component(_vcpkg_scripts_dir "${CMAKE_TOOLCHAIN_FILE}" DIRECTORY)
    get_filename_component(_vcpkg_dir "${_vcpkg_scripts_dir}" DIRECTORY)
    get_filename_component(VCPKG_ROOT "${_vcpkg_dir}" DIRECTORY)
    set(VCPKG_BIN_DIR "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/bin")
    if (EXISTS "${VCPKG_BIN_DIR}")
        file(GLOB VCPKG_DLLS "${VCPKG_BIN_DIR}/*.dll")
        if (VCPKG_DLLS)
            install(FILES ${VCPKG_DLLS} DESTINATION ${CMAKE_INSTALL_BINDIR})
        endif()
    endif()
endif()
cmake_policy(SET CMP0167 NEW)
