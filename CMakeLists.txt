cmake_minimum_required(VERSION 3.2)
project(QtFrameWork)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets Core Gui Xml REQUIRED)

FILE(GLOB_RECURSE HEADER_FILES "*.h")
FILE(GLOB_RECURSE SRC_FILES "*.cpp")

set(SOURCES
    main.cpp
    MainWindow.cpp
    CommandScheduler.cpp
)

set(HEADERS
    ExampleCommand.h
    Command.h
    CommandQueue.h
    CommandScheduler.h
)

set(qt_moc_inc
    MainWindow.h
)

qt5_wrap_cpp(qt5_moc_cpp ${qt_moc_inc} ${qt5_uis})

#add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${qt5_moc_cpp} ${qt_moc_inc
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Xml)
