/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:51:57 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/23 17:19:46 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_angle(t_player *p, int map)
{
	if (map == 'N')
		p->angle = (3 * M_PI) / 2;
	if (map == 'S')
		p->angle = M_PI / 2;
	if (map == 'E')
		p->angle = 0;
	if (map == 'W')
		p->angle = M_PI;
}

t_player	find_player(int **mapp, int w, int h)
{
	t_player	p;
	int			i;
	int			j;

	j = 0;
	while (j < w)
	{
		i = 0;
		while (i < h)
		{
			if (mapp[j][i] == 'N' || mapp[j][i] == 'S' ||
				mapp[j][i] == 'E' || mapp[j][i] == 'W')
			{
				p.y = (j) + 0.5;
				p.x = (i) + 0.5;
				set_angle(&p, mapp[j][i]);
			}
			i++;
		}
		j++;
	}
	return (p);
}
