calc: calc.l calc.y
	@flex -o lexico.c calc.l
	@bison -v -d calc.y -o sintatico.c
	@gcc lexico.c sintatico.c -o calc

clear:
	@echo "Limpando....."
	@rm  lexico.c  sintatico.c sintatico.h sintatico.output calc
