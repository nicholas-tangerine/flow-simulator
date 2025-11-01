CC      := gcc
CFLAGS  := -Wconversion -Wpedantic -Wall -Wextra -g -O0 -I "../include/"
LDFLAGS := -ltiff -lm

SRC     := main.c vectors.c debug_utils.c particle.c math_helper.c noise.c vortex.c particle_sys.c particle_sys_render.c tiff_wrapper.c
OBJ     := $(SRC:.c=.o)
TARGET  := main

MISC	:= *.ppm *.txt *.tif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(MISC)
