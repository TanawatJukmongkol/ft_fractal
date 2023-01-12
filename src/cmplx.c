/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmplx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:24:22 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/12 12:29:17 by tjukmong         ###   ########.fr       */
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
