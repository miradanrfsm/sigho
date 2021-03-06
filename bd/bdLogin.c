#include <stdio.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include <string.h>
#include "conexao.h"



PGresult *result;

int verificarSenha(char *name,char *senha){
	int comando_ok,verificacao=0;
	char *consulta;

	verificaConexao();

	comando_ok = ExecutaComando("BEGIN WORK", &result);

	sprintf(consulta,"DECLARE curr CURSOR FOR SELECT senha FROM funcionario where login = '%s'",name);

	if (comando_ok) {
		PQclear(result);
		/*Executa o comando*/

		comando_ok = ExecutaComando(consulta, &result);
		if (comando_ok) {
			PQclear(result);
			comando_ok = ExecutaComando("FETCH 1 IN curr", &result);

			while (comando_ok && PQntuples(result) > 0) {

				if(!strcmp(senha,PQgetvalue(result, 0, 0))) verificacao=1;
				PQclear(result);
				ExecutaComando("FETCH NEXT IN curr", &result);
			}

		}
		comando_ok = ExecutaComando("COMMIT WORK", &result);
	}
	if (comando_ok)
		PQclear(result);

	if(conn != NULL)
		PQfinish(conn);

	return verificacao;
}
