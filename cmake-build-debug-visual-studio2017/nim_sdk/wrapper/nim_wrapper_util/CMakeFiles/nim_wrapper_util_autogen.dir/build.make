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

# Utility rule file for nim_wrapper_util_autogen.

# Include the progress variables for this target.
include nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen.dir\progress.make

nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target nim_wrapper_util"
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_wrapper_util
	echo >nul && "D:\programming\Clion\install\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E cmake_autogen D:/programming/Clion/projects/NIMQtClient/cmake-build-debug-visual-studio2017/nim_sdk/wrapper/nim_wrapper_util/CMakeFiles/nim_wrapper_util_autogen.dir/AutogenInfo.json Release
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017

nim_wrapper_util_autogen: nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen
nim_wrapper_util_autogen: nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen.dir\build.make

.PHONY : nim_wrapper_util_autogen

# Rule to build all files generated by this target.
nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen.dir\build: nim_wrapper_util_autogen

.PHONY : nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen.dir\build

nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen.dir\clean:
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_wrapper_util
	$(CMAKE_COMMAND) -P CMakeFiles\nim_wrapper_util_autogen.dir\cmake_clean.cmake
	cd D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017
.PHONY : nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen.dir\clean

nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\programming\Clion\projects\NIMQtClient D:\programming\Clion\projects\NIMQtClient\nim_sdk\wrapper\nim_wrapper_util D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017 D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_wrapper_util D:\programming\Clion\projects\NIMQtClient\cmake-build-debug-visual-studio2017\nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : nim_sdk\wrapper\nim_wrapper_util\CMakeFiles\nim_wrapper_util_autogen.dir\depend

