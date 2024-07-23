/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:03:44 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/23 17:09:09 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_texture_y(int height, int y, t_texture *texture)
{
	int	texture_y;

	if (height)
		texture_y = ((y - ((SCREEN_HEIGHT / 2) - (height / 2)))
				* texture->height) / (height);
	else
		texture_y = ((y - ((SCREEN_HEIGHT / 2) - (height / 2)))
				* texture->height);
	return (texture_y);
}

void	draw_wall(t_mlx *mlx, int height, t_texture *texture, double texture_x)
{
	int	color;
	int	texture_y;
	int	y;
	int	pixel;
	int	img_pixel;

	y = (SCREEN_HEIGHT / 2) - (height / 2);
	while (y < ((SCREEN_HEIGHT / 2) + (height / 2)))
	{
		if (y >= 0 && y < SCREEN_HEIGHT)
		{
			texture_y = get_texture_y(height, y, texture);
			pixel = (texture_y * texture->size_line)
				+ ((int)(texture_x * texture->width) * (texture->bpp / 8));
			color = *(int *)(texture->img_data + pixel);
			img_pixel = (y * mlx->size_line) + (mlx->x * (mlx->bpp / 8));
			mlx->img_data[img_pixel] = color & 0xFF;
			mlx->img_data[img_pixel + 1] = (color >> 8) & 0xFF;
			mlx->img_data[img_pixel + 2] = (color >> 16) & 0xFF;
		}
		y++;
	}
}
