CXX := g++
CXXFLAGS := -I/usr/include/SDL2 -g
LDFLAGS := -L/usr/lib/x86_64-linux-gnu
LIBS := -lSDL2

TARGET := GameController

OBJECTS := main.o game_controller.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBS)
	chmod +x $@

main.o: main.cpp game_controller.h
	$(CXX) -c -o $@ main.cpp $(CXXFLAGS)

game_controller.o: game_controller.cpp game_controller.h
	$(CXX) -c -o $@ game_controller.cpp $(CXXFLAGS)

clean:
	rm -f $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)