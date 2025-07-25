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
    ret.vs[1] = y(v1) / denom;
    ret.vs[2] = z(v1) / denom;
    return (ret);
}

t_vec3  vec_smul(t_vec3 v1, t_data factor)
{
    t_vec3  ret;

    ret.vs[0] = x(v1) * factor;
    ret.vs[1] = y(v1) * factor;
    ret.vs[2] = z(v1) * factor;
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

t_data	modulus(t_vec3 vec)
{
    return (sqrt(x(vec) * x(vec)
                 + y(vec) * y(vec)
                 + z(vec) * z(vec)));
}

t_data	theta(t_vec3 a, t_vec3 b)
{
    return (acos((dot(a, b) / (modulus(a) * modulus(b)))));
}

t_vec3	n_unitary(t_vec3 a, t_vec3 b)
{
    t_vec3 out;

    out.vs[0] = y(a) * z(b) - y(b) * z(a);
    out.vs[1] = x(b) * z(a) - x(a) * z(b);
    out.vs[2] = x(a) * y(b) - x(b) * y(a);
    return (out);
}

t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
    t_data tt = theta(a, b);

    return (vec_smul(n_unitary(a, b), modulus(a) * modulus(b) * sin(tt)));
}

void test_cross_product(t_vec3 a, t_vec3 b)
{
    t_vec3 c = cross_product(a, b);
    // t_vec3 c_unit = n_unitary(c, b);

    print_vec3(a);
    print_vec3(b);
    print_vec3(c);
    // print_vec("unitary(a x b)", c_unit);
    printf("Magnitude |a x b|: %.3f\n", modulus(c));
    printf("Dot(a, a x b): %.3f (≈0)\n", dot(a, c));
    printf("Dot(b, a x b): %.3f (≈0)\n", dot(b, c));

    // Verificar antisimetría
    t_vec3 c2 = cross_product(b, a);
    printf("Check a x b = -(b x a)?\n");
    print_vec3(c2);
    printf("a x b + b x a = (%.3f, %.3f, %.3f)\n",
        x(c) + x(c2), y(c) + y(c2), z(c) + z(c2));
}

// int main(void)
// {
//     printf("==== Test cruzado ====\n");
//     t_vec3 a = vec3(1, 2, 3);
//     t_vec3 b = vec3(4, 5, 6);
//     test_cross_product(a, b);

//     return 0;
// }

