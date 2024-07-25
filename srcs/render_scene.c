/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:17:48 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/25 14:23:38 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_data(t_player *player, int x)
{
	double	ray_angle;

	ray_angle = player->angle - ((M_PI / 3) / 2.0)
		+ ((double)x / (double)SCREEN_WIDTH) * (M_PI / 3);
	player->ray_dir_x = cos(ray_angle);
	player->ray_dir_y = sin(ray_angle);
	if (player->ray_dir_x == 0)
		player->ray_dir_x = 0.00001;
	if (player->ray_dir_y == 0)
		player->ray_dir_y = 0.00001;
	player->delta_dist_x = fabs(1 / player->ray_dir_x);
	player->delta_dist_y = fabs(1 / player->ray_dir_y);
	player->map_x = (int)player->x;
	player->map_y = (int)player->y;
}

void	scene_data(t_player *player)
{
	if (player->ray_dir_x < 0)
	{
		player->step_x = -1;
		player->side_dist_x = (player->x - player->map_x)
			* player->delta_dist_x;
	}
	else
	{
		player->step_x = 1;
		player->side_dist_x = (player->map_x + 1.0 - player->x)
			* player->delta_dist_x;
	}
	if (player->ray_dir_y < 0)
	{
		player->step_y = -1;
		player->side_dist_y = (player->y - player->map_y)
			* player->delta_dist_y;
	}
	else
	{
		player->step_y = 1;
		player->side_dist_y = (player->map_y + 1.0 - player->y)
			* player->delta_dist_y;
	}
}

void	scene_loop(t_player *player)
{
	int	iteration_count;

	iteration_count = 0;
	while (player->hit == 0 && iteration_count < MAX_ITERATIONS)
	{
		if (player->side_dist_x < player->side_dist_y)
		{
			player->side_dist_x += player->delta_dist_x;
			player->map_x += player->step_x;
			player->side = 0;
		}
		else
		{
			player->side_dist_y += player->delta_dist_y;
			player->map_y += player->step_y;
			player->side = 1;
		}
		if (player->file.map[player->map_y][player->map_x] == 1
				|| player->file.map[player->map_y][player->map_x] == 3)
			player->hit = 1;
		iteration_count++;
	}
}

void	render_scene(t_mlx *mlx, t_player *player, t_texture textures[4])
{
	int	x;

	color_scene(mlx, *player);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		player->hit = 0;
		mlx->x = x;
		set_data(player, x);
		scene_data(player);
		scene_loop(player);
		if (player->hit)
			rendering_wall(mlx, player, textures);
		x++;
	}
}
