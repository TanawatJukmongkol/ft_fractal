/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:03:40 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/04 02:52:33 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Program shortcuts:
		[ Arrow key ] (any combination): Pans the camera
		[ Ctrl ] [ Up / down ] or [ Scroll ]: Zoom in / out
		[ Ctrl ] [ Shift ] [ Up / down ]: Change color scheme
		[ Esc ]: Exit application

	Or change the shortcuts defined in e_keydef at fractol.h!
*/


#include "fractol.h"
#include <X11/X.h>
#include <mlx.h>

int	loop(t_vars	*vars)
{
	// TODO: Draw a circle
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx.mlx_ptr = mlx_init();
	vars.mlx.win_ptr = mlx_new_window(vars.mlx.mlx_ptr, 690, 420, "ft_fractal");
	vars.keys = 0;
	vars.cam.x = 0;
	vars.cam.y = 0;
	vars.cam.zoom = 1;
	mlx_int_size_limit(&vars.mlx, 620, 350, 0);
	mlx_int_size_limit(&vars.mlx, 1380, 840, 1);
	mlx_hook(vars.mlx.win_ptr, DestroyNotify, 0L, close_window, &vars);
	mlx_hook(vars.mlx.win_ptr, 0, StructureNotifyMask, NULL, &vars);
	mlx_hook(vars.mlx.win_ptr, ConfigureNotify, 0L, resize_window, &vars);
	mlx_hook(vars.mlx.win_ptr, ButtonPress, ButtonPressMask, mouse_event,
		&vars);
	mlx_hook(vars.mlx.win_ptr, KeyPress, KeyPressMask, key_event, &vars);
	mlx_hook(vars.mlx.win_ptr, KeyRelease, KeyReleaseMask, key_released, &vars);
	mlx_loop_hook(vars.mlx.mlx_ptr, loop, &vars);
	mlx_loop(vars.mlx.mlx_ptr);
	return (0);
}
