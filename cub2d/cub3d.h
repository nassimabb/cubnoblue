/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:53:17 by nabboudi          #+#    #+#             */
/*   Updated: 2021/03/06 18:19:21 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "utils/utils.h"
# include <stdio.h>
# include "get_next_line/get_next_line.h"
# include <math.h>
#include <stdbool.h>
# include <limits.h>
# define EXIT_KEY		53
# define KEY_RIGHT		124
# define KEY_LEFT		123
# define KEY_DOWN		125
# define KEY_UP			126
# define TILE_SIZE      32
# define PI 3.14
# define FOV_ANGLE (60 * (PI / 180))
# define MAP_NUM_ROWS 14
# define MAP_NUM_COLS 33
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
#define MINI 0.3


typedef struct player
{
    int x;
    int y;
}               t_player;

t_player player;

typedef struct s_ray
{
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float  distance;
    float wasHitVertical;
    float isRayFacingDown;
    float isRayFacingUp;
    float isRayFacingLeft;
    float isRayFacingRight;
}               t_ray;

typedef struct s_player
{
    float rotationangle;
    float turndirection;
    float rotationspeed;
    float walkdirection;
    float movespeed;
    float movestep;
    float x;
    float y;
    float newplayerx;
    float newplayery;
    float dirangle;
}               t_plr;

t_plr nassim;

t_ray   ray;

typedef struct  s_cub {
    int           resolution_x;
    int         resolution_y;
    char*       no_path;
    char*       no_txt;
    char*       so_path;
    char*       so_txt;
    char*       we_path;
    char*       we_txt;
    char*       ea_path;
    char*       ea_txt;
    char*       s_path;
    char*       s_txt;  
     int     big_line;
int     big_colon;
}               t_cub;

typedef struct  s_color {
    char*       flor_a;
    char*       flor_b;
    int         color_x;
    int         color_y;
    int         color_z;
    int         color_xc;
    int         color_yc;
    int         color_zc;
}               t_color;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

char       **map;
char        **updated_map;
t_data  img;
t_cub   game_data;
t_color color;
void    *mlx;
void    *mlx_win;
void    ft_readmap(void);
char **fill_map();
void free_array(char **tab);
#endif