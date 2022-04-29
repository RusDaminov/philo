/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:48:41 by abernita          #+#    #+#             */
/*   Updated: 2022/04/07 18:48:45 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define RED    "\x1b[31m"
# define BLU    "\x1B[34m"
# define GRN    "\x1B[32m"
# define YEL    "\x1B[33m"
# define MAG    "\x1B[35m"
# define CYN    "\x1B[36m"
# define WHT    "\x1B[37m"
# define RESET  "\x1B[0m"

typedef struct s_philos
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				nbr_eated;
	long			t_last_eated;
	struct s_args	*args;
}					t_philos;

typedef struct s_args
{
	int				philo_number;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				nbr_of_eating;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	*forks;
	int				total_eat;
	int				f_is_dead;
	long			t_start;
	struct s_philos	*philo_arr;

}					t_args;

// philo.c
void	*ft_philo_lifecycle(void *philosopher);
void	*ft_should_philo_die(void *data);

// validation.c
int		ft_validation(int argc, char **argv);

// init.c
int		ft_structure_init(t_args *options, int argc, char **argv);
void	ft_init_philos(t_args *options, t_philos *philos, pthread_t *threads);

// utils.c
int		ft_atoi(char *str);
long	ft_current_time(void);
int		ft_time_passed(long t_start);
void	ft_mysleep(int ms);
void	ft_join_clean(t_args *s_options, t_philos *philos, pthread_t *threads);

// simulation.c
void	ft_philo_eating(t_philos *philo);
void	ft_philo_sleeping(t_philos *philo);
void	ft_philos_thinking(t_philos	*philo);

#endif