include("H:/CODE/Trae/Navigation/Navigation_Client/out/build/GCC 13.1.0 x86_64-w64-mingw32/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Navigation-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "H:/CODE/Trae/Navigation/Navigation_Client/out/build/GCC 13.1.0 x86_64-w64-mingw32/Navigation.exe"
    GENERATE_QT_CONF
)
