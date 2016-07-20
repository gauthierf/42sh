/*
** get_prompt.c for  in /home/fernan_w/Téléchargements/backup/start
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:03:36 2016
** Last update Wed Jun  8 09:38:55 2016 
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "parser.h"
#include "get_next_line.h"
#include "my.h"

static const t_prcode	g_prkw[] =
  {
    {'u', "USER", &get_username},
    {'p', "PWD", &prompt_get_wd},
    {'P', NULL, &prompt_mini_wd},
    {'h', NULL, &get_hostname},
    {'$', "$", &prompt_kw_char},
    {'S', NULL, &prompt_script},
    {'k', "\033[0;30m", &prompt_kw_char},
    {'r', "\033[0;31m", &prompt_kw_char},
    {'v', "\033[0;32m", &prompt_kw_char},
    {'y', "\033[0;33m", &prompt_kw_char},
    {'b', "\033[0;34m", &prompt_kw_char},
    {'m', "\033[0;35m", &prompt_kw_char},
    {'c', "\033[0;36m", &prompt_kw_char},
    {'w', "\033[0;37m", &prompt_kw_char},
    {'K', "\033[1;30m", &prompt_kw_char},
    {'R', "\033[1;31m", &prompt_kw_char},
    {'V', "\033[1;32m", &prompt_kw_char},
    {'Y', "\033[1;33m", &prompt_kw_char},
    {'B', "\033[1;34m", &prompt_kw_char},
    {'M', "\033[1;35m", &prompt_kw_char},
    {'C', "\033[1;36m", &prompt_kw_char},
    {'W', "\033[1;37m", &prompt_kw_char},
    {'N', "\033[0m", &prompt_kw_char}
  };

static char	*get_prompt_kw(char c, t_mini *shell, t_ps *pr)
{
  int		i;
  char		*ret;

  i = 0;
  while (g_prkw[i].funct && g_prkw[i].code != c)
    i++;
  if (g_prkw[i].funct)
    {
      if (!(ret = g_prkw[i].funct(g_prkw[i].var, shell)))
	return (NULL);
      if (i < 5)
	pr->len += my_strlen(ret);
      return (ret);
    }
  return (NULL);
}

static void	put_prompt_kw(char c, t_mini *shell, t_ps *pr, int *j)
{
  char		*tmp1;
  char		*tmp2;

  tmp1 = pr->str;
  pr->str = my_append(pr->str, (tmp2 = get_prompt_kw(c, shell, pr)));
  (*j) += my_strlen(tmp2);
  free(tmp1);
  free(tmp2);
}

static t_ps	*prompt_parser(char *s, t_ps *pr, t_mini *shell)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (s && s[i])
    {
      if (s[i] == '$' && s[i + 1])
	put_prompt_kw(s[++i], shell, pr, &j);
      else if (s[i] == '\\' && s[i + 1] == 'n')
	{
	  append_one_char(pr, '\n', &j);
	  i++;
	}
      else
	append_one_char(pr, s[i], &j);
      i++;
    }
  pr->str[j] = '\0';
  return (pr);
}

t_ps	*put_prompt(char *base, t_mini *shell)
{
  t_ps	*pr;

  if (!(pr = malloc(sizeof(t_ps)))
      || !(pr->str = malloc(my_strlen(base) + 2))
      || !(pr->str = memset(pr->str, 0, my_strlen(base))))
    return (NULL);
  if (!isatty(0))
    return (pr);
  return (prompt_parser(base, pr, shell));
}
