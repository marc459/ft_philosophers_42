/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:02:16 by marcos            #+#    #+#             */
/*   Updated: 2021/09/25 22:35:18 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_eat(t_philo *p)
{
	if (*p->died != 1)
	{
		if (p->id == p->num_philos - 1)
		{
			pthread_mutex_lock(p->r_fork);
			print_message(p, "picked up his right fork", GREEN);
			pthread_mutex_lock(p->l_fork);
			print_message(p, "picked up his left fork", GREEN);
		}
		else
		{
			pthread_mutex_lock(p->l_fork);
			print_message(p, "picked up his left fork", GREEN);
			pthread_mutex_lock(p->r_fork);
			print_message(p, "picked up his right fork", GREEN);
		}
	}
	p->starving_time = start_clock();
	print_message(p, "is eating", CYAN);
	ft_usleep2(p->num_philos, p->time_to_eat);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
	p->num_of_meals--;
}

void	philo_sleep(t_philo *p)
{
	if (*p->died != 1)
	{
		print_message(p, "is sleeping", YELLOW);
		ft_usleep2(p->num_philos, p->time_to_sleep);
	}
}

void	philo_think(t_philo *p)
{
	if (*p->died != 1)
		print_message(p, "is thinking", PURPLE);
	//usleep(70);
}
