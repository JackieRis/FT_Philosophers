/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:36:50 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/30 12:51:11 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	solo_philo(t_philo *philo)
{
	lock_left(philo);
	msleep(philo->tdie);
	speak(philo, MSG_DEATH);
	unlock_forks(philo);
}

int	lock_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->c->fork[philo->id - 1]);
	if (mut_death(philo) == -1)
		return (-1);
	speak(philo, MSG_FORK);
	pthread_mutex_lock(&philo->c->fork[philo->id % philo->nb_philo]);
	if (mut_death(philo) == -1)
		return (-1);
	speak(philo, MSG_FORK);
	return (0);
}

void	unlock_mutex(t_philo *philo, int bool)
{	
	if (bool >= 1)
		pthread_mutex_unlock(&philo->c->fork[philo->id - 1]);
	if (bool >= 2)
		pthread_mutex_unlock(&philo->c->fork[philo->id % philo->nb_philo]);
}

int	read_death(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(philo->mut_death);
	ret = *philo->death;
	pthread_mutex_unlock(philo->mut_death);
	return (ret);
}
