%{
/* balisage */
int ouvrante = 0;
%}

%option nounput
%option noinput

%x FONCTION
%x VOIDFONCTION

%%

void[ \n\t]*[_a-zA-Z][_a-zA-Z0-9]*[ \n\t]*[(][^{]*[)][ \n\t]*[{] ECHO; printf("\n\tPROFILE"); ouvrante += 1; BEGIN(VOIDFONCTION);
<VOIDFONCTION>\{ ouvrante+=1; ECHO;
<VOIDFONCTION>\} ouvrante-=1;if(ouvrante == 0) {printf("\treturn;\n"); BEGIN(INITIAL);} ECHO;
<VOIDFONCTION>.|\n ECHO;


[_a-zA-Z][_a-zA-Z0-9]*[*]*[ \n\t]*[_a-zA-Z][_a-zA-Z0-9]*[ \n\t]*[(][^{]*[)][ \n\t]*[{]  ECHO; printf("\n\tPROFILE"); ouvrante += 1; BEGIN(FONCTION);
<FONCTION>\{ ouvrante+=1; ECHO;
<FONCTION>\} ouvrante-=1;if(ouvrante == 0) BEGIN(INITIAL); ECHO;
				
<FONCTION>.|\n ECHO;



.|\n ECHO; 

%%

int main(){
	return yylex();
}
