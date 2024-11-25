#include "../includes/philo.h"

void    monitor_philo_died(t_data *data, int i)
{
    print_status(&data->philos[i], DIE);
    data->over = 1;
    data->philos[i].over_philo = 1;
}

int    monitor_aux(t_data *data, int i)
{
    if (data->over)
    {
        pthread_mutex_unlock(&data->death_lock);
        return (1);
    }
    i = -1;
    while (++i < data->num_philos)
    {
        if (current_time_in_ms() - data->philos[i].last_meal_time >= data->time_to_die)
        {
            monitor_philo_died(data, i);
            pthread_mutex_unlock(&data->death_lock);
            return (1);
        }
    }
    if (data->philos[data->num_philos - 1].meals_eaten == data->must_eat_count)
        return (1);
    return (0);
}

void    *monitor_routine(void *arg)
{
    int     i;
    t_data  *data;

    i = 0;
    data = (t_data *)arg;
    while (!(data->over))
    {
        pthread_mutex_lock(&data->death_lock);
        if (monitor_aux(data, i))
            return (NULL);
        pthread_mutex_unlock(&data->death_lock);
        usleep(100);
    }
    return (NULL);
}
