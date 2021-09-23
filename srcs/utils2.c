/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 15:21:21 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/23 16:51:32 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_message(t_philo *p, char *message, char *color)
{
	pthread_mutex_lock(p->print_msg);
	printf("%llu ms :: %s Philosopher %d - %s %s\n",
		start_clock() - p->start, color, p->id + 1, message, RESET_COLOR);
	pthread_mutex_unlock(p->print_msg);
}

void	freeforall(t_info *info)
{
	free(info->philos);
	free(info->forkss);
}

void	threads_destroy(t_info *info, int num_of_philo)
{
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(info->forkss);
}
