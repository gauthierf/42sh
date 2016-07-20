/*
** interprete_args.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:57:42 2016
** Last update Wed Jun  8 10:56:30 2016 
*/

#include <unistd.h>
#include <stdlib.h>
#include "parser.h"
#include "tools.h"
#include "builtins.h"
#include "shell.h"
#include "readline.h"
#include "shell.h"
#include "my.h"

void	rm_quotes(char *str, int is_rm)
{
  int	i;

  i = 0;
  while (str[i])
    {
      str[i] = str[i + 1];
      i += 1;
    }
  if (i > 0)
    str[i - 1] = 0;
  if (i > 1 && is_rm == 1)
    str[i - 2] = 0;
}

static int	i_am_your_father(int pipefd[2], char **new)
{
  char		buffer[512];
  char		*to_rm;
  char		*str;
  int		size_read;

  if ((str = my_strdup("\0")) == NULL)
    return (-1);
  buf_zero(buffer, 512);
  close (pipefd[1]);
  while ((size_read = read(pipefd[0], buffer, 511)) > 0 && buffer[0] != '\0')
    {
      to_rm = str;
      if ((str = str_cat(str, buffer)) == NULL)
	return (-1);
      free(to_rm);
    }
  if (size_read == -1)
    return (my_putstr("error: could not read\n", 2));
  close(pipefd[0]);
  *new = str;
  return (0);
}

static int	mng_underground(char *str, t_mini *shell,
				char ***files_completition, char **new)
{
  t_process	*proc;
  int		pipefd[2];
  int		pid;

  proc = NULL;
  if ((parser(str, &(proc), shell, files_completition)) == -1)
    return (-1);
  if (pipe(pipefd) == -1)
    return (my_putstr("error: pipe\n", 2));
  if ((pid = fork()) == -1)
    return (my_putstr("error: fork\n", 2));
  else if (pid == 0)
  {
    if ((do_the_job_son(pipefd, shell, proc)) == -1)
      return (-1);
  }
  else if ((i_am_your_father(pipefd, new)) == -1)
    return (-1);
  free(str);
  return (0);
}

int	interprete_args(t_process *proc, t_mini *shell, char ***files_comp)
{
  int	i;
  char	*new;
  char	first;

  i = 0;
  while (proc && proc->cmd_argv && proc->cmd_argv[i] != NULL)
    {
      if ((my_strncmp(proc->cmd_argv[i], "$(", 2) == 0
	   && proc->cmd_argv[i][my_strlen(proc->cmd_argv[i]) - 1] == ')')
	  || proc->cmd_argv[i][0] == '`')
	{
	  first = proc->cmd_argv[i][0];
	  rm_quotes(proc->cmd_argv[i], 1);
	  if (first != '`')
	    rm_quotes(proc->cmd_argv[i], 0);
	  if ((mng_underground(proc->cmd_argv[i], shell, files_comp, &new)
	       == -1) || ((proc->cmd_argv = remake_argv(proc, i, new)) == NULL))
	    return (-1);
	  i = -1;
	}
      i += 1;
    }
  return (0);
}
