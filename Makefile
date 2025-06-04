CFLAGS=-g -Wall -Wextra
CC=gcc

TARGET=ltxlog

SRCS=ltxlog.c file-utils.c sumlog.c version.c utils.c
OBJS=$(SRCS:.c=.o)

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(SRCS) -o $(TARGET)

clean:
	rm -f *.o $(TARGET)

install: $(TARGET)
	install -d $(BINDIR)
	install -m 0755 $(TARGET) $(BINDIR)
	@echo "installed $(TARGET) to $(BINDIR)"

uninstall:
	rm -f $(BINDIR)/$(TARGET)
	@echo "uninstalled $(TARGET) from $(BINDIR)"
