#include "../includes/philo.h"

int     check_number(char *str)
{
	int     i;

	i = 0;
	if (str[i] == '+' && ft_isdigit(str[i + 1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
    return (1);
}

int     args_check(int ac, char **av)
{
    int     i;

    if (ac == 5 || ac == 6)
    {
        i = 1;
        while (i < ac && check_number(av[i]))
            i++;
        if (i != ac)
        {
            printf("Erro\nArgumento(s) inválidos\n");
            return (1);
        }
        if (ft_atoi(av[1]) <= 0)
        {
            printf("Erro\nNúmero de filósofos inválido\n");
            return (1);
        }
        return (0);
    }
    printf("Erro\nNúmero de argumentos inválido\n");
    return (1);
}
