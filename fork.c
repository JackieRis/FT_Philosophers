/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:15:40 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/30 12:51:21 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->c->fork[philo->id - 1]);
	if (philo->c->fork_user[philo->id - 1] == 0)
	{	
		philo->c->fork_user[philo->id - 1] = philo->id;
		philo->lfork = 1;
		speak(philo, MSG_FORK);
	}
	pthread_mutex_unlock(&philo->c->fork[philo->id - 1]);
}

void	lock_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->c->fork[philo->id % philo->nb_philo]);
	if (philo->c->fork_user[philo->id % philo->nb_philo] == 0)
	{	
		philo->c->fork_user[philo->id % philo->nb_philo] = philo->id;
		philo->rfork = 1;
		speak(philo, MSG_FORK);
	}
	pthread_mutex_unlock(&philo->c->fork[philo->id % philo->nb_philo]);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->c->fork[philo->id - 1]);
	if (philo->lfork)
	{	
		philo->c->fork_user[philo->id - 1] = 0;
		philo->lfork = 0;
	}
	pthread_mutex_unlock(&philo->c->fork[philo->id - 1]);
	pthread_mutex_lock(&philo->c->fork[philo->id % philo->nb_philo]);
	if (philo->rfork)
	{	
		philo->c->fork_user[philo->id % philo->nb_philo] = 0;
		philo->rfork = 0;
	}
	pthread_mutex_unlock(&philo->c->fork[philo->id % philo->nb_philo]);
}

int	lock_fork(t_philo *philo)
{
	while (philo->lfork != 1 && timestamp() <= philo->tbdie)
	{
		lock_left(philo);
		if (philo->lfork)
			break ;
		usleep(25);
	}
	if (timestamp() > philo->tbdie)
	{
		unlock_forks(philo);
		return (0);
	}
	while (philo->rfork != 1 && timestamp() <= philo->tbdie)
	{
		lock_right(philo);
		if (philo->rfork)
			break ;
		usleep(25);
	}
	if (timestamp() > philo->tbdie)
	{
		unlock_forks(philo);
		return (0);
	}
	return (1);
}
