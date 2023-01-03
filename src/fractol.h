/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:20:41 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/03 19:54:00 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

// Standard headers
# include <X11/Xlib.h>
# include <stdio.h>
# include <stdlib.h>

// X display server headers
# include <X11/X.h>
# include <mlx.h>
# include <mlx_int.h>

typedef struct s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_width;
	int		win_height;
}	t_mlx;

typedef struct s_vars {
	t_mlx			mlx;
	unsigned int	keys;
}	t_vars;

// 0 = no key assigned
enum	e_keydef {
	kdef_mod	= XK_Control_L,
	kdef_up		= XK_w,
	kdef_down	= XK_s,
	kdef_left	= XK_a,
	kdef_right	= XK_d
};

enum	e_keybit {
	kbit_mod	= 0b000000001,
	kbit_up		= 0b000000010,
	kbit_down	= 0b000000100,
	kbit_left	= 0b000001000,
	kbit_right	= 0b000010000
};

// MiniLibX extra functions (reversed engineered by tjukmong)
void	mlx_int_size_limit(t_mlx *mlx, int w, int h, int max);

// Event listeners
int		key_event(int code, t_vars *vars);
int		key_released(int code, t_vars *vars);
int		mouse_event(int code, int x, int y);
int		resize_window(t_vars *vars);
int		close_window(t_vars *vars);

#endif