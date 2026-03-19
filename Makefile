# Build for Linux
VERSION = 0.3
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -L./libs -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wl,-rpath,'$$ORIGIN/libs'

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

dist: $(TARGET) $(WIN_TARGET)
	@echo "Publishing Linux build to bin/ and Windows build to winbin/"
	# Create the full directory structure 
	mkdir -p bin/libs winbin
	
	# Copy Linux binary and all assets 
	cp $(TARGET) fireworks_settings.ini glow.vs glow.fs brightpass.fs blur.fs LICENSE firework.wav imgui.ini editundo.ttf trails.ini README.md bin/
	
	# Copy the specific Raylib shared library into the new libs folder 
	cp /usr/lib64/libraylib.so.550 bin/libs/
	
	# Copy Windows binary and all assets 
	cp $(WIN_TARGET) fireworks_settings.ini glow.vs glow.fs brightpass.fs blur.fs LICENSE firework.wav imgui.ini editundo.ttf trails.ini README.md winbin/

zip: dist
	@echo "Creating ZIP archives for version $(VERSION)..."
	# Zip the Linux build (renaming the folder inside the zip for clarity)
	zip -r FWorksFun_Linux_$(VERSION).zip bin/
	# Zip the Windows build
	zip -r FWorksFun_Windows_$(VERSION).zip winbin/
	@echo "Done! Created FWorksFun_Linux_$(VERSION).zip and FWorksFun_Windows_$(VERSION).zip"

help:
	@echo "Available targets:"
	@echo "  all      - Build Linux version (default)"
	@echo "  windows  - Cross-compile for Windows"
	@echo "  clean    - Remove all built files"
	@echo "  run      - Build and run Linux version"
	@echo "  dist     - Package builds for distribution"
	@echo "  help     - Show this help"

.PHONY: all windows clean run help dist zip