/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:22:53 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/23 15:54:28 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

void	ft_free_map(int **map, t_file *file)
{
	int	i;

	i = 0;
	while (i < file->streak)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	ft_free_file(t_file *file, int x)
{
	if (file->free)
		return (x);
	if (file->no)
		free(file->no);
	if (file->so)
		free(file->so);
	if (file->we)
		free(file->we);
	if (file->ea)
		free(file->ea);
	if (file->map)
		ft_free_map(file->map, file);
	file->free = 1;
	return (x);
}

int	ft_color_err(t_file file)
{
	if ((file.c[0] < 0 || file.c[0] > 255)
		|| (file.c[1] < 0 || file.c[1] > 255)
		|| (file.c[2] < 0 || file.c[2] > 255)
		|| (file.f[0] < 0 || file.f[0] > 255)
		|| (file.f[1] < 0 || file.f[1] > 255)
		|| (file.f[2] < 0 || file.f[2] > 255))
		return (1);
	return (0);
}

void	ft_path(t_file *file, char *line)
{
	if (!file->no)
		file->no = get_path("NO", line);
	if (!file->so)
		file->so = get_path("SO", line);
	if (!file->we)
		file->we = get_path("WE", line);
	if (!file->ea)
		file->ea = get_path("EA", line);
}
