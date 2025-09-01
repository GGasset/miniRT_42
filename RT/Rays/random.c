/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-01 12:36:06 by ggasset-          #+#    #+#             */
/*   Updated: 2025-09-01 12:36:06 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

int	xorshift32()
{
	static int	x;

	if (!x)
		x = 13;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return (x);
}

t_vec3	small_direction_shift(t_rotation to_rotate)
{
	t_vec3	rotation;
	t_vec3	out;

	rotation.vs[0] = (abs(xorshift32()) % 7 - 3);
	rotation.vs[1] = (abs(xorshift32()) % 7 - 3);
	rotation.vs[2] = (abs(xorshift32()) % 7 - 3);
	rotation = vec_sdiv(rotation, 1);
	out = norm(rotate(to_rotate, rotation));
	return (out);
}
