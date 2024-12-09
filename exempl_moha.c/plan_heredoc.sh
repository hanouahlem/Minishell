typedef struct t_hd 
{
	int pipe_fd[2];
	char *delim;
}	t_hd;

t_mini 
{


	t_hd *hd;
	int nbhd;
}


initheredoc(t_hd hd, str)
{
	hd.delim = getdelim(str)
	pipe(hd.pipe);
}

heredoc()
{
	mini.nbhd = count_hd();
	mini.hd = malloc(mini.nbhd * sizeof(t_here))
	while i < mini.nbhd
		initheredoc(&mini.hd[i], str)
}

main
{
	heredoc()
	exec()
}


"<< avion | cat << bateau | test << mer << chevre << grec"

hd[0].delim = "avion"
hd[1].delim = "bateau"
hd[2].delim = "mer"
hd[3].delim = "chevre"
hd[4].delim = "grec"