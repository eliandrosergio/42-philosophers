/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/14 09:21:12 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_spmn(const char *str, int *minus)
{
	int		i;

	i = 0;
	while ((str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*minus = 1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nprt)
{
	int	start_n;
	int	minus;
	int	int_res;
	int	i;

	minus = 0;
	start_n = is_spmn (nprt, &minus);
	i = start_n;
	int_res = 0;
	while (nprt[i] >= '0' && nprt[i] <= '9' && nprt[i] != '\0')
		i++;
	i = 0;
	while (nprt[start_n] >= '0' && nprt[start_n] <= '9'
		&& nprt[start_n] != '\0')
	{
		int_res = (int_res * 10) + (nprt[start_n] - 48);
		i++;
		start_n++;
	}
	if (minus == 1)
		int_res = int_res * -1;
	return (int_res);
}

void	ft_wait(long time_to_sleep)
{
	struct timeval	tv;
	long long		time_current;
	long long		time_begin;

	gettimeofday(&tv, NULL);
	time_begin = (long long)tv.tv_sec
		* (long long)1000000 + (long long)tv.tv_usec;
	time_current = time_begin;
	while (time_current - time_begin < time_to_sleep)
	{
		usleep(20);
		gettimeofday(&tv, NULL);
		time_current = (long long)tv.tv_sec
			* (long long)1000000 + (long long)tv.tv_usec;
	}
}

void	print_state_change(char *message, t_state *state)
{
	struct timeval	tv;
	long long		time_stamp;

	gettimeofday(&tv, NULL);
	time_stamp = (long long)tv.tv_sec
		* (long long)1000000 + (long long)tv.tv_usec - state->start_time;
	printf("%lli %i %s\n", time_stamp / 1000,
		state->current_philo_id + 1, message);
	pthread_mutex_unlock(&state->p_dead->mutex);
}
