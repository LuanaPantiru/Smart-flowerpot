# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/e/FlowerPot/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/FlowerPot/project/cmake-build-wsl

# Include any dependencies generated for this target.
include CMakeFiles/smart_pot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/smart_pot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/smart_pot.dir/flags.make

CMakeFiles/smart_pot.dir/src/main.cpp.o: CMakeFiles/smart_pot.dir/flags.make
CMakeFiles/smart_pot.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/FlowerPot/project/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/smart_pot.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/smart_pot.dir/src/main.cpp.o -c /mnt/e/FlowerPot/project/src/main.cpp

CMakeFiles/smart_pot.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smart_pot.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/FlowerPot/project/src/main.cpp > CMakeFiles/smart_pot.dir/src/main.cpp.i

CMakeFiles/smart_pot.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smart_pot.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/FlowerPot/project/src/main.cpp -o CMakeFiles/smart_pot.dir/src/main.cpp.s

CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.o: CMakeFiles/smart_pot.dir/flags.make
CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.o: ../src/AppHttpHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/FlowerPot/project/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.o -c /mnt/e/FlowerPot/project/src/AppHttpHandler.cpp

CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/FlowerPot/project/src/AppHttpHandler.cpp > CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.i

CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/FlowerPot/project/src/AppHttpHandler.cpp -o CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.s

CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.o: CMakeFiles/smart_pot.dir/flags.make
CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.o: ../src/AppHardwareHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/FlowerPot/project/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.o -c /mnt/e/FlowerPot/project/src/AppHardwareHandler.cpp

CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/FlowerPot/project/src/AppHardwareHandler.cpp > CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.i

CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/FlowerPot/project/src/AppHardwareHandler.cpp -o CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.s

CMakeFiles/smart_pot.dir/src/SmartPot.cpp.o: CMakeFiles/smart_pot.dir/flags.make
CMakeFiles/smart_pot.dir/src/SmartPot.cpp.o: ../src/SmartPot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/FlowerPot/project/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/smart_pot.dir/src/SmartPot.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/smart_pot.dir/src/SmartPot.cpp.o -c /mnt/e/FlowerPot/project/src/SmartPot.cpp

CMakeFiles/smart_pot.dir/src/SmartPot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smart_pot.dir/src/SmartPot.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/FlowerPot/project/src/SmartPot.cpp > CMakeFiles/smart_pot.dir/src/SmartPot.cpp.i

CMakeFiles/smart_pot.dir/src/SmartPot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smart_pot.dir/src/SmartPot.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/FlowerPot/project/src/SmartPot.cpp -o CMakeFiles/smart_pot.dir/src/SmartPot.cpp.s

CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.o: CMakeFiles/smart_pot.dir/flags.make
CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.o: ../src/NotificationCenter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/FlowerPot/project/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.o -c /mnt/e/FlowerPot/project/src/NotificationCenter.cpp

CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/FlowerPot/project/src/NotificationCenter.cpp > CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.i

CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/FlowerPot/project/src/NotificationCenter.cpp -o CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.s

CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.o: CMakeFiles/smart_pot.dir/flags.make
CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.o: ../src/MqttClientHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/FlowerPot/project/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.o -c /mnt/e/FlowerPot/project/src/MqttClientHandler.cpp

CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/FlowerPot/project/src/MqttClientHandler.cpp > CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.i

CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/FlowerPot/project/src/MqttClientHandler.cpp -o CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.s

# Object files for target smart_pot
smart_pot_OBJECTS = \
"CMakeFiles/smart_pot.dir/src/main.cpp.o" \
"CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.o" \
"CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.o" \
"CMakeFiles/smart_pot.dir/src/SmartPot.cpp.o" \
"CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.o" \
"CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.o"

# External object files for target smart_pot
smart_pot_EXTERNAL_OBJECTS =

smart_pot: CMakeFiles/smart_pot.dir/src/main.cpp.o
smart_pot: CMakeFiles/smart_pot.dir/src/AppHttpHandler.cpp.o
smart_pot: CMakeFiles/smart_pot.dir/src/AppHardwareHandler.cpp.o
smart_pot: CMakeFiles/smart_pot.dir/src/SmartPot.cpp.o
smart_pot: CMakeFiles/smart_pot.dir/src/NotificationCenter.cpp.o
smart_pot: CMakeFiles/smart_pot.dir/src/MqttClientHandler.cpp.o
smart_pot: CMakeFiles/smart_pot.dir/build.make
smart_pot: CMakeFiles/smart_pot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/FlowerPot/project/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable smart_pot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/smart_pot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/smart_pot.dir/build: smart_pot

.PHONY : CMakeFiles/smart_pot.dir/build

CMakeFiles/smart_pot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/smart_pot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/smart_pot.dir/clean

CMakeFiles/smart_pot.dir/depend:
	cd /mnt/e/FlowerPot/project/cmake-build-wsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/FlowerPot/project /mnt/e/FlowerPot/project /mnt/e/FlowerPot/project/cmake-build-wsl /mnt/e/FlowerPot/project/cmake-build-wsl /mnt/e/FlowerPot/project/cmake-build-wsl/CMakeFiles/smart_pot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/smart_pot.dir/depend

