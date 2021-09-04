/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:32:57 by msantos-          #+#    #+#             */
/*   Updated: 2021/09/04 22:16:20 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

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
typedef struct s_philo{
	int				id;
	pthread_t		thread;
	int				status; // 0 eating, 1 sleeping, 2 thinking
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				starving_time;
	int				num_of_meals;
	pthread_mutex_t	*r_fork; // 0 if not used, 1 if used
	pthread_mutex_t	*l_fork;
	

}				t_philo;

typedef struct s_info{
	int				num_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	t_philo			*philosophers;
	//int				*used_forks;
	//pthread_mutex_t	*mutex;
}				t_info;

pthread_mutex_t *forks;

size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
int			str_error(char *s);
int			ft_atoi(const char *str);
void		ft_usleep(int miliseconds);
int			ft_time(int start);
int			str_isnumber(char *str);
int			arg_validation(char **argv);
void		arg_save(t_info *info,int argc, char **argv);
int			start_clock(void);

#endif