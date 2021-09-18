/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 15:21:21 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/18 20:44:51 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_message(t_philo *p, char *message, char *color)
{
	pthread_mutex_lock(p->print_msg);
	printf("%llu ms :: %s Philosopher %d - %s %s\n",
		start_clock() - p->start, color, p->id + 1, message, RESET_COLOR);
	pthread_mutex_unlock(p->print_msg);
}

void	ft_usleep(int miliseconds)
{
	int	start;

	start = ft_time(0);
	while (ft_time(start) < miliseconds)
	{
		usleep(1);
	}
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

void	freeforall(t_info *info)
{
	free(info->philos);
	free(info->forkss);
}
