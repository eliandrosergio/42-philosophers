/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/10 10:28:42 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(t_data *data, int ac, char **av)
{
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->total_eat_count = -1;
	if (ac == 6)
		data->total_eat_count = ft_atoi(av[5]);
	data->over = 0;
	data->finished_eating = 0;
}

void	init_mutex(t_data *data)
{
	int		i;

	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks || !data->philos)
		ft_exit ("Failed to allocate memory", data, 1);
	while (++i < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->aux_lock, NULL);
	data->start_time = current_time_in_ms();
}

void	init_philo(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i;
		data->philos[i].last_eat_time = data->start_time;
		data->philos[i].eaten_count = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = 0;
	}
}

void	init_thread(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].right_fork
			= data->philos[(i + 1) % data->num_philos].left_fork;
		if (pthread_create(&data->philos[i].thread
				, NULL, philo_routine, &data->philos[i]) != 0)
			ft_exit("Failed to create philosopher(s) thread", data, 1);
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
	{
		data->over = 1;
		ft_exit("Failed to create monitoring thread", data, 1);
	}
	pthread_join(monitor, NULL);
}
