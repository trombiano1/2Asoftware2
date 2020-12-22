CC = gcc
CFLAGS = -Wall -g
LDLIBS = -lm
OBJS = mtfuji.o func1.o optimize1.o compare.o
TARGET = mtfuji

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

.PHONY: tmpclean clean
tmpclean:
	rm -f *~
clean: tmpclean
	rm -f $(OBJS) $(TARGET) 
