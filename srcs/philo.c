/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:14:04 by msantos-          #+#    #+#             */
/*   Updated: 2021/07/26 20:47:31 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philo_doroutine(void *arg_philo)
{

	t_philo *philo = (t_philo *)arg_philo;
	struct timeval current_time;
	int time;

	time = 0;
	while(1)
	{
		// FORK DEFINITION
		philo->l_fork = &forks[philo->id];
		philo->r_fork = &forks[1];
		if(philo->id == (philo->num_philos - 1))
		{
			philo->r_fork = &forks[0];
		}
		else
			philo->r_fork = &forks[philo->id + 1];
		//printf("%d lf %p rf %p\n",philo->id + 1,philo->l_fork, philo->r_fork);
		

		pthread_mutex_lock(philo->l_fork);
		printf("%d ms :: %sPhilosopher %d picked up his left fork.%s\n",time,  GREEN, philo->id + 1, RESET_COLOR);
		pthread_mutex_lock(philo->r_fork);
		printf("%d ms :: %sPhilosopher %d picked up his right fork %s\n",time,  GREEN, philo->id + 1, RESET_COLOR);
		printf("%d ms :: %sPhilosopher %d is eating%s\n",time, CYAN, philo->id + 1, RESET_COLOR);

		/*TIME TO EAT*/
		/*if (philo->id == (philo->num_philos - 1))
		{
			pthread_mutex_lock(philo->r_fork);
			printf("%sPhilosopher %d picked up his right fork.%s\n", GREEN, philo->id + 1, RESET_COLOR);
			pthread_mutex_lock(philo->l_fork);
			printf("%sPhilosopher %d picked up his left fork%s\n",  GREEN, philo->id + 1, RESET_COLOR);
			printf("%sPhilosopher %d is eating%s\n", CYAN, philo->id + 1, RESET_COLOR);
			
		}
		else
		{
			pthread_mutex_lock(philo->l_fork);
			printf("%sPhilosopher %d picked up his left fork.%s\n",  GREEN, philo->id + 1, RESET_COLOR);
			pthread_mutex_lock(philo->r_fork);
			printf("%sPhilosopher %d picked up his right fork %s\n",  GREEN, philo->id + 1, RESET_COLOR);
			printf("%sPhilosopher %d is eating%s\n", CYAN, philo->id + 1, RESET_COLOR);
		}*/
		usleep(philo->time_to_eat);
		time += philo->time_to_eat;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		printf("%d ms :: %sPhilosopher %d is done eating and has released his forks.%s\n",time ,GREEN, philo->id + 1, RESET_COLOR);
		
		/*TIME TO SLEEP*/
		gettimeofday(&current_time, NULL);
		printf("%d ms :: %sPhilosopher %d is sleeping %s\n",time , YELLOW, philo->id + 1, RESET_COLOR);
		philo->starving_time = current_time.tv_usec;
		usleep(philo->time_to_sleep);
		time += philo->time_to_sleep;
		gettimeofday(&current_time, NULL);
		if(philo->time_to_die < current_time.tv_usec - philo->starving_time)
		{
			printf("%d ms :: %s Philosopher %d died%s\n",time ,RED, philo->id + 1, RESET_COLOR);
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