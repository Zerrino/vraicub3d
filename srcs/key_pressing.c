/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:21:18 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/25 02:04:48 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_update(t_player *player, double x, double y)
{
	if ((player->file.map[(int)(y + BORDER)][(int)(x + BORDER)] != 1
		&& player->file.map[(int)(y + BORDER)][(int)(x - BORDER)] != 1
		&& player->file.map[(int)(y - BORDER)][(int)(x + BORDER)] != 1
		&& player->file.map[(int)(y - BORDER)][(int)(x - BORDER)] != 1)
		&&
		(player->file.map[(int)(y + BORDER)][(int)(x + BORDER)] != 3
		&& player->file.map[(int)(y + BORDER)][(int)(x - BORDER)] != 3
		&& player->file.map[(int)(y - BORDER)][(int)(x + BORDER)] != 3
		&& player->file.map[(int)(y - BORDER)][(int)(x - BORDER)] != 3)
		)
	{
		player->x = x;
		player->y = y;
	}
	else
	{
		if ((player->file.map[(int)player->y][(int)(x + BORDER)] != 1
			&& player->file.map[(int)player->y][(int)(x - BORDER)] != 1
			&& player->file.map[(int)player->y][(int)(x + BORDER)] != 1
			&& player->file.map[(int)player->y][(int)(x - BORDER)] != 1)
			&&
			(player->file.map[(int)player->y][(int)(x + BORDER)] != 3
			&& player->file.map[(int)player->y][(int)(x - BORDER)] != 3
			&& player->file.map[(int)player->y][(int)(x + BORDER)] != 3
			&& player->file.map[(int)player->y][(int)(x - BORDER)] != 3))
			player->x = x;
		else if ((player->file.map[(int)(y + BORDER)][(int)player->x] != 1
			&& player->file.map[(int)(y + BORDER)][(int)player->x] != 1
			&& player->file.map[(int)(y - BORDER)][(int)player->x] != 1
			&& player->file.map[(int)(y - BORDER)][(int)player->x] != 1)
			&&
			(player->file.map[(int)(y + BORDER)][(int)player->x] != 1
			&& player->file.map[(int)(y + BORDER)][(int)player->x] != 1
			&& player->file.map[(int)(y - BORDER)][(int)player->x] != 1
			&& player->file.map[(int)(y - BORDER)][(int)player->x] != 1)
			)
			player->y = y;
	}
}

int mouse_move(int x, int y, void *param)
{
	t_player	*player;

	(void)y;
	player = param;
	if (player->last_x < x)
		player->angle += PLAYER_ROTATE_SPEED;
	else if (player->last_x > x)
		player->angle -= PLAYER_ROTATE_SPEED;
	player->last_x = x;
	return (0);
}

void	player_pos(t_player *player, int key)
{
	if (key == 13)
	{
		player->new_x += (cos(player->angle) * (double)PLAYER_MOVE_SPEED);
		player->new_y += (sin(player->angle) * (double)PLAYER_MOVE_SPEED);
	}
	if (key == 1)
	{
		player->new_x -= (cos(player->angle) * (double)PLAYER_MOVE_SPEED);
		player->new_y -= (sin(player->angle) * (double)PLAYER_MOVE_SPEED);
	}
	if (key == 0)
	{
		player->new_x += (sin(player->angle) * (double)PLAYER_TURN_SPEED);
		player->new_y -= (cos(player->angle) * (double)PLAYER_TURN_SPEED);
	}
	if (key == 2)
	{
		player->new_x -= (sin(player->angle) * (double)PLAYER_TURN_SPEED);
		player->new_y += (cos(player->angle) * (double)PLAYER_TURN_SPEED);
	}
	if (key == 14)
		opening_door(player);
}

int	handle_keypress(int key, void *param)
{
	t_player	*player;

	player = (t_player *)param;
	player->new_x = player->x;
	player->new_y = player->y;
	if (key == 53)
	{
		ft_free_file(&player->file, 0);
		exit(0);
	}
	if (key == 123)
		player->angle -= PLAYER_ROTATE_SPEED;
	if (key == 124)
		player->angle += PLAYER_ROTATE_SPEED;
	player_pos(player, key);
	player_update(player, player->new_x, player->new_y);
	return (0);
}
