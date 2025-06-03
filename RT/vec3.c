#include "../Headers/RT_headers/vec3.h"
#include "../libft/libft.h"
#include "stdio.h"

t_vec3	*alloc_vec3(t_data x, t_data y, t_data z)
{
    t_vec3  *vec;

    vec = ft_calloc(1, sizeof(t_vec3));
    if (vec == NULL)
        return (NULL);
    vec->vs[0] = x;
    vec->vs[1] = y;
    vec->vs[2] = z;
    return (vec);
}

t_vec3	*asign_vec3(t_vec3 *vec, t_data x, t_data y, t_data z)
{
    vec->vs[0] = x;
    vec->vs[1] = y;
    vec->vs[2] = z;
    return (vec);
}

void	copy_vec3(t_vec3 *dest, t_vec3 *src)
{
    dest->vs[0] = x(src);
    dest->vs[1] = y(src);
    dest->vs[2] = z(src);
}

void    destroy_vec3(t_vec3 *vec)
{
    free(vec);
}

t_data  x(t_vec3 *vec)
{
    return (vec->vs[0]);
}

t_data  y(t_vec3 *vec)
{
    return (vec->vs[1]);
}

t_data  z(t_vec3 *vec)
{
    return (vec->vs[2]);
}

void    print_vec3(t_vec3 *vec)
{
    printf("(%lf, %lf, %lf)\n", x(vec), y(vec), z(vec));
}

void    vec_sum(t_vec3 *v1, t_vec3 *v2)
{
    v1->vs[0] = x(v1) + x(v2);
    v1->vs[1] = y(v1) + y(v2);
    v1->vs[2] = z(v1) + z(v2);
}