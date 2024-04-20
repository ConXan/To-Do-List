# Compiler
CC := gcc

# Directories
SRCDIR := src
INCDIR := include
OBJDIR := obj

# Files
SRCS := $(wildcard $(SRCDIR)/*.c)
HEADERS := $(wildcard $(INCDIR)/*.h)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Compiler flags
CFLAGS := -I$(INCDIR)

# Target executable
TARGET := task

# Main target
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

# Rule for compiling object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
