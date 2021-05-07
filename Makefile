CFLAGS = -std=c99 -Wall -pedantic -Werror -I..\SDL2-2.0.14\i686-w64-mingw32\include\SDL2 
LFLAGS = -lmingw32 -lSDL2main -lSDL2 -L..\SDL2-2.0.14\i686-w64-mingw32\lib
SRCS = $(wildcard src/*.h src/*.c)
OBJS = $(SRCS:c=o)
TARGET = sdl_app
CC = gcc

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS) $(LFLAGS)

clean:
	del $(TARGET).exe src\*.o
