/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <nabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:53:08 by nabboudi          #+#    #+#             */
/*   Updated: 2020/12/26 16:53:09 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	put_character()
{
	float	phi;
	float	val;
	int		r;
	float	x;
	float	y;
	val = g_player.rotation_angle;
	r = 4;
	while (r >= 0)
	{
		phi = 0;
		while (phi <= 360)
		{
			y = (g_player.y) + (r * sin(phi * val));
			x = (g_player.x) + (r * cos(phi * val));
			if (x >= 0 && x < WIN_WIDTH &&
			y >= 0 && y < WIN_HEIGHT)
				img_update(x, y, 0xff0000);
			phi += 0.1;
		}
		r--;
	}
}