/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:38:55 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/25 01:28:57 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_line_map(t_file *file, char *line)
{
	if (!file->streak && ft_strlen(line) > 1 && !is_present(line, " 1\n"))
	{
		file->len_max = ft_strlen(line);
		file->streak = 1;
	}
	else if (file->streak && ft_strlen(line) > 1 && !is_present(line, " 1\n"))
	{
		if (file->len_max < (int)ft_strlen(line))
			file->len_max = ft_strlen(line);
		file->streak++;
	}
	else if (file->streak && !is_present(line, " 130NSEW\n"))
	{
		if (file->len_max < (int)ft_strlen(line))
			file->len_max = ft_strlen(line);
		file->streak++;
	}
}

int	get_map(char *str, t_file *file)
{
	char	*line;
	int		fd;

	fd = open(str, 0);
	if (fd == -1)
		return (ft_free_file(file, 1));
	line = get_next_line(fd);
	file->streak = 0;
	while (line)
	{
		get_line_map(file, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map_alloc(str, file, file->len_max, file->streak);
	return (0);
}

int	verify_map(t_file *file)
{
	int	**map;

	map = map_copy(*file);
	if (verify_player(map, file))
	{
		ft_free_map(map, file);
		return (ft_free_file(file, 1));
	}
	map_recursive(map, file->i, file->j, file);
	ft_free_map(map, file);
	return (0);
}

void	get_alloc(t_file *file, char *line, int len_max)
{
	static int	streak2;

	if (!streak2 && ft_strlen(line) > 1 && !is_present(line, " 1\n"))
	{
		file->map[streak2] = map_line(line, len_max);
		streak2 = 1;
	}
	else if (streak2 && ft_strlen(line) > 1 && !is_present(line, " 1\n"))
	{
		file->map[streak2] = map_line(line, len_max);
		streak2++;
	}
	else if (streak2 && !is_present(line, " 103NSEW\n"))
	{
		file->map[streak2] = map_line(line, len_max);
		streak2++;
	}
}

void	map_alloc(char *str, t_file *file, int len_max, int streak)
{
	char	*line;
	int		fd;

	fd = open(str, 0);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	file->map = (int **)malloc(sizeof(int *) * (streak));
	while (line)
	{
		get_alloc(file, line, len_max);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
