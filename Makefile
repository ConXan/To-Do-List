CC := gcc

# Dir
SRCDIR := src
INCDIR := include
OBJDIR := obj

# Files
SRCS := $(wildcard $(SRCDIR)/*.c)
HEADERS := $(wildcard $(INCDIR)/*.h)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Flags
CFLAGS := -I$(INCDIR)

# exe
TARGET := task

# Main target
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

# obj
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
