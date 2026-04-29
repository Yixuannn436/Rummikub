# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic-errors

# Define the target executable name
TARGET = rummikub

# List all source (.cpp) files exactly as they appear in the directory
SRCS = main.cpp \
       ai.cpp \
       board.cpp \
       deck.cpp \
       game.cpp \
       player.cpp \
       storage.cpp \
       ui.cpp \
       validator.cpp

# Automatically generate object (.o) file names from source files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the entire project
all: $(TARGET)

# Rule to link the object files and create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile individual .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up build artifacts (executable and object files)
clean:
	rm -f $(TARGET) $(OBJS)

# Rule to compile and run the game directly
run: $(TARGET)
	./$(TARGET)
