# Compiler settings
CXX = g++
CXXFLAGS = -Iinclude -std=c++17 -Wall

# Sources and target
SOURCES = src/*.cpp
TARGET = output.exe

# Default rule: build and run
all: $(TARGET)
	@echo running HMS software...
	@$(TARGET)

# Link and compile
$(TARGET): $(SOURCES)
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Clean rule
clean:
	@cmd /C "if exist $(TARGET) del $(TARGET)"
