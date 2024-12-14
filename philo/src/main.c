/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/14 09:21:12 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	cleanup(t_state *state, pthread_t *philo_threads)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		pthread_mutex_destroy(&state->p_philos[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&state->p_dead->mutex);
	free(state->p_philos);
	free(state->p_forks);
	free(state->p_dead);
	free(state);
	free(philo_threads);
}

int	init(t_state *state, int ac, char **av)
{
	if (init_arguments(state, ac, av) == -1 || init_structs(state) == -1)
		return (-1);
	if (init_fork_mutexes(state) == -1)
		return (-1);
	if (init_philo_mutexes(state) == -1)
		return (-1);
	if (init_dead_mutex(state) == -1)
		return (-1);
	return (1);
}

int	main(int ac, char **av)
{
	t_state		*state;
	pthread_t	*philo_threads;

	if (args_check(ac, av) == -1)
		return (-1);
	state = (t_state *) malloc(ft_atoi(av[1]) * sizeof(t_state));
	if (state == NULL)
		return (print_erro("malloc of state failed.", 1), -1);
	if (init(state, ac, av) == -1)
		return (-1);
	if (init_threads(state, &philo_threads) == -1)
		return (-1);
	if (create_threads(state, philo_threads) == -1)
		return (-1);
	while (is_program_end(state) == 0)
	{
		ft_wait(9000);
	}
	wait_for_threads(state, philo_threads);
	cleanup(state, philo_threads);
	return (0);
}
