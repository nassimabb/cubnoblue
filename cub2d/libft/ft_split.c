/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 23:00:55 by nabboudi          #+#    #+#             */
/*   Updated: 2019/10/27 17:36:27 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		words_number(const char *str, char c)
{
	int i;
	int space_flag;
	int words_number;

	words_number = 0;
	space_flag = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			space_flag = 1;
		else
		{
			words_number += space_flag;
			space_flag = 0;
		}
		i++;
	}
	return (words_number);
}

static void		copy(const char *str, char *tab, int len, int i)
{
	int k;

	k = -1;
	while (++k < len)
		tab[k] = str[i + k];
	tab[k] = '\0';
}

static char		**freeespace(char **tab, int j)
{
	while (j >= 0)
	{
		free(tab[j]);
		j--;
	}
	free(tab);
	return (NULL);
}

static char		**add_words(const char *str, char **tab, char c)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	while (str[i])
	{
		len = 0;
		while (str[i] == c)
			i++;
		if (str[i])
		{
			while (str[i + len] && (str[i + len]) != c)
				len++;
			if ((tab[j] = malloc(sizeof(*tab[j]) * (len + 1))) == NULL)
				return (freeespace(tab, j));
			copy(str, tab[j++], len, i);
			i += len;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char			**ft_split(const char *str, char c)
{
	char	**tab;
	int		wnb;

	if (!str)
		return (NULL);
	wnb = words_number(str, c);
	tab = malloc(sizeof(*tab) * (wnb + 1));
	if (tab == NULL)
	{
		free(tab);
		return (NULL);
	}
	return (add_words(str, tab, c));
}
