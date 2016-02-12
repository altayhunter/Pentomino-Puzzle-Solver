TARGET = exact_cover
CC = g++
CFLAGS = -O3 -g -std=c++11
C_SRCS := $(wildcard *.cpp)
C_OBJS := $(C_SRCS:.c=.o)
HDRS = $(wildcard *.h)

.PHONY: debug run edit clean

$(TARGET): $(C_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(C_OBJS)

debug: $(C_OBJS)
	$(CC) $(CFLAGS) -DDEBUG -o $(TARGET) $(C_OBJS)

$(C_OBJS): $(HDRS)

run: $(TARGET)
	./$(TARGET)

edit:
	vim $(C_SRCS)

clean:
	-rm -f *.stackdump *.exe *.o *.swp
