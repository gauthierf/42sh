/*
** prompt_tools.c for  in /home/fernan_w/Téléchargements/backup/start
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:03:15 2016
** Last update Wed Jun  8 09:57:18 2016 
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include "tools.h"
#include "builtins.h"
#include "my.h"

char	*prompt_kw_char(char *str, t_mini *shell)
{
  (void)shell;
  return (my_str_copy(str, 0));
}

char	*prompt_get_wd(char *ignore, t_mini *shell)
{
  (void)ignore;
  (void)shell;
  return (getcwd(NULL, 0));
}

char		*get_homedir()
{
  struct passwd	*pwd;
  char		*homedir;

  if (!(pwd = getpwuid(getuid())))
    return (NULL);
  else
    homedir = my_str_copy(pwd->pw_dir, 0);
  endpwent();
  return (homedir);
}

char		*get_username(char *nothing, t_mini *shell)
{
  struct passwd	*pwd;
  char		*username;

  (void)nothing;
  (void)shell;
  if (!(pwd = getpwuid(getuid())))
    return (NULL);
  else
    username = my_str_copy(pwd->pw_name, 0);
  endpwent();
  return (username);
}

char	*get_hostname(char *nothing, t_mini *shell)
{
  int	fd;
  int	red;
  char	*ehost;
  char	host[50];

  (void)nothing;
  ehost = NULL;
  red = 0;
  if (!(ehost = clean_var(find_str_in_tab("HOST", shell->env)))
      && !(ehost = clean_var(find_str_in_tab("HOSTNAME", shell->env))))
    {
      if ((fd = open("/etc/hostname", O_RDONLY)) > 0
	  && (red = read(fd, host, 50 - 1)) >= 0)
	{
	  if (host[red - 1] == '\n')
	    red--;
	  host[red] = '\0';
	  return (my_str_copy(host, 0));
	}
    }
  return (ehost);
}
