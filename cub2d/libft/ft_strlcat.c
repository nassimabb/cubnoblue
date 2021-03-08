/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 03:03:15 by nabboudi          #+#    #+#             */
/*   Updated: 2019/10/30 03:03:16 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	lens;
	size_t	i;

	i = 0;
	lens = ft_strlen(src);
	if (!size)
		return (lens);
	while (*dest && size)
	{
		dest++;
		i++;
		size--;
	}
	while (*src && size > 1)
	{
		*dest++ = *src++;
		size--;
	}
	if (size != 0)
		*dest = '\0';
	return (lens + i);
}
