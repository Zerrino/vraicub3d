/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:10:32 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/25 00:37:11 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	color_scene1(t_mlx *mlx, t_player player)
{
	int	x;
	int	y;
	int	pixel;

	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			pixel = (y * mlx->size_line) + (x * (mlx->bpp / 8));
			mlx->img_data[pixel] = ft_rgb(player.file.f) & 0xFF;
			mlx->img_data[pixel + 1] = (ft_rgb(player.file.f) >> 8) & 0xFF;
			mlx->img_data[pixel + 2] = (ft_rgb(player.file.f) >> 16) & 0xFF;
			x++;
		}
		y++;
	}
}

void	color_scene(t_mlx *mlx, t_player player)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			pixel = (y * mlx->size_line) + (x * (mlx->bpp / 8));
			mlx->img_data[pixel] = ft_rgb(player.file.c) & 0xFF;
			mlx->img_data[pixel + 1] = (ft_rgb(player.file.c) >> 8) & 0xFF;
			mlx->img_data[pixel + 2] = (ft_rgb(player.file.c) >> 16) & 0xFF;
			x++;
		}
		y++;
	}
	color_scene1(mlx, player);
}

void	get_texture_player(t_player *player)
{
	if (player->side == 0)
	{
		if (player->step_x > 0)
			player->texture_index = 2;
		else
			player->texture_index = 0;
	}
	else
	{
		if (player->step_y > 0)
			player->texture_index = 3;
		else
			player->texture_index = no_animation(player);
	}
}

void	rendering_wall(t_mlx *mlx, t_player *player, t_texture textures[4])
{
	if (player->side == 0)
		player->perp_wall_dist = (player->map_x - player->x
				+ (1 - player->step_x) / 2) / player->ray_dir_x;
	else
		player->perp_wall_dist = (player->map_y - player->y
				+ (1 - player->step_y) / 2) / player->ray_dir_y;
	player->line_height = (int)(SCREEN_HEIGHT / player->perp_wall_dist);
	if (player->side == 0)
		player->wall_x = player->y + player->perp_wall_dist * player->ray_dir_y;
	else
		player->wall_x = player->x + player->perp_wall_dist * player->ray_dir_x;
	player->wall_x -= floor(player->wall_x);
	player->tex_x = (int)(player->wall_x * (double)(textures[0].width));
	if (player->side == 0 && player->ray_dir_x > 0)
		player->tex_x = textures[0].width - player->tex_x - 1;
	if (player->side == 1 && player->ray_dir_y < 0)
		player->tex_x = textures[0].width - player->tex_x - 1;
	get_texture_player(player);
	draw_wall(mlx, player->line_height, &textures[player->texture_index],
		(double)player->tex_x / textures[player->texture_index].width);
}
