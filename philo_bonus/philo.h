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
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define RED	"\x1b[31m"
# define BLU   "\x1B[34m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

typedef struct s_philo
{
	int				name;
	int				x_ate;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	struct s_all	*all;
	pthread_t		death_check;
	pid_t			proc_id;
}					t_philo;

typedef struct s_all
{
	int				philo_count;
	long			time_eat;
	long			time_die;
	long			time_sleep;
	int				eat_count;
	int				dead;
	long long		time_start;
	sem_t			*meal_check;
	sem_t			*forks;
	sem_t			*message;
	t_philo			philo[200];
}					t_all;

// message.c
void		action_print(t_all *all, int id, char *str);
int			error_message(char *str);
int			error_manager(int error);
//init.c
int			init_all(t_all *all, char **av);
//simulation.c
int			launcher(t_all *all);
//utils.c
int			ft_atoi(const char *str);
long long	timestamp(void);
void		smart_sleep(long long time, t_all *all);
long long	time_diff(long long past, long long pres);

#endif
