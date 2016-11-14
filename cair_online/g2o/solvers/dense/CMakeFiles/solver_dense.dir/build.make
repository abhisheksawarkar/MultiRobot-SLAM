# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/abhishek/g2o

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abhishek/g2o

# Include any dependencies generated for this target.
include g2o/solvers/dense/CMakeFiles/solver_dense.dir/depend.make

# Include the progress variables for this target.
include g2o/solvers/dense/CMakeFiles/solver_dense.dir/progress.make

# Include the compile flags for this target's objects.
include g2o/solvers/dense/CMakeFiles/solver_dense.dir/flags.make

g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o: g2o/solvers/dense/CMakeFiles/solver_dense.dir/flags.make
g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o: g2o/solvers/dense/solver_dense.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/abhishek/g2o/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o"
	cd /home/abhishek/g2o/g2o/solvers/dense && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/solver_dense.dir/solver_dense.cpp.o -c /home/abhishek/g2o/g2o/solvers/dense/solver_dense.cpp

g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solver_dense.dir/solver_dense.cpp.i"
	cd /home/abhishek/g2o/g2o/solvers/dense && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/abhishek/g2o/g2o/solvers/dense/solver_dense.cpp > CMakeFiles/solver_dense.dir/solver_dense.cpp.i

g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solver_dense.dir/solver_dense.cpp.s"
	cd /home/abhishek/g2o/g2o/solvers/dense && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/abhishek/g2o/g2o/solvers/dense/solver_dense.cpp -o CMakeFiles/solver_dense.dir/solver_dense.cpp.s

g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o.requires:
.PHONY : g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o.requires

g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o.provides: g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o.requires
	$(MAKE) -f g2o/solvers/dense/CMakeFiles/solver_dense.dir/build.make g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o.provides.build
.PHONY : g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o.provides

g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o.provides.build: g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o

# Object files for target solver_dense
solver_dense_OBJECTS = \
"CMakeFiles/solver_dense.dir/solver_dense.cpp.o"

# External object files for target solver_dense
solver_dense_EXTERNAL_OBJECTS =

lib/libg2o_solver_dense.so: g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o
lib/libg2o_solver_dense.so: g2o/solvers/dense/CMakeFiles/solver_dense.dir/build.make
lib/libg2o_solver_dense.so: lib/libg2o_core.so
lib/libg2o_solver_dense.so: lib/libg2o_stuff.so
lib/libg2o_solver_dense.so: g2o/solvers/dense/CMakeFiles/solver_dense.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../../lib/libg2o_solver_dense.so"
	cd /home/abhishek/g2o/g2o/solvers/dense && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/solver_dense.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
g2o/solvers/dense/CMakeFiles/solver_dense.dir/build: lib/libg2o_solver_dense.so
.PHONY : g2o/solvers/dense/CMakeFiles/solver_dense.dir/build

g2o/solvers/dense/CMakeFiles/solver_dense.dir/requires: g2o/solvers/dense/CMakeFiles/solver_dense.dir/solver_dense.cpp.o.requires
.PHONY : g2o/solvers/dense/CMakeFiles/solver_dense.dir/requires

g2o/solvers/dense/CMakeFiles/solver_dense.dir/clean:
	cd /home/abhishek/g2o/g2o/solvers/dense && $(CMAKE_COMMAND) -P CMakeFiles/solver_dense.dir/cmake_clean.cmake
.PHONY : g2o/solvers/dense/CMakeFiles/solver_dense.dir/clean

g2o/solvers/dense/CMakeFiles/solver_dense.dir/depend:
	cd /home/abhishek/g2o && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abhishek/g2o /home/abhishek/g2o/g2o/solvers/dense /home/abhishek/g2o /home/abhishek/g2o/g2o/solvers/dense /home/abhishek/g2o/g2o/solvers/dense/CMakeFiles/solver_dense.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : g2o/solvers/dense/CMakeFiles/solver_dense.dir/depend

