CXX := g++
CXXFLAGS := -I/usr/include/SDL2
LDFLAGS := -L/usr/lib/x86_64-linux-gnu
LIBS := -lSDL2

myprogram: controller.o
	$(CXX) -o $@ controller.o $(LDFLAGS) $(LIBS)
	chmod +x $@

controller.o: controller.cpp
	$(CXX) -c -o $@ controller.cpp $(CXXFLAGS)

clean:
	rm -f myprogram controller.o

run: myprogram
	./myprogram
