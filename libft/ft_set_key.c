/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:10:57 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/09 17:45:03 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	try_set(int *found, char *to_set, void *value, enum e_types t)
{
	int	tmp;

	if (!*found)
		return ;
	tmp = ft_set_void(value, to_set, t);
	*found = !tmp - (tmp != 0);
}

int	ft_set_key(char **argv, char *searched_k, void *value, enum e_types t)
{
	char	*key;
	char	*to_set;
	int		found;
	size_t	i;

	key = 0;
	to_set = 0;
	found = 0;
	i = 0;
	while (argv[i] && !found)
	{
		found = !ft_key_value(argv[i], &key, &to_set, 0);
		found = found && !ft_strncmp(key, searched_k, -1);
		try_set(&found, to_set, value, t);
		if (key)
			(free(key), key = 0);
		if (to_set && !(t == pntr && found == 1))
			(free(to_set), to_set = 0);
		i++;
	}
	return (found);
}
