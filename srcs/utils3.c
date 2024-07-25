/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:34:44 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/25 01:47:46 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	*map_line(char *line, int len_max)
{
	int	*map;
	int	i;

	map = (int *)malloc(sizeof(int) * (len_max));
	if (!map)
		return (0);
	i = 0;
	while (i < len_max)
	{
		if (i < (int)ft_strlen(line))
		{
			if (line[i] == ' ' || line[i] == '\n')
				map[i] = -1;
			else if (line[i] == '0' || line[i] == '1' || line[i] == '3')
				map[i] = line[i] - '0';
			else
				map[i] = line[i];
		}
		else
			map[i] = -1;
		i++;
	}
	return (map);
}

int	**map_copy(t_file file)
{
	int	**map;
	int	i;
	int	j;

	i = 0;
	map = (int **)malloc(sizeof(int *) * file.streak);
	if (!map)
		return (0);
	while (i < file.streak)
	{
		map[i] = (int *)malloc(sizeof(int) * file.len_max);
		i++;
	}
	i = 0;
	while (i < file.streak)
	{
		j = 0;
		while (j < file.len_max)
		{
			map[i][j] = file.map[i][j];
			j++;
		}
		i++;
	}
	return (map);
}

int	verify_file(char *str, t_file *file)
{
	int		fd;
	int		tot;
	int		nb_line;
	char	*line;

	fd = open(str, 0);
	if (fd == -1)
		return (1);
	tot = file->streak + 6;
	if (file->n1)
		tot++;
	if (file->n2)
		tot++;
	if (file->n3)
		tot++;
	line = get_next_line(fd);
	nb_line = 0;
	while (line)
	{
		nb_line++;
		if (!is_present(line, " \n"))
			tot++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (tot != nb_line)
		return (ft_free_file(file, 1));
	return (0);
}

int	verify_player(int **map, t_file *file)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	i = 0;
	while (i < file->streak)
	{
		j = 0;
		while (j < file->len_max)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				file->i = i;
				file->j = j;
				nb++;
			}
			j++;
		}
		i++;
	}
	if (nb != 1)
		return (1);
	return (0);
}

void	map_recursive(int **map, int i, int j, t_file *file)
{
	if (file->flag)
		return ;
	map[i][j] = -3;
	if (i == file->streak || i == 0 || j == file->len_max || j == 0)
	{
		file->flag = 1;
		return ;
	}
	if (map[i][j + 1] == 0 || map[i][j + 1] == 3)
		map_recursive(map, i, j + 1, file);
	if (map[i][j + 1] == -1)
		file->flag = 1;
	if (map[i][j - 1] == 0 || map[i][j - 1] == 3)
		map_recursive(map, i, j - 1, file);
	if (map[i][j - 1] == -1)
		file->flag = 1;
	if (map[i + 1][j] == 0 || map[i + 1][j] == 3)
		map_recursive(map, i + 1, j, file);
	if (map[i + 1][j] == -1)
		file->flag = 1;
	if (map[i - 1][j] == 0 || map[i - 1][j] == 3)
		map_recursive(map, i - 1, j, file);
	if (map[i - 1][j] == -1)
		file->flag = 1;
}
