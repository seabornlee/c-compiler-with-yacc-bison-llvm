%option noyywrap

%{
#include "y.tab.h"
%}

%%
<<EOF>> return EOP;
%%