/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 15:21:22 by msantos-          #+#    #+#             */
/*   UpÇ¿¨ñlkj¡'dated: 2021/07/20 15:25
/*	- 0:27 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

int	arg_validation(char **argv)
{
	int i;

	i = 0;
	while(argv[i])
	{
		if(str_isnumber(argv[i]))
			return (0);
		i++;
	}
	return (0);
	
}

int	arg_save(t_info *info,int argc, char **argv)
{
	info->num_philos = argc;
	info->time_to_eat = argv[3];
	info->time_to_sleep = argv[4];
	if(argc == 6)
		info->num_of_meals = argv[5];
}
