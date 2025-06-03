#include "../Headers/dynamic_array.h"
#include <stdio.h>

char	*dstr(t_darray *darr)
{
	char	*str;
	str = (char *) darr->darray;
	return (str);
}

char	**dpstr(t_darray *darr)
{
	char	**pstr;
	pstr = (char **) darr->darray;
	return (pstr);
}
