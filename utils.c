/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:29:06 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/30 11:27:54 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_struct(t_philo *philo, t_create *c, pthread_mutex_t	*fork, \
	pthread_mutex_t *mut_death)
{
	pthread_mutex_destroy(fork);
	pthread_mutex_destroy(mut_death);
	free(c->fork_user);
	free (fork);
	free (philo);
}

uint64_t	timestamp(void)
{
	struct timeval	end;
	struct timezone	tz;

	gettimeofday(&end, &tz);
	return (end.tv_sec * 1000 + end.tv_usec * 1e-3);
}

int	mut_death(t_philo *philo)
{
	if (read_death(philo) == -1)
	{
		unlock_forks(philo);
		return (-1);
	}
	if (timestamp() > philo->tbdie)
	{
		pthread_mutex_lock(philo->mut_death);
		if (*philo->death != -1)
		{
			*philo->death = -1;
			printf(MSG_DEATH, timestamp() - philo->tstamp, philo->id);
		}
		unlock_forks(philo);
		pthread_mutex_unlock(philo->mut_death);
		return (-1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	r;

	i = 0;
	signe = 1;
	r = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
				str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	if (!(str[i] > 47 && str[i] < 58))
		return (0);
	while (str[i] > 47 && str[i] < 58)
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r);
}
