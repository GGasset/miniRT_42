/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:52:34 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 17:53:32 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dictionary.h"

void	insert_or_update_entry(t_dictionary *dic, t_dic_entry *entry,
		unsigned int index)
{
	while (dic->entries[index] != NULL)
	{
		if (!ft_strcmp(dic->entries[index]->key, entry->key))
		{
			free(dic->entries[index]->value);
			dic->entries[index]->value = entry->value;
			free(entry->key);
			free(entry);
			return ;
		}
		index++;
		if (index == dic->capacity - 1)
			index = 0;
	}
	dic->entries[index] = entry;
	dic->n_elements++;
}

void	dict_insert(t_dictionary **dic_p, t_dic_entry *entry)
{
	unsigned int	hash_entry;
	unsigned int	index;
	t_dictionary	*dic;

	if (entry->key == NULL)
		return ;
	dic = *dic_p;
	if (dic->n_elements > (dic->capacity / 2))
	{
		if (!dict_expand(dic_p))
			return (dict_delete(dic));
		dic = *dic_p;
	}
	hash_entry = dict_hash(entry->key);
	index = hash_entry % dic->capacity;
	insert_or_update_entry(dic, entry, index);
	*dic_p = dic;
}
