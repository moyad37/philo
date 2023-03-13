/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:10:05 by sgoffaux          #+#    #+#             */
/*   Updated: 2023/03/13 13:56:27 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_fill_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->count)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&rules->meal, NULL))
		return (1);
	if (pthread_mutex_init(&rules->writing, NULL))
		return (1);
	if (pthread_mutex_init(&rules->haupt, NULL))
		return (1);
	return (0);
}

static int	ft_fill_philo(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->count)
	{
		rules->philos[i].ate_times = 0;
		rules->philos[i].pos = i + 1;
		rules->philos[i].pos_str = ft_itoa(i + 1);
		if (!rules->philos[i].pos_str)
			break ;
		rules->philos[i].ffork = i;
		rules->philos[i].sfork = (i + 1) % rules->count;
		rules->philos[i].rules = rules;
		i++;
	}
	if (i != rules->count)
	{
		while (i >= 0)
		{
			free(rules->philos[i].pos_str);
			i--;
		}
		return (1);
	}
	return (0);
}

int	ft_fill(t_rules *rules)
{
	rules->philos = malloc(sizeof(t_philo) * rules->count);
	if (!rules->philos)
		return (0);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->count);
	if (!rules->forks)
	{
		free(rules->philos);
		return (0);
	}
	if (ft_fill_mutex(rules))
	{
		free(rules->philos);
		free(rules->forks);
		return (0);
	}
	if (ft_fill_philo(rules))
	{
		free(rules->philos);
		free(rules->forks);
		return (0);
	}
	return (1);
}
