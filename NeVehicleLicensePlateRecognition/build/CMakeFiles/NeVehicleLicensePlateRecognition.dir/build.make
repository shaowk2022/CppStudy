# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build

# Include any dependencies generated for this target.
include CMakeFiles/NeVehicleLicensePlateRecognition.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/NeVehicleLicensePlateRecognition.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/NeVehicleLicensePlateRecognition.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NeVehicleLicensePlateRecognition.dir/flags.make

CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/flags.make
CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.o: ../AnnPredict.cpp
CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.o -MF CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.o.d -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.o -c /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/AnnPredict.cpp

CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/AnnPredict.cpp > CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.i

CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/AnnPredict.cpp -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.s

CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/flags.make
CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.o: ../ColorLocate.cpp
CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.o -MF CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.o.d -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.o -c /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ColorLocate.cpp

CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ColorLocate.cpp > CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.i

CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ColorLocate.cpp -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.s

CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/flags.make
CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.o: ../NeVehicleLicensePlateRecognition.cpp
CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.o -MF CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.o.d -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.o -c /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/NeVehicleLicensePlateRecognition.cpp

CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/NeVehicleLicensePlateRecognition.cpp > CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.i

CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/NeVehicleLicensePlateRecognition.cpp -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.s

CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/flags.make
CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.o: ../PlateLocate.cpp
CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.o -MF CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.o.d -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.o -c /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/PlateLocate.cpp

CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/PlateLocate.cpp > CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.i

CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/PlateLocate.cpp -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.s

CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/flags.make
CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.o: ../PlateRecognize.cpp
CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.o -MF CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.o.d -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.o -c /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/PlateRecognize.cpp

CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/PlateRecognize.cpp > CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.i

CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/PlateRecognize.cpp -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.s

CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/flags.make
CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.o: ../SobelLocate.cpp
CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.o -MF CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.o.d -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.o -c /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/SobelLocate.cpp

CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/SobelLocate.cpp > CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.i

CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/SobelLocate.cpp -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.s

CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/flags.make
CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.o: ../SvmPredict.cpp
CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.o: CMakeFiles/NeVehicleLicensePlateRecognition.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.o -MF CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.o.d -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.o -c /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/SvmPredict.cpp

CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/SvmPredict.cpp > CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.i

CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/SvmPredict.cpp -o CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.s

# Object files for target NeVehicleLicensePlateRecognition
NeVehicleLicensePlateRecognition_OBJECTS = \
"CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.o" \
"CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.o" \
"CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.o" \
"CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.o" \
"CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.o" \
"CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.o" \
"CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.o"

# External object files for target NeVehicleLicensePlateRecognition
NeVehicleLicensePlateRecognition_EXTERNAL_OBJECTS =

../bin/NeVehicleLicensePlateRecognition: CMakeFiles/NeVehicleLicensePlateRecognition.dir/AnnPredict.cpp.o
../bin/NeVehicleLicensePlateRecognition: CMakeFiles/NeVehicleLicensePlateRecognition.dir/ColorLocate.cpp.o
../bin/NeVehicleLicensePlateRecognition: CMakeFiles/NeVehicleLicensePlateRecognition.dir/NeVehicleLicensePlateRecognition.cpp.o
../bin/NeVehicleLicensePlateRecognition: CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateLocate.cpp.o
../bin/NeVehicleLicensePlateRecognition: CMakeFiles/NeVehicleLicensePlateRecognition.dir/PlateRecognize.cpp.o
../bin/NeVehicleLicensePlateRecognition: CMakeFiles/NeVehicleLicensePlateRecognition.dir/SobelLocate.cpp.o
../bin/NeVehicleLicensePlateRecognition: CMakeFiles/NeVehicleLicensePlateRecognition.dir/SvmPredict.cpp.o
../bin/NeVehicleLicensePlateRecognition: CMakeFiles/NeVehicleLicensePlateRecognition.dir/build.make
../bin/NeVehicleLicensePlateRecognition: CMakeFiles/NeVehicleLicensePlateRecognition.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable ../bin/NeVehicleLicensePlateRecognition"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NeVehicleLicensePlateRecognition.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NeVehicleLicensePlateRecognition.dir/build: ../bin/NeVehicleLicensePlateRecognition
.PHONY : CMakeFiles/NeVehicleLicensePlateRecognition.dir/build

CMakeFiles/NeVehicleLicensePlateRecognition.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NeVehicleLicensePlateRecognition.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NeVehicleLicensePlateRecognition.dir/clean

CMakeFiles/NeVehicleLicensePlateRecognition.dir/depend:
	cd /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build /home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/build/CMakeFiles/NeVehicleLicensePlateRecognition.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NeVehicleLicensePlateRecognition.dir/depend

