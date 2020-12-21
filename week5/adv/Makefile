CC = gcc
CFLAGS = -Wall -g
LDLIBS = -lm
OBJS = adv_regression.o func1.o optimize1.o compare.o
TARGET = optimizer1

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

.PHONY: tmpclean clean
tmpclean:
	rm -f *~
clean: tmpclean
	rm -f $(OBJS) $(TARGET) 
