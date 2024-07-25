/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 00:37:35 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/25 01:00:49 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;
	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	no_animation(t_player *player)
{
	static int	nb;
	static int	ret;

	if (ret == 0)
		ret = 1;
	if (player->time == 0 || (player->time + INTERVAL) < get_time())
	{
		player->time = get_time();
		nb++;
		if (player->file.no && nb == 1)
			ret = 1;
		else if (player->file.n1 && nb < 3)
			ret = 4;
		else if (player->file.n2 && nb < 4)
			ret = 5;
		else if (player->file.n3 && nb < 5)
			ret = 6;
		else
			nb = 0;
	}
	return (ret);
}
