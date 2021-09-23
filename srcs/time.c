/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:53:02 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/23 18:48:42 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_usleep(int miliseconds)
{
	int	start;

	start = ft_time(0);
	while (ft_time(start) < miliseconds)
	{
		usleep(1);
	}
}

void	ft_usleep2(int miliseconds, int n_philos)
{
	int	start;

	start = start_clock() * 1000;
	miliseconds = 1000 * miliseconds;
	while ((start_clock() * 1000) < (start + miliseconds))
		usleep(n_philos);
}

int	ft_time(int start)
{
	int					current_time;
	struct timeval		aux_clock;

	gettimeofday(&aux_clock, NULL);
	current_time = (int)
		((aux_clock.tv_usec / 1000) + (aux_clock.tv_sec * 1000));
	return (current_time - start);
}

long long	start_clock(void)
{
	struct timeval	aux_clock;

	gettimeofday(&aux_clock, NULL);
	return ((long long)((aux_clock.tv_usec / 1000))
		+ (aux_clock.tv_sec * 1000));
}
