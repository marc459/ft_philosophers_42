/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathrelated.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:18:13 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/23 16:34:12 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	hasthephilosate(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		if (info->philos[i].num_of_meals != 0)
			return (0);
		i++;
	}
	info->someone_died = 1;
	return (1);
}

int	isittheendofphilo(t_philo *philo)
{
	if (*philo->died != 1 && philo->num_of_meals != 0)
	{
		if (philo->time_to_die < (start_clock() - philo->starving_time))
		{
			printf ("%llu ms :: %s Philo %d died%s\n",
				start_clock() - philo->start, RED, philo->id + 1, RESET_COLOR);
			*philo->died = 1;
			pthread_detach(philo->thread);
			return (1);
		}
	}
	return (0);
}

void	endofmeeting(t_info *info)
{
	int	i;

	while (info->someone_died != 1)
	{
		hasthephilosate(info);
		i = 0;
		while (i < info->num_philos)
		{
			isittheendofphilo(&info->philos[i]);
			i++;
		}
	}
}
