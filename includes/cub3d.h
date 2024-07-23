/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:35:16 by alexafer          #+#    #+#             */
/*   Updated: 2024/07/23 17:19:24 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "../minilibx/mlx.h"
# include "../includes/get_next_line.h"
# include "../libft/libft.h"

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define MAX_DEPTH 16
# define PLAYER_MOVE_SPEED 0.08
# define PLAYER_TURN_SPEED 0.05
# define PLAYER_ROTATE_SPEED 0.05
# define MAX_ITERATIONS 1000
# define BORDER 0.05

typedef struct s_file
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f[3];
	int		c[3];
	int		**map;
	int		len_max;
	int		streak;
	int		flag;
	int		free;
	int		i;
	int		j;
}	t_file;

typedef struct s_player
{
	double	x;
	double	new_x;
	double	y;
	double	new_y;
	double	angle;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	double	wall_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		hit;
	int		tex_x;
	int		texture_index;
	t_file	file;
}	t_player;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		flag;
	int		x;
}	t_mlx;

typedef struct s_texture
{
	void	*img_ptr;
	char	*img_data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
	int		flag;
}	t_texture;

int			ft_parser(int argc, char *argv[], t_file *file);
int			ft_free_file(t_file *file, int x);
int			err(char *str);
int			extension(char *str);
int			opening(char *str);
int			ft_free_split(char **splited, int f);
char		*get_path(char *str, char *line);
int			ft_is_onlyd(char *str);
void		ft_free_map(int **map, t_file *file);
int			ft_free_file(t_file *file, int x);
int			ft_color_err(t_file file);
void		ft_path(t_file *file, char *line);
char		*replace_oc(char *line);
char		*get_color(char *str, char *line, int n[3], t_file *file);
int			get_texture(char *str, t_file *file);
int			is_present(char *line, char *val);
int			verify_map(t_file *file);
void		map_recursive(int **map, int i, int j, t_file *file);
int			verify_player(int **map, t_file *file);
int			**map_copy(t_file file);
int			verify_file(char *str, t_file *file);
int			get_map(char *str, t_file *file);
void		map_alloc(char *str, t_file *file, int len_max, int streak);
int			*map_line(char *line, int len_max);
void		map_print(int **map, t_file *file);
void		elem_color(char **elem, int n[3], t_file *file);
void		draw_wall(t_mlx *mlx, int height,
				t_texture *texture, double texture_x);
void		render_scene(t_mlx *mlx, t_player *player, t_texture textures[4]);
int			ft_rgb(int nb[3]);
void		rendering_wall(t_mlx *mlx, t_player *player, t_texture textures[4]);
void		color_scene(t_mlx *mlx, t_player player);
int			handle_keypress(int key, void *param);
t_player	find_player(int **mapp, int w, int h);

#endif
