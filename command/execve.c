#include "ft_minishell.h"
void check_build_in(t_command_and_flag *all,int *pipe_1,int fd1, t_env *env)
{
	//pwd
	if((!ft_strncmp(all->command,"/bin/pwd",9) || !ft_strncmp(all->command,"pwd",4))  && fd1)
		ft_pwd(env->env,fd1);
	if(!ft_strncmp(all->command,"/bin/pwd",9) && pipe_1!=0)
		ft_pwd(env->env,pipe_1[1]);
	if(!ft_strncmp(all->command,"/bin/pwd",9))
		ft_pwd(env->env,0);
	//env
	if(!ft_strncmp(all->command,"/usr/bin/env",13) && fd1)
		ft_env(all,env->env,fd1);
	if(!ft_strncmp(all->command,"/usr/bin/env",13) && pipe_1!=0)
		ft_env(all,env->env,pipe_1[1]);
	if(!ft_strncmp(all->command,"/usr/bin/env",13))
		ft_env(all,env->env,0);
	//echo
	if(!ft_strncmp(all->command,"/bin/echo",10)&& fd1)
		ft_echo(all,fd1);
	if(!ft_strncmp(all->command,"/bin/echo",10)&& pipe_1!=0)
		ft_echo(all,pipe_1[1]);
	if(!ft_strncmp(all->command,"/bin/echo",10))
		ft_echo(all,0);
	//cd
	if(!ft_strncmp(all->command,"/usr/bin/cd",13))
		exit(ft_cd(all,env->env));
	//unset
	if(!ft_strncmp(all->command,"unset",6))
		exit(ft_unset(all,env));
	//export
	if(!ft_strncmp(all->command,"export",7) && fd1)
	{	
		exit(ft_export(all,fd1,env));
	}
	else if(!ft_strncmp(all->command,"export",7) && pipe_1!=0)
	{
		exit(ft_export(all,pipe_1[1],env));
	}
	else if(!ft_strncmp(all->command,"export",7))
	{
		exit(ft_export(all,0,env));
	}
	//<<
	if(all->pape==DOUBLE_LESS && fd1)
		ft_double_less_print(all,fd1);
	if(all->pape==DOUBLE_LESS && pipe_1!=0)
		ft_double_less_print(all,pipe_1[1]);
	if(all->pape==DOUBLE_LESS)
		ft_double_less_print(all,0);
}
void redirect(t_command_and_flag *all,int *fd1,int *fd2)
{
	if(all->pape==MORE)
		*fd1=open(all->command,O_WRONLY|O_TRUNC);
	else if(all->pape==DOUBLE_MORE)
		*fd1=open(all->command,O_WRONLY|O_APPEND);
	else if(all->pape==LESS)
		*fd2=open(all->command,O_RDONLY);
}
t_command_and_flag *redirect2(t_command_and_flag *all)
{
	int fd;
	
	fd=0;
	while(all && ( all->pape==MORE || all->pape==DOUBLE_MORE || all->pape==LESS))
	{
		if(all->pape==MORE)
		{
			fd=open(all->command,O_WRONLY|O_TRUNC);
			close(fd);
		}
		else if(all->pape==DOUBLE_MORE)
		{
			fd=open(all->command,O_WRONLY|O_APPEND);
			close(fd);	
		}
		else if(all->pape==LESS)
		{
			fd=open(all->command,O_RDONLY);
			close(fd);
		}
		all=all->next;
	}
	return(all);
}

pid_t test(t_command_and_flag *all,int *pipe_1,int *pipe_2,int fd1,int fd2, t_env *env)
{
	struct stat buff;
	if(pipe_2!=0)
		pipe(pipe_2);
	pid_t pid=fork();
	g_global_pid = pid; /// add global pid
	if(!pid)
	{
		check_build_in(all,pipe_1,fd1,env);
		if(pipe_1!=0 )
		{
			dup2(pipe_1[1],1);
			close(pipe_1[1]);
			close(pipe_1[0]);//add function close_fd -5 lines
		}
		if(pipe_2!=0)
		{
			dup2(pipe_2[0],0);
			close(pipe_2[1]);
			close(pipe_2[0]);
		}
		if(fd1)
		{
			dup2(fd1,1);
			close(fd1);
		}
		if(fd2)
		{
			dup2(fd2,0);
			close(fd2);
		}
		if(stat(all->command,&buff))
		{
			exit(1);
		}
		if(!ft_strncmp(all->command,"a.out",6))
			exit(0);		
		if(execve(all->command,all->array_flags,env->env))
			exit(0);
	}
	if(pipe_1!=0)
	{
		close(pipe_1[1]);
		close(pipe_1[0]);
	}
	return(pid);
}

t_command_and_flag *ft_double_less(char *split)
{
	char *str;
	int len;
	t_command_and_flag *all;

	all=malloc(sizeof(t_command_and_flag));
	if(!all)
		return 0;
	all->command=ft_strdup(split);
	all->array_flags=0;
	all->array_flags=new_array_add(all->array_flags,split);
	len=ft_strlen(split);
	while(1)
	{
		str = term_from_double_less();
		if (str == NULL)
			break ;
		if(!ft_strncmp(str,split,len+1))
			break;
		all->array_flags=new_array_add(all->array_flags,str);
		free(str);
	}
	all->pape=DOUBLE_LESS;
	free(str);
	return(all);
}
void free_tmp(t_command_and_flag *tmp)
{
	int i;
 	
	i=-1;
	free(tmp->command);
 	while (tmp->array_flags[++i])
	 free(tmp->array_flags[i]);
	free(tmp->array_flags[i]);
	free(tmp->array_flags);
	free(tmp);
}
void number_of_pipes(int *size,t_command_and_flag **head1,t_command_and_flag **new_head)
{
	//1 | 2 > 3 >> 4 < 5; 6 eof
	t_command_and_flag *head;
	t_command_and_flag *tmp;
	
	tmp=0;
	head=*head1;
	*size=0;
	if(head->pape==MORE || head->pape==DOUBLE_MORE)
		*size=-1;
	ft_list_push_front(new_head,head);
	head=head->next;
	while(head)
	{
		
		if(head->pape!=MORE && head->pape!=DOUBLE_MORE &&head->pape!=LESS )
			*size+=1;
		if(head->pape==DOUBLE_LESS)
		{
			tmp=ft_double_less(head->command);
			ft_list_push_second(new_head,tmp);
			free_tmp(tmp);
		}
		else
			ft_list_push_front(new_head,head);
		head = head->next;
	}
}
int **make_pipe(int size)
{
	int **pipe;
	int i;

	i = 0;
	if(size < 0)
		return(0);
	pipe = malloc(sizeof(int*) * (size + 2));
	if(!pipe)
		return 0;
	pipe[i++] = NULL;
	while(i <= size)
	{
		pipe[i] = malloc(sizeof(int) * 2);
		if(!pipe[i++])
			return(0);
	}
	pipe[size+1]=NULL;
	return(pipe);
}
void export_errors(t_command_and_flag *all)
{
	int i;
	int i1;
	int flag;

	i = 1;
	if(!all->array_flags[i])
		return;
	while(all->array_flags[i])
	{
		flag=0;
		i1=0;
		while (all->array_flags[i][i1] && all->array_flags[i][i1]!='=')
			i1++;
		if(all->array_flags[i][i1]=='=')
		{	
			all->array_flags[i][i1]='\0';
			flag=1;
		}
		if(!ft_check_name(all->array_flags[i]) && !ft_check_name(&all->array_flags[i][1]))
		{	
			ft_putstr_fd("minishell: export: '",0);
			ft_putstr_fd(all->array_flags[i],0);
			ft_putstr_fd("': not a valid identifier\n",0);
		}
		if(flag)
			all->array_flags[i][i1]='=';
		i++;
	}
}
void print_errors(pid_t *pid,t_command_and_flag *reverse_head,int size,t_env *env)
{
	int fd1;
	while(size>=0)
	{	
		waitpid(pid[size],&fd1,0);
		pid[size]=0;
		ft_putstr_fd("\n",0);
		ft_putstr_fd(reverse_head->command,0);
		ft_putnbr_fd(fd1, 0);
		ft_putstr_fd("\n",0);
		while(reverse_head && ( reverse_head->pape==MORE || reverse_head->pape==DOUBLE_MORE || reverse_head->pape==LESS))
		{
			if(reverse_head->pape==LESS && (reverse_head->f_error==-3 || reverse_head->f_error==-1))
			{
				ft_putstr_fd("minishell: ",0);
				ft_putstr_fd(reverse_head->array_flags[1],0);
				ft_putstr_fd(": No such file or directory\n",0);
			}
			else if(reverse_head->pape==LESS && reverse_head->f_error==-2)
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'",0);
			else if((reverse_head->pape==MORE || reverse_head->pape==DOUBLE_MORE)&& reverse_head->f_error==-1)
			{
				ft_putstr_fd("minishell: ",0);
				ft_putstr_fd(reverse_head->array_flags[1],0);
				ft_putstr_fd(": No such file or directory\n",0);
			}
			else if((reverse_head->pape==MORE || reverse_head->pape==DOUBLE_MORE)&& reverse_head->f_error==-2)
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'",0);
			else if((reverse_head->pape==MORE || reverse_head->pape==DOUBLE_MORE)&& reverse_head->f_error==-2)
			{
				ft_putstr_fd("minishell: ",0);
				ft_putstr_fd(reverse_head->array_flags[1],0);
				ft_putstr_fd(": Permission denied\n",0);
			}
			reverse_head=reverse_head->next;
		}
		if(!ft_strncmp(reverse_head->command,"export",7))
			while(reverse_head->array_flags);
		else if(!ft_strncmp(reverse_head->command,"unset",6))
			while(reverse_head->array_flags);
		else if(fd1!=0)
		{	
			if(!ft_strncmp(reverse_head->command,"/usr/bin/env",13))
			{	
				ft_putstr_fd("env: ",0);
				ft_putstr_fd(reverse_head->array_flags[1],0);
				ft_putstr_fd(": No such file or directory",0);
				env->exit_num=127;
			}
			else if(!ft_strncmp(reverse_head->command,"/usr/bin/cd",13))
			{
				ft_putstr_fd("cd: no such file or directory: ",0);
				ft_putstr_fd(reverse_head->array_flags[1],0);
				env->exit_num=1;
			}
			else if(reverse_head->f_error==WRONG_COMMAND && fd1==256)
			{
				ft_putstr_fd("zsh: command not found:",0);
				ft_putstr_fd(reverse_head->command,0);
				env->exit_num=127;
			}
			else if(fd1==256)
				env->exit_num=1;
			else 
				env->exit_num=0;
			ft_putstr_fd("\n",0);
		}
		ft_putnbr_fd(env->exit_num, 0);
		ft_putstr_fd("\n", 0);
		size--;
		reverse_head=reverse_head->next;
	}
		while(reverse_head && ( reverse_head->pape==MORE || reverse_head->pape==DOUBLE_MORE || reverse_head->pape==LESS))
		{
			if(reverse_head->pape==LESS && (reverse_head->f_error==-3 || reverse_head->f_error==-1))
			{
				ft_putstr_fd("minishell: ",0);
				ft_putstr_fd(reverse_head->array_flags[1],0);
				ft_putstr_fd(": No such file or directory\n",0);
			}
			else if(reverse_head->pape==LESS && reverse_head->f_error==-2)
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'",0);
			else if((reverse_head->pape==MORE || reverse_head->pape==DOUBLE_MORE)&& reverse_head->f_error==-1)
			{
				ft_putstr_fd("minishell: ",0);
				ft_putstr_fd(reverse_head->array_flags[1],0);
				ft_putstr_fd(": No such file or directory\n",0);
			}
			else if((reverse_head->pape==MORE || reverse_head->pape==DOUBLE_MORE)&& reverse_head->f_error==-2)
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'",0);
			else if((reverse_head->pape==MORE || reverse_head->pape==DOUBLE_MORE)&& reverse_head->f_error==-2)
			{
				ft_putstr_fd("minishell: ",0);
				ft_putstr_fd(reverse_head->array_flags[1],0);
				ft_putstr_fd(": Permission denied\n",0);
			}
			reverse_head=reverse_head->next;
		}

}
void find_function(int size,t_env *env,t_command_and_flag *head,t_command_and_flag *reverse_head)
{
	int **pipe;
	int i;
	int fd1;
	int fd2;
	pid_t *pid;
	i = -1;
	fd1 = 0;
	fd2 = 0;
	(void)reverse_head;
	pipe = make_pipe(size);
	pid=malloc(sizeof(pid)*(size+1));//free
	if(!pid)
		return;
	while(++i<=size)
	{
		if(head && ( head->pape==MORE || head->pape==DOUBLE_MORE || head->pape==LESS))
			redirect(head,&fd1,&fd2);
		while(head && ( head->pape==MORE || head->pape==DOUBLE_MORE || head->pape==LESS))
			head = redirect2(head);
		pid[i]=test(head,pipe[i],pipe[i+1],fd1,fd2,env);
		fd1 = 0;
		fd2=0;
		head=head->next;
	}
	print_errors(pid,reverse_head,size,env);
	i=size;
	i = 0;
	free(pipe[i++]);
	while(pipe[i])
		free(pipe[i++]);
	free(pipe[i]);
	free(pipe);
	free(pid);
}
int functions_launch(t_command_and_flag **head,t_env *struct_env,int *lvl)
{
	t_command_and_flag *current_head;
	t_command_and_flag *tmp;
	int size;
	int i;
	int ret=-1;
	tmp=0;
	i=0;
	char **argv;
	char *tmp_2;
	current_head=*head;
	size=0;
	number_of_pipes(&size,&current_head,&tmp);
	printf("%d\n",size);
	if(!ft_strncmp(tmp->command,"export",7) && size==0)
	{
		ft_export(tmp,0,struct_env);
		export_errors(tmp);
	}
	else if(!ft_strncmp(tmp->command,"unset",6) && size==0)
	{
		ft_unset(tmp,struct_env);
		export_errors(tmp);
	}
	else if(size==0 &&!ft_strncmp(tmp->command,"/usr/bin/cd",13))
		ft_cd(tmp,struct_env->env);
	else if(!ft_strncmp(tmp->command,"exit",5))
	{
		if(tmp->array_flags[1])
		{
			if(ft_atoi(tmp->array_flags[1])>0)
				ret=ft_atoi(tmp->array_flags[1])%256;
			else
			{
				ret=ft_atoi(tmp->array_flags[1]);
				while (ret<0)
				{
					ret=256+ret;
				}
				
			}

		}
		else
			ret=0;		
	}
	else if(size>=0 || (size==0 && tmp->pape==MORE) || (size==0 && tmp->pape==DOUBLE_MORE)||(size==0 && tmp->pape==LESS))
		find_function(size,struct_env,tmp,*head);
	ft_list_clear(tmp);
	if(!ft_strncmp(current_head->command,"a.out",5))
	{
		(*lvl)++;
		argv=(char**)malloc(sizeof(char*)*3);
		if(!argv)
			return(0);
		argv[0]=ft_strdup("a.out");
		tmp_2 = ft_itoa(*(lvl));
		argv[1]=ft_strdup(tmp_2);
		free(tmp_2);
		argv[2]=0;
		struct_env->exit_num=main_dup(2,argv,struct_env->env);
		while (argv[i])
			free(argv[i++]);
		free(argv);
	}
	ft_putnbr_fd(struct_env->exit_num, 0);
	return(ret);
}
