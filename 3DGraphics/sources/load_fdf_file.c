/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_fdf_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:55:24 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/02 19:27:35 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

static t_3d_point	create_point(t_uint32 x, char *str, t_uint32 z);
static int			fill_quad_lst(t_list **quad_lst, char const *file_path);
static void			parse_lines(char *line1, char *line2, t_uint32 z_l1,
						t_list **quad_lst);
static t_list		*quad_lstnew(char **splited_line1, char **splited_line2,
						t_uint32 x0, t_uint32 z0);

t_3d_model	load_fdf_file(char const *file_path)
{
	t_3d_model	new_model;
	t_list		*quad_lst;
	int			lst_len;
	t_list		*watched;
	t_uint32	i;

	quad_lst = NULL;
	if (fill_quad_lst(&quad_lst, file_path) != 0)
		return ((t_3d_model){.quads = NULL});
	lst_len = ft_lstsize(quad_lst);
	new_model.quad_count = lst_len;
	new_model.quads = malloc(lst_len * sizeof(t_3d_quad));
	if (new_model.quads != NULL)
	{
		i = 0;
		watched = quad_lst;
		while (watched != NULL)
		{
			new_model.quads[i++] = *((t_3d_quad *)watched->data);
			watched = watched->next;
		}
	}
	ft_lstclear(&quad_lst, &free_wrapper);
	return (new_model);
}

static int	fill_quad_lst(t_list **quad_lst, char const *file_path)
{
	int			fd;
	char		*line1;
	char		*line2;
	t_uint32	z_l1;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	line1 = get_next_line(fd);
	line2 = get_next_line(fd);
	z_l1 = 0;
	while (line1 != NULL && line2 != NULL)
	{
		parse_lines(line1, line2, z_l1, quad_lst);
		free(line1);
		line1 = line2;
		line2 = get_next_line(fd);
		z_l1++;
	}
	free(line1);
	free(line2);
	close(fd);
	return (0);
}

static void	parse_lines(char *line1, char *line2, t_uint32 z_l1,
				t_list **quad_lst)
{
	char		**splited_line1;
	size_t		splited_line1_len;
	char		**splited_line2;
	size_t		splited_line2_len;
	t_uint32	x0;

	splited_line1 = ft_split(line1, ' ');
	splited_line2 = ft_split(line2, ' ');
	splited_line1_len = array_len(splited_line1, sizeof(char *));
	splited_line2_len = array_len(splited_line2, sizeof(char *));
	x0 = 0;
	while (x0 < splited_line1_len && x0 < splited_line2_len
		&& (x0 + 1) < splited_line1_len && (x0 + 1) < splited_line2_len)
	{
		ft_lstadd_front(quad_lst, quad_lstnew(splited_line1,
				splited_line2, x0, z_l1));
		x0++;
	}
	free_splited_str(splited_line1);
	free_splited_str(splited_line2);
}

static t_3d_point	create_point(t_uint32 x, char *str, t_uint32 z)
{
	int		y;
	t_color	color;
	char	**splited_str;

	y = ft_atoi(str);
	color = WHITE;
	splited_str = ft_split(str, ',');
	if (splited_str != NULL && splited_str[1] != NULL)
		color = color_raw_rgb(atoi_hex(splited_str[1]));
	if (splited_str != NULL)
		free_splited_str(splited_str);
	return ((t_3d_point){
		.pos = new_vect_3d((float)x, (float)y, (float)z),
		.color = color}
	);
}

static t_list	*quad_lstnew(char **splited_line1, char **splited_line2,
					t_uint32 x0, t_uint32 z0)
{
	t_3d_quad	*new_quad;
	t_list		*new_lst;

	new_quad = malloc(sizeof(t_3d_quad));
	if (new_quad == NULL)
		return (NULL);
	new_quad->p[0] = create_point(x0, splited_line1[x0], z0);
	new_quad->p[1] = create_point(x0 + 1, splited_line1[x0 + 1], z0);
	new_quad->p[2] = create_point(x0 + 1, splited_line2[x0 + 1], z0 + 1);
	new_quad->p[3] = create_point(x0, splited_line2[x0], z0 + 1);
	new_lst = ft_lstnew(new_quad);
	if (new_lst == NULL)
		free(new_quad);
	return (new_lst);
}
