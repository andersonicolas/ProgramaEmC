// Programa Escola de Nata��o - Prova B1 - 17/09/2014 - Turma da Tarde
//
#include "Escola.h"
//	Entry point do programa
//
void main(void)
{
	int nPeriodo,								// periodo da aula de nata��o
		nRaia,									// raia da piscina
		nQtdeRaiasDaPiscina,					// quantidade de raias da piscina
		nQtdeTotalDeRaias,						// qtde total de raias nos tr�s per�odos
		i = 0,
		j = 0;									// �ndices gen�ricos
	char cOpcao,								// opcao do operador
		cNomeAluno[] = "N�colas Anderson Santos de Jesus",
		cRA_Aluno[] = "18404816019",
		cWork[200];								// para sprintf_s
	SYSTEMTIME stTime;							// para data e hora do sistema
	// vetores dos periodos e raias das piscinas
	bool vetRaiasLivres[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS];	// vetor que indica se raia livre ou ocupada
	// true - indica ocupada e false indica livre
	char vetSobrenomes[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS][TAMANHO_SOBRENOME];	// vetor de sobrenomes
	double vetMensalidades[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS];	// vetor mensalidades
	// para duas casas decimais nos valores
	setlocale(LC_ALL, "portuguese_brazil");		// para acentua��o brasileira

	for (i = 0; i < sizeof(vetRaiasLivres) / sizeof(bool); i++)
	{
		vetRaiasLivres[i] = false;
	}

	while (true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);						// data e hora do sistema
		sprintf_s(cWork,
			"\tFATEC-Escola de Nata��o %02d/%02d/%04d �s %02d:%02d:%02d\n\tOperador: %s Matr�cula: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno, cRA_Aluno);
		cout << cWork << endl << endl;
		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um per�odo desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matr�cula de um aluno" << endl
			<< LANCAR_DESPESA << " - Lan�ar despesas em um aluno matriculado" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado per�odo" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin >> cOpcao;
		cOpcao = toupper(cOpcao);					// converte para mai�scula
		switch (cOpcao)								// avalia a op��o escolhida
		{
		case MATRICULAR_ALUNO:
			// <<<5>>> - pedir um per�odo v�lido (desejado pelo aluno) atrav�s da fun��o 
			//				BuscarPeriodo
			if (BuscarPeriodo(&nPeriodo, QTDE_PERIODOS, &cOpcao) == false)
			{
				LIMPAR_TELA;
				cout << "Op��o Inv�lida!" << endl;
				PAUSA;
			}
			else
			{
				// <<<6>>> - chamar a fun��o que verifica se tem uma raia livre no
				//			 per�odo desejado e se n�o houver uma livre, esta fun��o, devolve zero e
				//			 caso contr�rio, devolve o n�mero da raia livre no per�odo desejado
				//			 Se n�o houver uma raia livre cancelar esta a��o de matricular aluno
				//				(volta ao menu principal)
				nRaia = BuscarRaiaLivreNoPeriodo(vetRaiasLivres, nPeriodo, QTDE_RAIAS_DA_PISCINA);
				if (nRaia > 0)
				{
					nRaia--;
					// <<<7>>> - pedir o sobrenome do aluno sendo matriculado.
					//			 verificar se existe o mesmo sobrenome nas raias ocupadas. Para
					//			 cada parente encontrado ser� dado um desconto de 10% limitado ao
					//			 m�ximo de 40%.
					//			 Assim: Se houver um s� ou o primeiro aluno a mensalidade � cheia (100%); 
					//			  se houver mais um 10% de desconto, se houver
					//				mais um 20%; mais um 30% e apartir quarto todos ter�o 40% de desconto
					LIMPAR_TELA;
					cout << "Insira o sobrenome do(a) aluno(a) que ser� matriculado(a): ";
					cin >> vetSobrenomes[nRaia];
					for (j = -1, i = 0; i < QTDE_PERIODOS*QTDE_RAIAS_DA_PISCINA; i++)
					{
						if (strcmp(vetSobrenomes[nRaia], vetSobrenomes[i]) == 0)
							j++;
						if (j == 4)
							break;
					}
					// <<<8>>>	Associar este aluno ao per�odo e � raia desejada (ocupar a raia com a bool true
					//			no vetor de livre/ocupada, sobrenome que est� nesta raia, valor da mensalidade
					//			Indicar a raia e o per�odo onde o aluno foi matriculado
					//			Dar uma pausa e
					//			Voltar ao menu 
					//
					cout << "\nO(a) aluno(a) ter� um desconto de " << j * 10 << "% na mensalidade." << endl;
					vetMensalidades[nRaia] = VALOR_MENSALIDADE - (VALOR_MENSALIDADE / VALOR_DESCONTO_POR_PARENTE)*j;
					PAUSA;
					LIMPAR_TELA;
					vetRaiasLivres[nRaia] = true;
					cout << "Aluno(a): " << vetSobrenomes[nRaia] << " est� matriculado na raia "
						<< nRaia % QTDE_RAIAS_DA_PISCINA + 1 << ", no per�odo: " << nPeriodo << "." << endl
						<< "O valor de sua mensalidade � de: $" << vetMensalidades[nRaia] << ".\n" << endl;
					PAUSA;
					break;
				}
				LIMPAR_TELA;
				cout << "N�o h� raias livres!" << endl;
				PAUSA;
				break;

			} break;								// cai fora do switch
		case CANCELAR_MATRICULA:
			LIMPAR_TELA;
			// <<<9>>>  Chamar a fun��o que pede o periodo e a raia indicando que a a��o �
			//			Cancelamento de Matr�cula
			if (PedirPeriodoRaia(&nPeriodo, &nRaia, QTDE_PERIODOS, QTDE_RAIAS_DA_PISCINA, &cOpcao) == false)
			{
				cout << "A raia " << nRaia << " do per�odo " << nPeriodo << "j� est� livre. \n";
				PAUSA;
				break;
			}
			cout << "\t\t\tCancelamento de Matr�cula\n\n";
			// <<<10>>> Verificar se a raia est� ocupada e se estiver livre avisar ao operador e
			//			cancelar est� a��o voltando ao menu
			if (vetRaiasLivres[nRaia] == true)
			{
				cout << "O aluno(a): " << vetSobrenomes[nRaia + (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) - 1]
					<< " est� ocupando a raia " << nRaia << " do per�odo " << nPeriodo << ". \n"
					<< "Sua matr�cula � no valor de $" << vetMensalidades[nRaia + (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) - 1]
					<< ".\n";
				// <<<11>>> Pedir a confirma��o do cancelamento da matr�cula e havendo a confirma��o
				//			apenas indicar que est� raia deste periodo est� livre. Caso contr�rio
				//			voltar ao menu principal
				cout << "Deseja confirmar o cancelamento da matr�cula? (S ou N)";
				do
				{
					cout << "Insira uma op��o v�lida: ";
					cin >> cOpcao;
					cOpcao = toupper(cOpcao);
				} while (cOpcao != 'S' && cOpcao != 'N');
				if (cOpcao == 'S')
				{
					vetRaiasLivres[nRaia + (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) - 1] = false;
					cout << "A raia " << nRaia << " do per�odo " << nPeriodo << " est� livre. \n";
					PAUSA;
					break;
				}

				cout << "A��o cancelada.";
				PAUSA;
				break;
			}
			cout << "A raia " << nRaia << " do per�odo " << nPeriodo << "j� est� livre. \n";
			PAUSA;
			break;								// cai fora do switch
		case LANCAR_DESPESA:
			// N�o codificar ????????????????????????????????????????????
			// <<<12>>> Chamar a fun��o que pede o periodo e a raia indicando que a a��o �
			//			Lan�amento de Despesa
			// <<<13>>> Verificar se a raia est� ocupada e se estiver livre avisar ao operador e
			//			cancelar est� a��o voltando ao menu
			// <<<14>>> Se a raia estiver ocupada exibir o Sobrenome e as despesas at� o momento
			//			Pedir o valor da despesa
			//			Somar o valor informado �s despesas anteriores deste aluno
			//			Voltar ao menu
			break;								// cai fora do switch
		case LISTAR_PERIODO:
			// <<<15>>> Pedir um per�odo v�lido ou zero para cancelar a a��o de listar
			//			Se foi informado um per�odo v�lido listar todos as raias ocupadas
			//			no seguinte formato:
			//				Listagem das raias do periodo: ppppppp
			//			Raia Sobrenome  Mensalidade 
			//			 RR  SSSSSSSSS  MMMMMM,MM	
			//			.....
			//			.....
			//					       Total Mensalidades: TTTTTT,TT
			//			Onde: PPPPPPP - periodo: "Manh�", "Tarde" ou "Noite"
			//				  RR - raia ocupada ( 1 a Qtde de Raias da Piscina)
			//				  SSSSSSSSS - sobrenome do aluno
			//				  MMMMM - valor da mensalidade
			//				  TTTTTT,TT - valor total de todas as mensalidades
			break;								// cai fora do switch
		case SAIR_DO_PROGRAMA:
			cout << "Vai sair realmente? (S ou N): ";
			cin >> cOpcao;
			if (cOpcao == 's' || cOpcao == 'S')	// sair realmente?
				return;
			break;								// cai fora do switch
		default:
			cout << "Op��o inv�lida!" << endl;
			PAUSA;
	} // switch
} // while
} // main
// 
// Fun��es do Programa
//
// Fun��o que pede um per�odo v�lido e uma raia da piscina v�lida
// Par�metros:
//	Entrada: int *ptrPeriodo - ponteiro para receber o per�odo desejado
//			 int *ptrRaia - ponteiro para receber a raia da piscina desejada
//			 int nQtdePeriodos - quantidade de per�odos da Escola de Nata��o
//			 int nQtRaiasPiscina - quantidade de raias que tem a piscina da Escola de Nata��o
//			 char *ptrAcao - ponteiro de um string que cont�m a a��o que est� sendo executada
//	Retorno: bool - true - indica que foi informado um per�odo e uma raia v�lidos
//					false - indica que o operador desistiu da a��o que iria executar
//							digitando periodo zero
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia, int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao)
{
	if (*ptrAcao == 'C')
	{
		LIMPAR_TELA;
		cout << "Selecione o per�odo desejado conforme descrito abaixo: " << endl
			<< PERIODO_MANHA << " - para periodo da manh�" << endl
			<< PERIODO_TARDE << " - para periodo da tarde" << endl
			<< PERIODO_NOITE << " - para periodo da noite" << endl
			<< "\nIndique a op��o desejada: ";
		cin >> *ptrPeriodo;
		PAUSA;
		if (*ptrPeriodo > 0 && *ptrPeriodo <= nQtdePeriodos);
		{
			cout << "Selecione a raia onde o aluno est� matriculado: " << endl;
			cin >> *ptrRaia;
			if (*ptrRaia > 0 && *ptrRaia <= nQtRaiasPiscina)
				return true;
		}

		return false;							// ???? para n�o dar erro de compila��o
	}
	//

	// Fun��o que verifica se tem uma raia livre no per�odo desejado
	//	Par�metros:
	//		Entrada: bool *ptrVetLivreOcup - ponteiro do vetor de bool que indica se a raia est� 
	//										 livre ou ocupada
	//				 int nPeriodo - per�odo desejado
	//				 int nQtRaiasPiscina - quantidade de raia que a piscina te�m
	//		Retorno: int - N�mero da raia que est� livre ou zero se n�o existir nenhuma
	//						raia livre no per�odo desejado
	int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaiasPiscina)
	{
		int i;
		for (i = (nPeriodo - 1) * nQtRaiasPiscina; i < (nPeriodo * nQtRaiasPiscina); i++)
		{
			if (ptrVetLivreOcup[i] == false)
				return i + 1;
			break;
		}
		return 0;							// ???? para n�o dar erro de compila��o
	}



	// Par�metros:
	//	Entrada: int *ptrPeriodo - endere�o de uma inteira que receber� o periodo desejado
	//			 int nQtdePeriodos - quantidade de periodos
	//			 char *ptrAcao - ponteiro de um string que cont�m a a��o em execu��o
	//	Retorno: bool - true - foi indicado um per�odo v�lido
	//					false - foi indicado um periodo zero que indica cancelar a a��o desejada
	bool BuscarPeriodo(int *ptrPeriodo, int nQtdePeriodos, char *ptrAcao)
	{
		if (*ptrAcao == 'M' || *ptrAcao == 'L')
		{
			LIMPAR_TELA;
			cout << "Selecione o per�odo desejado conforme descrito abaixo: " << endl
				<< PERIODO_MANHA << " - para periodo da manh�" << endl
				<< PERIODO_TARDE << " - para periodo da tarde" << endl
				<< PERIODO_NOITE << " - para periodo da noite" << endl
				<< "\nIndique a op��o desejada: ";
			cin >> *ptrPeriodo;
			if (*ptrPeriodo > 0 && *ptrPeriodo <= nQtdePeriodos)
			{
				return true;
			}
			return false;
		}
	}