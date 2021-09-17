/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 19:54:15 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/17 20:08:31 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	arg_validation(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!str_isnumber(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	arg_save(t_info *info, int argc, char **argv)
{
	int	i;

	i = 0;
	info->num_philos = ft_atoi(argv[1]);
	info->someone_died = 0;
	info->philos = malloc(sizeof(t_philo) * info->num_philos);
	info->forkss = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	while (i < info->num_philos)
	{
		info->philos[i].id = i;
		info->philos[i].died = &info->someone_died;
		info->philos[i].num_philos = ft_atoi(argv[1]);
		info->philos[i].time_to_die = ft_atoi(argv[2]);
		info->philos[i].time_to_eat = ft_atoi(argv[3]);
		info->philos[i].time_to_sleep = ft_atoi(argv[4]);
		info->philos[i].start = start_clock();
		info->philos[i].starving_time = start_clock();
		if (argc == 6)
			info->philos[i].num_of_meals = ft_atoi(argv[5]);
		else
			info->philos[i].num_of_meals = -1;
		info->philos[i].l_fork = &info->forkss[info->philos[i].id];
		if (info->philos[i].id == (info->philos[i].num_philos - 1))
			info->philos[i].r_fork = &info->forkss[0];
		else
			info->philos[i].r_fork =
				&info->forkss[info->philos[i].id + 1];
		i++;
	}
}
