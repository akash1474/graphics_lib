CXXFLAGS=-O3 -s -std=c++17 -I./include -I./lib/include -L./bin -lglfw3 -lopengl32 -lglew32
SRC_DIR:=$(wildcard ./src/*.cpp)
SRC_OBJ:=$(patsubst %.cpp,%.o,$(SRC_DIR))
SRC_DEP:=$(patsubst %.cpp,%.d,$(SRC_DIR))

# LIB_DIR:=$(wildcard ./lib/*.cpp)
# LIB_OBJ:=$(patsubst %.cpp,%.o,$(LIB_DIR))

all:$(SRC_OBJ)
	@echo main.exe
	@g++ $(SRC_OBJ) $(CXXFLAGS) -o ./bin/main 
	@./bin/main.exe

%.o:%.cpp
	@echo $<
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
clean:
	@rm -r ./src/*.o 
	@rm -r ./bin/*.exe

build:$(SRC_OBJ)
	@echo Building...
# 	@echo 

init_cmake:
	cmake -H. -GNinja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug -Bbuild/Debug

run:
	./bin/main.exe
