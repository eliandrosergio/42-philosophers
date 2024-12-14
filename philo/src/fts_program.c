/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/14 09:21:12 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_must_eat_reached(t_state *state, int *must_eat_reached)
{
	if (state->number_of_times_each_philosopher_must_eat != 0
		&& *must_eat_reached == 1)
	{
		pthread_mutex_lock(&state->p_dead->mutex);
		state->p_dead->dead = 1;
		pthread_mutex_unlock(&state->p_dead->mutex);
		return (1);
	}
	return (0);
}

static void	set_must_eat_reached(t_state *state, int *must_eat_reached, int i)
{
	if (state->number_of_times_each_philosopher_must_eat != 0
		&& state[i].p_philos[i].eat_counter
		< state->number_of_times_each_philosopher_must_eat)
		*must_eat_reached = 0;
}

static int	is_dead(t_state *state, struct timeval *tv,
	int *must_eat_reached, int i)
{
	long long	time_stamp;

	while (i < state->number_of_philosophers)
	{
		pthread_mutex_lock(&state[i].p_philos[i].mutex);
		gettimeofday(tv, NULL);
		if (((long long)tv->tv_sec * 1000000LL + (long long)tv->tv_usec)
			- state[i].p_philos[i].last_meal
			> (long long)state->time_to_die * (long long)1000)
		{
			pthread_mutex_lock(&state->p_dead->mutex);
			state->p_dead->dead = 1;
			time_stamp = (long long)tv->tv_sec * (long long)1000000
				+ (long long)tv->tv_usec - state->start_time;
			printf("%lli %i died\n",
				time_stamp / 1000, state[i].p_philos[i].id);
			pthread_mutex_unlock(&state->p_dead->mutex);
			pthread_mutex_unlock(&state[i].p_philos[i].mutex);
			return (1);
		}
		set_must_eat_reached(state, must_eat_reached, i);
		pthread_mutex_unlock(&state[i].p_philos[i].mutex);
		i++;
	}
	return (0);
}

int	is_program_end(t_state *state)
{
	int				i;
	struct timeval	tv;
	int				must_eat_reached;

	must_eat_reached = 1;
	i = 0;
	if (is_dead(state, &tv, &must_eat_reached, i) == 1)
		return (1);
	if (is_must_eat_reached(state, &must_eat_reached) == 1)
		return (1);
	return (0);
}
