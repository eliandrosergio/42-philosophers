/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/12 16:11:36 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_argerro(int id)
{
	if (id == 1)
		printf("Invalid number of philosophers (1 - 200)\n");
	else if (id == 2)
		printf("Invalid number of time_to_die (>= 1)\n");
	else if (id == 3)
		printf("Invalid number of time_to_eat (>= 1)\n");
	else if (id == 4)
		printf("Invalid number of time_to_sleep (>= 1)\n");
	else if (id == 5)
		printf("Invalid number of must_eat_count (>= 1)\n");
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

int	check_number(char *str, int id, int i)
{
	while (str[i])
	{
		if (!is_digits(str))
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
			return (-1);
		return (0);
	}
	printf("Invalid number of arguments");
	return (-1);
}
