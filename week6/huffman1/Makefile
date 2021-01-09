CC = gcc
CFLAGS = -Wall -I./include
OBJS = src/main.o src/encode.o
TARGET = bin/huffman1

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

.PHONY: tmpclean clean

tmpclean:
	find . -name *~ -exec rm -vf {} \;
clean: tmpclean
	rm -f $(OBJS) $(TARGET)
