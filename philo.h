/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:46:09 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/30 12:50:32 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <sys/types.h>
# include <limits.h>
# include <string.h>

# define MSG_DEATH "%llu %zu died\n"
# define MSG_FORK "%llu %zu has taken a fork\n"
# define MSG_EAT "%llu %zu is eating\n"
# define MSG_SLEEP "%llu %zu is sleeping\n"
# define MSG_THINK "%llu %zu is thinking\n"

typedef struct s_philo	t_philo;

typedef struct s_create
{
	int				start_lock;
	int				eat;
	int				bool;
	size_t			nb_philo;
	pthread_mutex_t	mut_death;
	pthread_mutex_t	*fork;
	int				*fork_user;
	t_philo			*philo;
}				t_create;

typedef struct s_philo
{
	t_create		*c;
	pthread_mutex_t	*mut_death;
	pthread_t		thread;
	int				rfork;
	int				lfork;
	int				*death;
	size_t			id;
	int				tdie;
	uint64_t		tbdie;
	int				teat;
	uint64_t		deat;
	int				tsleep;
	int				nteat;
	int				ndeat;
	uint64_t		dsleep;
	size_t			ready;
	size_t			nb_philo;
	size_t			tstamp;
}				t_philo;

//thread.c
int			create_thread(t_philo *philo, t_create *c, int argc, char **argv);

//utils.c
void		free_struct(t_philo *philo, t_create *c, pthread_mutex_t	*fork, \
	pthread_mutex_t *mu_death);
uint64_t	timestamp(void);
int			mut_death(t_philo *philo);
int			ft_atoi(const char *str);

//mutex.c
void		solo_philo(t_philo *philo);
int			lock_mutex(t_philo *philo);
void		unlock_mutex(t_philo *philo, int bool);
int			read_death(t_philo *philo);

// fork.c
void		lock_left(t_philo *philo);
void		lock_right(t_philo *philo);
void		unlock_forks(t_philo *philo);
int			lock_fork(t_philo *philo);

//main.c
void		speak(t_philo *p, const char *msg);
void		msleep(uint64_t n);

#endif