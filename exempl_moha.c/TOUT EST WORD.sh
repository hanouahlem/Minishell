TOUT EST WORD
sauf REDIR et ce qui suit une REDIR est un FICHIER

< blabla < -R > ls < avion bateau echo > -c < -e cat
cmd = bateau
arg = echo cat
redir = < < > < > <
file = blabla -R ls avion -c -e


exec()
{
        OUVRIR FICHIER!!!!!!!!!!!!!!!!!!!
        ca foire on quitte + message erreur
        VERIFIER COMMAND
        ca foire on quitte
}

ls < infile1 -R -l | < infile1 > outfile1 echo bonjour > outfile2 >> append1 | < Makefile

ft_print_struct(){}
COMMANDE 1:
cmd = ls
arg = ls -R -l
type <
file infile1

COMMANDE 2:
cmd = echo
arg = echo bonjour
type < > > >>
file infile1 outfile1 outfile2 append1 

COMMANDE 3:
cmd = NULL
arg = NULL
type <
file Makefile



cmd1 > file1 > file2 cmd2 -opt1 -op2 | cmd3 < file3 < file4 cmd4 -opt3 cmd5 -opt4

**cmd =   cmd[[cmd1][cmd2][cmd3][cmd4][cmd5]]
**opt =   options[[-opt1 -op2][-opt3][-opt4][]]


**cmd ==      [[cmd1][cmd2][cmd3][cmd4][cmd5]]
**cmd_opt ==  [[cmd1][cmd2 -opt1 -opt2][cmd3][cmd4 -opt3][cmd5 -opt4]]
