/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/10 10:28:37 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_argerro(int id)
{
	if (id == 1)
		ft_exit("Invalid number of philosophers (1 - 200)", 0, 0);
	else if (id == 2)
		ft_exit("Invalid number of time_to_die (>= 1)", 0, 0);
	else if (id == 3)
		ft_exit("Invalid number of time_to_eat (>= 1)", 0, 0);
	else if (id == 4)
		ft_exit("Invalid number of time_to_sleep (>= 1)", 0, 0);
	else if (id == 5)
		ft_exit("Invalid number of must_eat_count (>= 1)", 0, 0);
}

int	check_number(char *str, int id, int i)
{
	if (str[i] == '+' && ft_isdigit(str[i + 1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			print_argerro(id);
			return (0);
		}
		i++;
	}
	if ((ft_atoi(str) <= 0) || (id == 1 && (ft_atoi(str) > 200)))
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
		while (i < ac && check_number(av[i], i, 0))
			i++;
		if (i != ac)
			return (1);
		return (0);
	}
	ft_exit("Invalid number of arguments", 0, 0);
	return (1);
}
