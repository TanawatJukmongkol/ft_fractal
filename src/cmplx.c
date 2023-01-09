/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmplx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:24:22 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/09 19:20:06 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	cartesian_to_cmplx(t_vars *vars, t_cmplx *cmplx_nbr, int *x, int *y)
{
	cmplx_nbr->re = (*x - (vars->mlx.win_width >> 1))
		* ((float)4 / vars->mlx.win_width)
		* (vars->mlx.win_ratio / vars->cam.zoom)
		+ vars->cam.x;
	cmplx_nbr->im = -(*y - (vars->mlx.win_height >> 1))
		* ((float)4 / vars->mlx.win_height)
		* (1 / vars->cam.zoom)
		+ vars->cam.y;
}

// void	calculate_point(t_cmplx *cmplx_nbr, int *ittr, int *is_in_set)
// {
// 	t_cmplx	z0;

// 	z0.re = 0;
// 	z0.im = 0;
// 	*ittr = 0;
// 	(*is_in_set) = 1;
// 	while (*ittr < 3)
// 	{
// 		z0.re = (z0.re * z0.re) - (z0.im * z0.im) + cmplx_nbr->re;
// 		z0.im = (z0.re * z0.im) + cmplx_nbr->im;
// 		if ((z0.re * z0.re) + (z0.im * z0.im) > 4)
// 		{
// 			(*is_in_set) = 0;
// 			break ;
// 		}
// 		(*ittr)++;
// 	}
// }

void	calculate_point(t_cmplx *cmplx_nbr, int max_ittr, int *ittr, int *is_in_set)
{
	t_cmplx	z0;
	float	z0_re;

	z0.re = 0;
	z0.im = 0;
	*ittr = 0;
	*is_in_set = 0;
	while (*ittr < max_ittr)
	{
		z0_re = (z0.re * z0.re) - (z0.im * z0.im) + cmplx_nbr->re;
		z0.im = (2 * z0.re * z0.im) + cmplx_nbr->im;
		z0.re = z0_re;
		if ((z0.re * z0.re) + (z0.im * z0.im) > 4)
		{
			*is_in_set = 1;
			break ;
		}
		(*ittr)++;
	}
}