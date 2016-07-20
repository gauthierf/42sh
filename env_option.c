/*
** env_option.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:51:39 2016
** Last update Wed Jun  8 10:56:11 2016 
*/

#include <stdlib.h>
#include "builtins.h"
#include "tools.h"
#include "my.h"

int	reset_env(t_mini *shell, char *str, int *val, int *index)
{
  (void)str;
  (void)val;
  (void)index;
  shell->env = NULL;
  return (SUCCESS);
}

int	help_env(t_mini *shell, char *str, int *val, int *index)
{
  (void)str;
  (void)shell;
  (void)val;
  (void)index;
  my_printf("Usage: env [OPTION]... [-] [NAME=VALUE]... [COMMAND [ARG]...]\n\
Set each NAME to VALUE in the environment and run COMMAND.\n\n		\
Mandatory arguments to long options are mandatory for short options too.\n\
  -i,		       start with an empty environment\n\
  -0, --null           end each output line with 0 byte rather than newline\n\
  -u, [var]	       remove variable from the environment\n\
  -h, --help	       display this help and exit\n");
  return (FAILURE);
}

int	unset_env(t_mini *shell, char *str, int *val, int *cursor)
{
  int	index;
  char	*ptr;

  (void)val;
  if (!str)
    {
      my_print_error("env: option requires an argument\n");
      return (FAILURE);
    }
  if ((ptr = find_str_in_tab(str, shell->env)))
    {
      index = 0;
      while (ptr != shell->env[index])
	index++;
      free(shell->env[index]);
      shell->env[index] = NULL;
      while (shell->env[++index])
	my_swap_str(&shell->env[index - 1], &shell->env[index]);
    }
  *cursor = *cursor + 1;
  return (SUCCESS);
}

int	null_env(t_mini *shell, char *str, int *val, int *cursor)
{
  *val = FAILURE;
  (void)cursor;
  (void)shell;
  (void)str;
  return (SUCCESS);
}

int	my_add_at_env(t_mini *shell, char *str)
{
  int	index;
  int	cursor;
  char	*temp;

  if (test_var(str) == FAILURE)
    return (FAILURE);
  index = 0;
  while (str && str[index] && str[index] != '=')
    index++;
  if (!(temp = malloc(sizeof(char) * (index + 1))))
    return (FAILURE);
  cursor = 0;
  while (cursor < index)
    {
      temp[cursor] = str[cursor];
      cursor++;
    }
  temp[cursor] = '\0';
  if (!(find_str_in_tab(temp, shell->env)))
    add_str_end_env(shell, str);
  else
    remplace_str_in_env(shell, str, temp);
  return (SUCCESS);
}
