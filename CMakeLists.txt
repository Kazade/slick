CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(slick)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x")

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTKMM gtkmm-2.4 REQUIRED)

FIND_PACKAGE(Boost 1.46 COMPONENTS system filesystem thread regex date_time REQUIRED)
FIND_PACKAGE(CURL REQUIRED)

SET(KAZBASE_SOURCES
    ./src/kazbase/fdo/autostart.cpp
    ./src/kazbase/fdo/applications.cpp
    ./src/kazbase/fdo/base_directory.cpp
    ./src/kazbase/config/config_reader.cpp
    ./src/kazbase/os/path.cpp
    ./src/kazbase/os/core.cpp
    ./src/kazbase/string.cpp
    ./src/kazbase/logging/logging.cpp    
    ./src/kazbase/datetime.cpp    
    ./src/kazbase/parse/tree_parser.cpp
    ./src/kazbase/regex/regex.cpp
    ./src/kazbase/hash/md5.cpp
    ./src/kazbase/hash/md5_public_domain.cpp
    ./src/kazbase/requests/requests.cpp
    ./src/kazbase/network/net.cpp    
    ./src/kazbase/colour/colour.cpp
)

SET(FRONTEND_SOURCES
    ./src/frontend/main_window.cpp
)

LINK_DIRECTORIES(
    ${GTKMM_LIBRARY_DIRS}
)

INCLUDE_DIRECTORIES(
    ./src
    ${GTKMM_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
)

ADD_EXECUTABLE(slick 
    ${KAZBASE_SOURCES} 
    ${FRONTEND_SOURCES}
    ./src/main.cpp
)

TARGET_LINK_LIBRARIES(slick
    ${GTKMM_LIBRARIES}
    ${CURL_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
)




