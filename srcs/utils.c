/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:21:43 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/23 13:24:45 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 5)
		return (1);
	len--;
	if (str[len] == 'b' && str[len - 1] == 'u'
		&& str[len - 2] == 'c' && str[len - 3] == '.')
	{
		return (0);
	}
	return (1);
}

int	opening(char *str)
{
	int	fd;

	fd = open(str, 0);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	ft_free_split(char **splited, int f)
{
	int	i;

	if (!splited)
		return (0);
	i = 0;
	while (splited[i])
	{
		if (f)
			free(splited[i]);
		i++;
	}
	if (f)
		free(splited);
	return (i);
}

char	*get_path(char *str, char *line)
{
	char	**elements;
	char	*elem;
	int		nb_elm;

	elements = ft_split(line, ' ');
	if (!elements)
		return (0);
	nb_elm = ft_free_split(elements, 0);
	if (nb_elm != 2 || ft_strlen(elements[0]) != ft_strlen(str))
	{
		ft_free_split(elements, 1);
		return (0);
	}
	elem = elements[0];
	if (!ft_strncmp(str, elem, ft_strlen(str)))
	{
		elem = ft_strdup(elements[1]);
		ft_free_split(elements, 1);
		return (elem);
	}
	ft_free_split(elements, 1);
	return (0);
}

int	ft_is_onlyd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
