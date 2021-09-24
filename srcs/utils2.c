/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 15:21:21 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/24 18:57:49 by msantos-         ###   ########.fr       */
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

long	ft_atol(const char *str)
{
	unsigned int	i;
	int				minus;
	long			value;

	value = 0;
	minus = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		minus++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	while (str[i] <= 57 && str[i] >= 48)
	{
		value *= 10;
		value += str[i] - '0';
		i++;
	}
	if (minus == 1)
		value = value * -1;
	return (value);
}