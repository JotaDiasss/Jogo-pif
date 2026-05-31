CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

ifeq ($(OS),Windows_NT)
    EXEEXT = .exe
    LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -luser32
    RM = del /Q /F
    RM_OBJS = $(subst /,\\,$(OBJS))
    RM_TARGET = $(subst /,\\,$(TARGET))
    RUN_CMD = .\\$(TARGET)
else
    EXEEXT =
    LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11
    RM = rm -f
    RM_OBJS = $(OBJS)
    RM_TARGET = $(TARGET)
    RUN_CMD = ./$(TARGET)
endif

SRCS = src/main.c src/lista.c src/matriz.c src/raylib_utils.c src/render.c src/score_manager.c
OBJS = $(SRCS:.c=.o)
TARGET = candy_crush$(EXEEXT)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(RUN_CMD)

rebuild: clean all
	$(RUN_CMD)

clean:
	-$(RM) $(RM_OBJS) $(RM_TARGET)
