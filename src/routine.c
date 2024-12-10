/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/10 10:29:04 by efaustin         ###   ########.fr       */
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
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK);
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK);
	philo->last_meal_time = current_time_in_ms();
	print_status(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	routine_sleep_think(t_philo *philo)
{
	print_status(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo, THINK);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_usleep(1);
	while (!(philo->data->over))
	{
		pthread_mutex_lock(&philo->data->death_lock);
		if (philo->data->over)
		{
			pthread_mutex_unlock(&philo->data->death_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->death_lock);
		routine_eat(philo);
		if (philo->data->num_philos == 1)
			return (NULL);
		routine_sleep_think(philo);
	}
	return (NULL);
}
