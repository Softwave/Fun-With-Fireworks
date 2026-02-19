# Build for Linux
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Build for Windows (from Linux!)
WIN_CXX = x86_64-w64-mingw32-g++
WIN_CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -static
WIN_LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++

TARGET = FWorksFun
WIN_TARGET = FWorksFun.exe
SOURCE = main.cpp

# All the imgui stuff
IMGUI_SRCS = imgui.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp rlImGui.cpp

# Obj files
OBJS = main.o imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o rlImGui.o
WIN_OBJS = main_win.o imgui_win.o imgui_draw_win.o imgui_tables_win.o imgui_widgets_win.o rlImGui_win.o

# Linux is the default
all: $(TARGET)

# Linux build
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@

# Build for Win from Linux
windows: $(WIN_TARGET)

$(WIN_TARGET): $(WIN_OBJS)
	$(WIN_CXX) $(WIN_CXXFLAGS) -o $(WIN_TARGET) $(WIN_OBJS) $(WIN_LDFLAGS)

%_win.o: %.cpp
	$(WIN_CXX) $(WIN_CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(WIN_TARGET)
	rm -rf bin winbin

run: $(TARGET)
	./$(TARGET)

# Distribution packaging
.PHONY: dist

dist: FWorksFun FWorksFun.exe
	@echo "Publishing Linux build to bin/ and Windows build to winbin/"
	mkdir -p bin winbin
	cp fireworks_settings.ini FWorksFun glow.vs glow.fs LICENSE firework.wav imgui.ini editundo.ttf trails.ini README.md bin/
	cp fireworks_settings.ini FWorksFun.exe glow.vs glow.fs LICENSE firework.wav imgui.ini editundo.ttf trails.ini README.md winbin/

help:
	@echo "Available targets:"
	@echo "  all      - Build Linux version (default)"
	@echo "  windows  - Cross-compile for Windows"
	@echo "  clean    - Remove all built files"
	@echo "  run      - Build and run Linux version"
	@echo "  dist     - Package builds for distribution"
	@echo "  help     - Show this help"

.PHONY: all windows clean run help