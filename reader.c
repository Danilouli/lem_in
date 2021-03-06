/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schmurz <schmurz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 20:17:42 by schmurz           #+#    #+#             */
/*   Updated: 2018/04/05 18:12:31 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	read_nbants(int op)
{
	char	*l;
	int		r;

	while ((r = get_next_line(0, &l)) > 0 && !ft_isnumstr(l))
	{
		if (!is_comment_line(l)
		&& ft_printf("ERROR - BAD FIRST LINE\n") && ft_strdelbool(&l))
			exit(EXIT_SUCCESS);
		ft_strdel(&l);
	}
	if ((r <= 0 || ft_overf_ll(l) || ft_atoi(l) > 2147483647
	|| (NBANTS = (int)ft_atoi(l)) <= 0)
	&& ft_printf("ERROR - NO OR NEGATIVE ANTS\n"))
		exit(EXIT_SUCCESS);
	ft_strdel(&l);
	if (!op)
		ft_printf("%d\n", NBANTS);
}

static	int	read_line(char *l)
{
	static char	*room_type = 0;
	static int	room_num = -1;

	if (is_command_line(l))
		room_type = is_command_line(l);
	else if (is_room_line(l) && (++room_num) >= 0)
	{
		if (!init_room(l, room_type, room_num)
		&& ft_printf("ERROR\n") && ft_strdelbool(&l))
			return (good_or_exit());
	}
	else if (is_tube_line(l))
	{
		if (!init_tube(l) && ft_printf("ERROR\n") && ft_strdelbool(&l))
			return (good_or_exit());
	}
	else if (!is_comment_line(l) && ft_strdelbool(&l))
		return (good_or_exit());
	if (!is_command_line(l) && !is_comment_line(l))
		room_type = 0;
	return (1);
}

void		read_lemin(int op)
{
	char	*l;
	int		status;
	int		r;

	init_g_lemin();
	read_nbants(op);
	status = 1;
	r = 1;
	while (get_next_line(0, &l) == 1)
	{
		if (!op)
			ft_putendl(l);
		if ((status = read_line(l)))
			ft_strdel(&l);
	}
	if (!op)
		ft_putchar('\n');
	if (!add_ants())
		exit(EXIT_FAILURE);
}
