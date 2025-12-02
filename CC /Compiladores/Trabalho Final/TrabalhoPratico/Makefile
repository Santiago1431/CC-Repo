simples: utils.c lexico.l sintatico.y;
	@flex -o lexico.c lexico.l
	@bison -v -d sintatico.y -o sintatico.c
	@gcc sintatico.c utils.c  -o simples
limpa: ;
	@echo "Limpando"
	@rm lexico.c sintatico.c sintatico.h sintatico.output simples