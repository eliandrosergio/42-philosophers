#include "../includes/philo.h"

void    print_status(t_philo *philo, char *message)
{
    pthread_mutex_lock(&philo->data->print_lock);
    if (philo->data->over)
    {
        pthread_mutex_unlock(&philo->data->print_lock);
        return ;
    }
    printf("%ldms %d %s\n", current_time_in_ms() - philo->data->start_time, philo->id, message);
    pthread_mutex_unlock(&philo->data->print_lock);
}

void    routine_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, FORK);
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, FORK);
    philo->last_meal_time = current_time_in_ms();
    print_status(philo, EAT);
    ft_usleep(philo->data->time_to_eat);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    routine_sleep_think(t_philo *philo)
{
    print_status(philo, SLEEP);
    ft_usleep(philo->data->time_to_sleep);
    print_status(philo, THINK);
}

void    *philo_routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    if (philo->id & 1)
        ft_usleep(philo->data->time_to_eat * 0.9 + 1);
    while (!(philo->over_philo) && !(philo->data->over))
    {
        routine_eat(philo);
        routine_sleep_think(philo);
        if (philo->meals_eaten == philo->data->must_eat_count)
        {
            printf("%ld %d já comeu %d vezes\n", current_time_in_ms() - philo->data->start_time, philo->id, philo->data->must_eat_count);
            philo->over_philo = 1;
        }
    }
    return (NULL);
}
