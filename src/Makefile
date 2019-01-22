TARGET = main.exe
CC = $(shell if command -v clang++ >/dev/null 2>&1; then echo "clang++"; else echo "g++"; fi)
CFLAGS = -O3 -g -std=c++14
C_SRCS := $(wildcard *.cpp)
C_OBJS := $(C_SRCS:.cpp=.o)
HDRS = $(wildcard *.hpp)

.PHONY: debug run perf clean

$(TARGET): $(C_OBJS)
	$(CC) $(CFLAGS) -DNDEBUG -o $(TARGET) $(C_OBJS)

debug:
	$(CC) $(CFLAGS) -DDEBUG -o $(TARGET) $(C_SRCS)

$(C_OBJS): $(HDRS)
	$(CC) $(CFLAGS) -DNDEBUG -c -o $@ $(@:.o=.cpp)

run: $(TARGET)
	./$(TARGET)

perf: $(TARGET)
	perf stat ./$(TARGET)

clean:
	-rm -f *.stackdump *.exe *.o *.swp
