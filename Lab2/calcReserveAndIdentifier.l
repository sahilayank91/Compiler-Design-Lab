/*WAP to identify a valid reserve word and identify of a c program*/
/*Name - sahil ayank*/
/*2015kucp1025*/
%%
auto |
double |
int |
struct |
case |
enum |
register |
typedef | 
char |
extern |
return |
union |
const |
float |
short |
unsigned |
continue |
for |
signed | 
void |
default |
goto |
sizeof |
volatile |
do |
static |
if |
else {printf("IT IS A KEYWORD.");}
[_a-zA-Z][_a-zA-Z0-9]{0,30} {printf("It is an Identifier\n");}
.* {printf ("Neither a reserved word not identifier");}
%%

main()
{
yylex();
}

int yywrap()
{
return 1;
}




