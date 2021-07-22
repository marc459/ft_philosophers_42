/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:14:04 by msantos-          #+#    #+#             */
/*   Updated: 2021/07/22 22:26:38 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

pthread_mutex_t forks[10] = {0,0,0,0,0,0,0,0,0,0};

void	*philo_doroutine(void *arg_philo)
{
	t_philo *philo = (t_philo *)arg_philo;
	struct timeval current_time;
	int time;
  	
	//printf("Starting routine philo Nº %d\n", philo1->id);
	//printf("seconds : %ld\nmicro seconds : %ld\n\n", current_time.tv_sec, current_time.tv_usec);
	//printf("seconds : %ld\nmicro seconds : %ld\n\n", current_time.tv_sec, current_time.tv_usec);

	pthread_mutex_t *left_fork = &forks[philo->id];
	pthread_mutex_t *right_fork;
	if(philo->id == philo->num_philos - 1)
		right_fork = &forks[philo->id + 1];
	else
		right_fork = &forks[0];

	pthread_mutex_lock(left_fork);
	printf("Philosopher %d picked up his left fork.\n", philo->id + 1);
	pthread_mutex_lock(right_fork);
	printf("Philosopher %d picked up his right fork and started eating.\n", philo->id + 1);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	printf("Philosopher %d is done eating and has released his forks.\n", philo->id + 1);


	/*TESTING GET OF TIME*/
	gettimeofday(&current_time, NULL);
	printf("cu->%d\n",current_time.tv_usec);
	time = current_time.tv_usec;
	usleep(900);
	gettimeofday(&current_time, NULL);
	printf("pu->%d\n",current_time.tv_usec);
	printf("how many time passed? %d\n",current_time.tv_usec - time);
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