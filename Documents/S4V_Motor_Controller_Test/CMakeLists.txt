cmake_minimum_required(VERSION 3.19)
project(S4V_Motor_Controller_Test LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets SerialPort)

# This automatically handles AUTOMOC, AUTOUIC, and AUTORCC
qt_standard_project_setup()

qt_add_executable(S4V_Motor_Controller_Test
    WIN32 MACOSX_BUNDLE
    main.cpp

    UI/mainwindow.cpp
    UI/mainwindow.h
    UI/mainwindow.ui

    Hardware/serialcontroller.cpp
    Hardware/serialcontroller.h

)


# --- NEW: The Bulletproof Qt 6 Resource Compiler ---
qt_add_resources(S4V_Motor_Controller_Test "assets"
    PREFIX "/"
    BASE "Resources"
    FILES
        Resources/style.qss
        Resources/steamforvietnam.png
        Resources/connection.svg
        Resources/control.svg
        Resources/update.svg
        Resources/motor_controller.png
        Resources/speed.svg
        Resources/brake.svg
        Resources/electricity.svg

)

target_link_libraries(S4V_Motor_Controller_Test
    PRIVATE
    Qt::Core
    Qt::Widgets
    Qt::SerialPort
)

target_include_directories(S4V_Motor_Controller_Test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

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