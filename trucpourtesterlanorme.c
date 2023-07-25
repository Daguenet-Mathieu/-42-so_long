
int	verif_case(int pos, int x, int y, int check)
{
	t_case	all_zone[4];
	int		in_case;
	int		i;

	i = 0;
	init_case(all_zone, x, y);
	while (i < 4)
	{
		in_case = check_case(all_zone[i], (i < 2), (i == 0 || i == 2));
		if (check == 0 && in_case == 30)
			remove_obj(all_zone[i].x, all_zone[i].y);
		else if (check == 1 && in_case == 80)
			return (1);
		else if (in_case == 0)
			return (1);
		i++;
	}
	return (0);
}
