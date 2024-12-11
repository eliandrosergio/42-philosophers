/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/10 10:33:30 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eaten_count;
	long			last_eat_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				over;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_eat_count;
	int				finished_eating;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	aux_lock;
	t_philo			*philos;
}	t_data;

void		ft_usleep(long int time);
void		init_mutex(t_data *data);
void		init_philo(t_data *data);
void		init_thread(t_data *data);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
void		ft_exit(char *str, t_data *data, int i);
void		init_data(t_data *data, int ac, char **av);
void		print_status(t_philo *philo, char *message);

int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			args_check(int ac, char **av);
long int	current_time_in_ms(void);

#endif