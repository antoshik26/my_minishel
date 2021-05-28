#include "ft_minishell.h"

void test(t_command_and_flag *all,int *pipe_1,int *pipe_2,int fd, char **env)
{
	
	if(pipe_2!=0)
		pipe(pipe_2);
	if(!fork())
	{
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
		if(fd)
		{	
			dup2(fd,1);
			close(fd);
		}
		execve(all->command,all->array_flags,env);
	}
	if(pipe_1!=0)
	{
		close(pipe_1[1]);
		close(pipe_1[0]);
	}
}
t_command_and_flag *number_of_pipes(int *size,t_command_and_flag *head)
{
	//1 | 2 > 3 >> 4 < 5; 6 eof
	*size=0;
	if(head->pape==2)
		*size=-1;
	if(!head->f_error)
		head=head->next;
	else
	{
		*size=-1;
		return head->next;
	}
	while(head)
	{
		if(!head->f_error)
			*size+=1;
		else
			return(head);
		if(head->pape==2 || head->pape==3 ||head->pape==4 || head->pape==5 )
			return head->next;
		head = head->next;
	}
	return head;
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
void find_function(int size,char **env,t_command_and_flag *head)
{
	int **pipe;
	int i;
	int fd;

	i = -1;
	fd = 0;
	pipe = make_pipe(size);
	while(++i<=size)
	{
		if(head->pape==4)//add function check pipe to chosw correct options for open
		{
			fd=open(head->array_flags[1],O_WRONLY);
			head=head->next;
		}
		test(head,pipe[i],pipe[i+1],fd,env);
		fd = 0;
		head=head->next;
	}
	while(size--)
		wait(0);
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
char	*ftstrdup(const char *s1)
{
	char	*copy_s1;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s1[len] != '\0')
	{
		len++;
	}
	copy_s1 = (char *)malloc(sizeof(char) * (len + 1));
	if (copy_s1 == NULL)
		return (NULL);
	while (i < len)
	{
		copy_s1[i] = s1[i];
		i++;
	}
	copy_s1[i] = '\0';
	return (copy_s1);
}

void functions_launch(t_command_and_flag **head,char **env)
{
	t_command_and_flag *current_head;
	t_command_and_flag *tmp;
	int size;

	current_head=*head;
	while(current_head)
	{
		tmp = number_of_pipes(&size,current_head);
		printf("%d %s %p\n",size,current_head->command,tmp);
		if(size==-1 && tmp->f_error)
			printf("zsh: command not found:%s\n",current_head->command);
/*		else if(current_head->pape==4)
		{
			do_redirect()
		}*/
		else if(size>=0)
			find_function(size,env,current_head);
		current_head=tmp;
	}
}
/*
int main(int argc,char **argv,char **env)
{
	//function_lounch test
	//t_minishell *all;
	argc=0;
	printf("%s\n\n",argv[0]);
	//free(argv[0]);
	//char *a[2];
	//a[1] = argv[0];
	//a[2]=NULL;
	t_command_and_flag *head1;
	t_command_and_flag *head2;
	t_command_and_flag *head3;
	t_command_and_flag *head4;
	//all=malloc(sizeof(t_minishell));
	head1 = malloc(sizeof(t_command_and_flag));
	head2 = malloc(sizeof(t_command_and_flag));
	head3 = malloc(sizeof(t_command_and_flag));
	head4 = malloc(sizeof(t_command_and_flag));
	head1->command=ftstrdup("/usr/bin/wc");
	head1->next=0;
	head1->pape=1;
	head1->f_error=0;
	head2->command=ftstrdup("/bin/ls");
	head2->next=0;
	head2->pape=5;
	head2->f_error=0;
	head3->command=ftstrdup("/bin/ls");
	head3->next=0;
	head3->pape=1;
	head3->f_error=0;
	head4->command=NULL;
	//char a[3];
	head4->array_flags=malloc(sizeof(3));
	head4->array_flags[0]=argv[0];
	head4->array_flags[1]="k";
	head4->array_flags[2]=0;
	head4->next=0;
	head4->pape=4;
	head4->f_error=0;
	head4->next=head2;
	head2->next=head3;
	//head2->next=head3;
	head1->array_flags=argv;
	head2->array_flags=argv;
	head3->array_flags=argv;
	//head3->next=head4;
	functions_launch(&head4,env);
	//make_pipe test
	//int pipe1[2];
	//int pipe2[2];

	//test(head1,0,pipe1,0,env);
	//test(head2,pipe1,pipe2,0,env);
//	test(head3,pipe2,0,0,env);
//	wait(0);
//	wait(0);
//	wait(0);
}
*/