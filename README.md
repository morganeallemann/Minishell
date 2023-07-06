# Minishell

# Minishell
Créer un shell minimaliste

Fonctions autorisées :

Nom de la fonction | Définition | Prototype | Bibliothèque
--- | --- | --- | ---
readline | Permet de lire une ligne de texte entrée par l'utilisateur. | char* readline(const char *prompt); | libreadline
rl_clear_history | Efface l'historique des commandes entrées via readline. | void rl_clear_history(void); | libreadline
rl_on_new_line | Indique à readline qu'une nouvelle ligne a été ajoutée. | void rl_on_new_line(void); | libreadline
rl_replace_line | Remplace la ligne courante de readline par une nouvelle chaîne de caractères. | void rl_replace_line(const char *text, int clear_undo); | libreadline
rl_redisplay | Actualise l'affichage de readline. | void rl_redisplay(void); | libreadline
add_history | Ajoute une commande à l'historique de readline. | void add_history(const char *line); | libreadline
printf | Affiche du texte formaté sur la sortie standard. | int printf(const char *format, ...); | stdio.h
malloc | Alloue de la mémoire dynamiquement. | void* malloc(size_t size); | stdlib.h
free | Libère la mémoire allouée dynamiquement. | void free(void *ptr); | stdlib.h
write | Écrit des données dans un fichier. | ssize_t write(int fd, const void *buf, size_t count); | unistd.h
access | Vérifie l'existence et les permissions d'un fichier. | int access(const char *pathname, int mode); | unistd.h
open | Ouvre un fichier. | int open(const char *pathname, int flags, mode_t mode); | fcntl.h
read | Lit des données à partir d'un fichier. | ssize_t read(int fd, void *buf, size_t count); | unistd.h
close | Ferme un fichier ou une socket. | int close(int fd); | unistd.h
fork | Crée un nouveau processus en copiant le processus existant. | pid_t fork(void); | unistd.h
wait | Attend qu'un processus fils se termine. | pid_t wait(int *wstatus); | sys/wait.h
waitpid | Attend qu'un processus fils se termine. | pid_t waitpid(pid_t pid, int *wstatus, int options); | sys/wait.h
wait3 | Attend qu'un processus fils se termine. | pid_t wait3(int *wstatus, int options, struct rusage *rusage); | sys/resource.h, sys/wait.h
wait4 | Attend qu'un processus fils se termine. | pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage); | sys/resource.h, sys/wait.h
signal | Installe un gestionnaire de signal pour un signal particulier. | void (*signal(int sig, void (*handler)(int)))(int); | signal.h
sigaction | Installe un gestionnaire de signal pour un signal particulier. | int sigaction(int sig, const struct sigaction *act, struct sigaction *oldact); | signal.h
sigemptyset | Initialise un ensemble de signaux vides. | int sigemptyset(sigset_t *set); | signal.h
sigaddset | Ajoute un signal à un ensemble de signaux. | int sigaddset(sigset_t *set, int signum); | signal.h
exit | Termine le programme en cours et retourne un code de sortie à l'appelant. | void exit(int status); | stdlib.h
getcwd | Récupère le répertoire de travail actuel. | char* getcwd(char *buf, size_t size); | unistd.h
chdir | Change le répertoire de travail actuel. | int chdir(const char *path); | unistd.h
stat | Obtient les informations sur un fichier. | int stat(const char *path, struct stat *buf); | sys/stat.h
lstat | Obtient les informations sur un fichier (sans suivre les liens symboliques). | int lstat(const char *path, struct stat *buf); | sys/stat.h
fstat | Obtient les informations sur un fichier à partir d'un descripteur de fichier. | int fstat(int fd, struct stat *buf); | sys/stat.h
unlink | Supprime un fichier du système de fichiers. | int unlink(const char *pathname); | unistd.h
execve | Exécute un programme existant. | int execve(const char *pathname, char *const argv[], char *const envp[]); | unistd.h
dup | Duplique un descripteur de fichier. | int dup(int oldfd); | unistd.h
dup2 | Duplique un descripteur de fichier vers un autre descripteur spécifié. | int dup2(int oldfd, int newfd); | unistd.h
pipe | Crée une paire de descripteurs de fichier pour la communication par tube. | int pipe(int pipefd[2]); | unistd.h
opendir | Ouvre un répertoire pour la lecture. | DIR* opendir(const char *name); | dirent.h
readdir | Lit le contenu d'un répertoire. | struct dirent* readdir(DIR *dirp); | dirent.h
closedir | Ferme un descripteur de répertoire ouvert précédemment. | int closedir(DIR *dirp); | dirent.h
strerror | Récupère une chaîne de caractères décrivant l'erreur associée à un code d'erreur. | char* strerror(int errnum); | string.h
perror | Affiche un message d'erreur suivi de la description de l'erreur courante. | void perror(const char *s); | stdio.h
isatty | Vérifie si un descripteur de fichier est un terminal interactif. | int isatty(int fd); | unistd.h
ttyname | Récupère le nom du terminal associé à un descripteur de fichier. | char* ttyname(int fd); | unistd.h
ttyslot | Récupère le numéro de l'entrée de terminal dans la table des terminaux. | int ttyslot(void); | ttyent.h
ioctl | Manipule diverses opérations de contrôle sur les descripteurs de fichiers. | int ioctl(int fd, unsigned long request, ...); | sys/ioctl.h
getenv | Récupère la valeur d'une variable d'environnement. | char* getenv(const char *name); | stdlib.h
tcsetattr | Modifie les paramètres d'un terminal. | int tcsetattr(int fd, int optional_actions, const struct termios *termios_p); | termios.h
tgetent | Récupère les capacités d'un terminal à partir de la base de données terminfo. | int tgetent(char *bp, const char *name); | curses.h
tgetflag | Récupère la valeur d'un drapeau (flag) de capacité du terminal. | int tgetflag(const char *capname); | curses.h
tgetnum | Récupère la valeur d'une capacité numérique du terminal. | int tgetnum(const char *capname); | curses.h
tgetstr | Récupère la valeur d'une capacité de chaîne de caractères du terminal. | char* tgetstr(const char *capname, char **area); | curses.h
tgoto | Formate une séquence de contrôle de terminal en utilisant les paramètres spécifiés. | char* tgoto(const char *cap, int col, int row); | curses.h
tputs | Écrit une séquence de contrôle de terminal. | int tputs(const char *str, int affcnt, int (*putc)(int)); | curses.h
tcgetattr | Récupère les paramètres d'un terminal. | int tcgetattr(int fd, struct termios *termios_p); | termios.h
kill | Envoie un signal à un processus ou à un groupe de processus. | int kill(pid_t pid, int sig); | signal.h

Consigne : 

Votre shell doit :
Afficher un prompt en l’attente d’une nouvelle commande.
Posséder un historique fonctionnel.
Chercher et lancer le bon exécutable (en se basant sur la variable d’environnement
PATH, ou sur un chemin relatif ou absolu).
Ne pas utiliser plus d’une variable globale. Réfléchissez-y car vous devrez jus-
tifier son utilisation.
Ne pas interpréter de quotes (guillemets) non fermés ou de caractères spéciaux non
demandés dans le sujet, tels que \ (le backslash) ou ; (le point-virgule).
Gérer ’ (single quote) qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets.
Gérer " (double quote) qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets sauf le $ (signe dollar).

Minishell Aussi mignon qu’un vrai shell
Implémenter les redirections :
"<" doit rediriger l’entrée.
">" doit rediriger la sortie.
"<<" doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une ligne
contenant le délimiteur. Cependant, l’historique n’a pas à être mis à jour !
">>" doit rediriger la sortie en mode append.
Implémenter les pipes (caractère |). La sortie de chaque commande de la pipeline
est connectée à l’entrée de la commande suivante grâce à un pipe.
Gérer les variables d’environnement (un $ suivi d’une séquence de caractères)
qui doivent être substituées par leur contenu.
Gérer $? qui doit être substitué par le statut de sortie de la dernière pipeline
exécutée au premier plan.
Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent fonctionner comme dans bash.
En mode interactif :
ctrl-C affiche un nouveau prompt sur une nouvelle ligne.
ctrl-D quitte le shell.
ctrl-\ ne fait rien.
Votre shell doit implémenter les builtins suivantes :
echo et l’option -n
cd uniquement avec un chemin relatif ou absolu
pwd sans aucune option
export sans aucune option
unset sans aucune option
env sans aucune option ni argument
exit sans aucune option
La fonction readline() peut causer des fuites de mémoire. Vous n’avez pas à les
gérer. Attention, cela ne veut pas pour autant dire que votre code, oui celui que
vous avez écrit, peut avoir des fuites de mémoire.
