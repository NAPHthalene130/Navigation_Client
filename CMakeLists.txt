cmake_minimum_required(VERSION 3.30)
project(Navigation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_policy(SET CMP0167 NEW)

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
if (EXISTS "H:/vcpkg/installed/x64-mingw-dynamic")
    list(APPEND CMAKE_PREFIX_PATH "H:/vcpkg/installed/x64-mingw-dynamic")
endif()

set(QT_FORCE_CMP0156_TO_VALUE NEW)
find_package(Qt6 6.6 REQUIRED COMPONENTS Core Widgets Network Svg)
find_package(Boost 1.80 CONFIG REQUIRED COMPONENTS system)

qt_standard_project_setup()

qt_add_executable(Navigation
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    util/MapDataNetReader.cpp
    util/MapDataNetReader.h
    util/ClickedButton.cpp
    util/ClickedButton.h
    widgets/mainWidget.cpp
    widgets/mainWidget.h
    util/MapPointButton.cpp
    util/MapPointButton.h
    widgets/leftWidget.cpp
    widgets/leftWidget.h
    widgets/mapConstructorWidget.cpp
    widgets/mapConstructorWidget.h
    widgets/LoadMapWidget.cpp
    widgets/LoadMapWidget.h
    widgets/SaveMapWidget.cpp
    widgets/SaveMapWidget.h
    widgets/addPointWidget.cpp
    widgets/addPointWidget.h
    util/MapDataContainer.cpp
    util/MapDataContainer.h
    util/DebugDialog.cpp
    util/DebugDialog.h
    util/NoticeDialog.cpp
    util/NoticeDialog.h
    util/Edge.cpp
    util/Edge.h
    util/DataIO.cpp
    util/DataIO.h
    img/mapPic.png
)

target_link_libraries(Navigation
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
        Qt::Svg
        Boost::system
        ws2_32
)

target_include_directories(Navigation PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/util)

include(GNUInstallDirs)

install(TARGETS Navigation
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/img DESTINATION ${CMAKE_INSTALL_BINDIR})

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
