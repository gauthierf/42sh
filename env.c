/*
** env.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:54:15 2016
** Last update Wed Jun  8 09:07:36 2016 
*/

#include <stdlib.h>
#include "tools.h"
#include "builtins.h"
#include "my.h"

static const t_builtins	g_opt[] =
  {
    {"-i", &reset_env,},
    {"-0", &null_env},
    {"--null", &null_env},
    {"-u", &unset_env},
    {"--help", &help_env},
    {"-h", &help_env},
    {NULL, NULL},
  };

static void	my_env_execution(t_mini *shell, t_process *proc, int ac_pos,
				 char **old_env)
{
  int		size;
  char		*new;
  char		**temp;
  t_process	*tmp;

  if (proc->cmd_argv[ac_pos] == NULL)
    return ;
  size = get_new_size(ac_pos - 1, proc->cmd_argv);
  if ((new = malloc(size * sizeof(*new))) == NULL)
    return ;
  get_new_cmd(new, ac_pos, proc->cmd_argv);
  tmp = NULL;
  if (parser(new, &tmp, shell, NULL) == -1)
    return ;
  temp = shell->env;
  shell->env = old_env;
  shell->env_exec = temp;
  shell->is_env_exec = SUCCESS;
  my_execute(tmp, shell);
  free_proc(tmp);
  free(new);
  shell->env = temp;
  shell->env_exec = old_env;
}

int	my_print_env(char **env, int type)
{
  int	index;

  index = 0;
  while (type == SUCCESS && env && env[index])
    if ((my_printf("%s\n", env[index++])) == - 1)
      return (EXIT_FAILURE);
  while (type == FAILURE && env && env[index])
    if ((my_printf("%s", env[index++])) == -1)
      return (EXIT_FAILURE);
  if (type == FAILURE && env && env[0] && my_printf("\n") != 1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static int	my_val_zero(t_process *proc, int *index)
{
  if ((my_print_error("env: invalid option: %s\n",
		      proc->cmd_argv[*index])) == -1)
    return (SUCCESS);
  return (SUCCESS);
}

static int	my_env_loop(t_mini *shell, t_process *proc,
			    int *index, int *ret)
{
  int		val;
  int		count;

  val = 0;
  count = -1;
  while (g_opt[++count].str)
    if ((my_strcmp(g_opt[count].str, proc->cmd_argv[*index])) == 0)
      {
	if (g_opt[count].f_tab(shell, proc->cmd_argv[*index + 1],
			       ret, index) == FAILURE)
	  return (SUCCESS);
	val++;
      }
  if (is_in_str(proc->cmd_argv[*index], '=') == SUCCESS)
    {
      if (my_add_at_env(shell, proc->cmd_argv[*index]) == FAILURE)
	return (SUCCESS);
    }
  else if (val == 0)
    return (my_val_zero(proc, index));
  *index = *index + 1;
  return (FAILURE);
}

int	my_env(t_mini *shell, t_process *proc)
{
  int	val;
  int	index;
  char	**tmp;

  val = SUCCESS;
  proc->status = 0;
  index = 1;
  if (!(proc->cmd_argv[1]))
    {
      my_print_env(shell->env, val);
      return (SUCCESS);
    }
  tmp = create_new_env(shell->env);
  while (is_in_str(proc->cmd_argv[index], '=') == SUCCESS
	 || is_in_str(proc->cmd_argv[index], '-') == SUCCESS)
    if (my_env_loop(shell, proc, &index, &val) == SUCCESS)
      return (SUCCESS);
  if (!(proc->cmd_argv[index]))
    my_print_env(shell->env, val);
  my_env_execution(shell, proc, index, tmp);
  free_tab(shell->env);
  shell->env = tmp;
  return (SUCCESS);
}
