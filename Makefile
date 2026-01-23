# Default Linux build
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# For building for Windows
WIN_CXX = x86_64-w64-mingw32-g++
WIN_CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -static
WIN_LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++

TARGET = FWorksFun
WIN_TARGET = FWorksFun.exe
SOURCE = main.cpp

# Default target (Linux)
all: $(TARGET)

# Linux build
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

# Build for Win from Linux
windows: $(WIN_TARGET)

$(WIN_TARGET): $(SOURCE)
	$(WIN_CXX) $(WIN_CXXFLAGS) -o $(WIN_TARGET) $(SOURCE) $(WIN_LDFLAGS)

clean:
	rm -f $(TARGET) $(WIN_TARGET)

run: $(TARGET)
	./$(TARGET)

help:
	@echo "Available targets:"
	@echo "  all      - Build Linux version (default)"
	@echo "  windows  - Cross-compile for Windows"
	@echo "  clean    - Remove all built files"
	@echo "  run      - Build and run Linux version"
	@echo "  help     - Show this help"

.PHONY: all windows clean run help