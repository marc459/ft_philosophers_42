/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:14:04 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/18 17:20:14 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	hasthephilosate(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		if (info->philos[i].num_of_meals != 0)
			return (0);
		i++;
	}
	info->someone_died = 1;
	return (1);
}

int	isittheendofphilo(t_philo *philo)
{
	if (*philo->died != 1 && philo->num_of_meals != 0)
	{
		if (philo->time_to_die < (start_clock() - philo->starving_time))
		{
			printf ("%llu ms :: %s Philo %d died%s\n",
				start_clock() - philo->start, RED, philo->id + 1, RESET_COLOR);
			*philo->died = 1;
			return (1);
		}
	}
	return (0);
}

void	*philo_doroutine(void *arg_philo)
{
	t_philo			*philo;
	struct timeval	current_time;

	philo = (t_philo *)arg_philo;
	if (philo->id % 2 != 0)
		ft_usleep(10);
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
	while (info->someone_died != 1)
	{
		hasthephilosate(info);
		i = 0;
		while (i < info->num_philos)
		{
			isittheendofphilo(&info->philos[i]);
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

void	anyleaks()
{
	system("leaks philo");
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
	freeforall(&info);
	//system("leaks philo");
	return (0);
}
