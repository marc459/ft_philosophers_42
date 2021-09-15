/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:02:16 by marcos            #+#    #+#             */
/*   Updated: 2021/09/15 16:51:14 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_eat(t_philo *philo)
{
	philo->l_fork = &forks[philo->id];
	if(philo->id == (philo->num_philos - 1))
		philo->r_fork = &forks[0];
	else
		philo->r_fork = &forks[philo->id + 1];

	/*TIME TO EAT*/
	if (philo->id == (philo->num_philos - 1))
	{
		if (*philo->died != 1)
		{
			pthread_mutex_lock(philo->r_fork);
			printf("%llu ms :: %sPhilosopher %d picked up his left fork.%s\n",(uint64_t)(start_clock() - philo->start),  GREEN, philo->id + 1, RESET_COLOR);
		}
		if (*philo->died != 1)
		{
			pthread_mutex_lock(philo->l_fork);
			philo->starving_time = start_clock();
			printf("%llu ms :: %sPhilosopher %d picked up his right fork %s\n",(uint64_t)(start_clock() - philo->start),  GREEN, philo->id + 1, RESET_COLOR);
			printf("%llu ms :: %sPhilosopher %d is eating%s\n",(uint64_t)(start_clock() - philo->start), CYAN, philo->id + 1, RESET_COLOR);
		}
	}
	else
	{
		if (*philo->died != 1)
		{
			pthread_mutex_lock(philo->l_fork);
			printf("%llu ms :: %sPhilosopher %d picked up his left fork.%s\n",start_clock() - philo->start,  GREEN, philo->id + 1, RESET_COLOR);
		}
		if (*philo->died != 1)
		{
			pthread_mutex_lock(philo->r_fork);
			philo->starving_time = start_clock();
			printf("%llu ms :: %sPhilosopher %d picked up his right fork %s\n",start_clock() - philo->start,  GREEN, philo->id + 1, RESET_COLOR);
			printf("%llu ms :: %sPhilosopher %d is eating%s\n",start_clock() - philo->start, CYAN, philo->id + 1, RESET_COLOR);
		}
	}
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->num_of_meals--;
	
}
void	philo_sleep(t_philo *philo)
{
	if (*philo->died != 1)
	{
		printf("%llu ms :: %sPhilosopher %d is sleeping %s\n",start_clock() - philo->start, YELLOW, philo->id + 1, RESET_COLOR);
		ft_usleep(philo->time_to_sleep);
	}
}
void	philo_think(t_philo *philo)
{
	if (*philo->died != 1)
		printf("%llu ms :: %sPhilosopher %d is thinking %s\n",start_clock() - philo->start, PURPLE, philo->id + 1, RESET_COLOR);
}