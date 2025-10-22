/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_color_interval.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:11:19 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 17:12:00 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_color	get_color(t_vec3 in)
{
	t_color	out;

	out = 0xFF << 24;
	out += (int)in.vs[0] << 16;
	out += (int)in.vs[1] << 8;
	out += (int)in.vs[2];
	return (out);
}

t_vec3	get_rgb(t_color in)
{
	t_vec3	out;

	out.vs[0] = in >> 16 & 255;
	out.vs[1] = in >> 8 & 255;
	out.vs[2] = in & 255;
	return (out);
}

t_interval	interval(t_data min, t_data max)
{
	t_interval	out;

	out.min = min;
	out.max = max;
	return (out);
}
