CFLAGS=-g
CC=gcc

TARGET=ltxlog

SRCS=ltxlog.c sumlog.c version.c
OBJS=$(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(SRCS) -o $(TARGET)

clean:
	rm -f *.o $(TARGET)

