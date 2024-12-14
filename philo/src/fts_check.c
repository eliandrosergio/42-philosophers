/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/14 09:21:12 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_argerro(int id)
{
	if (id == 1)
		print_erro("Invalid number of philosophers (1 - 200)", 1);
	else if (id == 2)
		print_erro("Invalid number of time_to_die (>= 60)", 1);
	else if (id == 3)
		print_erro("Invalid number of time_to_eat (>= 60)", 1);
	else if (id == 4)
		print_erro("Invalid number of time_to_sleep (>= 60)", 1);
	else if (id == 5)
		print_erro("Invalid number of must_eat_count (>= 1)", 1);
}

int	is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int	check_number(char *str, int id)
{
	if (!is_digits(str))
	{
		print_argerro(id);
		return (0);
	}
	if ((ft_atoi(str) <= 0) || ((id == 1 && (ft_atoi(str) > 200))
			|| ((id == 2 || id == 3 || id == 4) && (ft_atoi(str) < 60))))
	{
		print_argerro(id);
		return (0);
	}
	return (1);
}

int	args_check(int ac, char **av)
{
	int		i;

	if (ac == 5 || ac == 6)
	{
		i = 1;
		while (i < ac && check_number(av[i], i))
			i++;
		if (i != ac)
			return (-1);
		return (0);
	}
	print_erro("Invalid number of arguments", 1);
	return (-1);
}
