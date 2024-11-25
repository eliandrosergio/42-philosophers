#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include "colors.h"

# define EAT BOLD YELLOW "esta comendo 😋️" RESET
# define SLEEP BOLD BLUE "esta dormindo 😪️" RESET
# define THINK BOLD CYAN "esta pensando 😣️" RESET
# define FORK BOLD MAGENTA "pegou um garfo 🍽️" RESET
# define DIE RED BOLD "foi de base 😵️" RESET
# define DEVIL BOLD RED "Parece que hoje ninguém morreu, infelizmente 😈️\n" RESET


typedef struct s_philo {
    int             id;
    int             meals_eaten;
    long            last_meal_time;
    int             over_philo;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data   *data;
} t_philo;

typedef struct s_data {
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_count;
    int             over;
    long int        start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t death_lock;
    t_philo         *philos;
} t_data;


int         ft_isdigit(int c);
int         ft_atoi(const char *str);
long int    current_time_in_ms(void);
int         args_check(int ac, char **av);

void        ft_usleep(long int time);
void        init_mutex(t_data *data);
void        init_philo(t_data *data);
void        init_thread(t_data *data);
void        *philo_routine(void *arg);
void        *monitor_routine(void *arg);
void        ft_exit(char *str, t_data *data, int i);
void        init_data(t_data *data, int ac, char **av);
void        print_status(t_philo *philo, char *message);

#endif
