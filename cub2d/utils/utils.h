/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 17:04:17 by nabboudi          #+#    #+#             */
/*   Updated: 2020/12/31 16:54:46 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

  
#ifndef UTILS_H
# define UTILS_H
#include <string.h>
#include <stdlib.h>

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t  ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void    *ft_realalloc(void *target, int csize, int nsize);
size_t	ft_tablen(char **s);
#endif