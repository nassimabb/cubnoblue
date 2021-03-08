#include "cub3d.h"



int main()
{
	char    **a;

	a = ft_realloc(a, "hi");
	a = ft_realloc(a, "nassim");
	a = ft_realloc(a, "i m here");
	int i;

	i = -1;
	while (++i < ft_tablen(a))
		printf("%s\n", a[i]);
	return (0);
}