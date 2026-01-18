
# Locations of raylib.h and libraylib.a/libraylib.so
# NOTE: Those variables are only used for PLATFORM_OS: LINUX, BSD
RAYLIB_INCLUDE_PATH   ?= /usr/local/include
RAYLIB_LIB_PATH       ?= /usr/local/lib


hello.out: hello.c
	gcc hello.c -lraylib -lGL -lm -lpthread -ldl -lrt -L$(RAYLIB_LIB_PATH) -I$(RAYLIB_INCLUDE_PATH) -o hello.out

clean:
	rm hello.out

.PHONY: clean
