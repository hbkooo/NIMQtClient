cmake_minimum_required(VERSION 3.19)
project(NIMQtClient)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "D:/programming/QT/install/5.14.1/msvc2017/lib/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

set(CMAKE_BUILD_TYPE "Release")

IF (MSVC)
    ADD_DEFINITIONS(
            -DUNICODE
            -DUNICODE
            -DNOMINMAX
            -DWIN32_LEAN_AND_MEAN
            -DPSAPI_VERSION=1
            -DNIM_SDK_DLL_IMPORT
    )
    ADD_DEFINITIONS(-DWIN32)
    ADD_COMPILE_OPTIONS(/wd4573 /wd4251 /wd4273 /wd4819)
    ADD_COMPILE_OPTIONS("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    ADD_COMPILE_OPTIONS("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
ENDIF ()

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

include_directories(nim_sdk/include)
include_directories(nim_sdk/wrapper)
add_subdirectory(nim_sdk/wrapper)

include_directories(src)
include_directories(window)

aux_source_directory(src SOURCE_FILES)
file(GLOB HEADER_FILES src/*.h)

#aux_source_directory(window WINDOW_SOURCE_FILES)
file(GLOB WINDOW_SOURCE_FILES
        window/*.cpp
        window/util/*.cpp
        window/login/*.cpp
        window/userinfo/*.cpp
        window/recentSessionWidget/*.cpp
        window/friendsWidget/*.cpp
        window/chattingWidget/*.cpp)
file(GLOB WINDOW_HEADER_FILES
        window/*.h
        window/util/*.h
        window/login/*.h
        window/userinfo/*.h
        window/recentSessionWidget/*.h
        window/friendsWidget/*.h
        window/chattingWidget/*.h)

message(${WINDOW_SOURCE_FILES})

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES} ${HEADER_FILES} ${WINDOW_SOURCE_FILES} ${WINDOW_HEADER_FILES} Qrc.qrc)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

set(NIM_LIBRARY nim_wrapper_util nim_cpp_wrapper nim_tools_cpp_wrapper nim_chatroom_cpp_wrapper)
target_link_libraries(${PROJECT_NAME} ${NIM_LIBRARY})

if (WIN32)
    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB ${REQUIRED_LIBS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)

    foreach(NIM_LIB ${NIM_LIBRARY})
        if (EXISTS "${CMAKE_BINARY_DIR}/nim_sdk/wrapper/${NIM_LIB}/${NIM_LIB}.dll")
            add_custom_command(TARGET  ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${CMAKE_BINARY_DIR}/nim_sdk/wrapper/${NIM_LIB}/${NIM_LIB}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        endif ()
    endforeach(NIM_LIB)

endif ()