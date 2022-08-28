/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:04:23 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/04/22 18:13:57 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	speak(t_philo *p, const char *msg)
{
	if (read_death(p) < 0)
		return ;
	printf(msg, timestamp() - p->tstamp, p->id);
}

void	msleep(uint64_t n)
{
	uint64_t	tmp;

	tmp = timestamp() + n;
	while (timestamp() < tmp)
		usleep(60);
}

static pthread_mutex_t	*create_fork(t_create *c)
{
	pthread_mutex_t	*fork;
	size_t			i;

	fork = malloc(sizeof(pthread_mutex_t) * (c->nb_philo));
	if (!fork)
		return (NULL);
	c->fork_user = malloc(sizeof(int) * (c->nb_philo));
	if (!c->fork_user)
		return (NULL);
	memset(c->fork_user, 0, sizeof(int) * (c->nb_philo));
	i = 0;
	while (i < c->nb_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

static int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_create		c;
	size_t			i;

	if ((argc < 5 || argc > 6) || check_args(argc, argv) == -1)
		return (0);
	memset(&c, 0, sizeof(t_create));
	c.nb_philo = ft_atoi(argv[1]);
	c.philo = malloc(sizeof(t_philo) * (c.nb_philo));
	if (!c.philo)
		return (0);
	memset(c.philo, 0, sizeof(t_philo) * (c.nb_philo));
	c.fork = create_fork(&c);
	if (!c.fork)
		return (0);
	c.bool = 0;
	if (!create_thread(c.philo, &c, argc, argv))
		return (0);
	i = 0;
	while (i < c.nb_philo)
	{
		pthread_join(c.philo[i].thread, NULL);
		i++;
	}
	free_struct(c.philo, &c, c.fork, &c.mut_death);
	return (0);
}
