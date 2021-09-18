/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:02:16 by marcos            #+#    #+#             */
/*   Updated: 2021/09/18 20:50:53 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_eat(t_philo *p)
{
	if (p->id == (p->num_philos - 1))
	{
		if (*p->died != 1)
		{
			pthread_mutex_lock(p->r_fork);
			print_message(p, "picked up his right fork", GREEN);
		}
		if (*p->died != 1)
		{
			pthread_mutex_lock(p->l_fork);
			p->starving_time = start_clock();
			print_message(p, "picked up his left fork", GREEN);
			print_message(p, "is eating", CYAN);
		}
	}
	else
	{
		if (*p->died != 1)
		{
			pthread_mutex_lock(p->l_fork);
			print_message(p, "picked up his left fork", GREEN);
		}
		if (*p->died != 1)
		{
			pthread_mutex_lock(p->r_fork);
			p->starving_time = start_clock();
			print_message(p, "picked up his right fork", GREEN);
			print_message(p, "is eating", CYAN);
		}
	}
	ft_usleep(p->time_to_eat);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
	p->num_of_meals--;
}

void	philo_sleep(t_philo *p)
{
	if (*p->died != 1)
	{
		print_message(p, "is sleeping", YELLOW);
		ft_usleep(p->time_to_sleep);
	}
}

void	philo_think(t_philo *p)
{
	if (*p->died != 1)
		print_message(p, "is thinking", PURPLE);
}
