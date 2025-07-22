
MINILIBX_FUNCS_O_FILES=render.o hooks.o dealloc.o

RT_RAYS_O_FILES=hit.o
RT_O_FILES = $(addprefix /Rays/, ${RT_RAYS_O_FILES})
# RT_O_FILES += scene_creation.o vec3.o

O_FILES = $(addprefix ./minilibx-funcs/, ${MINILIBX_FUNCS_O_FILES})
O_FILES += $(addprefix ./RT/, ${RT_O_FILES})

O_FILES += main.o

LIBFT_DIR=./libft
LIBFT_NAME=libft.a

MINILIBX_DIR=./minilibx-linux
MINILIBX_NAME=libmlx_Linux.a

STATIC_FILES=${LIBFT_DIR}/${LIBFT_NAME} ${MINILIBX_DIR}/${MINILIBX_NAME}

INCLUDE=-I/usr/include -I ./Headers/ -I ./Headers/RT_headers/ -I ${LIBFT_DIR}/ -I ${MINILIBX_DIR} -lX11 -lm

# CC_SHARED_FLAGS=-fsanitize=address,undefined
CC_flags=${CC_SHARED_FLAGS} -c -Wall -Wextra -Werror ${INCLUDE}
CC_LINKING_FLAGS=${CC_SHARED_FLAGS}
MINILIBX_LINKING_FLAGS=-L/usr/lib -lXext -lX11 -lm -lz 

NAME=miniRT

all: ${NAME}

${NAME}: minilib-all libft ${O_FILES}
	gcc -o ${NAME} ${CC_LINKING_FLAGS} ${MINILIBX_LINKING_FLAGS} ${O_FILES} ${STATIC_FILES}

%.o : %.c
	gcc $? ${CC_flags} -o $@

re: fclean all

fclean: clean
	rm -f ${MINI_RT}

clean: minilib-clean libft_fclean
	rm -f ${O_FILES}

libft:
	make --directory=./libft/ all

libft_fclean:
	make --directory=./libft/ fclean

# MINILIB

minilib-all:
	make --directory=./minilibx-linux/ all

minilib-clean:
	make --directory=./minilibx-linux/ clean

.PHONY: all ${NAME} re fclean clean libft libft_fclean minilib-all minilib-clean