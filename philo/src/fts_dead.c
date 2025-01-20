/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_dead.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/14 09:21:12 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead_flag(t_state *state)
{
	pthread_mutex_lock(&state->p_dead->mutex);
	if (state->p_dead->dead == 1)
	{
		pthread_mutex_unlock(&state->p_dead->mutex);
		return (1);
	}
	return (0);
}

int	am_i_dead(t_state *state, struct timeval *tv)
{
	if (((long long)tv->tv_sec * 1000000LL + (long long)tv->tv_usec)
		- state->p_philos[state->current_philo_id].last_meal
		> (long long)state->time_to_die * (long long)1000)
		return (1);
	return (0);
}
