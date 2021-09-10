/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 19:54:15 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/10 17:57:21 by marcos           ###   ########.fr       */
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
	info->someone_died;
	if(argc == 6)
		info->num_of_meals = ft_atoi(argv[5]);
	else
		info->num_of_meals = 0;
	info->philosophers = malloc(sizeof(t_philo) * info->num_philos);
	forks = malloc(sizeof(pthread_mutex_t) * info->num_philos);

	while(i < info->num_philos)
	{
		info->philosophers[i].id = i;
		info->philosophers[i].died = &info->someone_died;
		info->philosophers[i].num_philos = ft_atoi(argv[1]);
		info->philosophers[i].time_to_die = ft_atoi(argv[2]);
		info->philosophers[i].time_to_eat = ft_atoi(argv[3]);
		info->philosophers[i].time_to_sleep = ft_atoi(argv[4]);
		if(argc == 6)
			info->num_of_meals = ft_atoi(argv[5]);
		else
			info->num_of_meals = 0;
		i++;
	}
}
