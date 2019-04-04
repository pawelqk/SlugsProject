FLAGS = -std=c++17 -c -Wall -Werror
DEPS = -lncurses -lpthread
OBJ = bin/src/Drawer.o bin/src/Leaf.o bin/src/Slug.o bin/src/SlugColony.o bin/src/LeafField.o
MAIN_OBJ = bin/src/main.o
TEST_OBJ = bin/test/utMain.o bin/test/SlugTest.o

.PHONY:
	clean
	ut

all: directory $(OBJ) $(MAIN_OBJ)
	g++ -o bin/Slugs $(MAIN_OBJ) $(OBJ) $(DEPS)

ut: directory $(OBJ) $(TEST_OBJ)
	g++ -o bin/TestSlugs $(TEST_OBJ) $(OBJ) $(DEPS) -lgtest

bin/src/%.o: src/%.cpp
	g++ -g $(FLAGS) -o $@ $^

bin/test/%.o: test/%.cpp
	g++ -o $@ $^ $(FLAGS)

directory:
	mkdir -p bin/src bin/test

clean:
	rm bin/src/*.o
	rm bin/test/*.o
