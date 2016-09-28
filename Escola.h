// Declarações do programa Escola de Natação
#include <iostream>
#include <windows.h>
using namespace std;
// Definições
#define PAUSA				system("pause")
#define LIMPAR_TELA			system("cls")
// Delimitação do programa
#define QTDE_PERIODOS		3			// quantidade de períodos (1 - manhã, 2 - tarde e 3 - noite)
#define QTDE_RAIAS_DA_PISCINA	10			// quantidade máxima de raias da piscina
#define PERIODO_MANHA		1			// período da manhã
#define PERIODO_TARDE		2			// período da tarde
#define PERIODO_NOITE		3			// período da noite
#define TAMANHO_SOBRENOME	15			// tamanho do sobrenome sem o delimitador
// opções do menu
#define MATRICULAR_ALUNO		'M'			
#define CANCELAR_MATRICULA		'C'
#define LANCAR_DESPESA			'D'
#define LISTAR_PERIODO			'P'
#define SAIR_DO_PROGRAMA		'S'
// valores e descontos de mensalidade
#define VALOR_MENSALIDADE			130.00	// valor da mensalidade do primeiro da família
#define VALOR_DESCONTO_POR_PARENTE	10		// valor para cada parente com o mesmo sobrenome
// limite de descontos até quatro parentes
// protótipos das funções
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia, int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao);
int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaiasPiscina);
bool BuscarPeriodo(int *ptrPeriodo, int nQtdePeriodos, char *ptrAcao);
