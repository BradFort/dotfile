#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

echo ="******Bienvenue Bradley Fortin*******"

alias la='ls -a'
alias lla='ls -a'
alias c='clear'
alias grepc='grep --color=red'
alias ls='ls --color=white'
alias grep='grep --color=auto'


NouvDossier()
{
 mkdir nouveauDossier
 cd nouveauDossier
}

NouvFichier()
{
	touch nouveauFichier.sh
	vim nouveauFichier.sh
}

mygrep()
{
 alias grep='find . -iname'
}

PS1='[\w]\$'
