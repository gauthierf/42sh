/*
** echo.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:54:02 2016
** Last update Wed Jun  8 09:56:38 2016 
*/

#include <stdlib.h>
#include "builtins.h"
#include "tools.h"
#include "readline.h"
#include "my.h"

static const t_echo	g_tab[] =
  {
    {'\\', '\\'},
    {'\a', 'a'},
    {'\b', 'b'},
    {'\f', 'f'},
    {'\n', 'n'},
    {'\r', 'r'},
    {'\t', 'r'},
  };

static int	my_print_backslash(char *str, int *count)
{
  int		index;

  index = 0;
  *count += 1;
  while (g_tab[index].next_val)
    {
      if (g_tab[index].next_val == str[*count])
	if ((my_printf("%c", g_tab[index].exec_val)) == -1)
	  return (FAILURE);
      index++;
    }
  *count += 1;
  return (SUCCESS);
}

static int	my_special_echo(t_process *proc, int i, int *op)
{
  int		count;
  int		val;

  val = 0;
  while (proc->cmd_argv && proc->cmd_argv[i])
    {
      if (val++ != 0)
	my_putchar(' ');
      count = 0;
      while (proc->cmd_argv[i][count])
	{
	  if ((proc->cmd_argv[i][count] != '$')
	      && proc->cmd_argv[i][count] != '\\')
	    {
	      if ((my_printf("%c", proc->cmd_argv[i][count++])) == -1)
		return (FAILURE);
	    }
	  else
	    my_print_backslash(proc->cmd_argv[i], &count);
	}
      i++;
    }
  if (op[1] == FAILURE && my_printf("\n") == -1)
    return (FAILURE);
  return (SUCCESS);
}

static int	my_normal_echo(t_process *proc, int index, int *op)
{
  int		count;
  int		val;

  val = 0;
  while (proc->cmd_argv && proc->cmd_argv[index])
    {
      count = 0;
      if (val++ != 0)
	my_putchar(' ');
      while (proc->cmd_argv[index][count])
	if ((my_printf("%c", proc->cmd_argv[index][count++])) == -1)
	  return (FAILURE);
      index++;
    }
  if (op[1] == FAILURE && my_printf("\n") != 1)
    return (FAILURE);
  return (SUCCESS);
}

static void	get_option(t_process *proc, int *opt, int *index)
{
  opt[0] = FAILURE;
  opt[1] = FAILURE;
  opt[2] = FAILURE;
  while (proc->cmd_argv && proc->cmd_argv[*index]
	 && proc->cmd_argv[*index][0] == '-')
    {
      if (my_strcmp(proc->cmd_argv[*index], "-e") == 0)
	opt[0] = SUCCESS;
      else if (my_strcmp(proc->cmd_argv[*index], "-n") == 0)
	opt[1] = SUCCESS;
      else
	return ;
      *index += 1;
    }
}

int	my_echo(t_mini *shell, t_process *proc)
{
  int	index;
  int	opt[2];

  (void)shell;
  if (!proc || !proc->cmd_argv || !proc->cmd_argv[1])
    {
      if ((my_printf("\n")) == -1)
	return (EXIT_FAILURE);
      return (EXIT_SUCCESS);
    }
  index = 1;
  get_option(proc, opt, &index);
  if (opt[0] == FAILURE)
    my_normal_echo(proc, index, opt);
  else
    my_special_echo(proc, index, opt);
  return (EXIT_SUCCESS);
}
