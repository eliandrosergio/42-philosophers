#include "../includes/philo.h"

void    init_data(t_data *data, int ac, char **av)
{
    data->num_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->must_eat_count = -1;
    if (ac == 6)
        data->must_eat_count = ft_atoi(av[5]);
    data->over = 0;
}

void    init_mutex(t_data *data)
{
    int     i;

    i = -1;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->forks || !data->philos)
        ft_exit ("Falha ao alocar a memória", data, 1);
    while (++i < data->num_philos)
        pthread_mutex_init(&data->forks[i], NULL);
    pthread_mutex_init(&data->print_lock, NULL);
    pthread_mutex_init(&data->death_lock, NULL);
    data->start_time = current_time_in_ms();
}

void    init_philo(t_data *data)
{
    int     i;

    i = -1;
    while (++i < data->num_philos)
    {
        data->philos[i].id = i;
        data->philos[i].last_meal_time = data->start_time;
        data->philos[i].meals_eaten = 0;
        data->philos[i].data = data;
        data->philos[i].over_philo = 0;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = 0;
    }
}

void    init_thread(t_data *data)
{
    int         i;
    pthread_t   monitor;

    i = -1;
    while (++i < data->num_philos)
    {
        data->philos[i].right_fork = data->philos[(i + 1) % data->num_philos].left_fork;
        if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
            ft_exit ("Falha ao criar o thread do(s) filósofo(s)", data, 1);
    }
    if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
    {
        data->over = 1;
        ft_exit ("Falha ao criar o thread de monitoramento", data, 1);
    }
    pthread_join(monitor, NULL);
}
