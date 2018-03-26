A shell for unix systems

Current feature set:
-Accepts piped input
-Accepts file as an argument
-Variable substitution
-$? $$ $# $0-9
-Set local vars with FOO=bar
-Local variables not passed with environment
-Set environmental variables with: setenv name value
-Unset environmental variables with: unsetenv name
-Alias commands with name=value arguments to the alias command
-Show command aliases with name arguments to the alias command
-A mix of the above 2 in one alias command
-cd
-env builtin to print environment. Falls through to std env if more than 1 arg
-quotes around arguments (accepting more stdin on mismatch in progress)
-escape characters with \
-&&, || and ;
-tilde expansion to home directory from env
-exit with status
-history
-help
