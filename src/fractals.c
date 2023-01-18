/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:29:28 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/19 04:09:58 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot_set(t_vars *vars, t_cmplx *cmplx_nbr,
	int *ittr, int *is_in_set)
{
	t_cmplx	z0;
	float	z0_re;

	z0.re = 0;
	z0.im = 0;
	*ittr = 0;
	*is_in_set = 0;
	while (*ittr < vars->max_ittr)
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

void	julia_set(t_vars *vars, t_cmplx *cmplx_nbr,
	int *ittr, int *is_in_set)
{
	t_cmplx	z0;
	float	z0_re;

	z0.re = cmplx_nbr->re;
	z0.im = cmplx_nbr->im;
	*ittr = 0;
	*is_in_set = 0;
	while (*ittr < vars->max_ittr)
	{
		z0_re = (z0.re * z0.re) - (z0.im * z0.im) + vars->init_cmplx.im;
		z0.im = (2 * z0.re * z0.im) + vars->init_cmplx.re;
		z0.re = z0_re;
		if ((z0.re * z0.re) + (z0.im * z0.im) > 4)
		{
			*is_in_set = 1;
			break ;
		}
		(*ittr)++;
	}
}

void	burning_ship(t_vars *vars, t_cmplx *cmplx_nbr,
	int *ittr, int *is_in_set)
{
	t_cmplx	z0;
	float	z0_re;

	z0.re = 0;
	z0.im = 0;
	*ittr = 0;
	*is_in_set = 0;
	while (*ittr < vars->max_ittr)
	{
		z0_re = (z0.re * z0.re) - (z0.im * z0.im) + cmplx_nbr->re;
		z0.im = -fabs(2 * z0.re * z0.im) + cmplx_nbr->im;
		z0.re = z0_re;
		if ((z0.re * z0.re) + (z0.im * z0.im) > 4)
		{
			*is_in_set = 1;
			break ;
		}
		(*ittr)++;
	}
}
