



%{
#include<stdio.h>
int vowel=0,consonant = 0;
%}
%%
[a|e|i|o|u|A|E|I|O|U] vowel++;
[b-df-hj-np-tv-z|B-DF-HJ-NP-TV-Z] consonant++;
%%

	



main(void)
{
yyin= fopen("myfile.txt","r");
yylex();
printf(" This File contains ...");
printf("\n\t%d Vowel", vowel);
printf("\n\t%d Consonant\n", consonant);
}
 
int yywrap()
{
return(1);
}
