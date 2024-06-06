#include "minishell.h"

void handeler(int sig)
{
	rl_on_new_line();
}

int main()
{
	int i = 1;
	char *str = NULL;
	while (i <= 6)
	{
		str = readline("enter an message");
		add_history(str);
		free(str);
		i++;
		//system("clear");
		rl_redisplay();
	}
}
// int main()
// {
// 	char *s = readline("prompt\n");
// 	system("clear");
// 	sleep(1);
// 	rl_redisplay();
// 	s = readline("prompt2\n");
// 	sleep(1);
// }