TARGET = main.exe
CC = g++
CFLAGS = -O3 -g -std=c++14
C_SRCS := $(wildcard *.cpp)
C_OBJS := $(C_SRCS:.cpp=.o)
HDRS = $(wildcard *.hpp)

.PHONY: debug run perf clean

$(TARGET): $(C_OBJS)
	$(CC) $(CFLAGS) -DNDEBUG -o $(TARGET) $(C_OBJS)

debug: $(C_OBJS)
	$(CC) $(CFLAGS) -DDEBUG -o $(TARGET) $(C_OBJS)

$(C_OBJS): $(HDRS)

run: $(TARGET)
	./$(TARGET)

perf: $(TARGET)
	perf stat ./$(TARGET)

clean:
	-rm -f *.stackdump *.exe *.o *.swp
