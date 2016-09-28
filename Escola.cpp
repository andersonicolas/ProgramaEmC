// Programa Escola de Natação - Prova B1 - 17/09/2014 - Turma da Tarde
//
#include "Escola.h"
//	Entry point do programa
//
void main(void)
{
	int nPeriodo,								// periodo da aula de natação
		nRaia,									// raia da piscina
		nQtdeRaiasDaPiscina,					// quantidade de raias da piscina
		nQtdeTotalDeRaias,						// qtde total de raias nos três períodos
		i = 0,
		j = 0;									// índices genéricos
	char cOpcao,								// opcao do operador
		cNomeAluno[] = "Nícolas Anderson Santos de Jesus",
		cRA_Aluno[] = "18404816019",
		cWork[200];								// para sprintf_s
	SYSTEMTIME stTime;							// para data e hora do sistema
	// vetores dos periodos e raias das piscinas
	bool vetRaiasLivres[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS];	// vetor que indica se raia livre ou ocupada
	// true - indica ocupada e false indica livre
	char vetSobrenomes[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS][TAMANHO_SOBRENOME];	// vetor de sobrenomes
	double vetMensalidades[QTDE_RAIAS_DA_PISCINA * QTDE_PERIODOS];	// vetor mensalidades
	// para duas casas decimais nos valores
	setlocale(LC_ALL, "portuguese_brazil");		// para acentuação brasileira

	for (i = 0; i < sizeof(vetRaiasLivres) / sizeof(bool); i++)
	{
		vetRaiasLivres[i] = false;
	}

	while (true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);						// data e hora do sistema
		sprintf_s(cWork,
			"\tFATEC-Escola de Natação %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s Matrícula: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno, cRA_Aluno);
		cout << cWork << endl << endl;
		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um período desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matrícula de um aluno" << endl
			<< LANCAR_DESPESA << " - Lançar despesas em um aluno matriculado" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado período" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin >> cOpcao;
		cOpcao = toupper(cOpcao);					// converte para maiúscula
		switch (cOpcao)								// avalia a opção escolhida
		{
		case MATRICULAR_ALUNO:
			// <<<5>>> - pedir um período válido (desejado pelo aluno) através da função 
			//				BuscarPeriodo
			if (BuscarPeriodo(&nPeriodo, QTDE_PERIODOS, &cOpcao) == false)
			{
				LIMPAR_TELA;
				cout << "Opção Inválida!" << endl;
				PAUSA;
			}
			else
			{
				// <<<6>>> - chamar a função que verifica se tem uma raia livre no
				//			 período desejado e se não houver uma livre, esta função, devolve zero e
				//			 caso contrário, devolve o número da raia livre no período desejado
				//			 Se não houver uma raia livre cancelar esta ação de matricular aluno
				//				(volta ao menu principal)
				nRaia = BuscarRaiaLivreNoPeriodo(vetRaiasLivres, nPeriodo, QTDE_RAIAS_DA_PISCINA);
				if (nRaia > 0)
				{
					nRaia--;
					// <<<7>>> - pedir o sobrenome do aluno sendo matriculado.
					//			 verificar se existe o mesmo sobrenome nas raias ocupadas. Para
					//			 cada parente encontrado será dado um desconto de 10% limitado ao
					//			 máximo de 40%.
					//			 Assim: Se houver um só ou o primeiro aluno a mensalidade é cheia (100%); 
					//			  se houver mais um 10% de desconto, se houver
					//				mais um 20%; mais um 30% e apartir quarto todos terão 40% de desconto
					LIMPAR_TELA;
					cout << "Insira o sobrenome do(a) aluno(a) que será matriculado(a): ";
					cin >> vetSobrenomes[nRaia];
					for (j = -1, i = 0; i < QTDE_PERIODOS*QTDE_RAIAS_DA_PISCINA; i++)
					{
						if (strcmp(vetSobrenomes[nRaia], vetSobrenomes[i]) == 0)
							j++;
						if (j == 4)
							break;
					}
					// <<<8>>>	Associar este aluno ao período e à raia desejada (ocupar a raia com a bool true
					//			no vetor de livre/ocupada, sobrenome que está nesta raia, valor da mensalidade
					//			Indicar a raia e o período onde o aluno foi matriculado
					//			Dar uma pausa e
					//			Voltar ao menu 
					//
					cout << "\nO(a) aluno(a) terá um desconto de " << j * 10 << "% na mensalidade." << endl;
					vetMensalidades[nRaia] = VALOR_MENSALIDADE - (VALOR_MENSALIDADE / VALOR_DESCONTO_POR_PARENTE)*j;
					PAUSA;
					LIMPAR_TELA;
					vetRaiasLivres[nRaia] = true;
					cout << "Aluno(a): " << vetSobrenomes[nRaia] << " está matriculado na raia "
						<< nRaia % QTDE_RAIAS_DA_PISCINA + 1 << ", no período: " << nPeriodo << "." << endl
						<< "O valor de sua mensalidade é de: $" << vetMensalidades[nRaia] << ".\n" << endl;
					PAUSA;
					break;
				}
				LIMPAR_TELA;
				cout << "Não há raias livres!" << endl;
				PAUSA;
				break;

			} break;								// cai fora do switch
		case CANCELAR_MATRICULA:
			LIMPAR_TELA;
			// <<<9>>>  Chamar a função que pede o periodo e a raia indicando que a ação é
			//			Cancelamento de Matrícula
			if (PedirPeriodoRaia(&nPeriodo, &nRaia, QTDE_PERIODOS, QTDE_RAIAS_DA_PISCINA, &cOpcao) == false)
			{
				cout << "A raia " << nRaia << " do período " << nPeriodo << "já está livre. \n";
				PAUSA;
				break;
			}
			cout << "\t\t\tCancelamento de Matrícula\n\n";
			// <<<10>>> Verificar se a raia está ocupada e se estiver livre avisar ao operador e
			//			cancelar está ação voltando ao menu
			if (vetRaiasLivres[nRaia] == true)
			{
				cout << "O aluno(a): " << vetSobrenomes[nRaia + (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) - 1]
					<< " está ocupando a raia " << nRaia << " do período " << nPeriodo << ". \n"
					<< "Sua matrícula é no valor de $" << vetMensalidades[nRaia + (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) - 1]
					<< ".\n";
				// <<<11>>> Pedir a confirmação do cancelamento da matrícula e havendo a confirmação
				//			apenas indicar que está raia deste periodo está livre. Caso contrário
				//			voltar ao menu principal
				cout << "Deseja confirmar o cancelamento da matrícula? (S ou N)";
				do
				{
					cout << "Insira uma opção válida: ";
					cin >> cOpcao;
					cOpcao = toupper(cOpcao);
				} while (cOpcao != 'S' && cOpcao != 'N');
				if (cOpcao == 'S')
				{
					vetRaiasLivres[nRaia + (nPeriodo*QTDE_RAIAS_DA_PISCINA - QTDE_RAIAS_DA_PISCINA) - 1] = false;
					cout << "A raia " << nRaia << " do período " << nPeriodo << " está livre. \n";
					PAUSA;
					break;
				}

				cout << "Ação cancelada.";
				PAUSA;
				break;
			}
			cout << "A raia " << nRaia << " do período " << nPeriodo << "já está livre. \n";
			PAUSA;
			break;								// cai fora do switch
		case LANCAR_DESPESA:
			// Não codificar ????????????????????????????????????????????
			// <<<12>>> Chamar a função que pede o periodo e a raia indicando que a ação é
			//			Lançamento de Despesa
			// <<<13>>> Verificar se a raia está ocupada e se estiver livre avisar ao operador e
			//			cancelar está ação voltando ao menu
			// <<<14>>> Se a raia estiver ocupada exibir o Sobrenome e as despesas até o momento
			//			Pedir o valor da despesa
			//			Somar o valor informado às despesas anteriores deste aluno
			//			Voltar ao menu
			break;								// cai fora do switch
		case LISTAR_PERIODO:
			// <<<15>>> Pedir um período válido ou zero para cancelar a ação de listar
			//			Se foi informado um período válido listar todos as raias ocupadas
			//			no seguinte formato:
			//				Listagem das raias do periodo: ppppppp
			//			Raia Sobrenome  Mensalidade 
			//			 RR  SSSSSSSSS  MMMMMM,MM	
			//			.....
			//			.....
			//					       Total Mensalidades: TTTTTT,TT
			//			Onde: PPPPPPP - periodo: "Manhã", "Tarde" ou "Noite"
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
			cout << "Opção inválida!" << endl;
			PAUSA;
	} // switch
} // while
} // main
// 
// Funções do Programa
//
// Função que pede um período válido e uma raia da piscina válida
// Parâmetros:
//	Entrada: int *ptrPeriodo - ponteiro para receber o período desejado
//			 int *ptrRaia - ponteiro para receber a raia da piscina desejada
//			 int nQtdePeriodos - quantidade de períodos da Escola de Natação
//			 int nQtRaiasPiscina - quantidade de raias que tem a piscina da Escola de Natação
//			 char *ptrAcao - ponteiro de um string que contém a ação que está sendo executada
//	Retorno: bool - true - indica que foi informado um período e uma raia válidos
//					false - indica que o operador desistiu da ação que iria executar
//							digitando periodo zero
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia, int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao)
{
	if (*ptrAcao == 'C')
	{
		LIMPAR_TELA;
		cout << "Selecione o período desejado conforme descrito abaixo: " << endl
			<< PERIODO_MANHA << " - para periodo da manhã" << endl
			<< PERIODO_TARDE << " - para periodo da tarde" << endl
			<< PERIODO_NOITE << " - para periodo da noite" << endl
			<< "\nIndique a opção desejada: ";
		cin >> *ptrPeriodo;
		PAUSA;
		if (*ptrPeriodo > 0 && *ptrPeriodo <= nQtdePeriodos);
		{
			cout << "Selecione a raia onde o aluno está matriculado: " << endl;
			cin >> *ptrRaia;
			if (*ptrRaia > 0 && *ptrRaia <= nQtRaiasPiscina)
				return true;
		}

		return false;							// ???? para não dar erro de compilação
	}
	//

	// Função que verifica se tem uma raia livre no período desejado
	//	Parâmetros:
	//		Entrada: bool *ptrVetLivreOcup - ponteiro do vetor de bool que indica se a raia está 
	//										 livre ou ocupada
	//				 int nPeriodo - período desejado
	//				 int nQtRaiasPiscina - quantidade de raia que a piscina te´m
	//		Retorno: int - Número da raia que está livre ou zero se não existir nenhuma
	//						raia livre no período desejado
	int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaiasPiscina)
	{
		int i;
		for (i = (nPeriodo - 1) * nQtRaiasPiscina; i < (nPeriodo * nQtRaiasPiscina); i++)
		{
			if (ptrVetLivreOcup[i] == false)
				return i + 1;
			break;
		}
		return 0;							// ???? para não dar erro de compilação
	}



	// Parâmetros:
	//	Entrada: int *ptrPeriodo - endereço de uma inteira que receberá o periodo desejado
	//			 int nQtdePeriodos - quantidade de periodos
	//			 char *ptrAcao - ponteiro de um string que contém a ação em execução
	//	Retorno: bool - true - foi indicado um período válido
	//					false - foi indicado um periodo zero que indica cancelar a ação desejada
	bool BuscarPeriodo(int *ptrPeriodo, int nQtdePeriodos, char *ptrAcao)
	{
		if (*ptrAcao == 'M' || *ptrAcao == 'L')
		{
			LIMPAR_TELA;
			cout << "Selecione o período desejado conforme descrito abaixo: " << endl
				<< PERIODO_MANHA << " - para periodo da manhã" << endl
				<< PERIODO_TARDE << " - para periodo da tarde" << endl
				<< PERIODO_NOITE << " - para periodo da noite" << endl
				<< "\nIndique a opção desejada: ";
			cin >> *ptrPeriodo;
			if (*ptrPeriodo > 0 && *ptrPeriodo <= nQtdePeriodos)
			{
				return true;
			}
			return false;
		}
	}