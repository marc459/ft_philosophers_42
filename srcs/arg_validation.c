/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 19:54:15 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/17 16:35:12 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	arg_validation(char **argv)
{
	int i;

	i = 1;
	while(argv[i])
	{
		if(!str_isnumber(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	arg_save(t_info *info,int argc, char **argv)
{
	int i;

	i = 0;
	info->num_philos = ft_atoi(argv[1]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->someone_died = 0;
	if(argc == 6)
		info->num_of_meals = ft_atoi(argv[5]);
	else
		info->num_of_meals = -1;
	info->philosophers = malloc(sizeof(t_philo) * info->num_philos);
	info->forkss = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	while(i < info->num_philos)
	{
		info->philosophers[i].id = i;
		info->philosophers[i].died = &info->someone_died;
		info->philosophers[i].num_philos = ft_atoi(argv[1]);
		info->philosophers[i].time_to_die = ft_atoi(argv[2]);
		info->philosophers[i].time_to_eat = ft_atoi(argv[3]);
		info->philosophers[i].time_to_sleep = ft_atoi(argv[4]);
		info->philosophers[i].start = start_clock();
	    info->philosophers[i].starving_time = start_clock();
		if(argc == 6)
			info->philosophers[i].num_of_meals = ft_atoi(argv[5]);
		else
			info->philosophers[i].num_of_meals = -1;

		info->philosophers[i].l_fork =  &info->forkss[info->philosophers[i].id];
		if(info->philosophers[i].id == (info->philosophers[i].num_philos - 1))
			info->philosophers[i].r_fork = &info->forkss[0];
		else
			info->philosophers[i].r_fork = &info->forkss[info->philosophers[i].id + 1];
		i++;
	}
}
