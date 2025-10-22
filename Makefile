MINILIBX_FUNCS_C_FILES=render.c hooks.c dealloc.c
C_FILES = $(addprefix ./minilibx-funcs/, ${MINILIBX_FUNCS_C_FILES})

RT_RAYS_C_FILES=hit.c rays.c random.c
RT_C_FILES = $(addprefix Rays/, ${RT_RAYS_C_FILES})
RT_C_FILES += vec3.c sphere.c plane.c cylinder.c camera_render.c ray_color.c
C_FILES += $(addprefix ./RT/, ${RT_C_FILES})

PARSING_C_FILES=checks.c check_line.c fill_scene.c scene_creation.c utils.c
C_FILES += $(addprefix ./Parsing/, ${PARSING_C_FILES})

DATA_STRUCTS_FILES=darray_conversions.c dictionary_utils.c dictionary.c dictionary2.c dynamic_array.c
C_FILES += $(addprefix ./data_structs/, ${DATA_STRUCTS_FILES})

C_FILES += main.c

O_FILES = $(patsubst %.c,%.o, ${C_FILES})

LIBFT_DIR=./libft
LIBFT_NAME=libft.a

MINILIBX_DIR=./minilibx-linux
MINILIBX_NAME=libmlx_Linux.a

STATIC_FILES=${LIBFT_DIR}/${LIBFT_NAME} ${MINILIBX_DIR}/${MINILIBX_NAME}

INCLUDE=-I/usr/include -I ./Headers/ -I ./Headers/RT_headers/ -I ./Parsing/ -I ${LIBFT_DIR}/ -I ${MINILIBX_DIR}

CC_SHARED_FLAGS=-O3 #-fsanitize=address,undefined
CC_flags=${CC_SHARED_FLAGS} -c -Wall -Wextra -g ${INCLUDE} #-Werror
CC_LINKING_FLAGS=${CC_SHARED_FLAGS}
MINILIBX_LINKING_FLAGS=-L/usr/lib -lXext -lX11 -lm -lz 

NAME=miniRT
MAKEFLAGS = --no-print-directory
all: minilib-all libft ${NAME}

${NAME}: ${O_FILES} ${STATIC_FILES}
	cc ${CC_LINKING_FLAGS} -o ${NAME} ${O_FILES} ${STATIC_FILES} ${MINILIBX_LINKING_FLAGS} 

%.o : %.c
	cc $? ${CC_flags} -o $@

re: fclean all

fclean: clean minilib-clean
	rm -f ${NAME}

clean:
	rm -f ${O_FILES}

libft:
	make --directory=./libft/ all

libft_fclean:
	make --directory=./libft/ fclean

debug: clean minilib-all libft ${C_FILES}
	cc -o ${NAME} -g3 -Wall -Wextra ${INCLUDE} ${C_FILES} ${STATIC_FILES} ${MINILIBX_LINKING_FLAGS}

# MINILIB

minilib-all:
	make --directory=./minilibx-linux/ all

minilib-clean:
	make --directory=./minilibx-linux/ clean

.PHONY: all re fclean clean libft libft_fclean minilib-all minilib-clean debug