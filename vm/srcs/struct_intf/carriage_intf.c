#include "vm.h"

t_carriages	*create_new_carriage(void)
{
	static int	nxt_id;
	t_carriages	*new;

	if (!(new = (t_carriages *)ml_malloc(sizeof(t_carriages), CARRIAGE_NODE)))
		return (NULL);
	new->id = ++nxt_id;
	new->carry = 0;
	new->op_code = 0;
	new->cycle_when_live = 0;
	new->cycle_op = 0;
	new->op_pos = NULL;
	new->cnt_bytes_to_op = 0;
	ft_bzero(new->reg, sizeof(new->reg));
	new->next = NULL;
	return (new);
}

void		push_front_carriage(t_carriages **carriages)
{
	t_carriages	*new_carriage;

	if (!*carriages)
		*carriages = create_new_carriage();
	else
	{
		if (!(new_carriage = create_new_carriage()))
			get_error("Carriage weren't been alloc");
		new_carriage->next = *carriages;
		*carriages = new_carriage;
	}
}