/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:49:14 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/06 18:30:51 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void free_array(char **tab)
{
    int i;

    i = -1;
    while (tab[++i])
        free(tab[i]);
    free(tab);
}

char **fill_map()
{
    char **tab;
    int i;
    int j;
    char *tmp;
    tab = malloc(sizeof(char*) * (game_data.big_colon + 1));
    i = 0;
    while (i < game_data.big_colon)
    {
        tab[i] = malloc(sizeof(char) * game_data.big_line + 1);
        j = 0;
        while (j < game_data.big_line)
        {
            if (j < ft_strlen(map[i]))
                tab[i][j] = map[i][j];
            else
                tab[i][j] = '1';

            j++;
        }
        // //tmp = ft_strrchr(tab[i], '0');
        //     //if (tmp)
        //     {
        //             *tmp = '1';
        //     }
        tab[i][j] = 0;
        i++;
    }
    tab[i] = NULL;
    free_array(map);
    return tab;
}

void       ft_split2(char* tab)
{
    char **tab2;
    char* num;
    num = tab;
    tab2 = ft_split(num ,',');
    color.color_x = ft_atoi(tab2[0]);
    color.color_y = ft_atoi(tab2[1]);
    color.color_z = ft_atoi(tab2[2]);
}

void       ft_splitc(char* tab)
{
    char **tab2;
    char* num;
    num = tab;
    tab2 = ft_split(num ,',');
    color.color_xc = ft_atoi(tab2[0]);
    color.color_yc = ft_atoi(tab2[1]);
    color.color_zc = ft_atoi(tab2[2]);
}

void    ft_countmap(void)
{
    int     i;
    int     j;
        
    j = 0;    
    j = ft_tablen(map);
    i = 0;
    game_data.big_line = ft_strlen(map[i]);
    while (i < j - 1)
    {
        if (game_data.big_line < ft_strlen(map[i + 1]))
            game_data.big_line = ft_strlen(map[i + 1]);
        i++;
    }
    game_data.big_colon = j;
    printf("$$$$%d$$$$\n$$$$%d$$$$\n",game_data.big_line,game_data.big_colon);
}

char    **ft_realloc(char **tab, char *element)
{
    int     i;
    char    **ret;
    int     len;

    i = 0;
    len = 1;
    if (tab)
        len = ft_tablen(tab) + 1;
    ret = (char **)malloc(sizeof(char *) * (len + 1));
    while (i < len - 1)
    {
        ret[i] = ft_strdup(tab[i]);
        i++;
    }
    ret[i] = ft_strdup(element);
    ret[i + 1] = NULL;
    game_data.big_colon += 1;
    if (game_data.big_line < ft_strlen(element))
        game_data.big_line = ft_strlen(element);
        
    return (ret);
}

void       ft_readmap(void)
{
    char *line;
    char **tab;
    int fd;


    map = NULL;                                                                                          
    fd = open("map.cub",O_RDONLY);
    while (get_next_line(fd,&line))
    {
        tab = ft_split(line ,' ');
        if(ft_tablen(tab))
        {
            //(ft_strlen(tab[0]) > 1 ? ft_strlen(tab[0]) : 1))
            if (!ft_strncmp(tab[0],"R",1))
            {   // check if tab[1] and tab[2] all num
                game_data.resolution_x = ft_atoi(tab[1]);
                game_data.resolution_y = ft_atoi(tab[2]);
            }
            else if (!ft_strncmp(tab[0],"NO",2))
            {
                game_data.no_path = tab[0];
                game_data.no_txt = tab[1];
            }
            else if (!ft_strncmp(tab[0],"SO",2))
            {
                game_data.so_path = tab[0];
                game_data.so_txt = tab[1];
            }
            else if (!ft_strncmp(tab[0],"WE",2))
            {
                game_data.we_path = tab[0];
                game_data.we_txt = tab[1];
            }
            else if (!ft_strncmp(tab[0],"EA",2))
            {
                game_data.ea_path = tab[0];
                game_data.ea_txt = tab[1];
            }
            else if (!ft_strncmp(tab[0],"S",2))
            {
                game_data.s_path = tab[0];
                game_data.s_txt= tab[1];
            }
            else if (!ft_strncmp(tab[0],"F",1))
            {
                tab = ft_split(line ,' ');
                color.flor_a = tab[0];
                ft_split2(tab[1]);
            }
            else if (!ft_strncmp(tab[0],"C",1))
            {
                tab = ft_split(line ,' ');
                color.flor_b = tab[0];
                ft_splitc(tab[1]);
            }
            else if (ft_isdigit(*line) || *line == ' ')
                map = ft_realloc(map, line);
        }
    }

   // printf("%d\n",color.color_xc );
   // printf("%d\n",color.color_yc );
   // printf("%d\n",color.color_zc);
   //
}
