#include "../Headers/RT_headers/vec3.h"
#include "../libft/libft.h"
#include "stdio.h"
#include "vec3.h"

t_color	get_color(t_vec3 in)
{
	t_color	out;

	out = 0xFF << 24;
	out += (int)in.vs[2] << 16;
	out += (int)in.vs[1] << 8;
	out += (int)in.vs[0];
	return (out);
}

t_vec3	get_rgb(t_color in)
{
	t_vec3	out;

	out.vs[0] = in & 255;
	out.vs[1] = in >> 8 & 255;
	out.vs[2] = in >> 16 & 255;
	return (out);
}

t_interval interval(t_data min, t_data max)
{
	t_interval	out;

	out.min = min;
	out.max = max;
	return (out);
}

t_vec3 vec3(t_data x, t_data y, t_data z)
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

t_vec3 element_mult(t_vec3 v1, t_vec3 v2)
{
	t_vec3	out;

	out = vec3(v1.vs[0] * v2.vs[0], v1.vs[1] * v2.vs[1], v1.vs[2] * v2.vs[2]);
	return (out);
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

    module = modulus(v);
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

t_data	vec_angle(t_vec3 a, t_vec3 b)
{
	t_vec3	tmp;
	t_data	out;

	a = norm(a);
	b = norm(b);
	out = dot(a, b) / (modulus(a) * modulus(b));
	if (out > 1)
		out = 1;
	if (out < -1)
		out = -1;
	out = acos(out);
	out *= 180 / 3.14159;
	return (out);
}

t_vec3 get_angles(t_vec3 a, t_vec3 b)
{
	t_vec3	out;
	t_vec3	tmp[2];

	a = norm(a);
	b = norm(b);
	tmp[0] = vec3(0, y(a), z(a));
	tmp[1] = vec3(0, y(b), z(b));
	out.vs[0] = vec_angle(tmp[0], tmp[1]);
	out.vs[0] *= 1 - (2 * (x(a) > x(b)));
	tmp[0] = vec3(x(a), 0, z(a));
	tmp[1] = vec3(x(b), 0, z(b));
	out.vs[1] = vec_angle(tmp[0], tmp[1]);
	out.vs[1] *= 1 - (2 * ((y(a) > y(b))));
	tmp[0] = vec3(x(a), y(a), 0);
	tmp[1] = vec3(x(b), y(b), 0);
	out.vs[2] = vec_angle(tmp[0], tmp[1]);
	out.vs[2] *= 1 - (2 * ((z(a) > z(b))));
	out = norm(out);
	return (out);
}

void	vec_matrix_mult(t_vec3 matrix_row, t_vec3 vec, t_vec3 *out, size_t r_i)
{
	t_data	row_value;

	if (!out)
		return ;
	row_value = matrix_row.vs[0] * vec.vs[0];
	row_value += matrix_row.vs[1] * vec.vs[1];
	row_value += matrix_row.vs[2] * vec.vs[2];
	out->vs[r_i] = row_value;
}
t_vec3	rotate(t_vec3 input, t_vec3 degrees)
{
	t_vec3	out;
	t_vec3	tmp;

	degrees = vec_smul(degrees, 3.14159 / 180);
	tmp = input;
	vec_matrix_mult(vec3(1, 0, 0), tmp, &out, 0);
	vec_matrix_mult(vec3(0, cos(x(degrees)), -sin(x(degrees))), tmp, &out, 1);
	vec_matrix_mult(vec3(0, sin(x(degrees)), cos(x(degrees))), tmp, &out, 2);
	tmp = out;
	vec_matrix_mult(vec3(cos(y(degrees)), 0, sin(y(degrees))), tmp, &out, 0);
	vec_matrix_mult(vec3(0, 1, 0), tmp, &out, 1);
	vec_matrix_mult(vec3(-sin(y(degrees)), 0, cos(y(degrees))), tmp, &out, 2);
	tmp = out;
	vec_matrix_mult(vec3(cos(z(degrees)), -sin(z(degrees)), 0), tmp, &out, 0);
	vec_matrix_mult(vec3(sin(z(degrees)), cos(z(degrees)), 0), tmp, &out, 1);
	vec_matrix_mult(vec3(0, 0, 1), tmp, &out, 2);
	return (out);
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

