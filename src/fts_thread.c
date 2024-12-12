/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/12 16:11:36 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	wait_for_threads(t_state *state, pthread_t *philo_threads)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		if (pthread_join(philo_threads[i], NULL) != 0)
		{
			printf("pthread_join failed.\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	create_threads(t_state *state, pthread_t *philo_threads)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		if (pthread_create(&philo_threads[i], NULL,
				(void *(*)(void *))philo_thread, (void *) &state[i]) != 0)
		{
			printf("pthread_create failed.\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_threads(t_state *state, pthread_t	**philo_threads)
{
	*philo_threads = (pthread_t *) malloc(state->number_of_philosophers
			* sizeof(pthread_t));
	if (*philo_threads == NULL)
	{
		printf("malloc of philo_threads failed.\n");
		return (-1);
	}
	return (0);
}

void	*philo_thread(void *arg)
{
	t_state			*state;

	state = (t_state *)arg;
	while (1)
	{
		if (is_dead_flag(state) == 0)
			thinking(state);
		else
			return (NULL);
		if (state->number_of_philosophers == 1)
			return (NULL);
		if (acquire_forks(state) == 0)
			return (NULL);
		if (eating(state) == 1)
			release_forks(state);
		else
			return (NULL);
		if (is_dead_flag(state) == 0)
			print_state_change("is sleeping", state);
		else
			return (NULL);
		ft_wait(state->time_to_sleep * 1000);
	}
	return (NULL);
}
