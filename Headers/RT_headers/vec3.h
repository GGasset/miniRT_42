/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:20:03 by ggasset-          #+#    #+#             */
/*   Updated: 2025/07/22 18:57:57 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "../../libft/libft.h"
# include <stddef.h>
# include <math.h>

typedef double	t_data;

typedef struct t_vec3
{
	t_data	vs[3];
}		t_vec3;

typedef t_vec3	t_point3;
typedef t_vec3	t_color;
typedef t_vec3	t_rotation;

typedef struct t_ray
{
	t_point3	orig;
	t_vec3		direct;
}		t_ray;
t_ray		ray(t_point3 position, t_rotation direction);

t_ray		bounce_ray(t_ray in, t_rotation surface_normal);
t_point3	ray_at(t_data t);

typedef struct t_interval
{
	t_data	min;
	t_data	max;
}		t_interval;

t_vec3	vec3(t_data x, t_data y, t_data z);
void	asign_vec3(t_vec3 *vec, t_data x, t_data y, t_data z);
void	copy_vec3(t_vec3 *dest, t_vec3 src);
t_data  x(t_vec3 vec);
t_data  y(t_vec3 vec);
t_data  z(t_vec3 vec);
void    print_vec3(t_vec3 vec);
t_vec3	vec_sum(t_vec3 v1, t_vec3 v2);
t_vec3  vec_sust(t_vec3 v1, t_vec3 v2);
t_vec3  vec_sdiv(t_vec3 v1, t_data denom);
t_vec3  vec_smul(t_vec3 v1, t_data factor);
t_data  dot(t_vec3 v1, t_vec3 v2);
t_vec3  norm(t_vec3 v);
t_data	modulus(t_vec3 vec);
t_data	theta(t_vec3 a, t_vec3 b);
t_vec3	n_unitary(t_vec3 a, t_vec3 b);
t_vec3	cross_product(t_vec3 a, t_vec3 b);

#endif
