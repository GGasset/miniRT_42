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

t_data	rand_fract(int include_negative)
{
	t_data	out;

	out = xorshift32() % (int)1E5;
	out = out / 1E5;
	if (include_negative)
		out = out * 2 - 1;
	return (out);
}

t_vec3	rand_vec3(int range, t_data out_divider)
{
	t_vec3	rotation;

	range += range % 2 == 0;
	rotation.vs[0] = (abs(xorshift32()) % range - (range - range % 2) / 2);
	rotation.vs[1] = (abs(xorshift32()) % range - (range - range % 2) / 2);
	rotation.vs[2] = (abs(xorshift32()) % range - (range - range % 2) / 2);
	rotation = vec_sdiv(rotation, out_divider);
	return (rotation);
}

t_vec3	small_direction_shift(t_rotation to_rotate)
{
	t_vec3	rotation;
	t_vec3	out;
	int		range;

	range = 500;
	rotation = rand_vec3(range, 1E5);
	out = norm(rotate(to_rotate, rotation));
	return (out);
}
