/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:14:04 by msantos-          #+#    #+#             */
/*   Updated: 2021/07/24 21:56:31 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philo_doroutine(void *arg_philo)
{

	t_philo *philo = (t_philo *)arg_philo;
	struct timeval current_time;
	while(1)
	{
		// FORK DEFINITION
		philo->l_fork = &forks[philo->id];
		if(philo->id == (philo->num_philos - 1))
			philo->r_fork = &forks[0];
		else
			philo->r_fork = &forks[philo->id + 1];

		/*TIME TO EAT*/
		if (philo->id == (philo->num_philos - 1))
		{
			pthread_mutex_lock(philo->r_fork);
			printf("Philosopher %d picked up his right fork.\n", philo->id + 1);
			pthread_mutex_lock(philo->l_fork);
			printf("Philosopher %d picked up his left fork and started eating.\n", philo->id + 1);
		}
		else
		{
			pthread_mutex_lock(philo->l_fork);
			printf("Philosopher %d picked up his left fork.\n", philo->id + 1);
			pthread_mutex_lock(philo->r_fork);
			printf("Philosopher %d picked up his right fork and started eating.\n", philo->id + 1);
		}
			
			usleep(philo->time_to_eat);
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			printf("Philosopher %d is done eating and has released his forks.\n", philo->id + 1);
		


		/*TIME TO SLEEP*/
		gettimeofday(&current_time, NULL);
		printf("Philosopher %d is sleeping> %ld\n",philo->id + 1, current_time.tv_usec);
		philo->starving_time = current_time.tv_usec;
		usleep(philo->time_to_sleep);
		gettimeofday(&current_time, NULL);
		if(philo->time_to_die < current_time.tv_usec - philo->starving_time)
		{
			printf("Philosopher %d died\n",philo->id + 1);
			exit(-1);
		}
	}
	return(NULL);
}

void	philo_meeting(t_info *info)
{
	int i;

	i = 0;
	while(i < info->num_philos)
	{
		if(pthread_create(&info->philosophers[i].thread, NULL, philo_doroutine, &info->philosophers[i]) != 0)
			str_error("Error: \n While creating thread\n");
		i++;
	}
	i = 0;
	while(i < info->num_philos)
	{
		pthread_join(info->philosophers[i].thread, NULL);
		i++;
	}
	
}

int main(int argc, char **argv)
{
	t_info info;
	
	if(argc != 6 && argc != 5)
		str_error("Error: \n Usage: ./philo num_philos  time_to_die  time_to_eat  time_to_sleep  [num_of_meals]");
	if (!arg_validation(argv))
		str_error("Error: \n Incorrect arguments\n");
	arg_save(&info ,argc, argv);
	
	philo_meeting(&info);
	
	
	return (0);
	
}