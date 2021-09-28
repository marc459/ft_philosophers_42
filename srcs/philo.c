/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:14:04 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/28 17:47:18 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philo_doroutine(void *arg_philo)
{
	t_philo			*philo;

	philo = (t_philo *)arg_philo;
	if ((philo->id + 1) % 2 == 0)
		usleep(300);
	while (*philo->died != 1)
	{
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
	i = 0;
	if (endofmeeting(info))
	{
		while (i < info->num_philos)
		{
			pthread_detach(info->philos[i].thread);
			i++;
		}
	}
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
	threads_destroy(&info);
	freeforall(&info);
	return (0);
}
