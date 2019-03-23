FLAGS = -std=c++17 -c -Wall -Werror
DEPS = -lncurses -lpthread
OBJ = bin/Drawer.o bin/Leaf.o bin/Logger.o bin/main.o bin/Slug.o bin/SlugColony.o

.PHONY:
	clean

all: $(OBJ) 
	g++ -o bin/Slugs $^ $(DEPS)

bin/%.o: src/%.cpp
	g++ $(FLAGS) -o $@ $<

clean:
	rm bin/*.o
