TARGET = main.exe
CC = $(shell if command -v clang++ >/dev/null 2>&1; then echo "clang++"; else echo "g++"; fi)
CFLAGS = -O3 -g -std=c++14
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
HDRS = $(wildcard *.hpp)

.PHONY: debug run perf clean

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -DNDEBUG -o $(TARGET) $(OBJS)

debug:
	$(CC) $(CFLAGS) -DDEBUG -o $(TARGET) $(SRCS)

$(OBJS): $(HDRS) $(SRCS)
	$(CC) $(CFLAGS) -DNDEBUG -c -o $@ $(@:.o=.cpp)

run: $(TARGET)
	./$(TARGET)

perf: $(TARGET)
	perf stat ./$(TARGET)

clean:
	-rm -f *.stackdump *.exe *.o *.swp
