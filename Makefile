# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Target executable name
TARGET = lab10

# Source file
SRC = BrettFreisberg_lab10.cpp

# Default rule
all: $(TARGET)

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean rule (removes executable)
clean:
	rm -f $(TARGET).exe $(TARGET)