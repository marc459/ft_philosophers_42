/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:14:04 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/24 18:28:56 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philo_doroutine(void *arg_philo)
{
	t_philo			*philo;
	struct timeval	current_time;

	philo = (t_philo *)arg_philo;
	
	while (*philo->died != 1)
	{
		if (philo->id % 2)
		{
			ft_usleep2(philo->num_philos, 5);
		}
		if(philo->num_philos % 2 != 0 && philo->id  == philo->num_philos -1)
		{
			ft_usleep2(philo->num_philos, 10);
		}
			
		philo_eat(philo);
		if (philo->num_of_meals == 0)
			return (NULL);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	philo_meeting(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		pthread_create(&info->philos[i].thread, NULL,
			philo_doroutine, &info->philos[i]);
		i++;
	}
	endofmeeting(info);
	i = 0;
	while (i < info->num_philos)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 6 && argc != 5)
		return (str_error("Error: \n Incorrect num of params"));
	if (!arg_validation(argv))
		return (str_error("Error: \n Incorrect arguments\n"));
	arg_save(&info, argc, argv);
	philo_meeting(&info);
	threads_destroy(&info, info.num_philos);
	freeforall(&info);
	return (0);
}
