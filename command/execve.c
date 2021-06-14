#include "ft_minishell.h"
void check_build_in(t_command_and_flag *all,int *pipe_1,int fd1, t_env *env)
{
	//pwd
	if((!ft_strncmp(all->command,"/bin/pwd",9) || !ft_strncmp(all->command,"pwd",4))  && fd1)
		ft_pwd(all,env->env,fd1);
	if(!ft_strncmp(all->command,"/bin/pwd",9) && pipe_1!=0)
		ft_pwd(all,env->env,pipe_1[1]);
	if(!ft_strncmp(all->command,"/bin/pwd",9))
		ft_pwd(all,env->env,0);
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
		ft_export(all,fd1,env);
	if(!ft_strncmp(all->command,"export",7) && pipe_1!=0)
		ft_export(all,pipe_1[1],env);
	if(!ft_strncmp(all->command,"export",7))
		ft_export(all,0,env);
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
/*void ft_double_less(int fd,t_command_and_flag *all)
{
	int len;
	char *str;
	str=0;
	get_next_line(0,&str);
	len=ft_strlen(all->command);
	while (!ft_strncmp(all->command,str,len))
	{
		ft_putstr_fd(">",0);
		ft_putstr_fd(str,0);
		ft_putstr_fd(str,fd);
		ft_putstr_fd("\n",fd);
		free(str);
	}
	free(str);
	exit(0);

}*/
pid_t test(t_command_and_flag *all,int *pipe_1,int *pipe_2,int fd1,int fd2, t_env *env)
{
	struct stat buff;
	pid_t tmp=0;
	int k;
	if(pipe_2!=0)
		pipe(pipe_2);
	pid_t pid=fork();
	g_global_pid = pid; /// add global pid
	if(!pid)
	{
		check_build_in(all,pipe_1,fd1,env);
		if(pipe_1!=0)
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
		/*if(all->pape==DOUBLE_LESS)
		{
			tmp=fork();
			if(!tmp)
				ft_double_less(pipe_1[1],all);
		}*/
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
			exit(3);
		}
		execve(all->command,all->array_flags,env->env);
	}
	waitpid(tmp,&k,0);
	if(pipe_1!=0)
	{
		close(pipe_1[1]);
		close(pipe_1[0]);
	}
	return(pid);
}
void number_of_pipes(int *size,t_command_and_flag **head1,t_command_and_flag **new_head)
{
	//1 | 2 > 3 >> 4 < 5; 6 eof
	t_command_and_flag *head;

	head=*head1;
	*size=0;
	if(head->pape==MORE || head->pape==DOUBLE_MORE)
		*size=-1;
	ft_list_push_front(new_head,head);
	head=head->next;
	while(head)
	{
		if(head->pape!=MORE && head->pape!=DOUBLE_MORE &&head->pape!=LESS && head->pape!=DOUBLE_LESS)
			*size+=1;
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
	pipe[i++] = NULL;
	while(i <= size)
		pipe[i++] = malloc(sizeof(int) * 2);
	pipe[size+1]=NULL;
	return(pipe);
	
}
void print_errors(pid_t *pid,t_command_and_flag *reverse_head,int size)
{
	int fd1;

	while(size>=0)
	{	
		waitpid(pid[size],&fd1,0);
		while(reverse_head && ( reverse_head->pape==MORE || reverse_head->pape==DOUBLE_MORE || reverse_head->pape==LESS))
			reverse_head=reverse_head->next;
		ft_putnbr_fd(fd1,0);
		if(fd1!=0 && fd1!=256)
		{	
			if(!ft_strncmp(reverse_head->command,"/bin/pwd",9))
				ft_putstr_fd("pwd: too many arguments",0);
			else if(!ft_strncmp(reverse_head->command,"/usr/bin/env",13))
			{	
				ft_putstr_fd("env: ",0);
				ft_putstr_fd(reverse_head->array_flags[1],0);
				ft_putstr_fd(": No such file or directory",0);
			}
			else if(!ft_strncmp(reverse_head->command,"/usr/bin/cd",13))
			{
				ft_putstr_fd("cd: no such file or directory: ",0);
				ft_putstr_fd(reverse_head->array_flags[1],0);
			}
			else
			{
				ft_putstr_fd("zsh: command not found:",0);
				ft_putstr_fd(reverse_head->command,0);
			}
			ft_putstr_fd("\n",0);
		}
		size--;
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
	pipe = make_pipe(size);
	pid=malloc(sizeof(pid)*(size+1));
	while(++i<=size)
	{
		if(head && ( head->pape==MORE || head->pape==DOUBLE_MORE || head->pape==LESS))
			redirect(head,&fd1,&fd2);
		while(head && ( head->pape==MORE || head->pape==DOUBLE_MORE || head->pape==LESS))
			head = redirect2(head);
		if(head && head->pape==DOUBLE_LESS)
		{	
			fd2=1;
			ft_putchar_fd('>',0);	//write(1,'>',1);
		}
		pid[i]=test(head,pipe[i],pipe[i+1],fd1,fd2,env);
		fd1 = 0;
		fd2=0;
		head=head->next;
	}
	print_errors(pid,reverse_head,size);
	i=size;
	if(i>0)
	{
		i = 0;
		free(pipe[i++]);
		while(pipe[i])
			free(pipe[i++]);
		free(pipe[i]);
		free(pipe);
	}
}
void functions_launch(t_command_and_flag **head,t_env *struct_env)
{
	t_command_and_flag *current_head;
	t_command_and_flag *tmp;
	int size;
	tmp=0;
	current_head=*head;
	size=0;
	number_of_pipes(&size,&current_head,&tmp);
	printf("%d\n",size);
	if(!ft_strncmp(tmp->command,"export",7) && size==0)
		ft_export(tmp,0,struct_env);
	else if(!ft_strncmp(tmp->command,"unset",6) && size==0)
		ft_unset(tmp,struct_env);
	else if(size==0 &&!ft_strncmp(tmp->command,"/usr/bin/cd",13))
		ft_cd(tmp,struct_env->env);
	//else if(size==0 &&!ft_strncmp(tmp->command,"exit",5))
	//	ft_exit(tmp);
	else if(size>=0 || (size==0 && tmp->pape==MORE) || (size==0 && tmp->pape==DOUBLE_MORE)||(size==0 && tmp->pape==LESS))
		find_function(size,struct_env,tmp,current_head);
	ft_list_clear(tmp);
}
