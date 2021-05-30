CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

MESSAGE(STATUS "================== wrapper ==================")

OPTION(BUILD_SHARED_LIBS "Build NeIM SDK C++ wrapper as a shared library." ON)
SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../ CACHE PATH "Default install prefix")
SET(INSTALL_CPP_WRAPPER ON CACHE BOOL "Exports headers of C++ warpper when called cmake --target INSTALL")

PROJECT(nim_cpp_wrapper)

SET(CMAKE_CXX_STANDARD 11)

message(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")

IF (MSVC)
    ADD_DEFINITIONS(
        -DUNICODE
        -D_UNICODE
        -DNOMINMAX
        -DWIN32_LEAN_AND_MEAN
        -DPSAPI_VERSION=1
        -DNIM_SDK_DLL_IMPORT
    )
    message(STATUS "add definitions UNICODE, UNICODE, NOMINMAX, WIN32_LEAN_AND_MEAN, PSAPI_VERSION=1, NIM_SDK_DLL_IMPORT")
ENDIF ()

INCLUDE_DIRECTORIES(
    # for development directory
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${CMAKE_CURRENT_LIST_DIR}/../nim/api
    ${CMAKE_CURRENT_LIST_DIR}/../nim/nim_defines
    ${CMAKE_CURRENT_LIST_DIR}/../nim_chatroom/api
    ${CMAKE_CURRENT_LIST_DIR}/../nim_chatroom/nim_chatroom_defines
    ${CMAKE_CURRENT_LIST_DIR}/../nim_tools_http
    ${CMAKE_CURRENT_LIST_DIR}/../public_defines
    # for export directory
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/../framework/nim.framework/Headers
    ${CMAKE_CURRENT_LIST_DIR}/../framework/nim_chatroom.framework/Headers
)

IF (MSVC)
    ADD_DEFINITIONS(-DWIN32)
    ADD_COMPILE_OPTIONS(/wd4573 /wd4251 /wd4273 /wd4819)
    ADD_COMPILE_OPTIONS("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    ADD_COMPILE_OPTIONS("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    SET(CMAKE_DEBUG_POSTFIX "_d")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
ENDIF ()

ADD_SUBDIRECTORY(nim_wrapper_util)
ADD_SUBDIRECTORY(nim_cpp_wrapper)
ADD_SUBDIRECTORY(nim_chatroom_cpp_wrapper)
IF (MSVC)
    ADD_SUBDIRECTORY(nim_tools_cpp_wrapper)
ENDIF ()

IF (INSTALL_CPP_WRAPPER)
    IF (MSVC)
        INSTALL(
            TARGETS nim_wrapper_util nim_cpp_wrapper nim_chatroom_cpp_wrapper nim_tools_cpp_wrapper
            ARCHIVE DESTINATION lib ${CMAKE_INSTALL_BINDIR}
            RUNTIME DESTINATION bin ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION lib ${CMAKE_INSTALL_LIBDIR}
        )
    ELSE ()
        INSTALL(
            TARGETS nim_wrapper_util nim_cpp_wrapper nim_chatroom_cpp_wrapper 
            ARCHIVE DESTINATION lib ${CMAKE_INSTALL_BINDIR}
            RUNTIME DESTINATION bin ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION lib ${CMAKE_INSTALL_LIBDIR}
        )
    ENDIF ()
    INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/ DESTINATION include FILES_MATCHING PATTERN "*.h")
ENDIF ()
