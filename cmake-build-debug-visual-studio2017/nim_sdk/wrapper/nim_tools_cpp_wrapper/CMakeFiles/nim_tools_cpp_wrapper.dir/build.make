# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\programming\Clion\install\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\programming\Clion\install\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\programming\Clion\projects\NIMQtClient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

# Include any dependencies generated for this target.
include nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\depend.make

# Include the progress variables for this target.
include nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\progress.make

# Include the compile flags for this target's objects.
include nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\flags.make

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp.obj: nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\flags.make
nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp.obj: nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object nim_sdk/wrapper/nim_tools_cpp_wrapper/CMakeFiles/nim_tools_cpp_wrapper.dir/nim_tools_cpp_wrapper_autogen/mocs_compilation.cpp.obj"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp.obj /FdCMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper.pdb /FS -c D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nim_tools_cpp_wrapper.dir/nim_tools_cpp_wrapper_autogen/mocs_compilation.cpp.i"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe > CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nim_tools_cpp_wrapper.dir/nim_tools_cpp_wrapper_autogen/mocs_compilation.cpp.s"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp.s /c D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_audio_cpp.cpp.obj: nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\flags.make
nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_audio_cpp.cpp.obj: ..\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_audio_cpp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object nim_sdk/wrapper/nim_tools_cpp_wrapper/CMakeFiles/nim_tools_cpp_wrapper.dir/nim_audio_cpp.cpp.obj"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\nim_tools_cpp_wrapper.dir\nim_audio_cpp.cpp.obj /FdCMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper.pdb /FS -c D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_audio_cpp.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_audio_cpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nim_tools_cpp_wrapper.dir/nim_audio_cpp.cpp.i"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe > CMakeFiles\nim_tools_cpp_wrapper.dir\nim_audio_cpp.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_audio_cpp.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_audio_cpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nim_tools_cpp_wrapper.dir/nim_audio_cpp.cpp.s"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\nim_tools_cpp_wrapper.dir\nim_audio_cpp.cpp.s /c D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_audio_cpp.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_http_cpp.cpp.obj: nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\flags.make
nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_http_cpp.cpp.obj: ..\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_http_cpp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object nim_sdk/wrapper/nim_tools_cpp_wrapper/CMakeFiles/nim_tools_cpp_wrapper.dir/nim_tools_http_cpp.cpp.obj"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_http_cpp.cpp.obj /FdCMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper.pdb /FS -c D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_http_cpp.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_http_cpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nim_tools_cpp_wrapper.dir/nim_tools_http_cpp.cpp.i"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe > CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_http_cpp.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_http_cpp.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_http_cpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nim_tools_cpp_wrapper.dir/nim_tools_http_cpp.cpp.s"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_http_cpp.cpp.s /c D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_http_cpp.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

# Object files for target nim_tools_cpp_wrapper
nim_tools_cpp_wrapper_OBJECTS = \
"CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp.obj" \
"CMakeFiles\nim_tools_cpp_wrapper.dir\nim_audio_cpp.cpp.obj" \
"CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_http_cpp.cpp.obj"

# External object files for target nim_tools_cpp_wrapper
nim_tools_cpp_wrapper_EXTERNAL_OBJECTS =

nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_cpp_wrapper.lib: nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_cpp_wrapper_autogen\mocs_compilation.cpp.obj
nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_cpp_wrapper.lib: nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_audio_cpp.cpp.obj
nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_cpp_wrapper.lib: nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\nim_tools_http_cpp.cpp.obj
nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_cpp_wrapper.lib: nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\build.make
nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_cpp_wrapper.lib: nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library nim_tools_cpp_wrapper.lib"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	$(CMAKE_COMMAND) -P CMakeFiles\nim_tools_cpp_wrapper.dir\cmake_clean_target.cmake
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\lib.exe /nologo /machine:X86 /out:nim_tools_cpp_wrapper.lib @CMakeFiles\nim_tools_cpp_wrapper.dir\objects1.rsp 
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

# Rule to build all files generated by this target.
nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\build: nim_sdk\wrapper\nim_tools_cpp_wrapper\nim_tools_cpp_wrapper.lib

.PHONY : nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\build

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\clean:
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper
	$(CMAKE_COMMAND) -P CMakeFiles\nim_tools_cpp_wrapper.dir\cmake_clean.cmake
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017
.PHONY : nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\clean

nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\programming\Clion\projects\NIMQtClient D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_tools_cpp_wrapper D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017 D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : nim_sdk\wrapper\nim_tools_cpp_wrapper\CMakeFiles\nim_tools_cpp_wrapper.dir\depend

