# List of source files
SOURCES := main.cpp base.cpp master.cpp assets/*.cpp

# Name of the output executable
TARGET := SimpleShooter

# Compiler flags
CXXFLAGS := -std=c++11
LIBS := -Llib -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2 

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SOURCES)
	g++ $(SOURCES) $(CXXFLAGS) $(LIBS) -o $(TARGET)

# Rule to clean compiled files and the executable
clean:
	del $(TARGET) $(wildcard *.o) $(wildcard assets/*.o)
