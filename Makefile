########################################################################
# Team members     : Jayden Joyce
#					 Derrick Phung
# Student Numbers  : s3543824 
# 					 s3546900
# Student Emails   : s3543824@student.rmit.edu.au 
#					 s3546900@student.rmit.edu.au
########################################################################

# Compiler
CXX       = g++
CXXFLAGS  = -Wall -pedantic -std=c++14

# Project name
PROGRAM   = draught

# Directories
MDLDIR    = model
VIEWDIR   = ncview
CTRLDIR   = nc_controller
BUILDDIR  = build

# Utility
RM        = rm -f
CXXENABLE = source /opt/rh/devtoolset-6/enable

# Files and folders
VPATH     = model:nc_controller:ncview
SOURCES   = $(wildcard *.cpp) $(wildcard */*.cpp)
HEADERS   = $(wildcard *.h) $(wildcard */*.h)
OBJECTS   = build/main_noncurses.o build/model.o build/command.o build/controller.o build/add_player_window.o build/game_window.o build/main_menu.o build/menu.o build/player_selection_window.o build/ui.o build/window.o

# Targets
all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(PROGRAM)
	
$(BUILDDIR)/%.o: %.cpp $(HEADERS)
	@echo "Compiling..."
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
run:
	./$(PROGRAM)

clean:
	@echo "Cleaning..."
	$(RM) $(BUILDDIR)/*.o $(PROGRAM)
	
source:
	@echo "Copy and run the following command:"
	@echo $(CXXENABLE)

archive:
	@echo "Ziping files..."
	zip $(USER) $(SOURCES) $(HEADERS) Makefile
	
help:
	@echo "Targets:"
	@echo "make(all) - builds and compiles program"
	@echo "run       - runs the program"
	@echo "clean     - deletes object files and executable"
	@echo "source    - prints line for enabling c++"
	@echo "archive   - zips relevant files"