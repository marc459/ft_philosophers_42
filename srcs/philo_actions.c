/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:02:16 by marcos            #+#    #+#             */
/*   Updated: 2021/09/17 20:12:02 by msantos-         ###   ########.fr       */
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
			printf("%llu ms :: %sPhilosopher %d picked up his left fork.%s\n",
				start_clock() - p->start, GREEN, p->id + 1, RESET_COLOR);
		}
		if (*p->died != 1)
		{
			pthread_mutex_lock(p->l_fork);
			p->starving_time = start_clock();
			printf("%llu ms :: %sPhilosopher %d picked up his right fork %s\n",
				start_clock() - p->start, GREEN, p->id + 1, RESET_COLOR);
			printf("%llu ms :: %sPhilosopher %d is eating%s\n",
				start_clock() - p->start, CYAN, p->id + 1, RESET_COLOR);
		}
	}
	else
	{
		if (*p->died != 1)
		{
			pthread_mutex_lock(p->l_fork);
			printf("%llu ms :: %sPhilosopher %d picked up his left fork.%s\n",
				start_clock() - p->start, GREEN, p->id + 1, RESET_COLOR);
		}
		if (*p->died != 1)
		{
			pthread_mutex_lock(p->r_fork);
			p->starving_time = start_clock();
			printf("%llu ms :: %sPhilosopher %d picked up his right fork %s\n",
				start_clock() - p->start, GREEN, p->id + 1, RESET_COLOR);
			printf("%llu ms :: %sPhilosopher %d is eating%s\n",
				start_clock() - p->start, CYAN, p->id + 1, RESET_COLOR);
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
		printf("%llu ms :: %sPhilosopher %d is sleeping %s\n",
			start_clock() - p->start, YELLOW, p->id + 1, RESET_COLOR);
		ft_usleep(p->time_to_sleep);
	}
}

void	philo_think(t_philo *p)
{
	if (*p->died != 1)
		printf("%llu ms :: %sPhilosopher %d is thinking %s\n",
			start_clock() - p->start, PURPLE, p->id + 1, RESET_COLOR);
}
