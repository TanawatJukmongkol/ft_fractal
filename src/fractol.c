/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:03:40 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/19 04:18:47 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//////////////////////////////////////////////////////////////////////
//	Program shortcuts:												//
//		[ Arrow keys ]: Pans the camera								//
//		[ Ctrl ] [ up / down ]										//
//			or														//
//		[ Ctrl ] [ scroll ]: Zoom in / out (locked to center).		//
//		[ Scroll ]: zoom in / out (follows the curser)				//
//		[ Ctrl ] [ shift ] [ up / down ]: Change color scheme		//
//		[ Ctrl ] [ shift ] [ left / right ]: Change fractal shader	//
//		[ Ctrl ] [ O ]: Go back to origin (0, 0).					//
//		[ Esc ]: Exit application									//
//																	//
//	Or change the shortcuts defined in e_keydef at fractol.h!		//
//////////////////////////////////////////////////////////////////////

#include "fractol.h"

int	loop(t_vars *vars)
{
	int	count;

	count = 0;
	if (!vars->image.ptr)
		return (0);
	if (vars->draw_ittr < 64 * 8)
	{
		while (count < 9)
		{
			vars->update(vars, vars->draw_ittr % 64);
			vars->draw_ittr += (count + vars->draw_offset) % 8;
			count++;
		}
		vars->draw_offset = (vars->draw_offset + 1) % 8;
	}
	return (0);
}

void	init_vars(t_vars *vars)
{
	vars->mlx.mlx_ptr = mlx_init();
	if (!vars->mlx.mlx_ptr)
		mlx_error(vars, "Failed to initialize MLX.");
	vars->mlx.win_ptr = mlx_new_window(vars->mlx.mlx_ptr, 400, 400,
			"ft_fractal");
	if (!vars->mlx.mlx_ptr)
		mlx_error(vars, "Failed to initialize MLX window.");
	vars->keys = 0;
	vars->cam.x = 0;
	vars->cam.y = 0;
	vars->cam.zoom = 1;
	vars->image.ptr = NULL;
	vars->max_ittr = 142;
	vars->draw_ittr = 0;
	vars->draw_offset = 5;
	vars->scheme = 0;
	vars->scheme_len = 2;
	vars->colors = vars->schemes[vars->scheme];
	vars->renderer = 0;
	vars->renderer_len = 1;
	vars->update = vars->renderers[vars->renderer];
	vars->init_cmplx.im = -0.4;
	vars->init_cmplx.re = 0.6;
	vars->fractol = &mandelbrot_set;
}

void	init_program(t_vars *vars, int argc, char *argv[])
{
	mlx_int_size_limit(&vars->mlx, 400, 400, 0);
	mlx_int_size_limit(&vars->mlx, 800, 800, 1);
	if (argc < 2)
	{
		ft_putstr_fd("No argument passed\nManual: \n", 1);
		ft_putstr_fd(" fractals [fractal 0 - 2] [*real] [*imaginary]\n", 1);
		close_window(vars);
	}
	if (ft_atoi(argv[1]) == 0)
		vars->fractol = &mandelbrot_set;
	else if (ft_atoi(argv[1]) == 1)
	{
		vars->fractol = &julia_set;
		if (!argv[2] || !argv[3])
			return ;
		vars->init_cmplx.im = (float)ft_atoi(argv[2]) / 1000;
		vars->init_cmplx.re = (float)ft_atoi(argv[3]) / 1000;
	}
	else if (ft_atoi(argv[1]) == 2)
		vars->fractol = &burning_ship;
	else
		mlx_error(vars, "invalid fractal argument");
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	vars.schemes[0] = (int [5]){3, 0xffbababa,
		0xff424242, 0xff242424, 0xff121212};
	vars.schemes[1] = (int [9]){7, 0xff000000, 0xffff0000, 0xffffa500,
		0xffffff00, 0xff008000, 0xff0000ff, 0xff4b0082, 0xffee82ee};
	vars.schemes[2] = (int [10]){8, 0xff000d0b, 0xff16d9b5, 0xff008b99,
		0xff4c3c99, 0xffff9019, 0xffff36d0, 0xffaa4fd1, 0xffff5555, 0xfff1fa8c};
	vars.renderers[0] = &shader_1;
	vars.renderers[1] = &shader_2;
	init_vars(&vars);
	init_program(&vars, argc, argv);
	mlx_hook(vars.mlx.win_ptr, DestroyNotify, 0L, close_window, &vars);
	mlx_hook(vars.mlx.win_ptr, 0, StructureNotifyMask, NULL, &vars);
	mlx_hook(vars.mlx.win_ptr, ConfigureNotify, 0L, resize_window, &vars);
	mlx_hook(vars.mlx.win_ptr, ButtonPress, ButtonPressMask, mouse_event,
		&vars);
	mlx_hook(vars.mlx.win_ptr, MotionNotify, Button3MotionMask,
		mouse_event_move, &vars);
	mlx_hook(vars.mlx.win_ptr, KeyPress, KeyPressMask, key_event, &vars);
	mlx_hook(vars.mlx.win_ptr, KeyRelease, KeyReleaseMask, key_released, &vars);
	mlx_loop_hook(vars.mlx.mlx_ptr, loop, &vars);
	mlx_loop(vars.mlx.mlx_ptr);
	return (0);
}
