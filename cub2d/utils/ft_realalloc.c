/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 17:04:59 by nabboudi          #+#    #+#             */
/*   Updated: 2020/12/26 17:05:16 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void    *ft_realalloc(void *target, int csize, int nsize)
{
    void    *ntarget;
    int     size;

    size = 0;
    if(csize == nsize)
        return target;
    if (csize > nsize)
        return NULL;
    if (!(ntarget = malloc(nsize)))
        return NULL;
    while (size < csize)
    {
        ((char*)ntarget)[size] = ((char*)target)[size];
        size++;
    }
    while (size < nsize)
        ((char*)ntarget)[size++] = 0;
    free(target);
    return ntarget;
}