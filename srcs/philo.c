/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:14:04 by msantos-          #+#    #+#             */
/*   Updated: 2021/07/22 19:51:08 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philo_doroutine(void *philo)
{
	t_philo *philo1 = (t_philo *)philo;
	struct timeval current_time;
  	gettimeofday(&current_time, NULL);

	printf("Starting routine philo Nº %d\n", philo1->id);
	//printf("seconds : %ld\nmicro seconds : %ld\n\n", current_time.tv_sec, current_time.tv_usec);
	//usleep(600);
	//printf("seconds : %ld\nmicro seconds : %ld\n\n", current_time.tv_sec, current_time.tv_usec);
	return(NULL);
}

void	philo_meeting(t_info *info)
{
	int i;

	i = 0;
	while(i < info->num_philos)
	{
		if(pthread_create(&info->philosophers[i].thread, NULL, philo_doroutine, &info->philosophers[i]) != 0)
			str_error("Error: \n Thread creating error\n");
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