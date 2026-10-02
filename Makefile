CC = gcc

CFLAGS = -Wall -pthread

SRC = src/main.c \
      src/task_queue.c \
      src/thread_pool.c \
      src/task_manager.c

TARGET = taskforge

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
