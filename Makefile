##
## Makefile for  in /home/fernan_w/Téléchargements/42sh
## 
## Made by 
## Login   <fernan_w@epitech.net>
## 
## Started on  Wed Jun  1 18:11:42 2016 
## Last update Wed Jun  8 10:46:28 2016 
##

CC=		gcc

NAME=		42sh

SRC=		add_rm.c \
		auto_completion.c \
		auto_completion_sur_path.c \
		background.c \
		bg.c \
		buffer.c \
		builtins.c \
		cd_adds.c \
		centrer.c \
		cgt_line.c \
		ch_list-en-str.c \
		clr.c \
		command_or_alias.c \
		comp_comm_alias.c \
		complete_string.c \
		completion_cut.c \
		completion_en_liste.c \
		curseur.c \
		disp_poss.c \
		droits.c \
		eddons_read.c \
		env.c \
		env_option.c  \
		env_tools.c \
		error_report.c \
		exec.c \
		filtre_auto_completion.c \
		gestion_arg.c \
		gestion_quotes.c \
		gestion_stage_metro.c \
		get_next_line.c \
		globb.c \
		histo.c \
		histo_list.c \
		historic.c \
		info_path.c \
		info_termcaps.c \
		info_var.c \
		init_all.c \
		input_en_list.c \
		le_bon_env.c \
		le_parseur.c \
		le_prompt.c \
		les_alias.c \
		les_alias_e.c \
		les_args.c \
		les_puts.c \
		les_redir.c \
		les_sigs.c \
		l_histo.c \
		list_pour_output.c \
		main_bis.c \
		main.c \
		mv_curseur_bis.c \
		mv_curseur.c \
		mv_curseur_ter.c \
		my_memset.c \
		our_cd.c \
		our_echo.c \
		our_echo_tools.c \
		our_exit.c \
		outils_prompt.c \
		process_des_paths.c \
		process_list.c \
		read_list.c \
		recup_ac_av.c \
		redir_clean.c \
		redirections.c \
		replace_it.c \
		rev_str.c \
		replace_var_in_str.c \
		script_du_prompt.c \
		set_all.c \
		source.c \
		stage.c \
		ta_free_ta_tout_compris.c \
		tools_completions.c \
		tools_redirections.c \
		tout_les_outils_du_monde.c \
		unset.c \
		use_env.c \
		verif_true.c \
		var_completion.c \
		fg.c \
		export.c \
		clean_str.c

OBJ=		$(SRC:.c=.o)

CFLAGS=		-Wall -Wextra -W -Iincludes

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) -lncurses -L -lmy libmy.a

clean:
		rm -f $(OBJ)
		rm -f *~

fclean:		clean
		rm -f $(NAME)

re:		fclean all
