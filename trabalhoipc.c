/**
 * @file trabalhoipc.c
 * @brief Mostra um menu com opções para criação de arquivos .txt 
 * que mantenha registros e realize uma analise estatistica 
 * de uma turma de estudantes
 * 
 * O programa possui vários menus, sendo que o primeiro dá opções para 
 * acessar outros menus como o de ler estudantes de um arquivo, imprimir
 * turma de estudantes, imprimir estatísticas da turma, cadastrar novo estudante,
 * editar informações, reler turma de estudantes ou salvar e sair
 * 
 * Instruções para compilar e executar o códico no Ubuntu: 
 * encontre o diretório no qual o código se encontra pelo
 * terminal e depois digite:
 * "gcc -std=c11 trabalhoipc.c -o trabalhoipc.exe"
 * "./trabalhoipc.exe"
 * 
 * @author Luiz André da Silva Carvalho
 * @author Ramon Maximo
 * @date 20/06/2019
 * @bugs Nenhum conhecido.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define clear() printf("\033[H\033[J") //limpar a tela

// typedef para struct
typedef struct 
{
    char nomeAluno[51];
    char matricula[12];
    double notasProvas[3];
    double notasTrabs[2];
    int faltas;
    double notafinal;
    char situacao;
} Cadastro;
//fim typedef
 
// Prototipação

void menuPrincipal(Cadastro estudantes[]);
void menuLerTurma(char arquivo[], Cadastro estudantes[]);
void lerTurma(char arquivo[], Cadastro estudantes[]);
void criarTurma(char arquivo[], Cadastro estudantes[]);
void imprimeTurma(char arquivo[], Cadastro estudantes[]);
void imprimeEstat(char arquivo[], Cadastro estudantes[]);
double calculaNotas(Cadastro estudantes[], int aux, int ind);
void verificaSituacoes(double situacao[], Cadastro *estudantes);
void cadEstud(Cadastro *estudantes, char arquivo[]);
void verificaSituacao(int i, Cadastro *estudantes);
int verificaVetS(Cadastro estudantes[]);
void menuEditEst1(Cadastro *estudantes, char arquivo[]);
int verificaEstudante(char strin[], Cadastro estudantes[]);
void menuEditEst2(Cadastro *estudantes, int i);
void relerTurma(Cadastro estudantes[], char arquivo[]);
void salvar_Sair(Cadastro estudantes[], char arquivo[]);
void imprimePraArq(char arquivo[], Cadastro estudantes[]);
void asterisco(int ast);
// Fim prototipação

int main(void) {
  Cadastro estudantes[80] = {{'\0'},{'\0'},{0.0},{0.0},0,0.0,'\0'};
  menuPrincipal(estudantes);
  return 0;
} // Main

/** 
 * @brief função que repassa a escolha do usuário
 * pro próximo menu.
 *
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 */
void menuPrincipal(Cadastro estudantes[]){
  int op = 0;
  char arquivo[20] = {'\0'};
  printf("=========================================\n");               
  printf("\t   Menu Principal\n");
  printf("=========================================\n\n");
	printf("Opções:\n");
	printf("\n 1 - Ler turma de estudantes do arquivo\n");
	printf(" 2 - Imprimir turma de estudantes\n");
	printf(" 3 - Imprimir estatísticas da turma\n");
	printf(" 4 - Cadastrar novo estudante\n");
	printf(" 5 - Editar informações de um estudante\n");
	printf(" 6 - Reler turma de estudantes do arquivo\n");
	printf(" 7 - Salvar e Sair\n");
  printf( "\nDigite uma opção:\n ");
  scanf("%d", &op);
  while(op != 7){
    switch(op){
      case 1:
        clear();
        menuLerTurma(arquivo, estudantes);
        break;
      case 2:
        clear();
        imprimeTurma(arquivo, estudantes);
        break;
      case 3:
        clear();
        imprimeEstat(arquivo, estudantes);
        break;
      case 4:
        clear();
        cadEstud(estudantes, arquivo);
        break;
      case 5:
        clear();
        menuEditEst1(estudantes, arquivo);
        break;
      case 6:
        clear();
        relerTurma(estudantes, arquivo);
        break;
      default: 
        clear();
        printf("Opção inválida!\nPressione Enter para voltar à tela anterior...\n");
				setbuf(stdin, NULL); 
				getchar(); 
				setbuf(stdin, NULL);   
				break; 
    }
    printf("=========================================\n");               
    printf("\t   Menu Principal\n");
    printf("=========================================\n\n");
	  printf("Opções:\n");
	  printf("\n 1 - Ler turma de estudantes do arquivo\n");
	  printf(" 2 - Imprimir turma de estudantes\n");
	  printf(" 3 - Imprimir estatísticas da turma\n");
	  printf(" 4 - Cadastrar novo estudante\n");
	  printf(" 5 - Editar informações de um estudante\n");
	  printf(" 6 - Reler turma de estudantes do arquivo\n");
	  printf(" 7 - Salvar e Sair\n");
    printf( "\nDigite uma opção:\n ");
		scanf("%d", &op); 
		setbuf(stdin, NULL); 
  }
  if(op==7){
    clear();
    salvar_Sair(estudantes, arquivo);
  }
}



/** 
 * @brief Função do menu de ler turma, que chama outras funções
 *        de acordo com a opção dada
 *
 * @param arquivo[] ponteiro para a string com o nome do arquivo no menu principal
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 */
void menuLerTurma(char arquivo[], Cadastro estudantes[]){
  int op = 0;
  printf("=========================================\n");
  printf("                 Ler Turma               \n"); 
  printf("=========================================\n");  
  printf("Opções:\n");
	printf(	" 1 - Ler turma existente\n");
	printf(	" 2 - Criar nova turma\n");
	printf(	" 3 - Voltar ao menu principal\n");
  printf( "\nDigite uma opção: ");
  scanf("%d", &op);
  while(op!=3){
    switch(op){
      case 1:
        clear();
        printf("\nDigite o nome do arquivo com a turma: ");
        scanf(" %s", arquivo);
        lerTurma(arquivo, estudantes);
        break;
      case 2:
        clear();
        printf("\nDigite o nome do arquivo para a nova turma: ");
        scanf(" %s", arquivo);
        criarTurma(arquivo, estudantes);
        break;
      default: 
        clear();
		  	printf("Opção inválida!\nPressione Enter para voltar à tela anterior...\n");
		  	setbuf(stdin, NULL); 
		  	getchar(); 
		  	setbuf(stdin, NULL);
        break;
    }
	printf("=========================================\n");
  printf("                 Ler Turma               \n"); 
  printf("=========================================\n");  
  printf("Opções:\n");
	printf(	" 1 - Ler turma existente\n");
	printf(	" 2 - Criar nova turma\n");
	printf(	" 3 - Voltar ao menu principal\n");
  printf( "\nDigite uma opção: "); 
	scanf("%d", &op);
  }
  op = 0;
}

/** 
 * @brief Função que abre arquivo digitado pelo usuário em modo leitura
 *
 * @param arquivo[] ponteiro para a string com o nome do arquivo no menu principal
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 */
void lerTurma(char arquivo[], Cadastro estudantes[]){ 
  FILE *fp = NULL;
  fp = fopen(arquivo, "r");

  if (fp == NULL){
    printf("\nArquivo %s não existe!\n", arquivo);
  }
  else{
    printf("\nArquivo %s lido com sucesso!\n", arquivo);
    for(int i = 0; fscanf(fp, " %c", &estudantes[i].nomeAluno[0]) != EOF && i<80; i++){
        for(int j = 1; j<51; j++){
          if(estudantes[i].nomeAluno[j-1]=='\n'){
            estudantes[i].nomeAluno[j-1] = '\0';
            break;
          }
          else{
            fscanf(fp, "%c", &estudantes[i].nomeAluno[j]);
          }
        }
        fgets(estudantes[i].matricula, sizeof(estudantes[i].matricula), fp);
        estudantes[i].matricula[strcspn(estudantes[i].matricula, "\n")] = '\0';
        fscanf(fp, "%lf\n", &estudantes[i].notasProvas[0]);
        fscanf(fp, "%lf\n", &estudantes[i].notasProvas[1]);
        fscanf(fp, "%lf\n", &estudantes[i].notasProvas[2]);
        fscanf(fp, "%lf\n", &estudantes[i].notasTrabs[0]);
        fscanf(fp, "%lf\n", &estudantes[i].notasTrabs[1]);
        fscanf(fp, "%d\n", &estudantes[i].faltas);
        fscanf(fp, "%lf\n", &estudantes[i].notafinal);
        fscanf(fp, " %c\n", &estudantes[i].situacao);
   }
   fclose(fp);
  }
}

/** 
 * @brief Função que abre o arquivo existente em formato de leitura ou cria ele em formato de escrita
 *
 * @param arquivo[] ponteiro para a string com o nome do arquivo no menu principal
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 */
void criarTurma(char arquivo[], Cadastro estudantes[]){ 
  char sn = '\0';
  FILE *fp = NULL;
  fp = fopen(arquivo, "r");
  if (fp == NULL){
    fp = fopen(arquivo, "w");
    printf("\nArquivo %s criado com sucesso.\n", arquivo);
    fclose(fp);
  }
  else{
    printf("Arquivo já existe. Deseja sobrescrevê-lo? (S/N) ");
    getchar();
    while(sn != 'S' || sn != 'N'){
      scanf(" %c", &sn);
      if(sn == 'S'){
        fclose(fp);
        fp = fopen(arquivo, "w");
        fclose(fp);
        break;
      }
      else if(sn == 'N'){
        fclose(fp);
        break;
      }
      else{
        printf("Opção inválida!\n");
        printf("Digite novamente: ");
      }
    }
  }
}

/** 
 * @brief Função acessa o arquivo em modo leitura e imprime uma tabela com os dados do vetor de
 *        struct
 *
 * @param arquivo[] ponteiro para a string com o nome do arquivo no menu principal
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 */
void imprimeTurma(char arquivo[], Cadastro estudantes[]){
  if(estudantes[0].nomeAluno[0]!='\0' || fopen(arquivo, "r") != NULL){
    printf("\n                                          Estudantes\n");
    printf("----------------------------------------------------------------------------------------------\n");
    printf("Nome                                                Matrícula    N1 N2 N3 T1 T2 Fal  Final Sit\n");
    printf("----------------------------------------------------------------------------------------------\n");
    for(int i = 0; i<80 && estudantes[i].nomeAluno[0]!='\0'; i++){
    printf("%-51s ", estudantes[i].nomeAluno);
    printf("%s  ", estudantes[i].matricula);
    printf("%2.0lf ", estudantes[i].notasProvas[0]);
    printf("%2.0lf ", estudantes[i].notasProvas[1]);
    printf("%2.0lf ", estudantes[i].notasProvas[2]);
    printf("%2.0lf ", estudantes[i].notasTrabs[0]);
    printf("%2.0lf ", estudantes[i].notasTrabs[1]);
    printf("%3d    ", estudantes[i].faltas);
    printf("%3.0lf   ", estudantes[i].notafinal);
    printf("%c\n", estudantes[i].situacao);
    }
    printf("----------------------------------------------------------------------------------------------\n");
  }
  else{
    printf("\nNão há turma carregada!\n");
  }
}

/** 
 * @brief Função que imprime as estatísticas dos
 *        estudantes do vetor de struct, acessa o arquivo
 *        em modo de leitura
 *
 * @param arquivo[] ponteiro para a string com o nome do arquivo no menu principal
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 */
void imprimeEstat(char arquivo[], Cadastro estudantes[]){ 
  double notas[18] = {0.0};
  double situacoes[3] = {0};
  verificaSituacoes(situacoes, estudantes);
  int i = (verificaVetS(estudantes));
  if(estudantes[0].nomeAluno[0]!='\0' || fopen(arquivo, "r") != NULL){
    printf("\n                        Estatísticas\n");
    printf("-----------------------------------------------------------\n");
    printf("                          N1    N2    N3    T1    T2  Final\n");
    printf("-----------------------------------------------------------\n");
    notas[0] = calculaNotas(estudantes, 1, 0);
    notas[1] = calculaNotas(estudantes, 1, 1);
    notas[2] = calculaNotas(estudantes, 1, 2);
    notas[3] = calculaNotas(estudantes, 2, 0);
    notas[4] = calculaNotas(estudantes, 2, 1);
    notas[5] = calculaNotas(estudantes, 3, 1);
    notas[6] = calculaNotas(estudantes, 4, 0);
    notas[7] = calculaNotas(estudantes, 4, 1);
    notas[8] = calculaNotas(estudantes, 4, 2);
    notas[9] = calculaNotas(estudantes, 5, 0);
    notas[10] = calculaNotas(estudantes, 5, 1);
    notas[11] = calculaNotas(estudantes, 6, 1);
    notas[12] = calculaNotas(estudantes, 7, 0);
    notas[13] = calculaNotas(estudantes, 7, 1);
    notas[14] = calculaNotas(estudantes, 7, 2);
    notas[15] = calculaNotas(estudantes, 8, 0);
    notas[16] = calculaNotas(estudantes, 8, 1);
    notas[17] = calculaNotas(estudantes, 9, 1);
    printf("Maiores notas da turma    %2.0lf    %2.0lf    %2.0lf    %2.0lf    %2.0lf    %3.0lf\n", notas[0], notas[1], notas[2], notas[3], notas[4], notas[5]);
    printf("Menores notas da turma    %2.0lf    %2.0lf    %2.0lf    %2.0lf    %2.0lf    %3.0lf\n", notas[6], notas[7], notas[8], notas[9], notas[10], notas[11]);
    printf("Notas médias da turma   %2.1lf  %2.1lf  %2.1lf   %2.1lf  %2.1lf   %3.1lf\n", notas[12], notas[13], notas[14], notas[15], notas[16], notas[17]);
    printf("-----------------------------------------------------------\n");
    printf("Número de estudantes aprovados:            %2.0lf (%2.1lf %%)\n", situacoes[0], ((situacoes[0]*100)/i));
    printf("Número de estudantes reprovados:           %2.0lf (%2.1lf %%)\n", situacoes[1], ((situacoes[1]*100)/i));
    printf("Número de estudantes reprovados por falta: %2.0lf (%2.1lf %%)\n", situacoes[2], ((situacoes[2]*100)/i));
    int aux[10] = {0};
    for(int i = 0; i< 80 && estudantes[i].nomeAluno[0]!='\0'; i++){
        if(estudantes[i].notafinal < 11){
            aux[0] = aux[0] + 1;
        }
        else if(estudantes[i].notafinal > 10 && estudantes[i].notafinal < 21){
            aux[1] = aux[1] + 1;
        }
        else if(estudantes[i].notafinal > 20 && estudantes[i].notafinal < 31){
            aux[2] = aux[2] + 1;
        }
        else if(estudantes[i].notafinal > 30 && estudantes[i].notafinal < 41){
            aux[3] = aux[3] + 1;
        }
        else if(estudantes[i].notafinal > 40 && estudantes[i].notafinal < 51){
            aux[4] = aux[4] + 1;
        }
        else if(estudantes[i].notafinal > 50 && estudantes[i].notafinal < 61){
            aux[5] = aux[5] + 1;
        }
        else if(estudantes[i].notafinal > 60 && estudantes[i].notafinal < 71){
            aux[6] = aux[6] + 1;
        }
        else if(estudantes[i].notafinal > 70 && estudantes[i].notafinal < 81){
            aux[7] = aux[7] + 1;
        }
        else if(estudantes[i].notafinal > 80 && estudantes[i].notafinal < 91){
            aux[8] = aux[8] + 1;
        }
        else if(estudantes[i].notafinal > 90){
            aux[9] = aux[9] + 1;
        }
    }
    printf("Histograma de notas finais em grupos de 10 pontos:\n");
    printf(" 0  -  10   %d ", aux[0]);asterisco(aux[0]);
    printf("11  -  20   %d ", aux[1]);asterisco(aux[1]);
    printf("21  -  30   %d ", aux[2]);asterisco(aux[2]);
    printf("31  -  40   %d ", aux[3]);asterisco(aux[3]);
    printf("41  -  50   %d ", aux[4]);asterisco(aux[4]);
    printf("51  -  60   %d ", aux[5]);asterisco(aux[5]);
    printf("61  -  70   %d ", aux[6]);asterisco(aux[6]);
    printf("71  -  80   %d ", aux[7]);asterisco(aux[7]);
    printf("81  -  90   %d ", aux[8]);asterisco(aux[8]);
    printf("91  - 100   %d ", aux[9]);asterisco(aux[9]);
    printf("----------------------------------------------------------------------------------------------\n");
  }
  else{
    printf("\nNão há turma carregada!\n");
  }
}

void asterisco(int ast){
    for(int i = 0; i < ast; i++){
        printf("*");
    }
    printf("\n");
}

/** 
 * @brief Função que faz os calcula todos dados de notas
 * 
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 * @param aux indicador do cálculo específico que será usado
 * @param ind indicador do índice dos vetores do vetor de struct
 * @return retorna o resultado do cálculo usado
 */
double calculaNotas(Cadastro estudantes[], int aux, int ind){ // tem que terminar
  int i = 0;
  double maiorNota = 0;
  double menorNota;
  double mediaNotas = 0;
  switch(aux){
    case 1: // indicador de cálculo de maior nota de provas
      for(i = 0; i<80 && estudantes[i].nomeAluno[0] !=  '\0'; i++){
        if(estudantes[i].notasProvas[ind]>maiorNota){
        maiorNota = estudantes[i].notasProvas[ind];
        }
      }
      return maiorNota;
      break;
    case 2: // indicador de cálculo de maior nota de trabalhos
      for(i = 0; i<80 && estudantes[i].nomeAluno[0] !=  '\0'; i++){
        if(estudantes[i].notasTrabs[ind]>maiorNota){
        maiorNota = estudantes[i].notasTrabs[ind];
        }
      }
      return maiorNota;
      break;
    case 3: // indicador de cálculo de maior nota final
      for(i = 0; i<80 && estudantes[i].nomeAluno[0] !=  '\0'; i++){
        if(estudantes[i].notafinal>maiorNota){
        maiorNota = estudantes[i].notafinal;
        }
      }
      return maiorNota;
    case 4: // indicador de cálculo de menor nota de provas
      menorNota = estudantes[i].notasProvas[ind];
      for(i = 0; i<80 && estudantes[i].nomeAluno[0] !=  '\0'; i++){
        if(estudantes[i].notasProvas[ind]<menorNota){
        menorNota = estudantes[i].notasProvas[ind];
        }
      }
      return menorNota;
      break;
    case 5: // indicador de cálculo de menor nota de trabalhos    
      menorNota = estudantes[i].notasTrabs[ind];  
      for(i = 0; i<80 && estudantes[i].nomeAluno[0] !=  '\0'; i++){
        if(estudantes[i].notasTrabs[ind]<menorNota){
        menorNota = estudantes[i].notasTrabs[ind];
        }
      }
      return menorNota;
      break;
    case 6: // indicador de cálculo de menor nota final
      menorNota = estudantes[i].notafinal;  
      for(i = 0; i<80 && estudantes[i].nomeAluno[0] !=  '\0'; i++){
        if(estudantes[i].notafinal<menorNota){
        menorNota = estudantes[i].notafinal;
        }
      }
      return menorNota;
      break;
    case 7: // indicador de cálculo de média de notas de provas
      for(i = 0; i<80 && estudantes[i].nomeAluno[0] !=  '\0'; i++){
        mediaNotas += estudantes[i].notasProvas[ind];
      }
      return mediaNotas/i;
      break;
    case 8: // indicador de cálculo de média de notas de trabalhos
      for(i = 0; i<80 && estudantes[i].nomeAluno[0] !=  '\0'; i++){
        mediaNotas += estudantes[i].notasTrabs[ind];
      }
      return mediaNotas/i;
      break;
    case 9: // indicador de cálculo de média de notas finais
      for(i = 0; i<80 && estudantes[i].nomeAluno[0] !=  '\0'; i++){
        mediaNotas += estudantes[i].notafinal;
      }
      return mediaNotas/i;
      break;
  }
  return 0;
}

/** 
 * @brief Função que aumenta os valores dos índices do vetor
 *        de situações de acordo com o número de alunos aprovados,
 *        reprovados e reprovados por falta
 *
 * @param situacao[] ponteiro para o vetor do qual os valores dos 
 *        índices serão alterados
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 */
void verificaSituacoes(double situacao[], Cadastro estudantes[]){
  for(int i=0; i<80 && estudantes[i].nomeAluno[0] != '\0'; i++){
    if(estudantes[i].situacao == 'A') situacao[0]++;
    else if(estudantes[i].situacao == 'R') situacao[1]++;
    else if(estudantes[i].situacao == 'F') situacao[2]++;
  }
}

/** 
 * @brief Função que cadastra um novo estudante no vetor de struct
 *
 * @param *estudantes ponteiro para o vetor de struct(estudantes)
 * @param arquivo[] ponteiro para a string com o nome do arquivo no menu principal
 */
void cadEstud(Cadastro *estudantes, char arquivo[]){
  int i = verificaVetS(estudantes);
  double notafinal = 0.0;
  if(estudantes[0].nomeAluno[0]!='\0' || fopen(arquivo, "r") != NULL){
  printf("=========================================\n");               
  printf("\t    Cadastrar Novo Estudante \n");
  printf("=========================================\n\n");    
  printf("\nDigite o nome: ");
    fgets(estudantes[i].nomeAluno, sizeof(estudantes[i].nomeAluno), stdin);
    estudantes[i].nomeAluno[strcspn(estudantes[i].nomeAluno, "\n")] = '\0';
    printf("Digite a matrícula: ");
    fgets(estudantes[i].matricula, sizeof(estudantes[i].matricula), stdin);
    estudantes[i].matricula[strcspn(estudantes[i].matricula, "\n")] = '\0';
    printf("Digite as três notas das provas: ");
    scanf("%lf", &estudantes[i].notasProvas[0]);
    scanf("%lf", &estudantes[i].notasProvas[1]);
    scanf("%lf", &estudantes[i].notasProvas[2]);
    printf("Digite as duas notas dos trabalhos: ");
    scanf("%lf", &estudantes[i].notasTrabs[0]);
    scanf("%lf", &estudantes[i].notasTrabs[1]);
    printf("Digite o número de faltas: ");
    scanf("%d", &estudantes[i].faltas);
    verificaSituacao(i, estudantes);
    printf("\nNota final calculada: %2.0lf", estudantes[i].notafinal);
    if(estudantes[i].situacao == 'F'){
      printf("\nSituação final: Reprovado por faltas\n");
    }
    else if(estudantes[i].situacao == 'R'){
      printf("\nSituação final: Reprovado\n");
    }
    else{
      printf("\nSituação final: Aprovado\n");
    }
    i = 0;
  }
  else{
    printf("\nNão há turma carregada!\n");
  }
}

/** 
 * @brief Função que cadastra um novo estudante no vetor de struct
 *
 * @param i 
 * @param *estudantes ponteiro para a string com o nome do arquivo no menu principal
 */
void verificaSituacao(int i, Cadastro *estudantes){
  double notafinal = 0;
  notafinal = estudantes[i].notasProvas[0] + estudantes[i].notasProvas[1] + estudantes[i].notasProvas[2] + estudantes[i].notasTrabs[0] + estudantes[i].notasTrabs[1];
  estudantes[i].notafinal = notafinal;
  if(estudantes[i].faltas>=18){
    estudantes[i].situacao = 'F';
  }
  else if(estudantes[i].notafinal<60){
    estudantes[i].situacao = 'R';
  }
  else{
    estudantes[i].situacao = 'A';
  }
}

/** 
 * @brief Função que verifica e retorna o primeiro  
 *        índice vazio do vetor de struct
 *
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 * @return o valor de i
 */
int verificaVetS(Cadastro estudantes[]){ 
  int i = 0;
  for(i=0; i<80 && estudantes[i].nomeAluno[0] != '\0'; i++){
  }
  return i;
}


/** 
 * @brief Função que chama as funções relacionadas ao menu
 *        de edição de acordo com as opções inseridas
 *
 * @param *estudantes ponteiro para o vetor de struct(estudantes)
 * @param arquivo[] ponteiro para a string com o nome do arquivo no menu principal
 */
void menuEditEst1(Cadastro *estudantes, char arquivo[]){
  int i = 0;
  char nomeAluno[51] = {'\0'};
  char matricula[12] = {'\0'};
  int op = 0;
  if(estudantes[0].nomeAluno[0]!='\0' || fopen(arquivo, "r") != NULL){
     printf("=========================================\n");               
  printf("\t    Editar informações do Estudante \n");
  printf("=========================================\n\n");            
  printf("Opções:\n");
  printf(" 1 - Selecionar por número de matrícula\n");
  printf(" 2 - Selecionar por nome\n");
  printf(" 3 - Voltar ao menu principal\n");
  printf("\nDigite uma opção: ");
    scanf("%d", &op);
    while(op!=3){
      switch(op){
        case 1:
          printf("\nDigite o número de matrícula: ");
          getchar();
          fgets(matricula, sizeof(matricula), stdin);
          matricula[strcspn(matricula, "\n")] = '\0';
          if(verificaEstudante(matricula, estudantes)!= -1){
            i = verificaEstudante(matricula, estudantes);
            menuEditEst2(estudantes, i);
          }
          else{
            printf("\nNúmero de matrícula inválido!\n");
          }
          break;
        case 2: 
          printf("\nDigite o Nome do estudante: ");
          getchar();
          fgets(nomeAluno, sizeof(nomeAluno), stdin);
          nomeAluno[strcspn(nomeAluno, "\n")] = '\0';
          if(verificaEstudante(nomeAluno, estudantes)!= -1){
            i = verificaEstudante(nomeAluno, estudantes);
            menuEditEst2(estudantes, i);
          }
          else{
            printf("\nNome de estudante inválido!\n");
          }
          break;
        default: 
			    printf("Opção inválida!\nPressione Enter para voltar à tela anterior...\n");
			    setbuf(stdin, NULL);
			    getchar(); 
			    setbuf(stdin, NULL); 
			    break;  
     }
  printf("=========================================\n");               
  printf("\t    Editar informações do Estudante \n");
  printf("=========================================\n\n");            
  printf("Opções:\n");
  printf(" 1 - Selecionar por número de matrícula\n");
  printf(" 2 - Selecionar por nome\n");
  printf(" 3 - Voltar ao menu principal\n");
  printf("\nDigite uma opção: ");
     scanf("%d", &op);
  }
  op = 0;
  }
  else{
    printf("\nNão há turma carregada!\n");
  }
}

/** 
 * @brief Função que verifica se o nome ou matrícula inseridos
 *        existem no vetor de struct
 *
 * @param strin[] recebe a string inserida no menu de edição
 *        correspondente ao nome ou matrícula do estudante
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 * @return o valor de i ou -1, depenendo da situação
 */
int verificaEstudante(char strin[], Cadastro estudantes[]){
  int i = 0;
  for(i = 0; i<80 && estudantes[i].nomeAluno[0]!='\0'; i++){
    if(strcmp(estudantes[i].nomeAluno, strin) == 0 || strcmp(estudantes[i].matricula, strin)==0){
      return i;
      break;
    }
    else{
    }
  }
  if(i == 79) return -1;
}


/** 
 * @brief Função que edita os dados do estudante escolhido
 *
 * @param *estudantes ponteiro para o vetor de struct(estudantes)
 * @param arquivo[] ponteiro para a string com o nome do arquivo no menu principal
 */
void menuEditEst2(Cadastro *estudantes, int i){
  int op = 0;
  printf("=========================================\n");               
  printf("\t    Editar informações do Estudante \n");
  printf("=========================================\n\n");  
  printf("Opções:\n");
	printf("\n 1 - Alterar nome\n");
	printf(" 2 - Alterar matrícula\n");
	printf(" 3 - Alterar nota da prova 1\n");
  printf(" 4 - Alterar nota da prova 2\n");
  printf(" 5 - Alterar nota da prova 3\n");
  printf(" 6 - Alterar nota do trabalho 1\n");
  printf(" 7 - Alterar nota do trabalho 2\n");
  printf(" 8 - Alterar número de faltas\n");
  printf(" 9 - Voltar ao menu anterior\n");
  printf("\nDigite uma opção: ");
  scanf("%d", &op);
  while(op!=9){
    switch(op){
        case 1: 
          printf("\nDigite o nome: ");
          getchar();
          fgets(estudantes[i].nomeAluno, sizeof(estudantes[i].nomeAluno), stdin);
          estudantes[i].nomeAluno[strcspn(estudantes[i].nomeAluno, "\n")] = '\0';
          break;
        case 2: 
          printf("\nDigite a matrícula: ");
          getchar();
          fgets(estudantes[i].matricula, sizeof(estudantes[i].matricula), stdin);
          estudantes[i].matricula[strcspn(estudantes[i].matricula, "\n")] = '\0';
          break;
        case 3: 
          printf("\nDigite a nota da prova 1: ");
          scanf("%lf", &estudantes[i].notasProvas[0]);
          break;
        case 4: 
          printf("\nDigite a nota da prova 2: ");
          scanf("%lf", &estudantes[i].notasProvas[1]);
          break;
        case 5: 
          printf("\nDigite a nota da prova 3: ");
          scanf("%lf", &estudantes[i].notasProvas[2]);
          break;
        case 6: 
          printf("\nDigite a nota do trabalho 1: ");
          scanf("%lf", &estudantes[i].notasTrabs[0]);
          break;
        case 7: 
          printf("\nDigite a nota do trabalho 2: ");
          scanf("%lf", &estudantes[i].notasTrabs[1]);
          break;
        case 8: 
          printf("\nDigite o número de faltas: ");
          scanf("%d", &estudantes[i].faltas);
          break;
        default:
          printf("Opção inválida!\nPressione Enter para voltar à tela anterior...\n");
			    setbuf(stdin, NULL);
			    getchar(); 
			    setbuf(stdin, NULL); 
          break;
    }
    verificaSituacao(i, estudantes);
   printf("=========================================\n");               
  printf("\t    Editar informações do Estudante \n");
  printf("=========================================\n\n");  
  printf("Opções:\n");
	printf("\n 1 - Alterar nome\n");
	printf(" 2 - Alterar matrícula\n");
	printf(" 3 - Alterar nota da prova 1\n");
  printf(" 4 - Alterar nota da prova 2\n");
  printf(" 5 - Alterar nota da prova 3\n");
  printf(" 6 - Alterar nota do trabalho 1\n");
  printf(" 7 - Alterar nota do trabalho 2\n");
  printf(" 8 - Alterar número de faltas\n");
  printf(" 9 - Voltar ao menu anterior\n");
  printf("\nDigite uma opção: ");
    scanf("%d", &op);
  }
  op = 0;
}

/** 
 * @brief Função que zera os dados da struct, para serem nomamente
 *        instanciados com os dados do último arquivo lido
 *
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 * @param arquivo[] ponteiro para a string com o nome do arquivo no menu principal
 */
void relerTurma(Cadastro estudantes[], char arquivo[]){
  int n = 80;
  FILE *fp = NULL;
  fp = fopen(arquivo, "r");
  for(int i = 0; i<n; i++){
    for(int j = 0; j<51; j++){
      estudantes[i].nomeAluno[j] = '\0';
      if(j<13){
        estudantes[i].matricula[j] = '\0';
      }
    }
    estudantes[i].notasProvas[0] = 0.0;
    estudantes[i].notasProvas[1] = 0.0;
    estudantes[i].notasProvas[2] = 0.0;
    estudantes[i].notasTrabs[0] = 0.0;
    estudantes[i].notasTrabs[1] = 0.0;
    estudantes[i].notafinal = 0.0;
    estudantes[i].faltas = 0;
    estudantes[i].situacao = '\0';
  }
  if (fp == NULL){
    printf("\nArquivo %s não existe!\n", arquivo);
  }
  else{
    printf("\nArquivo %s lido com sucesso!\n", arquivo);
    for(int i = 0; fscanf(fp, " %c", &estudantes[i].nomeAluno[0]) != EOF && i<80; i++){
        for(int j = 1; j<51; j++){
          if(estudantes[i].nomeAluno[j-1]=='\n'){
            estudantes[i].nomeAluno[j-1] = '\0';
            break;
          }
          else{
            fscanf(fp, "%c", &estudantes[i].nomeAluno[j]);
          }
        }
        fgets(estudantes[i].matricula, sizeof(estudantes[i].matricula), fp);
        estudantes[i].matricula[strcspn(estudantes[i].matricula, "\n")] = '\0';
        fscanf(fp, "%lf\n", &estudantes[i].notasProvas[0]);
        fscanf(fp, "%lf\n", &estudantes[i].notasProvas[1]);
        fscanf(fp, "%lf\n", &estudantes[i].notasProvas[2]);
        fscanf(fp, "%lf\n", &estudantes[i].notasTrabs[0]);
        fscanf(fp, "%lf\n", &estudantes[i].notasTrabs[1]);
        fscanf(fp, "%d\n", &estudantes[i].faltas);
        fscanf(fp, "%lf\n", &estudantes[i].notafinal);
        fscanf(fp, " %c\n", &estudantes[i].situacao);
   }
   fclose(fp);
  }
}

/** 
 * @brief Função que cria ou sobrescreve um arquivo.
 *
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 * @param arquivo[] recebe o valor da string com o último
 *        nome de arquivo salvo
 */
void salvar_Sair(Cadastro estudantes[], char arquivo[]){
  char sn = '\0';
  FILE *fp = NULL;
  fp = fopen(arquivo, "r");
  if(fp != NULL){
    printf("\nArquivo %s já existe. Deseja sobrescrevê-lo? (S/N) ", arquivo);
    while(sn != 'S' || sn != 'N'){
      scanf(" %c", &sn);
      if(sn == 'S'){
        fclose(fp);
        imprimePraArq(arquivo, estudantes);
        break;
      }
      else if(sn == 'N'){
        fclose(fp);
        break;
      }
      else{
        printf("Opção inválida!\n");
        printf("Digite novamente: ");
        break;
      }
    }
    printf("\nObrigado por utilizar \n  Até a próxima.\n");
  }
  else{
    printf("\nO arquivo %s não existe. Deseja criar um novo? (S/N) ", arquivo);
    while(sn != 'S' || sn != 'N'){
      scanf(" %c", &sn);
      if(sn == 'S'){
        imprimePraArq(arquivo, estudantes);
        break;
      }
      else if(sn == 'N'){
        break;
      }
      else{
        printf("Opção inválida!\n");
        printf("Digite novamente: ");
        break;
      }
    }
    printf("\nObrigado por utilizar \n  Até a próxima.\n");
  }
}

/** 
 * @brief Função que sobrescreve o arquivo.
 *
 * @param arquivo[] recebe o valor da string com o último
 *        nome de arquivo salvo
 * @param estudantes[] ponteiro para o vetor de struct(estudantes)
 */
void imprimePraArq(char arquivo[], Cadastro estudantes[]){ 
  FILE *fp = NULL;
  fp = fopen(arquivo, "w");
  for(int i = 0; i<80 && estudantes[i].nomeAluno[0]!='\0'; i++){
    fprintf(fp, "%s\n", estudantes[i].nomeAluno);
    fprintf(fp, "%s\n", estudantes[i].matricula);
    fprintf(fp, "%.0lf\n", estudantes[i].notasProvas[0]);
    fprintf(fp, "%.0lf\n", estudantes[i].notasProvas[0]);
    fprintf(fp, "%.0lf\n", estudantes[i].notasProvas[1]);
    fprintf(fp, "%.0lf\n", estudantes[i].notasProvas[2]);
    fprintf(fp, "%.0lf\n", estudantes[i].notasTrabs[0]);
    fprintf(fp, "%.0lf\n", estudantes[i].notasTrabs[1]);
    fprintf(fp, "%d\n", estudantes[i].faltas);
    fprintf(fp, "%.0lf\n", estudantes[i].notafinal);
    fprintf(fp, "%c\n", estudantes[i].situacao);
  }
  fclose(fp);
}