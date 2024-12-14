/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/14 09:21:12 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_arguments(t_state *state, int ac, char **av)
{
	(*state).number_of_philosophers = ft_atoi(av[1]);
	(*state).time_to_die = ft_atoi(av[2]);
	(*state).time_to_eat = ft_atoi(av[3]);
	(*state).time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*state).number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		(*state).number_of_times_each_philosopher_must_eat = 0;
	return (0);
}

int	init_structs(t_state *state)
{
	(*state).p_philos = (t_philosopher *)
		malloc((state->number_of_philosophers) * sizeof(t_philosopher));
	if ((*state).p_philos == NULL)
		return (print_erro("malloc of p_philos failed.", 1), -1);
	(*state).p_forks = (t_fork *)
		malloc(state->number_of_philosophers * sizeof(t_fork));
	if ((*state).p_forks == NULL)
		return (print_erro("malloc of p_forks failed.", 1), -1);
	(*state).p_dead = (t_dead *)malloc(sizeof(t_dead));
	if ((*state).p_dead == NULL)
		return (print_erro("malloc of p_dead failed.", 1), -1);
	fill_state(state);
	return (0);
}

int	init_fork_mutexes(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		if (pthread_mutex_init(&state->p_forks[i].mutex, NULL) != 0)
		{
			print_erro("mutex init failed.", 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_philo_mutexes(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		if (pthread_mutex_init(&state->p_philos[i].mutex, NULL) != 0)
		{
			print_erro("mutex init failed.", 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_dead_mutex(t_state *state)
{
	if (pthread_mutex_init(&state->p_dead->mutex, NULL) != 0)
	{
		print_erro("mutex init failed.", 1);
		return (-1);
	}
	return (0);
}
