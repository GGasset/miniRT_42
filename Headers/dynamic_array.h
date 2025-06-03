/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:10:38 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/06/03 03:54:36 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_darray
{
	void		*darray;
	size_t		len;
	size_t		full_idx;
	size_t		size;
}				t_darray;

t_darray		*alloc_darray(size_t len, size_t size);
int				resize_darray(t_darray **darray);
void			free_darray(t_darray *darray, int type);
int				append_darray(t_darray **darray, void *element);
unsigned char	*r_darray(t_darray *darray, int idx);
char			*dstr(t_darray *darr);
char			**dpstr(t_darray *darr);

#endif