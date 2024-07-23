/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:28:02 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/23 17:21:22 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*replace_oc(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = ' ';
		i++;
	}
	return (line);
}

char	*get_color(char *str, char *line, int n[3], t_file *file)
{
	char	**elements;
	char	*elem;
	int		nb_elm;

	elements = ft_split(line, ' ');
	if (!elements)
		return (0);
	nb_elm = ft_free_split(elements, 0);
	if (nb_elm < 2 || ft_strlen(elements[0]) != ft_strlen(str))
	{
		ft_free_split(elements, 1);
		return (0);
	}
	elem = elements[0];
	if (!ft_strncmp(str, elem, ft_strlen(str)))
	{
		elem_color(&elements[1], n, file);
		ft_free_split(elements, 1);
		return (0);
	}
	ft_free_split(elements, 1);
	return (0);
}

int	get_texture(char *str, t_file *file)
{
	int		fd;
	char	*line;

	fd = open(str, 0);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		line = replace_oc(line);
		ft_path(file, line);
		get_color("F", line, file->f, file);
		get_color("C", line, file->c, file);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (ft_color_err(*file))
		return (ft_free_file(file, 1));
	return (0);
}

int	is_present(char *line, char *val)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (val[j])
		{
			if (val[j] == line[i])
				break ;
			j++;
		}
		if (!val[j])
			return (1);
		i++;
	}
	return (0);
}

void	map_print(int **map, t_file *file)
{
	int	i;
	int	j;

	i = 0;
	while (i < file->streak)
	{
		j = 0;
		while (j < file->len_max)
		{
			printf("%d ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
