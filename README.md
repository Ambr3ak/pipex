# pipex
Introduction to redirections and pipes. 

### How to lunch the program ? 
``` ./pipex <infile> <cmd1> <cmd2> <outfile> ```
### How to launch the bonus ? 
``` ./pipex <infile> <cmd1> <cmd2> ... <cmdn> <outfile> ```

Le projet a pour but d'introduire aux redirections de fichiers et aux pipes. 


Exemple de commandes bash avec pipe sans redirection d'entrée.
``` ls -l | wc -l ```


Exemple de commande avec STDIN redirection
``` < infile ls -l | wc -l > outfile ```

## Les redirections

There are 3 data streams `stdin`, `stdout` and `stderr` map respectively to file descriptor 0,1 and 2.
Quand on utilise des pipes, il est important de comprendre comment les flux sont rediriges. 

`stdin` correspond au flux d´entree par default, principale le port d'ecoute du clavier. Certaines fonctions comme scanf l'utilise.

`stdout` is the default file descriptor where a process can write outputs.

`stderr` is the standard error stream. It is the file descriptor where a process can write error messages.

## Les processus

To create a process, the use of `fork` is mandatory. 

``` #include <unistd.h>
    pid_t fork(); ```

Every call of fork will create a new process and duplicste its memory. 

