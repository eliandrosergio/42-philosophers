/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/10 12:00:00 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	all_finished_eating(t_data *data)
{
	int	is_done;

	pthread_mutex_lock(&data->aux_lock);
	is_done = (data->finished_eating == data->num_philos);
	if (is_done)
		data->over = 1;
	pthread_mutex_unlock(&data->aux_lock);
	return (is_done);
}

int	monitor_aux(t_data *data, int i, long int time_here)
{
	pthread_mutex_lock(&data->aux_lock);
	if (data->over)
	{
		pthread_mutex_unlock(&data->aux_lock);
		return (1);
	}
	i = -1;
	while (++i < data->num_philos)
	{
		time_here = current_time_in_ms() - data->philos[i].last_eat_time;
		if (time_here >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->aux_lock);
			print_status(&data->philos[i], "died");
			pthread_mutex_lock(&data->aux_lock);
			data->over = 1;
			pthread_mutex_unlock(&data->aux_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&data->aux_lock);
	if (all_finished_eating(data))
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->aux_lock);
	while (!(data->over))
	{
		pthread_mutex_unlock(&data->aux_lock);
		if (monitor_aux(data, 0, 0))
			return (NULL);
		ft_usleep(1);
	}
	pthread_mutex_unlock(&data->aux_lock);
	return (NULL);
}
