/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 19:54:15 by msantos-          #+#    #+#             */
/*   Updated: 2021/07/22 19:39:28 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
/*
typedef struct s_info{
	int			num_philos;
	
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_meals;
	t_philo		*philosophers;
}				t_info;

typedef struct s_philo{
	int				id;
	int				status; // 0 eating, 1 sleeping, 2 thinking
	int				time_to_die;
	int				r_fork; // 0 if not used, 1 if used
	int				l_fork;
}				t_philo;
*/

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
	if(argc == 6)
		info->num_of_meals = ft_atoi(argv[5]);
	else
		info->num_of_meals = 0;
	info->philosophers = malloc(sizeof(t_philo) * info->num_philos);
	info->used_forks = malloc(sizeof(int) * info->num_philos);


	while(i < info->num_philos)
	{
		info->philosophers[i].id = i;
		info->philosophers[i].status = -1;
		info->philosophers[i].time_to_die = ft_atoi(argv[2]);
		i++;
	}
	//printf("info->num_philos %d\ninfo->time_to_eat %d\ninfo->time_to_sleep %d\ninfo->num_of_meals %d\n",info->num_philos,info->time_to_eat, info->time_to_sleep,info->num_of_meals);
}
