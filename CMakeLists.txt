cmake_minimum_required(VERSION 3.16)

project(KneeRehab VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)

# Add the src directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Bluetooth)

qt_standard_project_setup()

# set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/android")


qt_add_executable(KneeRehab
    src/main.cpp
)

set_property(TARGET KneeRehab APPEND PROPERTY
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)


qt_add_qml_module(KneeRehab
    URI KneeRehab
    VERSION 1.0
    QML_FILES
        ui/qml/Main.qml
        ui/qml/HomePage.qml
        ui/qml/DebugPage.qml
    SOURCES
        src/BluetoothManager.h src/BluetoothManager.cpp
        android/AndroidManifest.xml
        src/Utilities.h src/Utilities.cpp
        src/Parser.h src/Parser.cpp
        src/BluetoothDevice.h src/BluetoothDevice.cpp
    RESOURCES
        Resources.qrc
        SOURCES src/InternetSocketManager.h src/InternetSocketManager.cpp
        SOURCES src/BluetoothSocketManager.h src/BluetoothSocketManager.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(KneeRehab PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.KneeRehab
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(KneeRehab
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Bluetooth
)

include(GNUInstallDirs)
install(TARGETS KneeRehab
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
