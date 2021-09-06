/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:14:04 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/06 17:12:45 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	isittheendofphilo(t_philo *philo)
{
	printf("%d time: %d last meal at: %d, time_to_die: %d\n",philo->id + 1,start_clock() - philo->start, philo->starving_time - philo->start, philo->time_to_die);
	if(philo->time_to_die < (start_clock() - philo->starving_time))
		{
			printf("%d ms :: %s Philosopher %d died%s\n",start_clock() - philo->start ,RED, philo->id + 1, RESET_COLOR);
			exit(-1);
		}
}

void	*philo_doroutine(void *arg_philo)
{

	t_philo *philo = (t_philo *)arg_philo;
	struct timeval current_time;
	int time;
	int i;

	i = 0;
	philo->start = start_clock();
	philo->starving_time = start_clock();
	//wait half of the philos until the rest get their forks
	if(philo->id % 2 != 0)
		ft_usleep(10);
	/*if(philo->id == 1 || philo->id == 0)
		ft_usleep(10);*/

	while(1)
	{
		// FORK DEFINITION
		philo->l_fork = &forks[philo->id];
		//philo->r_fork = &forks[1];
		if(philo->id == (philo->num_philos - 1))
		{
			philo->r_fork = &forks[0];
		}
		else
			philo->r_fork = &forks[philo->id + 1];
		//printf("%d lf %p rf %p\n",philo->id + 1,philo->l_fork, philo->r_fork);

		/*TIME TO EAT*/
		if (philo->id == (philo->num_philos - 1))
		{

		pthread_mutex_lock(philo->r_fork);
		printf("0 - ");
		isittheendofphilo(philo);
		printf("%d ms :: %sPhilosopher %d picked up his left fork.%s\n",start_clock() - philo->start,  GREEN, philo->id + 1, RESET_COLOR);
		pthread_mutex_lock(philo->l_fork);
		printf("%d ms :: %sPhilosopher %d picked up his right fork %s\n",start_clock() - philo->start,  GREEN, philo->id + 1, RESET_COLOR);
		printf("%d ms :: %sPhilosopher %d is eating%s\n",start_clock() - philo->start, CYAN, philo->id + 1, RESET_COLOR);
			
		}
		else
		{
			pthread_mutex_lock(philo->l_fork);
		printf("%d ms :: %sPhilosopher %d picked up his left fork.%s\n",start_clock() - philo->start,  GREEN, philo->id + 1, RESET_COLOR);
		pthread_mutex_lock(philo->r_fork);
		printf("%d ms :: %sPhilosopher %d picked up his right fork %s\n",start_clock() - philo->start,  GREEN, philo->id + 1, RESET_COLOR);
		printf("%d ms :: %sPhilosopher %d is eating%s\n",start_clock() - philo->start, CYAN, philo->id + 1, RESET_COLOR);
		}
		//usleep(philo->time_to_eat);
		ft_usleep(philo->time_to_eat);
		philo->starving_time = start_clock();
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		printf("1 - ");
		printf("%d ms :: %sPhilosopher %d is done eating and has released his forks.%s\n",start_clock() - philo->start ,GREEN, philo->id + 1, RESET_COLOR);
		isittheendofphilo(philo);
		/*TIME TO SLEEP*/
		printf("%d ms :: %sPhilosopher %d is sleeping %s\n",start_clock() - philo->start, YELLOW, philo->id + 1, RESET_COLOR);
		ft_usleep(philo->time_to_sleep);
		printf("2 - ");
		isittheendofphilo(philo);
		/*TIME TO THINK*/
		printf("%d ms :: %sPhilosopher %d is thinking %s\n",start_clock() - philo->start, PURPLE, philo->id + 1, RESET_COLOR);
		printf("3 - ");
		isittheendofphilo(philo);
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