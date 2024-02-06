CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Libraries
LIBS = -lglfw -lGL -lGLEW

# Source files
SRCS = $(wildcard src/*.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output
OUT = out

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OUT) $(OBJS)
