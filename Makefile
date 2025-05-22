
MINILIBX_FUNCS_O_FILES=render.o hooks.o
RT_O_FILES=

O_FILES = $(addprefix ./minilibx_funcs/, ${MINILIBX_FUNCS_O_FILES})
O_FILES += $(addprefix ./RT/, ${RT_O_FILES})

STATIC_FILES=./libft/libft.a

INCLUDE=-I ./Headers/ I ./Headers/RT_headers/ -I ./libft/ -I ./minilibx-linux/

CC_SHARED_FLAGS=-fsanitize=address,undefined
CC_flags=${CC_SHARED_FLAGS} -c -Wall -Wextra -Werror ${INCLUDE}
CC_LINKING_FLAGS=${CC_SHARED_FLAGS}

NAME=miniRT

all: ${NAME}

${NAME}: libft ${O_FILES}
	cc -o ${NAME} ${CC_LINKING_FLAGS} ${O_FILES} ${STATIC_FILES}

%.o: %.c
	cc $? ${CC_flags} -o $%

re: fclean all

fclean: clean
	rm ${MINI_RT}

clean: libft_fclean
	rm ${O_FILES}

libft:
	make --directory=./libft/ all

libft_fclean:
	make --directory=./libft/ fclean

.PHONY: all ${NAME} re fclean clean libft libft_fclean