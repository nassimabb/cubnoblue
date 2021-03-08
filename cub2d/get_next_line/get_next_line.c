/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:06:57 by nabboudi          #+#    #+#             */
/*   Updated: 2019/11/20 14:59:09 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static	int		ft_check(int fd, char **str, char **line)
{
	if (fd < 0 || line == NULL || (read(fd, *line, 0) == -1) || BUFFER_SIZE < 0)
		return (-1);
	if (!*str)
	{
		if (!(*str = ft_strdup("")))
			return (-1);
	}
	return (0);
}

static	char	*ft_strchr(const char *s, int c)
{
	while (*s != (unsigned char)c)
	{
		if (!*s++)
			return (0);
	}
	return ((char *)s);
}

static	int		readline(char **str, int fd)
{
	char		*buff;
	int			ret;
	char		*tmp;

	if (!(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (((ret = read(fd, buff, BUFFER_SIZE)) > 0))
	{
		buff[ret] = '\0';
		tmp = *str;
		if (!(*str = ft_strjoin(*str, buff)))
		{
			free(buff);
			return (-1);
		}
		free(tmp);
		tmp = NULL;
		if (ft_strchr(*str, '\n'))
			break ;
	}
	free(buff);
	return (ret);
}

int				get_next_line(int fd, char **line)
{
	static char *str;
	int			r;
	char		*tmp;
	int			i;

	i = 0;
	if (ft_check(fd, &str, line) == -1 || (r = readline(&str, fd)) < 0)
		return (-1);
	while (str[i] && str[i] != '\n')
		i++;
	if (!((*line) = ft_substr(str, 0, i)))
		return (-1);
	if (str[i] != '\n' && !r)
	{
		free(str);
		str = NULL;
		return (0);
	}
	tmp = str;
	if (!(str = ft_strdup(str + i + 1)))
		return (-1);
	free(tmp);
	tmp = NULL;
	return (1);
}
