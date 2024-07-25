/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:31:04 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/25 14:24:14 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_rgb(int nb[3])
{
	int	ret;
	int	a;
	int	b;
	int	c;

	a = nb[0] << 1;
	a = a & (a - 1);
	a = a << 15;
	b = nb[1] << 1;
	b = b & (b - 1);
	b = b << 7;
	c = nb[2];
	ret = (((0 | a) | b) | c);
	return (ret);
}

void	elem_next(char **elem, int n[3], char **colors)
{
	int	nb;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (elem[i])
	{
		nb = 0;
		colors = ft_split(elem[i], ',');
		if (!colors)
			return ;
		while (colors[nb])
		{
			if (ft_is_onlyd(colors[nb]))
				n[j] = ft_atoi(colors[nb]);
			else
				n[j] = -1;
			j++;
			nb++;
		}
		ft_free_split(colors, 1);
		i++;
	}
}

void	elem_color(char **elem, int n[3], t_file *file)
{
	char	**colors;
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	while (elem[i])
	{
		colors = ft_split(elem[i], ',');
		if (!colors)
			return ;
		nb += ft_free_split(colors, 1);
		i++;
	}
	if (nb != 3)
	{
		file->flag = 1;
		return ;
	}
	elem_next(elem, n, colors);
	return ;
}

int	ft_parser(int argc, char *argv[], t_file *file)
{
	if (argc != 2)
		return (err("error: usage is "), err(argv[0]),
			err(" <path_to_map.cub>\n"));
	if (extension(argv[1]))
		return (err("error: file is not a .cub\n"));
	if (opening(argv[1]))
		return (err("error: unable to open the file\n"));
	if (get_texture(argv[1], file))
		return (err("error: unable to get the textures\n"));
	if (get_map(argv[1], file))
		return (err("error: unable to get the map\n"));
	if (verify_file(argv[1], file))
		return (err("error: file is bad\n"));
	if (verify_map(file))
		return (err("error: map is bad\n"));
	if (file->flag)
	{
		ft_free_file(file, 0);
		return (err("error: map is not closed or colors\n"));
	}
	return (0);
}
