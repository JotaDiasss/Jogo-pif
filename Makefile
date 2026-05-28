CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -luser32

SRCS = src/main.c src/lista.c src/matriz.c
OBJS = $(SRCS:.c=.o)
TARGET = candy_crush.exe

ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    RM_OBJS = $(subst /,\,$(OBJS))
    RM_TARGET = $(subst /,\,$(TARGET))
else
    RM = rm -f
    RM_OBJS = $(OBJS)
    RM_TARGET = $(TARGET)
endif

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	.\$(TARGET)

clean:
	-$(RM) $(RM_OBJS) $(RM_TARGET)
