/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:14:04 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/12 22:29:13 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int		hasthephilosate(t_info *info){
	int i;

	i = 0;
	while(i < info->num_philos)
	{
		if (info->philosophers[i].num_of_meals != 0)
			return (0);
		i++;
	}

	return (1);
}

int		isittheendofphilo(t_philo *philo)
{
	//printf("%d time: %llu last meal at: %llu, time_to_die: %llu\n",philo->id + 1,start_clock() - philo->start, philo->starving_time - philo->start, philo->time_to_die);
	if(*philo->died != 1 && philo->num_of_meals != 0)
	{
		
		if(philo->time_to_die < (start_clock() - philo->starving_time))
		{
		//	printf("%d time: %llu last meal at: %llu, time_to_die: %llu\n",philo->id + 1,start_clock() - philo->start, philo->starving_time - philo->start, philo->time_to_die);
			printf("%llu ms :: %s Philosopher %d died%s\n",(uint64_t)(start_clock() - philo->start) ,RED, philo->id + 1, RESET_COLOR);
			*philo->died = 1;
			return(1);
		}
	}
	return (0);
}

void	*philo_doroutine(void *arg_philo)
{

	t_philo *philo = (t_philo *)arg_philo;
	struct timeval current_time;
	int time;
	int i;

	i = 0;
	
	if(philo->id % 2 != 0)
		ft_usleep(10);
	while(*philo->died != 1)
	{
		// FORK DEFINITION
		philo->l_fork = &forks[philo->id];
		//philo->r_fork = &forks[1];
		if(philo->id == (philo->num_philos - 1))
			philo->r_fork = &forks[0];
		else
			philo->r_fork = &forks[philo->id + 1];

		/*TIME TO EAT*/
		if (philo->id == (philo->num_philos - 1))
		{
			if(*philo->died != 1)
			{
				pthread_mutex_lock(philo->r_fork);
				printf("%llu ms :: %sPhilosopher %d picked up his left fork.%s\n",(uint64_t)(start_clock() - philo->start),  GREEN, philo->id + 1, RESET_COLOR);
			}
			if(*philo->died != 1)
			{
				pthread_mutex_lock(philo->l_fork);
				philo->starving_time = start_clock();
				printf("%llu ms :: %sPhilosopher %d picked up his right fork %s\n",(uint64_t)(start_clock() - philo->start),  GREEN, philo->id + 1, RESET_COLOR);
				printf("%llu ms :: %sPhilosopher %d is eating%s\n",(uint64_t)(start_clock() - philo->start), CYAN, philo->id + 1, RESET_COLOR);
			}
		}
		else
		{
			if(*philo->died != 1)
			{
				pthread_mutex_lock(philo->l_fork);
				printf("%llu ms :: %sPhilosopher %d picked up his left fork.%s\n",start_clock() - philo->start,  GREEN, philo->id + 1, RESET_COLOR);
			}
			if(*philo->died != 1)
			{
				pthread_mutex_lock(philo->r_fork);
				philo->starving_time = start_clock();
				printf("%llu ms :: %sPhilosopher %d picked up his right fork %s\n",start_clock() - philo->start,  GREEN, philo->id + 1, RESET_COLOR);
				printf("%llu ms :: %sPhilosopher %d is eating%s\n",start_clock() - philo->start, CYAN, philo->id + 1, RESET_COLOR);
			}
		}
		usleep(philo->time_to_eat);
		//ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		philo->num_of_meals--;
		if(philo->num_of_meals == 0)
			return(NULL);
		
		/*TIME TO SLEEP*/
		if(*philo->died != 1)
		{
			printf("%llu ms :: %sPhilosopher %d is sleeping %s\n",start_clock() - philo->start, YELLOW, philo->id + 1, RESET_COLOR);
			ft_usleep(philo->time_to_sleep);
		}
		/*TIME TO THINK*/
		if(*philo->died != 1)
			printf("%llu ms :: %sPhilosopher %d is thinking %s\n",start_clock() - philo->start, PURPLE, philo->id + 1, RESET_COLOR);
	}
	return(NULL);
}

int		philo_meeting(t_info *info)
{
	int i;

	i = 0;
	while(i < info->num_philos)
	{
		pthread_create(&info->philosophers[i].thread, NULL, philo_doroutine, &info->philosophers[i]);
		i++;
	}

	while(info->someone_died != 1)
	{
		if(hasthephilosate(info) == 1)
			return(0);

		i = 0;
		while(i < info->num_philos)
		{
			if (isittheendofphilo(&info->philosophers[i]) == 1)
				return (0);
			i++;
		}
	}
	i = 0;
	while(i < info->num_philos)
	{
		pthread_join(info->philosophers[i].thread, NULL);
		i++;
	}
	return(1);
}

int main(int argc, char **argv)
{
	t_info info;
	
	if(argc != 6 && argc != 5)
		return(str_error("Error: \n Usage: ./philo num_philos  time_to_die  time_to_eat  time_to_sleep  [num_of_meals]"));
	if (!arg_validation(argv))
		return(str_error("Error: \n Incorrect arguments\n"));
	arg_save(&info ,argc, argv);
	philo_meeting(&info);
	return (0);
	
}