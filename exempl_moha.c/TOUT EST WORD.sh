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



<====     ORGANISE TOKEN     ====>
POUR LE MALLOC DE CMD ARGS REDIRR :
etape 1
	connaitre le nb de t_parse
etape 2
	boucler sur ce nombre
		et compter chaque parse cmb
			d'arg il a
			de redir il a
etape