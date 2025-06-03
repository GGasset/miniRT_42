/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:47:44 by ggasset-          #+#    #+#             */
/*   Updated: 2025/01/30 15:20:03 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_expand_argv(int *argc, char **argv, char *separator, int split_by)
{
	char	*tmp;

	tmp = ft_argv_join(argv, separator, FALSE);
	if (!tmp)
		return (0);
	argv = ft_split(tmp, (char)split_by);
	*argc = ft_get_split_count(argv);
	free(tmp);
	return (argv);
}
