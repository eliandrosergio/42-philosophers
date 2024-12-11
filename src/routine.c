/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/10 12:00:00 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, char *message)
{
	long int	time_here;

	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->over)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	time_here = current_time_in_ms() - philo->data->start_time;
	printf("%ld %d %s\n", time_here, (philo->id + 1), message);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->aux_lock);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->data->aux_lock);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	philo->last_eat_time = current_time_in_ms();
	philo->eaten_count++;
	if (philo->eaten_count == philo->data->total_eat_count)
		philo->data->finished_eating++;
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->data->aux_lock);
}

void	routine_sleep_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	pthread_mutex_lock(&philo->data->aux_lock);
	ft_usleep(philo->data->time_to_sleep);
	pthread_mutex_unlock(&philo->data->aux_lock);
	print_status(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->aux_lock);
	if (philo->id % 2)
		ft_usleep(1);
	pthread_mutex_unlock(&philo->data->aux_lock);
	while (!(philo->data->over))
	{
		pthread_mutex_lock(&philo->data->aux_lock);
		if (philo->data->over)
		{
			pthread_mutex_unlock(&philo->data->aux_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->aux_lock);
		routine_eat(philo);
		pthread_mutex_lock(&philo->data->aux_lock);
		if (philo->data->num_philos == 1)
		{
			pthread_mutex_unlock(&philo->data->aux_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->aux_lock);
		routine_sleep_think(philo);
	}
	return (NULL);
}
