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
include nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\depend.make

# Include the progress variables for this target.
include nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\progress.make

# Include the compile flags for this target's objects.
include nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\flags.make

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp.obj: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\flags.make
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp.obj: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object nim_sdk/wrapper/nim_chatroom_cpp_wrapper/CMakeFiles/nim_chatroom_cpp_wrapper.dir/nim_chatroom_cpp_wrapper_autogen/mocs_compilation.cpp.obj"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\nim_chatroom_cpp_wrapper.dir\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp.obj /FdCMakeFiles\nim_chatroom_cpp_wrapper.dir\ /FS -c D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nim_chatroom_cpp_wrapper.dir/nim_chatroom_cpp_wrapper_autogen/mocs_compilation.cpp.i"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe > CMakeFiles\nim_chatroom_cpp_wrapper.dir\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nim_chatroom_cpp_wrapper.dir/nim_chatroom_cpp_wrapper_autogen/mocs_compilation.cpp.s"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\nim_chatroom_cpp_wrapper.dir\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp.s /c D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\api\nim_chatroom_cpp.cpp.obj: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\flags.make
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\api\nim_chatroom_cpp.cpp.obj: ..\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\api\nim_chatroom_cpp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object nim_sdk/wrapper/nim_chatroom_cpp_wrapper/CMakeFiles/nim_chatroom_cpp_wrapper.dir/api/nim_chatroom_cpp.cpp.obj"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\nim_chatroom_cpp_wrapper.dir\api\nim_chatroom_cpp.cpp.obj /FdCMakeFiles\nim_chatroom_cpp_wrapper.dir\ /FS -c D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\api\nim_chatroom_cpp.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\api\nim_chatroom_cpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nim_chatroom_cpp_wrapper.dir/api/nim_chatroom_cpp.cpp.i"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe > CMakeFiles\nim_chatroom_cpp_wrapper.dir\api\nim_chatroom_cpp.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\api\nim_chatroom_cpp.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\api\nim_chatroom_cpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nim_chatroom_cpp_wrapper.dir/api/nim_chatroom_cpp.cpp.s"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\nim_chatroom_cpp_wrapper.dir\api\nim_chatroom_cpp.cpp.s /c D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\api\nim_chatroom_cpp.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_helper.cpp.obj: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\flags.make
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_helper.cpp.obj: ..\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\helper\nim_chatroom_helper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object nim_sdk/wrapper/nim_chatroom_cpp_wrapper/CMakeFiles/nim_chatroom_cpp_wrapper.dir/helper/nim_chatroom_helper.cpp.obj"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_helper.cpp.obj /FdCMakeFiles\nim_chatroom_cpp_wrapper.dir\ /FS -c D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\helper\nim_chatroom_helper.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nim_chatroom_cpp_wrapper.dir/helper/nim_chatroom_helper.cpp.i"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe > CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_helper.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\helper\nim_chatroom_helper.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nim_chatroom_cpp_wrapper.dir/helper/nim_chatroom_helper.cpp.s"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_helper.cpp.s /c D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\helper\nim_chatroom_helper.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_loader_helper.cpp.obj: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\flags.make
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_loader_helper.cpp.obj: ..\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\helper\nim_chatroom_loader_helper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object nim_sdk/wrapper/nim_chatroom_cpp_wrapper/CMakeFiles/nim_chatroom_cpp_wrapper.dir/helper/nim_chatroom_loader_helper.cpp.obj"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_loader_helper.cpp.obj /FdCMakeFiles\nim_chatroom_cpp_wrapper.dir\ /FS -c D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\helper\nim_chatroom_loader_helper.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_loader_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nim_chatroom_cpp_wrapper.dir/helper/nim_chatroom_loader_helper.cpp.i"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe > CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_loader_helper.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\helper\nim_chatroom_loader_helper.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_loader_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nim_chatroom_cpp_wrapper.dir/helper/nim_chatroom_loader_helper.cpp.s"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_loader_helper.cpp.s /c D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\helper\nim_chatroom_loader_helper.cpp
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

# Object files for target nim_chatroom_cpp_wrapper
nim_chatroom_cpp_wrapper_OBJECTS = \
"CMakeFiles\nim_chatroom_cpp_wrapper.dir\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp.obj" \
"CMakeFiles\nim_chatroom_cpp_wrapper.dir\api\nim_chatroom_cpp.cpp.obj" \
"CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_helper.cpp.obj" \
"CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_loader_helper.cpp.obj"

# External object files for target nim_chatroom_cpp_wrapper
nim_chatroom_cpp_wrapper_EXTERNAL_OBJECTS =

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper.dll: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\nim_chatroom_cpp_wrapper_autogen\mocs_compilation.cpp.obj
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper.dll: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\api\nim_chatroom_cpp.cpp.obj
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper.dll: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_helper.cpp.obj
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper.dll: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\helper\nim_chatroom_loader_helper.cpp.obj
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper.dll: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\build.make
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper.dll: nim_sdk\wrapper\nim_wrapper_util\nim_wrapper_util.lib
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper.dll: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library nim_chatroom_cpp_wrapper.dll"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	"D:\programming\Clion\install\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E vs_link_dll --intdir=CMakeFiles\nim_chatroom_cpp_wrapper.dir --rc="D:\Windows Kits\10\bin\10.0.17134.0\x86\rc.exe" --mt="D:\Windows Kits\10\bin\10.0.17134.0\x86\mt.exe" --manifests -- D:\programming\VisualStudio2017\IDE\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\nim_chatroom_cpp_wrapper.dir\objects1.rsp @<<
 /out:nim_chatroom_cpp_wrapper.dll /implib:nim_chatroom_cpp_wrapper.lib /pdb:D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper.pdb /dll /version:0.0 /machine:X86 /SAFESEH:NO /INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF /DEBUG /OPT:REF /OPT:ICF  ..\nim_wrapper_util\nim_wrapper_util.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib  
<<
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

# Rule to build all files generated by this target.
nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\build: nim_sdk\wrapper\nim_chatroom_cpp_wrapper\nim_chatroom_cpp_wrapper.dll

.PHONY : nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\build

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\clean:
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper
	$(CMAKE_COMMAND) -P CMakeFiles\nim_chatroom_cpp_wrapper.dir\cmake_clean.cmake
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017
.PHONY : nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\clean

nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\programming\Clion\projects\NIMQtClient D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_chatroom_cpp_wrapper D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017 D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : nim_sdk\wrapper\nim_chatroom_cpp_wrapper\CMakeFiles\nim_chatroom_cpp_wrapper.dir\depend

