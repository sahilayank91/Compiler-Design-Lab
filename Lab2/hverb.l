%% option noyywrap
%%
[\t]+ |
is |
am |
are |
was |
were | {printf("%s: is a helping verb",yytext);}
[a-z A-Z]+  {printf("%s : is a Character",yytext);}
%%
main()
{
yylex();
}

