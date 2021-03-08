#include "cub3d.h"


void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    int		*dst;

	dst = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	if (x < game_data.resolution_x && y < game_data.resolution_y && x >= 0 && y >= 0)
		dst[y * (int)game_data.resolution_x + x] = color;
}


int			key_press_hook(int keycode, void *ptr)
{
	ptr = NULL;
	if (keycode == EXIT_KEY)
		exit(1);
	if (keycode == KEY_UP)
		nassim.walkdirection = 1;
	if (keycode == KEY_DOWN)
		nassim.walkdirection = -1;
	if (keycode == KEY_RIGHT)
		nassim.turndirection = 1;
	if (keycode == KEY_LEFT)
		nassim.turndirection = -1;
	return (1);
}

int			key_release_hook(int keycode, void *ptr)
{
	ptr = NULL;
	if (keycode == KEY_UP)
		nassim.walkdirection = 0;
	if (keycode == KEY_DOWN)
		nassim.walkdirection = 0;
	if (keycode == KEY_RIGHT)
		nassim.turndirection = 0;
	if (keycode == KEY_LEFT)
		nassim.turndirection = 0;
	return (1);
}




void            draw_square(int i, int j)
{
    int x;
    int y;

    x = 0;
    while (x < TILE_SIZE)
    {
        y = 0;
        while(y < TILE_SIZE)
        {
            my_mlx_pixel_put(&img, (j * TILE_SIZE + y) * MINI, (i * TILE_SIZE +  x) * MINI, 0xFF5733);
            y++;
        } 
        x++;
    }
}

void            draw_2d()
{
    int i; 
    int j;

    i = 0;
    while (map[i] != NULL)
    {
        j = 0;
        while (map[i][j] != '\0')
        {
            if (map[i][j] == '1')
                draw_square(i, j);
            j += 1;
        }
        i++;
    }
}

int     hasWallAt(float x, float y)
{


    int x0 = floor(x / TILE_SIZE);
    int y0 = floor(y / TILE_SIZE);

    //printf("||%d ' %d || %d ' %d\n", x0, y0,game_data.big_colon,  game_data.big_line  );
    //if (y0 >= game_data.big_line - 3)
        //return (0);
    if (x0 < 0 || x0  >= game_data.big_colon  || y0 < 0 || y0 >= game_data.big_line)
        return (0);
    else if (map[x0][y0] == '1' ) //|| map[x0][y0] == ' ')
        return (1);
    return (0);
}


float normalizeAngle(float angle)
{
    float angler;
    angler = fmod(angle ,(2 * M_PI));
    if (angle < 0)
        angler = (2 * M_PI) + angle;
    return angler;
}

 int colorr  = 0xFFFFFF;

float distanceBetweenPoints(float x1,float y1, float x2, float  y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void dda(float  X0, float  Y0, float  X1, float  Y1) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float) steps; 
    float Yinc = dy / (float) steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) 
    {
        my_mlx_pixel_put(&img, Y, X, colorr);
        X += Xinc;
        Y += Yinc; 

    } 
} 

void    ray_direction(float angle)
{
    ray.rayAngle = normalizeAngle(angle);
    ray.wallHitX = 0;
    ray.wallHitY = 0;
    ray.distance = 0;
    ray.wasHitVertical = false;

    ray.isRayFacingDown = ray.rayAngle > 0 && ray.rayAngle < M_PI;
    ray.isRayFacingUp = !ray.isRayFacingDown;

    ray.isRayFacingRight = ray.rayAngle < (0.5 * M_PI) || ray.rayAngle > (1.5 * M_PI);
    ray.isRayFacingLeft = !ray.isRayFacingRight;
}

void    cast_ray(int col, float angle)
{
    ray_direction(angle);
    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    float foundHorzWallHit = false;
    float horzWallHitX = 0;
    float horzWallHitY = 0;

    // Find the y-coordinate of the closest horizontal grid intersenction
    yintercept = floor(nassim.y / TILE_SIZE) * TILE_SIZE;
    yintercept += ray.isRayFacingDown ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = nassim.x + (yintercept - nassim.y) / tan(ray.rayAngle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= ray.isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(ray.rayAngle);
    xstep *= (ray.isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (ray.isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX < game_data.big_colon * TILE_SIZE && nextHorzTouchY >= 0 && nextHorzTouchY < game_data.big_line * TILE_SIZE)
    {
        if (hasWallAt(nextHorzTouchX, nextHorzTouchY + (ray.isRayFacingUp ? -1 : 0)))
        {
            foundHorzWallHit = true;
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    ray_direction(angle);
    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    float foundVertWallHit = false;
    float vertWallHitX = 0;
    float vertWallHitY = 0;

    // Find the x-coordinate of the closest vertical grid intersenction
    xintercept = floor(nassim.x / TILE_SIZE) * TILE_SIZE;
    xintercept += ray.isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    yintercept = nassim.y + (xintercept - nassim.x) * tan(ray.rayAngle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= ray.isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(ray.rayAngle);
    ystep *= (ray.isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (ray.isRayFacingDown && ystep < 0) ? -1 : 1;
    

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX < game_data.big_colon * TILE_SIZE && nextVertTouchY >= 0 && nextVertTouchY < game_data.big_line * TILE_SIZE)
    {
        if (hasWallAt(nextVertTouchX  - (ray.isRayFacingLeft ? 1 : 0), nextVertTouchY))
        {
            foundVertWallHit = true;
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            break;
        }
        else
        {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical distances and choose the smallest value
    float horzHitDistance = (foundHorzWallHit)
        ? distanceBetweenPoints(nassim.x, nassim.y, horzWallHitX, horzWallHitY)
        : INT_MAX;
    float vertHitDistance = (foundVertWallHit)
        ? distanceBetweenPoints(nassim.x, nassim.y, vertWallHitX, vertWallHitY)
        : INT_MAX;
    // printf("%.2f %.2f %.2f %.2f %.2f\n", xstep, ystep, horzHitDistance, vertHitDistance, ray.isRayFacingRight);

    // only store the smallest of the distances
    ray.wallHitX = (horzHitDistance < vertHitDistance) ? horzWallHitX : vertWallHitX;
    ray.wallHitY = (horzHitDistance < vertHitDistance) ? horzWallHitY : vertWallHitY;
    ray.distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
    ray.wasHitVertical = (vertHitDistance < horzHitDistance);
    
    ray.distance *= cos(nassim.dirangle - ray.rayAngle);
    //printf("0%f\n",ray.rayAngle);
    //printf("1%f\n",nassim.rotationangle);
    //ray.distance *= cos(ray.rayAngle);
    float perpDistance = ray.distance;
    float distanceProjPlane = (game_data.big_colon * TILE_SIZE / 2) / tan(FOV_ANGLE / 2);
    float projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

    int wallStripHeight = projectedWallHeight;
    int wallTopPixel = (game_data.big_line * TILE_SIZE / 2) - (wallStripHeight / 2);
    wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

    int wallBottomPixel = (game_data.big_line * TILE_SIZE / 2) + (wallStripHeight / 2);
    wallBottomPixel = wallBottomPixel > game_data.big_line * TILE_SIZE ? game_data.big_line * TILE_SIZE : wallBottomPixel;
    colorr = 0xFFFFFF;
    dda(wallBottomPixel, col, wallTopPixel, col);
    colorr = 0xFF0000;
    dda(game_data.big_line * TILE_SIZE/2 + wallStripHeight/2, col, game_data.big_line * TILE_SIZE, col);
    dda(nassim.x* MINI , nassim.y*MINI, ray.wallHitX*MINI, ray.wallHitY*MINI);
    
   // dda(col , 0, ray.wallHitX, ray.wallHitY);
    // CEILLINGd
    //ft_draw_line(col , 0, WINDOW_HEIGHT/2 - wallStripHeight/2);
    //dda(col , WINDOW_HEIGHT/2 - wallStripHeight/2, 0, WINDOW_HEIGHT/2 + wallStripHeight/2);
    // FLOOR
    //ft_draw_line(col , data.Height/2 + wallStripHeight/2, col, data.Height);
}



void            cast(void)
{
    int i;
    float   rayangle;
    float   angle;

    i = 0;
    rayangle = (FOV_ANGLE / (game_data.resolution_x ));
    angle = (nassim.dirangle) - (FOV_ANGLE/2);
    while (i < game_data.resolution_x)
    {
        angle = normalizeAngle(angle);
        cast_ray(i, angle);
        angle += rayangle;
        i++;
    }
}

void move_player()
{
    nassim.dirangle += nassim.turndirection * nassim.rotationspeed;
    
    nassim.movestep = nassim.walkdirection * nassim.movespeed;

    nassim.newplayerx = nassim.x + cos(nassim.dirangle) * nassim.movestep;
    nassim.newplayery = nassim.y + sin(nassim.dirangle) * nassim.movestep;

    if (!hasWallAt( nassim.newplayerx,  nassim.newplayery))
    {
        nassim.x = nassim.newplayerx;
        nassim.y = nassim.newplayery;
    }
}


int            ft_update()
{
    if (img.img != NULL)
        mlx_destroy_image(mlx, img.img);

    img.img = mlx_new_image(mlx, game_data.resolution_x, game_data.resolution_y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    &img.endian);
    draw_2d();
    move_player();
    cast();
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    return (0);
}

void            get_player_pos()
{
    int i; 
    int j;

    i = 0;
    while (map[i] != NULL)
    {
        j = 0;
        while (map[i][j] != '\0')
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
            {
                nassim.x = (i + 0.5) * TILE_SIZE;
                nassim.y = (j + 0.5) * TILE_SIZE;
                if (map[i][j] == 'N')
                    nassim.dirangle = -(M_PI / 2);
                else if (map[i][j] == 'S')
                    nassim.dirangle  = M_PI / 2;
                else if (map[i][j] == 'W')
                    nassim.dirangle = M_PI;
                else if (map[i][j] == 'E')
                    nassim.dirangle  = 0;
            }
            j += 1;
        }
        i++;
    }
    nassim.dirangle = normalizeAngle(nassim.dirangle);
}

void    init_struct()
{
    nassim.rotationangle = M_PI/ 12;
    nassim.turndirection = 0;
    nassim.rotationspeed = 2 * M_PI / 180;
    nassim.walkdirection = 0;
    nassim.movespeed = 2.0;

}

int             main()
{

    
    char *line;
    char **tab;
    int fd;

    // fd = open("map.cub",O_RDONLY);
    // while (get_next_line(fd,&line) )
    // {
    //     tab = ft_split(line ,' ');
    //     if(ft_tablen(tab))
    //     {
    //         if (!ft_strncmp(tab[0],"R",ft_strlen(tab[0])))
    //         {
    //             game_data.resolution_x = ft_atoi(tab[1]);
    //             game_data.resolution_y = ft_atoi(tab[2]);
    //         }
    //         if (!ft_strncmp(tab[0],"NO",ft_strlen(tab[0])))
    //         {
    //             game_data.no_path = tab [0];
    //         }

    //     }
    // }
    game_data.big_colon = 0;
    game_data.big_line = 0;  
    ft_readmap();
    int i = -1;
    // printf("%s\n",line);
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, game_data.resolution_x, game_data.resolution_y, "CUb3d");
    img.img = NULL;
    printf("x = %d y = %d\n", game_data.resolution_x, game_data.resolution_y);
    get_player_pos();
    map = fill_map();
    while (++i < game_data.big_colon)
		printf("%s\n", map[i]);
    init_struct();
    mlx_hook(mlx_win, 2, 0, key_press_hook, "lll");
	mlx_hook(mlx_win, 3, 0, key_release_hook, "lll");
    mlx_loop_hook(mlx, &ft_update, "");
  
    mlx_loop(mlx);
    return(0);
}
