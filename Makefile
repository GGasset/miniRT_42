
STATIC_FILES=./libft/libft.a
O_FILES=
INCLUDE=-I ./Headers/ -I ./libft/

CC_flags=-c -Wall -Wextra -Werror ${INCLUDE}
CC_LINKING_FLAGS=
CC_SHARED_FLAGS=-fsanitize=address,undefined

NAME=MINI_RT

all: ${NAME}

${NAME}: libft ${O_FILES}
	cc -o ${NAME} ${CC_LINKING_FLAGS} ${CC_SHARED_FLAGS} ${O_FILES} ${STATIC_FILES}

%.o: %.c
	cc $? ${CC_flags} ${CC_SHARED_FLAGS} -o $%

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