/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/10 10:28:57 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	all_finished_eating(t_data *data, int i, int finished_eating)
{
	i = -1;
	finished_eating = 0;
	while (++i < data->num_philos)
	{
		if (data->philos[i].meals_eaten == data->must_eat_count)
			finished_eating++;
	}
	if (finished_eating == data->num_philos)
	{
		data->over = 1;
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	return (0);
}

int	monitor_aux(t_data *data, int i)
{
	if (data->over)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	i = -1;
	while (++i < data->num_philos)
	{
		if (current_time_in_ms() - data->philos[i].last_meal_time
			>= data->time_to_die)
		{
			print_status(&data->philos[i], DIE);
			data->over = 1;
			pthread_mutex_unlock(&data->death_lock);
			return (1);
		}
	}
	if (all_finished_eating(data, 0, 0))
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)arg;
	while (!(data->over))
	{
		pthread_mutex_lock(&data->death_lock);
		if (monitor_aux(data, i))
			return (NULL);
		pthread_mutex_unlock(&data->death_lock);
		ft_usleep(1);
	}
	return (NULL);
}
