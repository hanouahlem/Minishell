builtin

cd exit echo export pwd unset env



env -> printf env max 10 lignes
pwd -> printf getcwd() max 5 lignes


cd -> YA RIEN A GERER
	cd tout seul
		-> cd $HOME
	cd arg1 arg2
		-> ERROR too many arguments renvoyer 1
	cd chdir(arg1)
		si chdir renvoie -1 printf access error
	sinon c ok

# unset export

echo max 2 fonctions 15 lignes chacune
	si le premier argument est "-n"
		pas de \n
	tant que les arguments sont -n
		i++
	et afficher le reste

	PAS OUBLIER
		echo -
		affiche -
-n est valable que si ca commence par un tiret et que ya DES net export 
echo
	si le premier argument est "-n"
		pas de \n
	tant que les arguments sont -n
		i++
	et afficher le reste

	PAS OUBLIER
		echo -
		affiche -
-n est valable que si ca commence par un tiret et que ya DES n

exit -> fils de pute

TOUTES LES FONCTIONS
	renvoient 0 si c'est ok
	renvoient 1 si PAS c'est ok