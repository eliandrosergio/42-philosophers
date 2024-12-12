/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/12 16:11:36 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	quire_forks_without_last(t_state *state)
{
	pthread_mutex_lock(&state->p_forks[state->current_philo_id].mutex);
	if (is_dead_flag(state) == 0)
		print_state_change("has taken a fork", state);
	else
	{
		pthread_mutex_unlock(&state->p_forks[state->current_philo_id].mutex);
		return (0);
	}
	pthread_mutex_lock(&state->p_forks[(state->current_philo_id + 1)
		% state->number_of_philosophers].mutex);
	if (is_dead_flag(state) == 0)
		print_state_change("has taken a fork", state);
	else
	{
		pthread_mutex_unlock(&state->p_forks[(state->current_philo_id + 1)
			% state->number_of_philosophers].mutex);
		pthread_mutex_unlock(&state->p_forks[state->current_philo_id].mutex);
		return (0);
	}
	return (1);
}

static int	aquire_forks_last_philo(t_state *state)
{
	pthread_mutex_lock(&state->p_forks[(state->current_philo_id + 1)
		% state->number_of_philosophers].mutex);
	if (is_dead_flag(state) == 0)
		print_state_change("has taken a fork", state);
	else
	{
		pthread_mutex_unlock(&state->p_forks[(state->current_philo_id + 1)
			% state->number_of_philosophers].mutex);
		return (0);
	}
	pthread_mutex_lock(&state->p_forks[state->current_philo_id].mutex);
	if (is_dead_flag(state) == 0)
		print_state_change("has taken a fork", state);
	else
	{
		pthread_mutex_unlock(
			&state->p_forks[state->current_philo_id].mutex);
		pthread_mutex_unlock(&state->p_forks[(state->current_philo_id + 1)
			% state->number_of_philosophers].mutex);
		return (0);
	}
	return (1);
}

void	release_forks(t_state *state)
{
	if (state->current_philo_id + 1 == state->number_of_philosophers)
	{
		pthread_mutex_unlock(&state->p_forks[(state->current_philo_id + 1)
			% state->number_of_philosophers].mutex);
		pthread_mutex_unlock(&state->p_forks[state->current_philo_id].mutex);
	}
	else
	{
		pthread_mutex_unlock(&state->p_forks[state->current_philo_id].mutex);
		pthread_mutex_unlock(&state->p_forks[(state->current_philo_id + 1)
			% state->number_of_philosophers].mutex);
	}
}

int	acquire_forks(t_state *state)
{
	if (state->current_philo_id % 2 == 0)
		return (quire_forks_without_last(state));
	else
		return (aquire_forks_last_philo(state));
}
