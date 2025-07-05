/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:39:49 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/25 17:50:54 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "limits.h"
# include "signal.h"
# include "stdbool.h"
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>

extern int				g_status;

enum
{
	AJOUTER,
	FREYI
};

typedef enum token_type
{
	REDIRECT_IN,
	REDIRECT_APPEND,
	HEREDOC,
	REDIRECT_OUT,
	SPC,
	STRING,
	PIPE,
	DOUBLE_Q,
	SINGLE_Q,
	VAR,
	EXIT_STATUS,
	DOUBLE_DLR
}						t_token_type;

typedef struct s_free
{
	void				*add;
	struct s_free		*next;
}						t_free;

typedef struct s_fd
{
	int					fd;
	struct s_fd			*next;
}						t_fd;

typedef struct s_token_node
{
	int					type;
	char				*value;
	bool				flag;
	int					fd_hrd;
	struct s_token_node	*next;
}						t_token_node;

typedef struct command_node
{
	char				**argv;
	int					infile;
	int					outfile;
	bool				isfirst;
	bool				islast;
	int					pipe_fd[2];
	t_token_node		*red;
	struct command_node	*next;
}						t_cmd;

typedef struct s_env_var
{
	char				*cle;
	char				*value;
	struct s_env_var	*next;
	bool				env_flag;
}						t_env_var;

typedef struct s_pwd_data
{
	char				*pwd_before;
	char				*oldpwd_before;
	char				oldpwd[PATH_MAX];
	char				newpwd[PATH_MAX];
}						t_pwd_data;

typedef struct s_minishell
{
	t_env_var			*envp;
	t_cmd				*cmd_list;
	char				logical_pwd[PATH_MAX];
	int					exit_status;
}						t_minishell;

int						search_hrd(t_token_node *debut);
int						oui_space(char *str);
int						ft_fofo(char *str, char c);

char					**split_words_and_spaces(const char *str);
char					*join_flag_tokens(t_token_node **cur);

bool					is_strict_assign_token(const char *value);
bool					is_assign_form(const char *value);
bool					start_zone_has_equal(t_token_node *start);

t_token_node			*change_flag(t_token_node *debut);
t_token_node			*regrouper_tokens_marques(t_token_node *head);
t_token_node			*fix_isolated_flagged_tokens(t_token_node *head);

t_cmd					*ft_prepare_cmd(t_token_node *debut_token,
							t_env_var *debut_env, t_minishell *data);
void					handle_input(t_env_var *debut_env, t_minishell *data);

void					clean_cmd_line(char *command);
int						invalide_fd_hrdc(t_token_node *debut);
void					unset_free(t_env_var *current, int status);
size_t					ft_strlen(const char *str);
int						is_space(char c);
int						ft_isalnum(int c);
int						ft_isdigit(int c);
int						is_quotes(char c);
int						is_redirection(char c);
int						is_red(int type);
int						validate_quotes(char *command, bool print);
int						validate_redirections(t_token_node *debut, bool print);
int						validate_pipe_position(t_token_node *debut, bool print);
int						check_double_pipe_error(t_token_node *debut,
							bool print);
int						verify_cmd(t_token_node *debut_token, char *command,
							bool print);
int						valide_delimiter(int type);
int						readline_hdc(char *delimiter, t_env_var *env, int flag,
							t_minishell *data);
int						write_to_file(char *buffer);
int						is_espace(char c);
int						ft_count_args_cmd(t_token_node *debut);

char					*ft_strdup(const char *s);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_itoa(int n);
char					*lstlast_token(t_token_node *cur);
char					*ft_delimiter(t_token_node **debut, int *flag);
char					*decoupe_chaine_en_segment(char *str_var);

char					*expand_segment(char *str_var, t_env_var *env,
							t_minishell *data);
char					*get_var_sigle_dolar(char *str_var, t_env_var *env);
char					*ft_get_var(char *str_var);
char					*get_var_depui_env(t_env_var *env, char *get_var);
char					*add_cmd_dn_buffer(char *cmd, char *buffer);
char					**ft_decoupe_en_mots(char *token_value);
char					*expand_vars_and_heredoc(char *cmd, t_env_var *env,
							t_minishell *data);
void					init_env(t_env_var **debut_env, char **env,
							t_minishell *data);
void					*ft_malloc(size_t size);
t_free					*add_new_free(void *rest);
void					add_fin_free(t_free **debut, t_free *new);
void					ft_free_all(t_free *debut);
void					free_env(t_env_var *debut);
void					add_lst_back_token(t_token_node **debut_token,
							t_token_node *new);
void					ft_string(int i, char *commande,
							t_token_node **debut_token);
void					ft_espase(int *i, char *commande,
							t_token_node **debut_token);
void					ft_single_double_qoutes(int i, char *command,
							t_token_node **debut_token);
void					ft_redirection(int i, char *command,
							t_token_node **debut_token);
void					ft_dollar(int *i, char *command,
							t_token_node **debut_token);
void					suprime_qoutes(t_token_node *debut);
void					add_lst_back_env(t_env_var **lst, t_env_var *new_node);
void					ft_herdoc(t_token_node *debut, t_env_var *env,
							t_minishell *data);
void					clean_exit(char *commande, t_minishell *data);
void					ft_handler_signal(void);
void					handel_herdoc(int sig);
void					add_lst_back_cmd(t_cmd **debut_cmd, t_cmd *new);
void					new_redirection(t_token_node *debut_tmp,
							t_token_node **new, t_token_node **debut_red);
t_token_node			*gestion_input(char **command,
							t_token_node **debut_token, t_env_var *env,
							t_minishell *data);
t_token_node			*ft_tokenization(char *command,
							t_token_node **debut_token);
t_token_node			*new_token(int type_token, char *value, int fd);

t_token_node			*expand_var(t_token_node *debut, t_env_var *env,
							t_minishell *data);
t_token_node			*ft_concate_tkn(t_token_node *debut);
t_token_node			*remove_red(t_token_node *debut);
t_token_node			*remove_invalid_tokens(t_token_node *debut);

t_cmd					*set_cmd_false_true(t_cmd **cmds);
t_cmd					*token_list_to_cmd_list(t_token_node *debut);
t_cmd					*ft_split_cmd(t_token_node *debut_tmp);
t_cmd					*new_cmd(char **args, t_token_node *debut_red);

// excution
int						is_builtin(char *cmd);
void					execute_cmds(t_minishell *data);
void					exec_builtin(t_cmd *cmd, t_minishell *data);
void					exec_echo(char **argv, t_minishell *data);
void					exec_cd(char **argv, t_minishell *data);
int						env_size(t_env_var *env);
void					exec_export(char **argv, t_env_var *envp,
							t_minishell *data);
void					exec_exit(char **argv, bool is_forked,
							t_minishell *data);
bool					check_varname(const char *arg);
void					exec_unset(t_env_var **env, char **argv,
							t_minishell *data);
t_env_var				*get_env_value(t_env_var *env, const char *key);
t_env_var				*add_new_env(char *key, char *value, bool env_flag);
void					clear_cmd_list(t_cmd **cmd_list);
char					**env_to_tab(t_env_var *env);
void					restore_fd(t_cmd *cmd);
int						set_redirection(t_cmd *cmd, t_minishell *data);
char					**env_to_tab(t_env_var *env);
char					**get_path_directories(char **env);
char					*get_full_path_from_paths(char *command, char **paths);
void					ft_free_split(char **split);
char					*find_command_path(const char *command, char **env,
							t_minishell *data);
void					exec_external(t_cmd *cmd, t_minishell *data);
void					execute_pipeline(t_cmd *cmd, t_minishell *data);
void					close_fds_except_std(void);
void					free_env(t_env_var *env);
char					*get_env_value_char(t_env_var *env, const char *key);
void					update_or_add_env_value(t_env_var **env, char *key,
							char *value, bool env_flag);
void					close_fds_except_std(void);
void					check_exit_status(int has_error, t_minishell *data);
void					set_env_value(t_env_var **env, char *key, char *value);
bool					is_append_export(const char *arg);
void					print_sorted_env(t_env_var *env);
void					sort_env_tab(char **tab);
void					ignore_sig(void);
int						get_physical_pwd(char *buffer);
int						get_logical_pwd(char *buffer, t_env_var *envp);
char					*join_path(const char *base, const char *relative);
void					exec_env(char *argv, t_env_var *env, t_minishell *data);
void					handle_empty_executor(char *path, char **envp);
void					restore_sig(void);
int						fail_redirection(t_cmd *cmd);
void					handle_children(t_cmd *cmd, char **envp,
							t_minishell *data);
// Errors

void					error_command_not_found(const char *cmd,
							t_minishell *data);
void					error_permission_denied(const char *cmd,
							t_minishell *data);
void					error_no_such_file(const char *cmd, t_minishell *data);
void					error_fork(t_minishell *data);
void					error_open_file(const char *filename,
							t_minishell *data);
void					error_is_directory(const char *cmd);
void					error_open_dir(void);
void					handle_cd_error(char *target_dir, t_minishell *data);

// libf utils

long					ft_atol(const char *str);
int						ft_isalpha(int c);
char					**ft_split(char const *s, char c);
char					*ft_strchr(const char *s, int c);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *str1, const char *str2,
							size_t n);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
int						ft_strcmp(const char *s1, const char *s2);
void					ft_putstr_fd(const char *s, int fd);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strcpy(char *dest, const char *src);

#endif