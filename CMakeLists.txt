cmake_minimum_required(VERSION 3.20)
project(Life_After_School)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "D:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake")
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

include_directories(controller)
include_directories(domain)
include_directories(repository)
include_directories(ui)
include_directories(gui)

add_executable(Life_After_School
        controller/Controller.cpp
        controller/Controller.h
        domain/Event.cpp
        domain/Event.h
        repository/CSVEventRepository.cpp
        repository/CSVEventRepository.h
        repository/EventRepository.cpp
        repository/EventRepository.h
        repository/HTMLEventRepository.cpp
        repository/HTMLEventRepository.h
        ui/UI.cpp
        ui/UI.h
        ui/main.cpp
        gui/main.cpp
        gui/UserGUI.h
        gui/UserGUI.cpp gui/DialogShowAllEvents.cpp gui/DialogShowAllEvents.h gui/AdminGUI.cpp gui/AdminGUI.h gui/StartGUI.cpp gui/StartGUI.h gui/SingleEventGUI.cpp gui/SingleEventGUI.h "gui/user events/ManageUserEventsGUI.cpp" "gui/user events/ManageUserEventsGUI.h" "gui/user events/UserEventsTableModel.cpp" "gui/user events/UserEventsTableModel.h" controller/Operation.cpp controller/Operation.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})