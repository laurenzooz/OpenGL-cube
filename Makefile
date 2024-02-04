CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Libraries
LIBS = -lglfw -lGL -lGLEW

SRC = src/Main.cpp

# output
OUT = out

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)


clean:
	rm -f $(OUT)