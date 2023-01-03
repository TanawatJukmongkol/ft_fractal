/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:03:40 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/03 10:08:03 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Standard headers
#include <stdio.h>
#include <stdlib.h>

// X display server headers
#include <X11/X.h>
#include <mlx.h>
#include <mlx_int.h>

typedef struct s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_width;
	int		win_height;
}	t_mlx;

int	mouse_event(int code, int x, int y)
{
	printf("\033[A\33[2KMouseEvent [%d] (%d, %d)\n", code, x, y);
	return (0);
}

int	resize_window(t_mlx *mlx)
{
	XWindowAttributes	attr;

	XGetWindowAttributes((
			(t_xvar *)mlx->mlx_ptr)->display, (
			(t_win_list *)mlx->win_ptr)->window, &attr);
	printf("\033[A\33[2KResized! [%dx%d]\n", attr.width, attr.height);
	mlx->win_width = attr.width;
	mlx->win_height = attr.height;
	return (0);
}

int	close_window(t_mlx *mlx)
{
	printf("Bye bye!\n");
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit(0);
}

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

int	main(void)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr,
			690, 420,
			"ft_fractal");
	mlx_hook(mlx.win_ptr, DestroyNotify, 0L, close_window, &mlx);
	mlx_int_size_limit(&mlx, 620, 350, 0);
	mlx_int_size_limit(&mlx, 1380, 840, 1);
	mlx_hook(mlx.win_ptr, 0, StructureNotifyMask, NULL, &mlx);
	mlx_hook(mlx.win_ptr, ConfigureNotify, 0L, resize_window, &mlx);
	mlx_hook(mlx.win_ptr, ButtonPress, ButtonPressMask, mouse_event, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
