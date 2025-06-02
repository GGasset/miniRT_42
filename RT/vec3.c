#include "../Headers/RT_headers/vec3.h"
#include "../libft/libft.h"

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
