/*
** rc_center.c for  in /home/fernan_w/Téléchargements/backup/start
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:03:55 2016
** Last update Wed Jun  8 09:31:32 2016 
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "tools.h"
#include "my_printf.h"
#include "get_next_line.h"
#include "parser.h"
#include "my.h"

static char	*get_field(char *s)
{
  int		i;

  i = 0;
  while (s && s[i] && s[i] != ' ' && s[i] != '=' && i < 10)
    i++;
  if (i == 10)
    return (NULL);
  return (my_str_copy(s, i));
}

static int	rc_exec(char *str, t_mini *shell)
{
  int		nb;
  char		**file_tab;
  t_process	*rc_proc;

  rc_proc = NULL;
  file_tab = NULL;
  if (parser(str, &(rc_proc), shell, &(file_tab)) == -1)
    return (-1);
  nb = my_loop_proc(0, rc_proc, shell);
  if (isatty(0) && tcsetpgrp(0, getpgrp()) == -1)
    return (FAILURE);
  return (nb);
}

static int	rc_center(t_mini *shell, char *s, int line_no)
{
  char		*tmp;

  (void)line_no;
  if ((tmp = get_field(s)))
    {
      if (my_strcmp(tmp, "PS1") == 0 && s[3] && s[4])
	shell->prompt = my_str_copy(s + 4, 0);
      else if (my_strcmp(tmp, "alias") == 0 && s[5] == ' '
	       && check_alias(s + 6) == 0)
	{
	  if ((alias(s + 6, 1)) == NULL)
	    return (-1);
	}
      else if (my_strcmp(tmp, "plugins") == 0 && s[8])
	{
	  if (shell->prompt_plugins)
	    free(shell->prompt_plugins);
	  shell->prompt_plugins = my_str_to_wordtab(s + 8);
	}
      else if (rc_exec(s, shell) == FAILURE)
	return (FAILURE);
      free(tmp);
    }
  return (SUCCESS);
}

int	parse_rc_file(t_mini *shell)
{
  int	fd;
  int	line_no;
  char	*s;

  line_no = 1;
  shell->prompt_plugins = NULL;
  if (!isatty(0))
    return (SUCCESS);
  if ((fd = open(RC_FILELOC, O_RDONLY)) < 0)
    return (FAILURE);
  while ((s = get_next_line(fd)))
    {
      if (s[0] && s[0] != '#' && s[0] != '\n')
	rc_center(shell, s, line_no);
      free(s);
      line_no++;
    }
  close(fd);
  if (!shell->prompt)
    shell->prompt = my_strdup("$$> ");
  return (SUCCESS);
}
