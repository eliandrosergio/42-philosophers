/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/14 09:21:12 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	even_wait(t_state *state)
{
	if (state->number_of_philosophers % 2 == 1
		&& state->current_philo_id % 2 == 0
		&& state->p_philos[state->current_philo_id].eat_counter > 0)
		usleep(state->time_to_eat / 2 * 1000);
}

void	odd_wait(t_state *state)
{
	if (state->current_philo_id % 2 == 1
		&& state->p_philos[state->current_philo_id].eat_counter == 0)
		usleep(state->time_to_eat / 2 * 1000);
}

void	print_erro(char *msg, int erro)
{
	if (erro)
		printf("Erro\n%s\n", msg);
	else
		printf("%s\n", msg);
}
