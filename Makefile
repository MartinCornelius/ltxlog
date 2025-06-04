CFLAGS=-g
CC=gcc

TARGET=ltxlog

SRCS=ltxlog.c file-utils.c sumlog.c version.c utils.c
OBJS=$(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(SRCS) -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
