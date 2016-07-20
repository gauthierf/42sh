/*
** main.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:20:17 2016
** Last update Wed Jun  8 10:30:44 2016 
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "readline.h"
#include "get_next_line.h"
#include "tools.h"
#include "my.h"

static const t_fct	g_func[] =
{
  {{27, 91, 68, 0, 0, 0, 0}, go_left},
  {{127, 0, 0, 0, 0, 0, 0}, rm_left},
  {{27, 91, 51, 126, 0, 0, 0}, rm_cur},
  {{27, 91, 67, 0, 0, 0, 0}, go_right},
  {{12, 0, 0, 0, 0, 0, 0}, clean_screen},
  {{5, 0, 0, 0, 0, 0, 0}, go_end},
  {{1, 0, 0, 0, 0, 0, 0}, go_start},
  {{11, 0, 0, 0, 0, 0, 0}, rm_after},
  {{23, 0, 0, 0, 0, 0, 0}, rm_before},
  {{4, 0, 0, 0, 0, 0, 0}, rm_or_quit},
  {{25, 0, 0, 0, 0, 0, 0}, past_clipboard},
  {{27, 91, 49, 59, 53, 67, 0}, go_next_word},
  {{27, 91, 49, 59, 53, 68, 0}, go_prev_word},
  {{27, 91, 65, 0, 0, 0, 0}, move_up_hist},
  {{16, 0, 0, 0, 0, 0, 0}, move_up_hist},
  {{27, 91, 66, 0, 0, 0, 0}, move_down_hist},
  {{14, 0, 0, 0, 0, 0, 0}, move_down_hist},
  {{9, 0, 0, 0, 0, 0, 0}, completition},
  {{0, 0, 0, 0, 0, 0, 0}, NULL}
};

int	get_key(t_rdd *reader, char *buf)
{
  int	i;

  i = 0;
  buf[reader->size_read] = 0;
  while (g_func[i].function && my_strcmp(buf, (char*)g_func[i].str) != 0)
    i += 1;
  if (g_func[i].function)
    {
      if ((g_func[i].function(reader)) == -1)
	return (-1);
    }
  else if (get_char(reader, buf) == -1)
    return (-1);
  if (buf[0] != 9)
    reader->is_completition = 0;
  return (0);
}

int		init_read_cmd(t_rdd *reader,  char **env, int fd,
			      char ***files_completition)
{
  static int	is_first;

  reader->list_read = NULL;
  reader->path = *files_completition;
  reader->current = 0;
  reader->is_rm = 0;
  reader->fd = fd;
  reader->is_completition = 0;
  reader->dir_cur = search_in_env(env, "PWD");
  reader->env = env;
  if (reader->path == NULL && search_in_env(env, "PATH="))
    if ((reader->path = get_path(search_in_env(env, "PATH="))) == NULL)
      return (my_putstr("error: could not read\n", 2));
  *files_completition = reader->path;
  if (is_first == 0)
    init_termcaps(env, &(reader->term_attr), &(reader->term_attr_save));
  else
    tcsetattr(1, TCSANOW, &(reader->term_attr));
  if (is_first == 0)
    is_first = 1;
  if ((my_tputs(tgetstr("im", NULL), 1)) == -1)
    return (-1);
  manage_signal(0, reader);
  return (0);
}

char	*out_read_cmd(t_rdd *reader)
{
  char	*str;

  str = NULL;
  if (reader->size_read == -1)
    return ((void*)(unsigned long)my_putstr("error: could not read\n", 1));
  if (reader->list_read || reader->size_read > 0)
    if ((str = list_to_str(reader->list_read, &(reader->historic))) == NULL)
      return (NULL);
  if ((write(1, "\n", 1)) == -1)
    return (NULL);
  if ((my_tputs(tgetstr("ei", NULL), 1)) == -1)
    return (NULL);
  tcsetattr(1, TCSANOW, &(reader->term_attr_save));
  return (str);
}

char			*read_cmd(int fd, char **env, char ***file_completition,
				  char *prompt)
{
  static t_rdd		reader;
  char			buf[SIZE_BUF + 1];
  char			*str;

  if ((init_read_cmd(&reader, env, fd, file_completition)) == -1)
    return (NULL);
  if (((reader.prompt = prompt)) && (my_putstr(reader.prompt, 1) == -1))
    return (NULL);
  buf_zero(buf, SIZE_BUF);
  if (isatty(0))
    signal(SIGINT, get_sigint);
  while ((reader.size_read = read(0, &buf, SIZE_BUF)) > 0 && buf[0] != '\n')
    {
      if ((get_key(&reader, buf)) == -1)
	return (NULL);
      buf_zero(buf, SIZE_BUF);
    }
  str = out_read_cmd(&reader);
  if (str && my_strcmp(str, "history") == 0)
    {
      if ((disp_historic(reader.historic)) == -1)
	return (NULL);
      return (read_cmd(fd, env, file_completition, prompt));
    }
  return (str);
}

char		*read_line(int fd,  char ***file_completition,  char **env,
			   char *prompt)
{
  static char	*term;
  static int	is_term;
  char		*str;

  str = NULL;
  if (term == NULL && is_term == 0)
    {
      is_term = 1;
      if ((term = search_in_env(env, "TERM=")) == NULL)
	is_term = -1;
    }
  if (fd == 0 && is_term == 1 && env && isatty(0) == 1)
    str = read_cmd(fd, env, file_completition, prompt);
  else
    {
      if (isatty(0))
	signal(SIGINT, get_sigint);
      if (prompt && isatty(0))
	if ((my_putstr(prompt, 1)) == -1)
	  return (NULL);
      str = get_next_line(fd);
    }
  return (str);
}
