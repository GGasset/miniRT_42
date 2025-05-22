/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:06:08 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/25 16:28:54 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

#ifdef TEST
/*int main()
{
}*/
/*
int	main(int argc, char *argv[])
{
	printf("Main needs to be commented out!!!!\n");
	printf("Bugs:\nNo known bugs.\n\n");
	if (argc < 2 && argc > 4) return 1;
	if (!ft_strncmp(argv[1], "isalpha", ft_strlen(argv[1])))
	{
		printf("%i\n", ft_isalpha(argv[2][0]));
	}
	if (!ft_strncmp(argv[1], "isdigit", ft_strlen(argv[1])))
	{
		printf("%i\n", ft_isdigit(argv[2][0]));
	}
	if (!ft_strncmp(argv[1], "isalnum", ft_strlen(argv[1])))
	{
		printf("%i\n", ft_isalnum(argv[2][0]));
	}
	if (!ft_strncmp(argv[1], "isascii", ft_strlen(argv[1])))
	{
		printf("%i\n", ft_isascii(ft_atoi(argv[2])));
	}
	if (!ft_strncmp(argv[1], "isprint", ft_strlen(argv[1])))
	{
		printf("%i\n", ft_isprint(ft_atoi(argv[2])));
		
	}
	if (!ft_strncmp(argv[1], "strlen", ft_strlen(argv[1])))
	{
		printf("%i\n", (int)ft_strlen(argv[2]));
		
	}
	if (!ft_strncmp(argv[1], "memset", ft_strlen(argv[1])))
	{
		char out[5];
		write(1, out, 5);
		printf("\n");
		ft_memset(out, atoi(argv[2]), 5);
		write(1, out, 5);
		printf("\n");
	}
	if (!ft_strncmp(argv[1], "bzero", ft_strlen(argv[1])))
	{
		char out[5];
		write(1, out, 5);
		printf(" - Before\n");
		ft_bzero(out, 5);
		write(1, out, 5);
		printf(" - After\n");
	}
	if (!ft_strncmp(argv[1], "memcpy", ft_strlen(argv[1])))
	{
		char *out = malloc(ft_strlen(argv[2]) + 1);
		out[ft_strlen(argv[2])] = 0;
		ft_memcpy(out, argv[2], ft_strlen(argv[2]));
		printf("%s\n", out);
		free(out);
	}
	if (!ft_strncmp(argv[1], "memmove", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "strlcpy", ft_strlen(argv[1])))
	{
		size_t size = ft_strlen(argv[2]);
		char *out = malloc(ft_strlen(argv[2]) + 1);
		ft_strlcpy(out, argv[2], size + 1);
		write(1, out, size);
		free(out);
	}
	if (!ft_strncmp(argv[1], "strlcat", ft_strlen(argv[1])))
	{
		size_t size = ft_strlen(argv[2]) + ft_strlen(argv[3]);
		char *out = malloc(size);
		ft_memcpy(out, argv[2], ft_strlen(argv[2]) + 1);
		ft_strlcat(out, argv[3], size);
		write(1, out, size);
		free(out);
	}
	if (!ft_strncmp(argv[1], "toupper", ft_strlen(argv[1])))
	{
		printf("%c\n", ft_toupper(argv[2][0]));
	}
	if (!ft_strncmp(argv[1], "tolower", ft_strlen(argv[1])))
	{
		printf("%c\n", ft_tolower(argv[2][0]));
	}
	if (!ft_strncmp(argv[1], "strchr", ft_strlen(argv[1])))
	{
printf("%i\n",(int)(((size_t)ft_strchr(argv[2],argv[3][0]))-(size_t)argv[2]));
	}
	if (!ft_strncmp(argv[1], "strrchr", ft_strlen(argv[1])))
	{
printf("%i\n",(int)(((size_t)ft_strrchr(argv[2],argv[3][0]))-(size_t)argv[2]));
	}
	if (!ft_strncmp(argv[1], "strncmp", ft_strlen(argv[1])))
	{
		printf("%i\n", ft_strncmp(argv[2], argv[3], 10000));
	}
	if (!ft_strncmp(argv[1], "memchr", ft_strlen(argv[1])))
	{
printf("%i\n",(int)((size_t)ft_memchr(argv[2],argv[3][0],
		ft_strlen(argv[2]))-(size_t)argv[2]));
	}
	if (!ft_strncmp(argv[1], "memcmp", ft_strlen(argv[1])))
	{
		printf("%i\n", ft_memcmp(argv[2], argv[3], 20000));
	}
	if (!ft_strncmp(argv[1], "strnstr", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "atoi", ft_strlen(argv[1])))
	{
		char *output = ft_itoa(ft_atoi(argv[2]));
		write(1, output, ft_strlen(output));
		free(output);
	}
	if (!ft_strncmp(argv[1], "calloc", ft_strlen(argv[1])))
	{
		char *out = ft_calloc(3, 1);
		out[0] = 'H';
		out[1] = 'i';
		printf("%s\n", out);
		free(out);
	}
	if (!ft_strncmp(argv[1], "strdup", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "substr", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "strjoin", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "strtrim", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "split", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "strmapi", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "striteri", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "putchar_fd", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "putstr_fd", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "putendl_fd", ft_strlen(argv[1])))
	{
		
	}
	if (!ft_strncmp(argv[1], "putnbr_fd", ft_strlen(argv[1])))
	{
		
	}
	return (0);
}*/
#endif
