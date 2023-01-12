/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:36:50 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/12 17:21:48 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_point_rgb(t_vars *vars, int x, int y, int ittr)
{
	ft_draw_point(&vars->image, x, y,
		(((ittr * ((vars->colors[2] >> 16) & 0xff))
				/ vars->max_ittr) << 16)
		+ (((ittr * ((vars->colors[2] >> 8) & 0xff))
				/ vars->max_ittr) << 8)
		+ (((ittr * ((vars->colors[2]) & 0xff))
				/ vars->max_ittr)) + (0xff << 24));
}

void	shader_1(t_vars *vars)
{
	t_cmplx	complex;
	int		x;
	int		y;
	int		ittr;
	int		is_in_set;

	x = 0;
	y = 0;
	ft_init_image(vars, &vars->image,
		vars->mlx.win_width, vars->mlx.win_height);
	while (++y < vars->mlx.win_height)
	{
		while (++x < vars->mlx.win_width)
		{
			cartesian_to_cmplx(vars, &complex, &x, &y);
			vars->fractol(&complex, vars->max_ittr, &ittr, &is_in_set);
			if (ittr != vars->max_ittr)
				ft_draw_point(&vars->image, x, y,
					vars->colors[2 + ittr % vars->colors[0]]);
			else
				ft_draw_point(&vars->image, x, y, vars->colors[1]);
		}
		x = 0;
	}
	ft_put_image(&vars->image, 0, 0);
}

void	shader_2(t_vars *vars)
{
	t_cmplx	complex;
	int		x;
	int		y;
	int		ittr;
	int		is_in_set;

	x = 0;
	y = 0;
	ft_init_image(vars, &vars->image,
		vars->mlx.win_width, vars->mlx.win_height);
	while (++y < vars->mlx.win_height)
	{
		while (++x < vars->mlx.win_width)
		{
			cartesian_to_cmplx(vars, &complex, &x, &y);
			vars->fractol(&complex, vars->max_ittr,
				&ittr, &is_in_set);
			if (ittr != vars->max_ittr)
				draw_point_rgb(vars, x , y, ittr);
			else
				ft_draw_point(&vars->image, x, y, vars->colors[1]);
		}
		x = 0;
	}
	ft_put_image(&vars->image, 0, 0);
}
