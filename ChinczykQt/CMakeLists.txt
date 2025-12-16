cmake_minimum_required(VERSION 3.19)
project(ChinczykQt LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(ChinczykQt
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    gra.h gra.cpp
    plansza.h plansza.cpp
    gracz.h gracz.cpp
    pionek.h pionek.cpp
    kostka.h kostka.cpp
    boardscene.h boardscene.cpp
    tokenitem.h tokenitem.cpp
)

target_link_libraries(ChinczykQt
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS ChinczykQt
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ChinczykQt
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
