
nm -u minishell  //commande pour voir les fonctions utiliser

valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=supp.txt  --quiet ./minishell

ls -la | cat -e | echo hello $USER

ls -la | cat -e | echo hello $USER > out

ls -la < infile | cat -e | echo hello $USER > out

< out | cat -e | ls -la > out 

