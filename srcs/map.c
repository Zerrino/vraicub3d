/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:34:25 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/25 13:55:46 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_cub(t_player *player, t_mlx *mlx)
{
	int	**map;
	int	i;
	int	j;
	int	new_i;
	int	new_j;

	map = player->file.map;
	i = 10;
	while (i < (player->file.streak * SCALE_MAP) + Y_PADDING)
	{
		j = 10;
		while (j < (player->file.len_max * SCALE_MAP) + X_PADDING)
		{
			new_i = (i - Y_PADDING) / SCALE_MAP;
			new_j = (j - X_PADDING) / SCALE_MAP;
			if (map[new_i][new_j] == 1)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, j, i, 0xff0000);
			else if ((int)player->x == new_j && (int)player->y == new_i)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, j, i, 0x0000ff);
			else if (map[new_i][new_j] == 0)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, j, i, 0x00ff00);
			j++;
		}
		i++;
	}
}
