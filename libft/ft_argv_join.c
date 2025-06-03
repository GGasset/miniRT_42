/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:24:47 by ggasset-          #+#    #+#             */
/*   Updated: 2025/01/30 13:31:59 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_argv_join(char **argv, char *separator, int free_argv)
{
	char	*out;
	size_t	i;

	out = ft_strdup(argv[0]);
	i = 1;
	while (argv[i])
	{
		out = ft_strjoin_free(out, separator, TRUE, FALSE);
		out = ft_strjoin_free(out, ft_strdup(argv[i]), TRUE, TRUE);
		i++;
	}
	if (free_argv)
		ft_free_splitted(argv);
	return (out);
}
