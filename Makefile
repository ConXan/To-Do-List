CC = gcc

TARGET = task

SRCS = main.c fun1.c fun2.c

OBJS = $(SRCS:.c=.o) #include all srcs files

DEPS = fun1.h fun2.h task.h

all: $(TARGET)

#Executable files
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

#Object files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

#Clean files
clean:
	rm -f $(OBJS) $(TARGET)
