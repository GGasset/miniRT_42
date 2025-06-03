/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:09:28 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/21 20:28:58 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dictionary.h"
#include <stdio.h>

char	*dict_get(t_dictionary *dic, char *key)
{
	unsigned int	index;
	unsigned int	counter;

	if (key == NULL)
		return (NULL);
	index = dict_hash(key) % dic->capacity;
	counter = 0;
	while (counter < dic->capacity - 1)
	{
		if (dic->entries[index] && !ft_strcmp(dic->entries[index]->key, key))
			return (dic->entries[index]->value);
		index++;
		if (index == dic->capacity - 1)
			index = 0;
		counter++;
	}
	return (NULL);
}

void	dict_delete(t_dictionary *dic)
{
	unsigned int	i;

	i = 0;
	while (i < dic->capacity)
	{
		if (dic->entries[i] != NULL)
		{
			free(dic->entries[i]->key);
			free(dic->entries[i]->value);
			free(dic->entries[i]);
		}
		i++;
	}
	free(dic->entries);
	free(dic);
}

t_dic_entry	*dict_create_entry(char *key, char *value)
{
	t_dic_entry	*ret_entry;

	ret_entry = ft_calloc(1, sizeof(t_dic_entry));
	if (!ret_entry)
		return (NULL);
	ret_entry->key = key;
	ret_entry->value = value;
	return (ret_entry);
}

void	dict_delete_key(t_dictionary *dict, char *key)
{
	unsigned int	index;
	unsigned int	counter;

	if (key == NULL)
		write(1, "", 0);
	index = dict_hash(key) % dict->capacity;
	counter = 0;
	while (counter < dict->capacity - 1)
	{
		if (dict->entries[index] && !ft_strcmp(dict->entries[index]->key, key))
		{
			if (dict->entries[index]->key)
				free(dict->entries[index]->key);
			if (dict->entries[index]->value)
				free(dict->entries[index]->value);
			free(dict->entries[index]);
			dict->entries[index] = NULL;
			return ;
		}
		index++;
		if (index == dict->capacity - 1)
			index = 0;
		counter++;
	}
}

char	**dict_get_keys(t_dictionary *dict)
{
	unsigned int	counter;
	char			**ret;
	char			**tmp;

	ret = malloc((dict->capacity + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	tmp = ret;
	counter = 0;
	while (counter < dict->capacity - 1)
	{
		if (dict->entries[counter])
		{
			*tmp = ft_strdup(dict->entries[counter]->key);
			tmp++;
		}
		counter++;
	}
	*tmp = NULL;
	return (ret);
}
