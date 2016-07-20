/*
** about_termcaps.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:14:11 2016
** Last update Sun Jun  5 19:41:33 2016 retyt
*/

#include <stdlib.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

static void	save_term_attr(struct termios *term_attr,
			       struct termios *term_attr_save)
{
  unsigned int	size;
  unsigned int	i;
  char		*area_src;
  char		*area_dest;

  i = 0;
  area_src = (char*)term_attr;
  area_dest = (char*)term_attr_save;
  size = sizeof(*term_attr);
  while (i < size)
    {
      area_dest[i] = area_src[i];
      i += 1;
    }
}

int	init_termcaps(char **env, struct termios *term_attr,
		      struct termios *term_attr_save)
{
  char	term_buf[TERM_BUF_SIZE];
  char	*term_name;

  if ((term_name = search_in_env(env, "TERM=")) == NULL)
    return (my_putstr("error: could not determine your terminal\n", 2));
  if ((tgetent(term_buf, term_name)) <= 0)
    {
      if (((my_putstr("error: could not find termcap base or \"", 1)) == -1)
	  || (my_putstr(term_name, 1)) == -1
	  || (my_putstr("\" is not specified\n", 1) == -1))
	return (-1);
      return (-1);
    }
  if (tcgetattr(1, term_attr) < 0)
    return (my_putstr("error: could not get term values\n", 2));
  save_term_attr(term_attr, term_attr_save);
  term_attr->c_lflag &= ~ICANON;
  term_attr->c_lflag &= ~ECHO;
  term_attr->c_cc[VMIN] = 1;
  term_attr->c_cc[VTIME] = 0;
  if ((tcsetattr(1, TCSANOW, term_attr)) < 0)
    return (my_putstr("error: could not set term values\n", 2));
  return (0);
}

void	restore_shell(char **files_completition)
{
  int	i;

  i = 0;
  while (files_completition && files_completition[i])
    {
      free(files_completition[i]);
      i += 1;
    }
  if (files_completition)
    {
      free(files_completition[i]);
      free(files_completition);
    }
}
