/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/12 16:11:36 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	thinking(t_state *state)
{
	print_state_change("is thinking", state);
	odd_wait(state);
	even_wait(state);
}

int	is_dont_start_eating(t_state *state, struct timeval *tv)
{
	if (am_i_dead(state, tv) == 1)
	{
		pthread_mutex_lock(&state->p_dead->mutex);
		state->p_dead->dead = 1;
		pthread_mutex_unlock(&state->p_dead->mutex);
		release_forks(state);
		pthread_mutex_unlock(&state->p_philos[state->current_philo_id].mutex);
		return (1);
	}
	return (0);
}

int	eating(t_state *state)
{
	struct timeval	tv;

	pthread_mutex_lock(&state->p_philos[state->current_philo_id].mutex);
	gettimeofday(&tv, NULL);
	if (is_dont_start_eating(state, &tv) == 1)
		return (0);
	(*state).p_philos[state->current_philo_id].last_meal
		= (long long)tv.tv_sec * (long long)1000000 + (long long)tv.tv_usec;
	if ((*state).p_philos[state->current_philo_id].last_meal - state->start_time
		< state->time_to_eat / 2 * 1000)
		(*state).p_philos[state->current_philo_id].last_meal
			= state->start_time;
	(*state).p_philos[state->current_philo_id].eat_counter++;
	pthread_mutex_unlock(&state->p_philos[state->current_philo_id].mutex);
	if (is_dead_flag(state) == 0)
		print_state_change("is eating", state);
	else
	{
		release_forks(state);
		return (0);
	}
	ft_wait(state->time_to_eat * 1000);
	return (1);
}
