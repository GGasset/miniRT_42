#include "../Headers/RT_headers/vec3.h"
#include "../libft/libft.h"
#include "stdio.h"

t_vec3	vec3(t_data x, t_data y, t_data z)
{
    t_vec3  vec;

    vec.vs[0] = x;
    vec.vs[1] = y;
    vec.vs[2] = z;
    return (vec);
}

void    asign_vec3(t_vec3 *vec, t_data x, t_data y, t_data z)
{
    vec->vs[0] = x;
    vec->vs[1] = y;
    vec->vs[2] = z;
}

void	copy_vec3(t_vec3 *dest, t_vec3 src)
{
    dest->vs[0] = x(src);
    dest->vs[1] = y(src);
    dest->vs[2] = z(src);
}

t_data  x(t_vec3 vec)
{
    return (vec.vs[0]);
}

t_data  y(t_vec3 vec)
{
    return (vec.vs[1]);
}

t_data  z(t_vec3 vec)
{
    return (vec.vs[2]);
}

void    print_vec3(t_vec3 vec)
{
    printf("(%lf, %lf, %lf)\n", x(vec), y(vec), z(vec));
}

t_vec3  vec_sum(t_vec3 v1, t_vec3 v2)
{
    t_vec3  ret;

    ret.vs[0] = x(v1) + x(v2);
    ret.vs[1] = y(v1) + y(v2);
    ret.vs[2] = z(v1) + z(v2);
    return (ret);
}

t_vec3  vec_sust(t_vec3 v1, t_vec3 v2)
{
    t_vec3  ret;

    ret.vs[0] = x(v1) - x(v2);
    ret.vs[1] = y(v1) - y(v2);
    ret.vs[2] = z(v1) - z(v2);
    return (ret);
}

t_vec3  vec_sdiv(t_vec3 v1, t_data denom)
{
    t_vec3  ret;

    ret.vs[0] = x(v1) / denom;
    ret.vs[1] = y(v1) - denom;
    ret.vs[2] = z(v1) - denom;
    return (ret);
}

t_vec3  vec_smul(t_vec3 v1, t_data factor)
{
    t_vec3  ret;

    ret.vs[0] = x(v1) / factor;
    ret.vs[1] = y(v1) - factor;
    ret.vs[2] = z(v1) - factor;
    return (ret);
}

t_data  dot(t_vec3 v1, t_vec3 v2)
{
    return ((x(v1) * x(v2)) + (y(v1) * y(v2)) + (z(v1) * z(v2)));
}

t_vec3  norm(t_vec3 v)
{
    double  module;

    module = pow(x(v), 2) + pow(y(v), 2) + pow(z(v), 2);
    return (vec_sdiv(v, module));
}
