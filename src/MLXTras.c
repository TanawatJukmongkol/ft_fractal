/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXTras.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:34:07 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/12 14:48:26 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	mlx_int_size_limit(t_mlx *mlx, int w, int h, int max)
{
	XSizeHints	hints;
	long		toto;

	XGetWMNormalHints((
			(t_xvar *)mlx->mlx_ptr)->display, (
			(t_win_list *)mlx->win_ptr)->window, &hints, &toto);
	hints.width = w;
	hints.height = h;
	if (max)
	{
		hints.max_width = w;
		hints.max_height = h;
	}
	else
	{
		hints.min_width = w;
		hints.min_height = h;
	}
	hints.flags = PPosition | PSize | PMinSize | PMaxSize;
	XSetWMNormalHints((
			(t_xvar *)mlx->mlx_ptr)->display, (
			(t_win_list *)mlx->win_ptr)->window, &hints);
}

int	resize_window(t_vars *vars)
{
	XWindowAttributes	attr;

	XGetWindowAttributes((
			(t_xvar *)vars->mlx.mlx_ptr)->display, (
			(t_win_list *)vars->mlx.win_ptr)->window, &attr);
	printf("\033[A\33[2KResized! [%dx%d]\n", attr.width, attr.height);
	vars->mlx.win_width = attr.width;
	vars->mlx.win_height = attr.height;
	vars->mlx.win_ratio = (float)attr.width / attr.height;
	if (vars->image.ptr != NULL)
	{
		mlx_destroy_image(vars->mlx.mlx_ptr, vars->image.ptr);
		vars->image.ptr = NULL;
	}
	vars->update(vars);
	return (0);
}

int	close_window(t_vars *vars)
{
	printf("Bye bye!\n");
	mlx_destroy_image(vars->mlx.mlx_ptr, vars->image.ptr);
	mlx_destroy_window(vars->mlx.mlx_ptr, vars->mlx.win_ptr);
	mlx_destroy_display(vars->mlx.mlx_ptr);
	free(vars->mlx.mlx_ptr);
	exit(0);
}

void	mlx_error(t_vars *vars, char *msg)
{
	perror("MLX error: ");
	perror(msg);
	if (vars->image.ptr)
	{
		mlx_destroy_image(vars->mlx.mlx_ptr, vars->image.ptr);
		perror(">> image ptr destroyed.");
	}
	if (vars->mlx.win_ptr)
	{
		mlx_destroy_window(vars->mlx.mlx_ptr, vars->mlx.win_ptr);
		perror(">> window ptr destroyed.");
	}
	if (vars->mlx.mlx_ptr)
	{
		free(vars->mlx.mlx_ptr);
		perror(">> mlx freed.");
	}
	else {
		perror("mlx failed to initialize.");
	}
	exit(1);
}
