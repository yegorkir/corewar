#include "vm.h"
#include "vis.h"
#include "vis_errors.h"

t_vis_tools *g_vs;

void	start_game(t_corewar *corewar)
{
	bool		quit;

	create_vs();
	file = fopen("log.txt", "w");
	init_arena(corewar->arena, corewar->champs, &corewar->carriages);
	introducing_fighter(corewar->champs);
	if (!init())
		go_exit(ERR_CREATE_VS);
	quit = false;
	g_change = 1;
	while (!quit)
	{
		if (corewar->game_param.cycles_aft_start++ ==
		corewar->flgs.nbr_cycles_dump && corewar->flgs.set_flg & DUMP_FLG)
			print_map(corewar);
		++corewar->game_param.cycles_bfr_check;
  		carriages_actions(corewar);
		if (!(corewar->game_param.cycles_bfr_check -
corewar->game_param.cycles_to_die) || corewar->game_param.cycles_to_die <= 0)
			lets_check(corewar);
		if ((corewar->flgs.set_flg & B_FLG) && g_change)
			visualise_arena(corewar, &quit);
		if (!corewar->carriages)
			introducing_winner(corewar);
	}
}

void	init_arena(unsigned char arena[], t_champion *champs,
					t_carriages **carriages)
{
	unsigned int		code_shift;
	int					i;

	code_shift = MEM_SIZE / champions_cnt(champs);
	i = 0;
	while (champs)
	{
		ft_memcpy(arena + i++ * code_shift, champs->file.exec_code,
				sizeof(champs->file.exec_code));
		push_front_carriage(carriages);
		(*carriages)->reg[0] = -champs->num;
		(*carriages)->op_pos = arena + (i - 1) * code_shift;
		champs = champs->next;
	}
}

void	introducing_fighter(t_champion *champs)
{
	int		player;

	printf("Introducing contestants...\n"); /// change to ft_printf
	fprintf(file, "Introducing contestants...\n");
	player = 0;
	while (champs)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			++player, champs->file.header.prog_size,
			champs->file.header.prog_name, champs->file.header.comment); /// change to ft_printf
		fprintf(file, "* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				  player, champs->file.header.prog_size,
				  champs->file.header.prog_name, champs->file.header.comment);
		champs = champs->next;
	}
}

void	introducing_winner(t_corewar *corewar)
{
	int		winner;

	winner = corewar->game_param.who_lst_live;
	while (corewar->champs && corewar->champs->num != winner)
		corewar->champs = corewar->champs->next;
	printf("Contestant %d, \"%s\", has won !\n", corewar->champs->num,
			corewar->champs->file.header.prog_name); /// change to ft_printf
	fprintf(file, "Contestant %d, \"%s\", has won !\n", corewar->champs->num,
			  corewar->champs->file.header.prog_name);
	fclose(file);
	exit(0);
}

void    print_map(t_corewar *corewar)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < MEM_SIZE)
	{
		if (!j)
			printf("0x%04x : ", i);
		printf("%.2x", corewar->arena[i]);
		if (j < 31)
			printf(" ");
		else
		{
			printf("\n");
			j = -1;
		}
		i++;
		j++;
	}
	exit(5);
}
