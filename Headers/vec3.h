/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 10:20:03 by ggasset-          #+#    #+#             */
/*   Updated: 2025-05-20 10:20:03 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef double	t_data;

typedef struct t_vec3
{
	t_data	vs[3];
}		t_vec3;

typedef t_vec3	t_point3;
typedef t_vec3	t_color;

typedef struct t_ray
{
	t_point3	orig;
	t_vec3		direct;
};

#endif
