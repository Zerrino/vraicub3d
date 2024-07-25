/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:41:42 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/25 14:21:07 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_texture(t_mlx *mlx, t_texture *texture, char *filename)
{
	texture->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, filename,
			&texture->width, &texture->height);
	if (!texture->img_ptr)
	{
		mlx->flag = 1;
		return ;
	}
	texture->img_data = mlx_get_data_addr(texture->img_ptr,
			&texture->bpp, &texture->size_line, &texture->endian);
	if (!texture->img_ptr)
	{
		mlx->flag = 1;
		return ;
	}
}

int	handle_close(void *param)
{
	t_player	*player;

	player = (t_player *)param;
	ft_free_file(&player->file, 0);
	exit(0);
	return (0);
}

int	set_up(t_file *file, t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (ft_free_file(file, 1));
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!mlx->win_ptr)
		return (ft_free_file(file, 1));
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr,
			&mlx->bpp, &mlx->size_line, &mlx->endian);
	return (0);
}

int	game_run(t_mlx mlx, t_texture textures[4], t_file file, t_player player)
{
	load_texture(&mlx, &textures[0], file.we);
	load_texture(&mlx, &textures[1], file.no);
	load_texture(&mlx, &textures[2], file.ea);
	load_texture(&mlx, &textures[3], file.so);
	if (file.n1)
		load_texture(&mlx, &textures[4], file.n1);
	if (file.n2)
		load_texture(&mlx, &textures[5], file.n2);
	if (file.n3)
		load_texture(&mlx, &textures[6], file.n3);
	if (mlx.flag)
	{
		ft_free_file(&file, 0);
		return (err("error: unable to open xpm file\n"));
	}
	mlx_hook(mlx.win_ptr, 6, 0, mouse_move, &player);
	mlx_hook(mlx.win_ptr, 2, (1), handle_keypress, &player);
	mlx_hook(mlx.win_ptr, 17, (1 << 17), handle_close, &player);
	while (1)
	{
		mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
		mlx.img_data = mlx_get_data_addr(mlx.img_ptr,
				&mlx.bpp, &mlx.size_line, &mlx.endian);
		render_scene(&mlx, &player, textures);
		mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
		map_cub(&player, &mlx);
		mlx_destroy_image(mlx.mlx_ptr, mlx.img_ptr);
		mlx_do_sync(mlx.mlx_ptr);
	}
}

int	main(int argc, char *argv[])
{
	t_mlx		mlx;
	t_player	player;
	t_file		file;
	t_texture	textures[7];

	mlx.flag = 0;
	ft_memset(&file, 0, sizeof(file));
	ft_memset(&player, 0, sizeof(player));
	ft_memset(file.f, -1, sizeof(file.f));
	ft_memset(file.c, -1, sizeof(file.c));
	if (ft_parser(argc, argv, &file))
		return (1);
	player = find_player(file.map, file.streak, file.len_max);
	player.file = file;
	player.time = 0;
	if (set_up(&file, &mlx))
		return (1);
	if (game_run(mlx, textures, file, player))
		return (1);
	return (0);
}
