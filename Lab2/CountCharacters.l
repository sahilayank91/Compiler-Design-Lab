%{
#include<stdio.h>
int count=0;
%}
%%

[A-Z a-z] count++;
%%





main(void)
{
yyin= fopen("myfile.txt","r");
yylex();
printf(" This File contains ...");
printf("\n\t%d letters", count);

}
 
int yywrap()
{
return(1);
}
