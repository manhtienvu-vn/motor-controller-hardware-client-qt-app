cmake_minimum_required(VERSION 3.19)
project(S4V_Motor_Controller_Test LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets SerialPort)

qt_standard_project_setup()

qt_add_executable(S4V_Motor_Controller_Test
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

)

qt_add_resources(S4V_Motor_Controller_Test "stylesheets"
    PREFIX "/"
    FILES
        style.qss
        steamforvietnam.png
        connection.svg
        control.svg
        update.svg
)

target_link_libraries(S4V_Motor_Controller_Test
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::SerialPort
)

install(TARGETS S4V_Motor_Controller_Test
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET S4V_Motor_Controller_Test
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
