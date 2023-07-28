#ifndef SO_LONG_H
# define SO_LONG_H
# include "../lib/libft/libft.h"
# include <string.h>
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <time.h>
# define SCAN_LEFT 1 
# define SCAN_UP 2 
# define SCAN_RIGHT 3 
# define SCAN_DOWN 4 
# define COIN 'C'
# define V_COIN 'c'
# define BAD 'B'
# define M_BAD 'b'
# define EXIT 'E'
# define PATH '0'
# define V_PATH 'o'
# define PLAY 'P'
# define WALL '1'
# define BITS 32

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	*map;
	char	*img;
	char 	r_bad;
	int 	error[18];
    int		catch;
    int		fd;
	int 	c_coin;
	int 	s_coin;
	int 	c_exit;
	int 	s_exit;
	int 	c_play;
	int 	n_play;
	int 	p_play;
	int		map_len;
	int 	moves;
	int 	width;
	int 	t_width;
	int 	time;
	t_img	bad;
	t_img	coin;
	t_img	exit;
	t_img	path;
	t_img   wall;
	t_img	player;
}	t_data;

int		close_hook(t_data *data);

int		key_hook(int key, t_data *data);

int		render(t_data *data, int i);

void	clean_data(t_data *data);

void	load_assets(t_data *data);

void	perror_map_validate(t_data *data);

void	print_moves(t_data *data);

#endif