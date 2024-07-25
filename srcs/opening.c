/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:11:47 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/25 01:54:29 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	wall_loop(t_player *player)
{
	int	iteration_count;

	iteration_count = 0;
	while (player->hit_wall == 0 && iteration_count < 1)
	{
		if (player->side_dist_x < player->side_dist_y)
		{
			player->side_dist_x += player->delta_dist_x;
			player->map_x += player->step_x;
		}
		else
		{
			player->side_dist_y += player->delta_dist_y;
			player->map_y += player->step_y;
		}
		if (player->file.map[player->map_y][player->map_x] == 3)
		{
			player->file.map[player->map_y][player->map_x] = 2;
			player->hit_wall = 1;
		}
		else if (player->file.map[player->map_y][player->map_x] == 2)
		{
			player->file.map[player->map_y][player->map_x] = 3;
			player->hit_wall = 1;
		}
		iteration_count++;
	}
}

void	hit_door(t_player *player)
{
	int	x;

	x = SCREEN_WIDTH - HITBOX_E;
	player->hit_wall = 0;
	while (x < SCREEN_WIDTH + HITBOX_E)
	{
		set_data(player, x);
		scene_data(player);
		wall_loop(player);
		x++;
	}
}

void	opening_door(t_player *player)
{
	hit_door(player);
}
