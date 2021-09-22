/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:32:57 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/22 20:18:09 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define PURPLE "\033[0;35m"
# define RESET_COLOR "\033[0;m"

typedef long long unsigned int	uint64_t;

typedef struct s_philo{
	int				id;
	pthread_t		thread;
	int				*died;
	int				num_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		starving_time;
	int				num_of_meals;
	uint64_t		start;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_msg;
}				t_philo;

typedef struct s_info{
	int				num_philos;
	int				someone_died;
	t_philo			*philos;
	pthread_mutex_t	*forkss;
	pthread_mutex_t	print;
}				t_info;

size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
int			str_error(char *s);
int			ft_atoi(const char *str);
void		ft_usleep(int miliseconds);
int			ft_time(int start);
int			str_isnumber(char *str);
int			arg_validation(char **argv);
void		arg_save(t_info *info, int argc, char **argv);
long long	start_clock(void);
void		philo_think(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		freeforall(t_info *info);
void		print_message(t_philo *p, char *message, char *color);

#endif
