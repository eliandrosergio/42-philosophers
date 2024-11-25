#include "../includes/philo.h"

void    cleanup(t_data *data)
{
    int     i;

    i = -1;
    while (++i < data->num_philos)
        pthread_join(data->philos[i].thread, (void *)&data->philos[i]);
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->death_lock);
    free(data->forks);
    free(data->philos);
}

void    ft_exit(char *str, t_data *data, int nbr_exit)
{
    if (data)
        cleanup(data);
    if (*str)
        printf("Erro\n%s\n", str);
    if (nbr_exit)
        exit (nbr_exit);
}

int     main(int ac, char **av)
{
    t_data      data;

    if (!args_check(ac, av))
    {
        init_data(&data, ac, av);
        init_mutex(&data);
        init_philo(&data);
        init_thread(&data);
        cleanup(&data);
    }
    return (0);
}
