CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

RAYLIB_PATH = /home/uservranger/raylib

INCLUDES = -I$(RAYLIB_PATH)/src

LIBS = $(RAYLIB_PATH)/build/raylib/libraylib.a \
       -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = 31-16

SRC = src/main.cpp

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

fclean: clean

re: fclean all