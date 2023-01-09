/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:03:40 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/09 19:45:06 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//////////////////////////////////////////////////////////////////////
//	Program shortcuts:												//
//		[ Arrow keys ]: Pans the camera								//
//		[ Ctrl ] [ Up / down ]										//
//			or														//
//		[ Ctrl ] [ Scroll ]: Zoom in / out (locked to center).		//
//		[ Scroll ]: Zoom in / out (follows the curser)				//
//		[ Ctrl ] [ Shift ] [ Up / down ]: Change color scheme		//
//		[ Ctrl ] [ O ]: Go back to origin (0, 0).					//
//		[ Esc ]: Exit application									//
//																	//
//	Or change the shortcuts defined in e_keydef at fractol.h!		//
//////////////////////////////////////////////////////////////////////

#include "fractol.h"
#include <stdlib.h>

// int	loop(t_vars *vars)
// {
// 	t_image	image;

// 	image.ptr = NULL;
// 	ft_init_image(vars, &image, 69, 69);
// 	for (int y = 0; y < 69; ++y) {
// 		for (int x = 0; x < 69; ++x) {
// 			ft_draw_point(&image, x, y, 0xffffff);
// 		}
// 	}
// 	ft_put_image(&image, 69, 69);
// 	ft_put_image(&image, 42, 42);
// 	return (0);
// }

void	update(t_vars *vars)
{
	t_cmplx	complex;
	int		ittr;
	int		is_in_set;

	ft_init_image(vars, &vars->image, vars->mlx.win_width, vars->mlx.win_height);
	for (int y = 0; y < vars->mlx.win_height; y += 1) {
		for (int x = 0; x < vars->mlx.win_width; x += 1) {
			cartesian_to_cmplx(vars, &complex, &x, &y);
			calculate_point(&complex, vars->max_ittr, &ittr, &is_in_set);
			if (ittr != vars->max_ittr)
				ft_draw_point(&vars->image, x, y, vars->colors[2 + ittr % vars->colors[0]]);
			else
				ft_draw_point(&vars->image, x, y, vars->colors[1]);
		}
	}
	ft_put_image(&vars->image, 0, 0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx.mlx_ptr = mlx_init();
	vars.mlx.win_ptr = mlx_new_window(vars.mlx.mlx_ptr, 400, 400, "ft_fractal");
	vars.keys = 0;
	vars.cam.x = 0;
	vars.cam.y = 0;
	vars.cam.zoom = 1;
	vars.image.ptr = NULL;
	vars.update = &update;
	vars.max_ittr = 50;
	vars.schemes[0] = (int [5]){3, 0xffbababa, 0xff424242, 0xff242424, 0xff121212};
	vars.schemes[1] = (int [9]){7, 0xff000000, 0xffff0000, 0xffffa500, 0xffffff00, 0xff008000, 0xff0000ff, 0xff4b0082, 0xffee82ee};
	vars.schemes[2] = (int [5]){3, 0xff000000, 0xff2242a2, 0xff2242b2, 0xff0212c2};
	vars.scheme = 0;
	vars.scheme_len = 2;
	vars.colors = vars.schemes[vars.scheme];
	mlx_int_size_limit(&vars.mlx, 400, 400, 0);
	mlx_int_size_limit(&vars.mlx, 900, 900, 1);
	mlx_hook(vars.mlx.win_ptr, DestroyNotify, 0L, close_window, &vars);
	mlx_hook(vars.mlx.win_ptr, 0, StructureNotifyMask, NULL, &vars);
	mlx_hook(vars.mlx.win_ptr, ConfigureNotify, 0L, resize_window, &vars);
	mlx_hook(vars.mlx.win_ptr, ButtonPress, ButtonPressMask, mouse_event,
		&vars);
	mlx_hook(vars.mlx.win_ptr, KeyPress, KeyPressMask, key_event, &vars);
	mlx_hook(vars.mlx.win_ptr, KeyRelease, KeyReleaseMask, key_released, &vars);
	// mlx_loop_hook(vars.mlx.mlx_ptr, loop, &vars);
	mlx_loop(vars.mlx.mlx_ptr);
	return (0);
}
