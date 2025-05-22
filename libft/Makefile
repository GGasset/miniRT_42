# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 15:29:33 by ggasset-          #+#    #+#              #
#    Updated: 2025/05/19 17:58:22 by apaz-pri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

o_files = ft_format.o ft_splitdup.o ft_strcmp.o ft_strchr_i.o ft_realloc.o ft_strfilter.o ft_isspace.o ft_isquotes.o ft_replace.o ft_index_replace.o ft_strdup_free.o ft_expand_argv.o ft_get_split_count.o ft_argv_join.o ft_sqrt.o ft_abs.o ft_set_key.o ft_set_void.o ft_atoi_s.o ft_atof_s.o ft_atof.o ft_atod_s.o ft_atod.o ft_key_value.o ft_atoi.o ft_bzero.o ft_calloc.o ft_free_splitted.o ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o ft_itoa.o ft_lstadd_back_bonus.o ft_lstadd_front_bonus.o ft_lstclear_bonus.o ft_lstdelone_bonus.o ft_lstiter_bonus.o ft_lstlast_bonus.o ft_lstmap_bonus.o ft_lstnew_bonus.o ft_lstsize_bonus.o ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memmove.o ft_memset.o ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o ft_split.o ft_strchr.o ft_strdup.o ft_striteri.o ft_strjoin.o ft_strjoin_free.o ft_strlcat.o ft_strlcpy.o ft_strlen.o ft_strmapi.o ft_strncmp.o ft_strnstr.o ft_strrchr.o ft_strtrim.o ft_substr.o ft_tolower.o ft_toupper.o

bonus_o_files = ft_lstadd_back_bonus.o ft_lstadd_front_bonus.o ft_lstclear_bonus.o ft_lstdelone_bonus.o ft_lstiter_bonus.o ft_lstlast_bonus.o ft_lstmap_bonus.o ft_lstnew_bonus.o ft_lstsize_bonus.o

NAME = libft.a

CC_FLAGS = -g -c -Wall -Wextra -Werror
AR_COMM = ar -rsc ${NAME}

#------------- COLORS -------------

NC=\033[0m
On_UIGreen=\033[4;102m
On_IGreen=\033[0;102m
UGreen=\033[4;32m
IGreen=\033[0;92m
IYellow=\033[0;93m 
UYellow=\033[4;33m

all: ${NAME}

re: fclean all

fclean: clean
	@rm -f ${NAME}

clean:
	@rm -f ${o_files} ${bonus_o_files}

${NAME}: ${o_files} ${bonus_o_files}
	@${AR_COMM} ${o_files} ${bonus_o_files}

%.o : %.c
	@len=$$(printf "%s" "$<" | wc -c); printf "$(IGreen)\rCompiling: $(UGreen)%*s$(NC) 🔨\033[K" "$$len" "$<"
	@cc ${CC_FLAGS} $?

.PHONY: all re fclean clean bonus