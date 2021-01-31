/*
Ficheiro: Hanabi Game
Título: Hanabi Game
Autor: Bruno Miguel Barrigas Medeiros 71337
Obs: O load do jogo encontra-se neste momento inacabado por falta de tempo.
Data: 18/01/2020
Revisões:
......
*/
#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "graphsettings.h" //header file que contem funcoes de ajuda na interface do programa
#include <time.h>

/*Subrotina do bot*/
bot_algorithm(int hand_player1[],int hand_player2[],int deck_c[], int deck_n[],int cluep2_n[], int cluep2_c[]);
/*Subrotina que mostra a mesa das cartas*/
print_table(int row, int col, int matrix[row][col]);
/*Subrotina que descarta a carta que escolhermos*/
discard_card(int hand_player[],int deck_c[],int deck_n[], int index);
/*Subrotina que dá as pistas*/
give_clue(int hand_player[],int deck_c[],int deck_n[],int index,int clue_n[],int clue_c[]);
/*Subrotina que guarda o jogo criando um ficheiro de texto com 
todas as variaveis globais guardadas*/
save_game();
/*Subrotina que procura cartas jogáveis na mao do bot*/
int playable_card(int deck_n[],int deck_c[]);
/*Subrotina que procura cartas jogáveis na mao do jogador*/
int playable_card2(int deck_n[],int deck_c[]);
/*Subrotina que joga uma carta*/
play_card(int hand_player[], int deck_c[],int deck_n[], int index);
/*Subrotina que da print de todas as variaveis e graficos necessarios para jogar*/
show_graph_elements();
//subrotina que mostra o baralho;
void show_deck();
//funcao que baralha dois vetores aleatoriamente
shuffle(int [],int [], int);
/*subrotina que atraves da posicao da carta no deck_n[] 
da uma cor, cor essa que equivale á mesma posicao no vetor
deck_c[]*/
color(int [], int);

//deck com todos os numeros do baralho
int deck_n[50] = {1,1,1,2,2,3,3,4,4,5,1,1,1,2,2,3,3,4,4,5,1,1,1,2,2,3,3,4,4,5,1,1,1,2,2,3,3,4,4,5,1,1,1,2,2,3,3,4,4,5};
//deck para determinar a cor da carta;verde/azul/amarelo/vermelho/ branco
int deck_c[50] ={1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5};
//variaveis para a mao dos jogadores, mesa de jogo e tabela de cartas descartadas
int hand_player1[5], hand_player2[5], table[5][5], discard_table[5][5];
//vetores onde vao estar contidas as pistas da cor e do numero dado pelos jogadores
int cluep1_c[5]= {0,0,0,0,0}, cluep2_c[5] = {0,0,0,0,0},cluep1_n[5] = {0,0,0,0,0},cluep2_n[5]= {0,0,0,0,0};

//ultima carta do baralho
int last_deckcard=49;
//numero de vidas no jogo
int life_tokens=3;
//numero de pistas no jogo
int clue_tokens=8;
//cartas que sobram ao entregar as 5 cartas a cada jogador
int shop_deck=40;
//variavel onde vai ficar guardada o nome do jogador(maximo 16 caracteres)
char name[17];
/*Variavel que guarda a pontuacao*/
int points=0;
/*variavel responsavel pelos turnos
caso o valor seja ímpar vai ser o jogador a jogar
caso seja par será o bot*/
int turn=0;

//variavel para sortear quem comeca primeiro
int random;

int main(void) 
{
	/*Criacao de um apontador para ler o ficheiro de texto 
	, ou seja para fazer load do jogo*/
	FILE *jp;
	//permite nos criar uma nova semente a cada execute assim sabemos que vai 
	//gerar sempre numeros diferentes
	srand(time(NULL));
	int k,a,index,i,j;
	//variavel que vai ser usada no menu inicial para escolher o que fazer
	char choose,op;
	
	setlocale(LC_ALL, "");//para permitir acentos nos nomes e etc
	system("title HANABI V1.2");//define um titulo na console
	system("mode con:cols=250 lines=70" ); //define o tamanho da console 	
do 
{	
	inicio:
    system("cls");	
    //criação das letras da interface inicial (HANABI)
    //atraves da subrotina showRectAt()
	for(k=0,a=0; k<5 ; a+=2 ,k++)
	{
		setColor(15,15);
	    showRectAt(50+k,2+k,5-a,12-a); //perna do H
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(65+k,2+k,5-a,12-a);
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(74+k,2+k,5-a,12-a); //perna do H
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(88+k,2+k,5-a,12-a); //perna do A
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(97+k,2+k,5-a,12-a);//perna do A
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(123+k,2+k,5-a,12-a); //perna do 2 A
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(137+k,2+k,5-a,12-a);//perna do 2 A
	    resetColor();  
	    
	    setColor(15,15);
	    showRectAt(114+k,2+k,5-a,12-a);//perna de N
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(146+k,2+k,5-a,12-a);//perna de B
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(168+k,2+k,5-a,12-a);//perna de I
	    resetColor();
	    
	    setColor(0,0);
	    showRectAt(174+k,2+k,5-a,12-a);//perna de I
	    resetColor();
	}
	
	for (k=0; k<12; k++)
	{
		setColor(15,15);
	    showRectAt(102+k,2+k,1,1); //linha diagonal do N
	    resetColor();
	}
	    setColor(15,15);
	    showRectAt(56,6,8,3); //traco do H
	    resetColor();
	    setColor(15,15);
	    showRectAt(57,7,6,1);
	    resetColor();
	    setColor(15,15);
	    showRectAt(58,7,6,1);
	    resetColor();          
	    
	    setColor(15,15);
	    showRectAt(79,2,8,1); //traco do A
	    resetColor();
	    setColor(15,15);
	    showRectAt(80,3,6,0);
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(79,6,8,3);
	    resetColor(); // traco do A
	    setColor(15,15);
	    showRectAt(80,7,6,1);
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(128,2,8,1); //traco do  2A
	    resetColor();
	    setColor(15,15);
	    showRectAt(129,3,6,0);
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(128,6,8,3);
	    resetColor(); // traco do 2 A
	    setColor(15,15);
	    showRectAt(129,7,6,1);
	    resetColor();
        
        setColor(15,15);
	    showRectAt(151,2,9,1); //linha diagonal do B
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(161,5,3,1); //linha diagonal do B
	    resetColor();
	    setColor(15,15);
	    showRectAt(161,4,3,2); //linha diagonal do B
	    resetColor();
	    
	    
	    setColor(15,15);
	    showRectAt(151,7,9,1); //linha diagonal do B
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(151,13,9,1); //linha diagonal do B
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(161,9,3,1); //linha diagonal do B
	    resetColor();
	    setColor(15,15);
	    showRectAt(161,10,3,2); //linha diagonal do B
	    resetColor();
	    setColor(15,15);
	    showRectAt(161,11,3,1); //linha diagonal do B
	    resetColor();

    printf("\n\n\n\n");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tDATA : %s \n\n\n",__DATE__);
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t  HORA: %s \n\n",__TIME__);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t$ Seja Bem-Vindo ao Grande Jogo do Hanabi $ \n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t    Escreva uma das seguintes opções: \n\n\n\n\n");
    setColor(10,0);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tA-->   NOVO JOGO \n\n\n\n\n");
    resetColor();
    setColor(9,0);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tB-->   RETOMAR A PARTIDA GUARDADA \n\n\n\n\n");
    resetColor();
    setColor(6,0);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tC-->   REGRAS DO JOGO \n\n\n\n\n");
    resetColor();
    setColor(4,0);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tD-->   SAIR DO JOGO \n\n\n\n\n");
    resetColor();
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tEscreva o seu nome: ");
	fgets(name,17,stdin);
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t  Escolha: ");
    scanf("%c", &choose);
    
}while(choose !='a' && choose !='A' && choose !='b'&& choose !='B' && choose !='c' && choose !='C' && choose !='d' && choose !='D');
//enquanto a escolha for diferente de 'a','A','b','B','c','C','d','D' o utilizador terá que inserir novamente 
//outra opção até ser igual a alguma das anteriores, é por isso que usamos o do while
   	switch (choose) 
	{	
	    case 'a':
		case 'A':
				//caso escolha a opção A irá iniciar um novo jogo
			system("cls"); //limpar o ecra
	        shuffle(deck_n,deck_c, 49);//troca os numeros do deck_n e ao mesmo tempo a sua cor.    
             //subrotina que da as cartas aos jogadores
            for (k=0; k < 5; k++)
			{
				//distribui uma carta a cada um alternadamente ate cada um ter 5 cartas
             	get_card(hand_player1, k);
    	        get_card2(hand_player2, k);
    	        
	        }
	        gotoxy(0,0);
			setColor(15,0);
            showRectAt(0,0,75,7);
			resetColor();
			
	        gotoxy(2,58);
			printf("*BARALHO DAS CORES*\n");
			show_deck(deck_c);
			gotoxy(2,60);
		    printf("*BARALHO DOS NUMEROS*\n");
		    show_deck(deck_n);

          	printf("\nCartas Jogador1      Cartas Jogador2\n");
	        for (k=0, index=49; k < 5; k++, index--)
			{
	         	color(deck_c, deck_c[index-k]);
                printf("%d  ", hand_player1[k]);
                resetColor();  	
	        }                                                  
            printf("***** ");
	
	        for (k=0, index=48; k < 5; k++, index--)
			{ 
		       color(deck_c, deck_c[index-k]);
    	       printf(" %d ", hand_player2[k]);
    	       resetColor();
        	}
        	
        	print_hand();
        	print_table(5,5,table);
            //mostra os elementos graficos como  nº vida, nºpistas...
	        show_graph_elements();
	        //mostra a tabela de cartas descartadas
	        show_discard(5,5,discard_table);   
	        gotoxy(0,0);
	        //sortear quem começa primeiro!
            random = 1;//0 + rand() % 2; //ou sai 1 ou sai 0
            //se o numero gerado for igual a 1 o primeiro jogador é o humano caso
            //contrario é o bot,
            
	        if (random == 1 )
        	{ 
        	   gotoxy(1,1);
        	   setColor(9,0);
        	   printf("O primeiro jogador é o HUMANO!");
        	   gotoxy(1,2);
        	   setColor(7,0);
        	   printf("A cada turno é guardada a partida.");
        	   resetColor();
        	   gotoxy(1,3);
        	   setColor(7,0);
        	   printf("O programa ainda se encontra em fase de desenvolvimento");
        	   resetColor();
        	   gotoxy(1,4);
        	   setColor(7,0);
        	   printf("pela qual a existencia de bugs é possivel, obrigado por jogar!");
        	   resetColor();
        	   /*recebe um valor impar*/
			   turn = 1;
			   getch();
			   Turn();
		    } 
		    //caso seja o bot o primeiro jogador faz isto:
        	else
        	{
        	   gotoxy(2,1);
        	   setColor(10,0);
        	   printf("O primeiro jogador é o BOT!");
        	   resetColor();
        	   /*recebe um valor par*/
        	   turn=2;
        	   resetColor();
		       print_hand();
		       
		       bot_algorithm(hand_player1,hand_player2,deck_c,deck_n,cluep2_n,cluep2_n);
			}     	
		
		/*A Opcao para dar load da partida guardada encontra-se inacaba pelo qual nao funciona
		,nao consegui ler o ficheiro e atribuir os valores dos vectores a cada posicao correctamente*/			   
        case 'b': //opcao para ler os dados previamente guardados e retomar a partida gravada.
		case 'B':
				jp = fopen("savegame.txt","r");
				
					if (jp == NULL)
					{
						printf("Nao foi possivel ler o save!");
					}
					else
					{
						system("cls");
						fscanf(jp,"%d %d %d %d %d",&random,&points,&shop_deck,&clue_tokens,&life_tokens);//le as primeiras duas linhas
						fscanf(jp,"%*[^\n] %s",&name);

					fclose(jp);
					}
				Turn();	
			    break;		    
		case 'c': //opcao para saber as regras do jogo
		case 'C':
			system("cls");
		    printf("\n\n\tRegras do Jogo:\n\n");
			printf("Este programa é baseado no jogo de tabuleiro chamado hanabi\n");
			printf("onde é possivel jogar com o computador de maneira interativa,\n");
			printf("o objetivo é criar uma determinada ordem de forma a criar sequências de cor.\n");
			printf("***************************");
			printf("\n\tComposição:\n\n");
			printf("-50 cartas;\n-10 cartas de cada uma das 5 cores(");
			setColor(10,0);
			printf("verde,");
			resetColor();
			setColor(11,0);
			printf(" azul,");
			resetColor();
			setColor(6,0);
			printf(" amarelo,");
			resetColor();
			setColor(4,0);
			printf(" vermelho");
			resetColor();
			printf(" e");
			printf(" branco");
			printf(").\n");
			printf("-cada cor contém: 3 cartas nº 1; 2 cartas nº2; 2 cartas nº3, 2 cartas nº4; 1 carta nº5.\n");
			printf("-8 tokens com pista.\n");
			printf("-3 tokens de vida.\n");
			printf("***************************\n");
			printf("\tObjetivo:\n\n");
			printf("-Jogar para a mesa por ordem crescente do 1 ao 5 todas as cartas da mesma cor.\n");
			printf("***************************\n");
			printf("\tPreparação:\n\n");
			printf("-5 cartas a cada jogador.\n");
			printf("-Na tua vez ");
			setColor(10,0);
			printf("PODES:\n");
			resetColor();
			printf("  -Dar uma pista sobre todas as cartas com o mesmo numero ou cor (ganha 1 token com pista se acertar).\n");
			printf("  -Jogar uma carta para a mesa. Se estiver errada perde uma vida, se for jogado um 5 ganha uma pista.\n");
			printf("  -Descartar uma carta ganhando uma pista.\n");
			printf("***************************\n");
			setColor(4,0);
			printf("\tFinal do Jogo:\n\n");
			resetColor();
			printf("- Se nao tiverem vidas perdem!\n");
			printf("- Se nao tiverem vidas, contem quantas cartas conseguiram jogar correctamente,\n");
			printf("na mesa sendo a pontuação dada da seguinte maneira:\n\n");
			printf("***************************\n");
			printf("\t Tabela de Pontuação \n\n");
			setColor(4,0);
			printf("  - 0-15 HORRIVEL\n");
			resetColor();
			setColor(12,0);
			printf("  - 6-10 POBREZINHO\n");
			resetColor();
			setColor(10,0);
			printf("  - 11-15 OK\n");
			resetColor();
			setColor(2,0);
			printf("  - 16-20 BOM\n");
			resetColor();
			setColor(14,0);
			printf("  - 21-24 Excelente\n");
			resetColor();
			setColor(6,0);
			printf("  - 25 LEGENDARIO\n");
			resetColor();
			getch();
			
			//volta ao menu inicial
			goto inicio;
			
			break;
		case 'd':
		case 'D': //opcao para sair do jogo
		exit(0);	
	}
	return 0; 
	
}
/*Esta subrotina é responsavel pelos turnos
quando a variavel turn é par vai executar o codigo para
o bot jogar caso contrario vai executar o codigo para nos jogarmos*/
int Turn()
{
	int k,a, index,random;
	char op;

	//caso a variavel seja impar o jogador que vai jogar é o humano 
	/*enquanto existir vidas e as cartas do baralho nao tiverem acabado*/
	if(life_tokens > 0 && turn % 2 == 1 && shop_deck>0)
	{	
			system("cls"); //limpar o ecra
			
			gotoxy(0,0);
			setColor(15,0);
            showRectAt(0,0,75,7);
			resetColor();
			
	        gotoxy(2,58);
			printf("*BARALHO DAS CORES*\n");
			show_deck(deck_c);
			gotoxy(2,60);
		    printf("*BARALHO DOS NUMEROS*\n");
		    show_deck(deck_n);

          	printf("\nCartas Jogador1      Cartas Jogador2\n");
	        for (k=0, index=49; k < 5; k++, index--)
			{
	         	color(deck_c, deck_c[index-k]);
                printf("%d  ", hand_player1[k]);
                resetColor();  	
	        }                                                  
            printf("***** ");
	
	        for (k=0, index=48; k < 5; k++, index--)
			{ 
		       color(deck_c, deck_c[index-k]);
    	       printf(" %d ", hand_player2[k]);
    	       resetColor();
        	}
        	print_hand();
        	print_table(5,5,table);
            //mostra os elementos graficos como  nº vida, nºpistas...
	        show_graph_elements();
	        //mostra a tabela de cartas descartadas
	        show_discard(5,5,discard_table);   
			   
			   gotoxy(2,1);	
			   setColor(10,0);
			   printf("É a sua vez de jogar %s",name);
			   resetColor();
			   gotoxy(2,2);
		       printf("O que deseja fazer? Dar Pista(p), Jogar Carta(j) ou Descartar(d): ");
		       op=getch();
		       
		       switch(op)
			     {
		       //opcao para dar pista das cartas do bot
		       case 'p':
		       	case 'P':
		       		if (clue_tokens > 0)
					{			
		       		 system("cls");
		       		 	gotoxy(0,0);
						setColor(15,0);
			            showRectAt(0,0,75,7);
						resetColor();
						
				        gotoxy(2,58);
						printf("*BARALHO DAS CORES*\n");
						show_deck(deck_c);
						gotoxy(2,60);
					    printf("*BARALHO DOS NUMEROS*\n");
					    show_deck(deck_n);
			
			          	printf("\nCartas Jogador1      Cartas Jogador2\n");
				        for (k=0, index=49; k < 5; k++, index--)
						{
				         	color(deck_c, deck_c[index-k]);
			                printf("%d  ", hand_player1[k]);
			                resetColor();  	
				        }                                                  
			            printf("***** ");
				
				        for (k=0, index=48; k < 5; k++, index--)
						{ 
					       color(deck_c, deck_c[index-k]);
			    	       printf(" %d ", hand_player2[k]);
			    	       resetColor();
			        	}
                	 show_graph_elements();
                   	 show_discard(5,5,discard_table); 
                     print_hand(); 
                     print_table(5,5,table);
                     
                     give_clue(hand_player2,deck_c,deck_n,48,cluep2_n,cluep2_c);
                    }
                    /*caso nº pistas for = 0 tem de descartar cartas*/
                    else 
					{
						gotoxy(2,3);
						setColor(4,0);
						printf("Nao possui pistas, descarte cartas!!");
						resetColor();

						getch();
						Turn();
					
					}
		       	break;
		       //opcao para jogar uma carta do baralho
		       case 'j':
		       	case 'J':
		       		 system("cls");
       		 		gotoxy(0,0);
					setColor(15,0);
		            showRectAt(0,0,75,7);
					resetColor();
					
			        gotoxy(2,58);
					printf("*BARALHO DAS CORES*\n");
					show_deck(deck_c);
					gotoxy(2,60);
				    printf("*BARALHO DOS NUMEROS*\n");
				    show_deck(deck_n);
		
		          	printf("\nCartas Jogador1      Cartas Jogador2\n");
			        for (k=0, index=49; k < 5; k++, index--)
					{
			         	color(deck_c, deck_c[index-k]);
		                printf("%d  ", hand_player1[k]);
		                resetColor();  	
			        }                                                  
		            printf("***** ");
			
			        for (k=0, index=48; k < 5; k++, index--)
					{ 
				       color(deck_c, deck_c[index-k]);
		    	       printf(" %d ", hand_player2[k]);
		    	       resetColor();
		        	}
                	 show_graph_elements();
                   	 show_discard(5,5,discard_table); 
                     print_hand();
                     print_table(5,5,table);
                     
		       		 play_card(hand_player1,deck_c,deck_n,49);
		       		 turn++;
					   	
  				   	getch();
  				   	save_game();
			       	Turn();
		       		break;
		       //opcao para descartar uma carta do baralho		
		       case 'd':
			    case 'D':
			    	 system("cls");
			    	gotoxy(0,0);
					setColor(15,0);
		            showRectAt(0,0,75,7);
					resetColor();
					
			        gotoxy(2,58);
					printf("*BARALHO DAS CORES*\n");
					show_deck(deck_c);
					gotoxy(2,60);
				    printf("*BARALHO DOS NUMEROS*\n");
				    show_deck(deck_n);
		
		          	printf("\nCartas Jogador1      Cartas Jogador2\n");
			        for (k=0, index=49; k < 5; k++, index--)
					{
			         	color(deck_c, deck_c[index-k]);
		                printf("%d  ", hand_player1[k]);
		                resetColor();  	
			        }                                                  
		            printf("***** ");
			
			        for (k=0, index=48; k < 5; k++, index--)
					{ 
				       color(deck_c, deck_c[index-k]);
		    	       printf(" %d ", hand_player2[k]);
		    	       resetColor();
		        	}
                	 show_graph_elements();
                   	 show_discard(5,5,discard_table); 
                     print_hand();
                     print_table(5,5,table);
			    	 discard_card(hand_player1,deck_c,deck_n,49);
					break;		         	
		         }
      }
      
      //caso contrario se a varivavel for par é o bot
      //TURNO DO BOT!
      else if ((life_tokens > 0) && (turn % 2 == 0))
	  {
	  		system("cls");
			gotoxy(0,0);
			setColor(15,0);
            showRectAt(0,0,75,7);
			resetColor();
			
	        gotoxy(2,58);
			printf("*BARALHO DAS CORES*\n");
			show_deck(deck_c);
			gotoxy(2,60);
		    printf("*BARALHO DOS NUMEROS*\n");
		    show_deck(deck_n);

          	printf("\nCartas Jogador1      Cartas Jogador2\n");
	        for (k=0, index=49; k < 5; k++, index--)
			{
	         	color(deck_c, deck_c[index-k]);
                printf("%d  ", hand_player1[k]);
                resetColor();  	
	        }                                                  
            printf("***** ");
	
	        for (k=0, index=48; k < 5; k++, index--)
			{ 
		       color(deck_c, deck_c[index-k]);
    	       printf(" %d ", hand_player2[k]);
    	       resetColor();
        	}

        	print_hand();
        	print_table(5,5,table);
	        show_graph_elements();
	        show_discard(5,5,discard_table);	   
	  		bot_algorithm(hand_player1,hand_player2,deck_c,deck_n,cluep2_n,cluep2_c);	  		
	  }
      else
	  {
		game_over();
	  }
}
/*Subrotina que quando executa limpa o ecra e mostra a pontuacao
e a frase predefinida de acordo com a pontuaçao*/
void game_over()			
{	    
		system("cls");
	  	printf("\n\n\n\n");
    	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tDATA : %s \n\n\n",__DATE__);
    	printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t  HORA: %s \n\n",__TIME__);
   		printf("\t\t\t\t\t\t\t\t\t\t\t\t$ GAME-OVER!! Obrigado por jogar o HANABI $ \n\n\n\n\n");
   		
   		
   		switch(points)
		  {
		  	case 0 ... 5:
		  		gotoxy(102,19);
		  		setColor(4,0);
		  		printf("Oh! Credo foram todos vaiados.");
		  		resetColor();
		  		break;
		  	case 6 ... 10:
		  		gotoxy(102,19);
		  		setColor(12,0);
		  		printf("– Muito pobre, os espectadores estão entediados.");
		  		resetColor();
		  		break;
			case 11 ... 15:
		  		gotoxy(102,19);
		  		setColor(10,0);
		  		printf("– O espetáculo foi razoável, mas os espectadores já viram melhor");
		  		resetColor();
		  		break;
			case 16 ... 20:
		  		gotoxy(102,19);
		  		setColor(2,0);
		  		printf("Bom espetáculo! O público está satisfeito.");
		  		resetColor();
		  		break;
			case 21 ... 24:
		  		gotoxy(102,19);
		  		setColor(14,0);
		  		printf("Muito bom! O público está entusiasmado!");
		  		resetColor();
		  		break;
			case 25:
		  		gotoxy(102,19);
		  		setColor(6,0);
		  		printf("– Lendário! O público nunca esquecerá este espetáculo!");
		  		resetColor();
		  		break;	  	  	  	  	
		  }
		  
	  	gotoxy(105,22);
	  	setColor(10,0);
	  	printf("Pontuação: %d pontos\n\n", points);
	  	resetColor();
	    getch();
	    exit(0);
}
/*
show_deck
Assinatura: show_deck: parâmetros --> deck_n[]
Comentários:
Esta subrotina apresenta no ecra todas as cartas do vetor
deck_n e a cor respetiva de cada carta.
*/
void show_deck(int deck_n[])
{
	int i;
	for (i= 0; i<50; i++)
	{
		//define a cor atendendo á posição no vetor deck_c[]
		color(deck_n, deck_c[i]);	
		printf("%d   ", deck_n[i]);
		resetColor();
	}
}
/*
swap
Assinatura: swap: parâmetros --> int v[], int a, int b
Comentários: troca as posições de a e b do vetor v[],
ou seja o vetor v[a] recebe o valor de v[b] e vice-versa.
*/
swap (int v[], int a, int b) 
{ 
    int aux;
    aux = v[a]; 
    v[a] = v[b]; 
    v[b] = aux;
}
/*
shuffle
Assinatura: shuffle: parâmetros --> int v[],int c[], int dim
Comentários: subrotina que baralha um vetor v[] criando um segundo vetor de numeros
aleatorios r[] e ordenando este ultimo, replicando todas as trocas
no vetor v[](numeros) e c[](cor).
*/
shuffle(int v[],int c[], int dim){
	int r[dim],k,m;
	
	for (k=0;k<dim; k++)
	{
	   r[k] = rand();//criacao do vetor aleatorio com a mesma dimensao que o vetor deck_n
    }
  for (m= 0; m<=dim ;m++){
    for (k=1; k<dim; k++)
	{
		//desta forma vemos se o elemento anterior e maior que o seguinte, se for trocamos de posicao
  	    if (r[k] > r[k+1]){
  		swap(r, k, k+1);
  		swap(v, k, k+1);//replica as trocas para o vector deck_n[] para deste modo baralhar, onde v[k] = v[k+1] e v[k+1]= v[k]
  		
  		//troca no vetor deck_c[] para deste modo quando
		//trocar de numero , a cor desse numero trocar de posicao
	    //e assim o numero trocado ficar com a mesma cor já 
	    //que está tem de permanecer inalterada.
  		swap(c,k,k+1);
	  }
  }
 }
}
/*
get_card
Assinatura: get_card: parâmetros --> int v[],int p1
Comentários: subrotina que vai buscar a ultima carta disponivel do baralho
e lhe atribui na posicao p1 de um vetor v[], diminuindo uma posição no baralho
para deste modo ir buscar a próxima carta.
*/
//subrotina para conseguir as cartas do jogador
get_card(int v[], int k){ 
	v[k] = deck_n[49-(k*2)];
}

//subrotina para conseguir as cartas do bot
//a unica alteracao é a primeira comecar no index 49 do deck_n e a do bot comecar no index 48
get_card2(int v[], int k){ 
	v[k] = deck_n[48-(k*2)];
}
/*
color
Assinatura: color: parâmetros --> int deck_n[],int index_c
Comentários: subrotina que atraves da posicao do numero no vetor deck_n[] consegue 
determinar a cor da carta a que esse numero pertence pois essa mesma posição
vai corresponder no vetor deck_c[].
A carta nº1 que é deck_n[2] por exemplo vai corresponder a carta deck_c[2] que é verde
*/
color(int deck_n[], int index_c)
{	
    /*1-VERDE
	  2-AZUL
	  3-AMARELO
	  4-VERMELHO
	  5-BRANCO*/
		switch(index_c)
		{
			case 1://cor de verde
				setColor(10,0);
				break;
			case 2://cor de azul
				setColor(11,0);
				break;	
			case 3://cor de amarelo
				setColor(6,0);
				break;
			case 4://cor de vermelho
				setColor(12,0);
				break;
			case 5://cor de branco
				setColor(15,0);
				break;		
		}
}
show_graph_elements()
{
	int  i,a,b,j;
	//define o lugar onde vao aparecer as pistas e vidas
			gotoxy(185,3);
			printf("TURNO: %d",turn);
			
	        gotoxy(185,1);
	        printf("VIDAS: ");
	        setColor(2,0);
	        printf("%d", life_tokens);
	        resetColor();
	        gotoxy(185,2);
	        printf("PISTAS DISPONÍVEIS: ");
	        setColor(9,0);
	        printf("%d", clue_tokens);
	        resetColor();
	        //mostra o baralho de compra
	        gotoxy(185,23);
	        setColor(14,0);
	        printf("** Baralho de Compra **");
	        resetColor();
	        
	        setColor(15,0);
	        showRectAt(190,26,11,11);
	        resetColor();
            gotoxy(195,31);
	        setColor(15,0);
            printf("%d",shop_deck);
	        resetColor();
	        
	        //mostra as pistas
	        gotoxy(185,43);
	        printf("** Pistas dadas **");
	        gotoxy(180,44);
	        printf("Pistas de Nº do BOT:");
	        gotoxy(180,45);
	        printf("Pistas de Cº do BOT:");
	        
	        for (i=0,a=0;i<5;a=a+2,i++)
			{
				gotoxy(200+a,44);
				setColor(10,0);
				printf("|%d|",cluep2_n[i]);
				gotoxy(200+a,45);
				printf("|%d|",cluep2_c[i]);
				resetColor();
			}
			
	        gotoxy(185,47);
	        printf("** Pistas dadas **");
	        gotoxy(180,48);
	        printf("Pistas de Nº do JOGADOR:");
	        gotoxy(180,49);
	        printf("Pistas de Cº do JOGADOR:");
	        
	        for (i=0,a=0;i<5;a=a+2,i++)
			{
				gotoxy(205+a,48);
				setColor(10,0);
				printf("|%d|",cluep1_n[i]);
				gotoxy(205+a,49);
				printf("|%d|",cluep1_c[i]);
				resetColor();
			}
			
			//retangulo ao pe do baralho
		    setColor(15,0);
			showRectAt(157,58,1,5);
			resetColor();
}
/*
print_hand
Assinatura: print_hand: parâmetros --> int jog,int bot
Comentários: subrotina que imprime as cartas na interface, possui
um parametro para saber se é bot, se for bot mostra as cartas com 
numero e cor caso seja jog nao mostrar nem cor nem numero.
*/
print_hand(void)
{
	
	int i,space,index;
	
		//uso da variavel space para espaçamento entre as cartas		
		for (i=0,space=0,index=49; i<5; i++, index = index - 2, space = space +13)
		{
		  // hand_player1 || JOGADOR
		   gotoxy(113,45);
		   setColor(15,0);
		   printf("Cartas do %s ", name);
		   showRectAt(90+space,47,11,11);	
		}
		//uso da varivel index, onde a cada loop diminui 2 pois 
		//quando são dadas as cartas cada jogar recebe uma de cada 
		//vez deste modo para a carta do bot estar correcta tenho de subtrair 2.
		for (i=0,space=0, index=48; i<5; i++, index= index-2, space = space +13)
		{
		//hand_player2 || BOT
		   gotoxy(110,5);
		   printf("** Cartas do BOT **");
		   color(deck_c, deck_c[index]);
		   showRectAt(90+space,8,11,11);
		   resetColor();
		   gotoxy(95+space,13);
	       setColor(15,0);
	       printf("%d",hand_player2[i]);
	       resetColor();
		}
		
}

/*
show_discard
Assinatura: show_discard: parâmetros --> int row,int col,int matrix[row][col]
Comentários: subrotina que mostra a tabela de cartas descartadas ao longo do
jogo, atualizando os valores em tempo real
*/
show_discard(int row, int col, int matrix[row][col])
{
	int i,j,a,b;
	
	gotoxy(10,23);	
	printf("   **Tabela de Cartas Descartadas**\n\n");
	printf("\t\t      1   2   3   4   5   \n\n");
	setColor(10,0);
	printf("\t VERDE\n\n");
	resetColor();
	setColor(11,0);
	printf("\t AZUL\n\n");
	resetColor();
	setColor(6,0);
	printf("\t AMARELO\n\n");
	resetColor();
	setColor(12,0);
	printf("\t VERMELHO \n\n");
	resetColor();
	setColor(15,0);
	printf("\t BRANCO\n\n");
	resetColor();
	
	//criação dos da matriz de numeros descartados
	//sendo a variavel a e b usadas para espaçamento 
	//entre os zeros.
	for (i=0, b=0; i<row; i++,b=b+2)
	{
		for (j=0,a=0; j<col ;j++,a =a+4)
		{
			gotoxy(22+a,27+b);
			printf("%d",matrix[i][j]);
		}
		printf("\n");
	}
	
}
//subrotina que da a pista de uma cor das cartas ou numero
give_clue(int hand_player[],int deck_c[],int deck_n[],int index,int clue_n[],int clue_c[])
{
	
	int cor_index;//posicao da cor da carta que damos a pista
	int cont_n=0;//variavel para contar nº de cartas que estao de acordo com determinado if
	
	int cor,num;//1-verde/azul/amarelo/vermelho/ branco
	char clue;
	int i,space,cont_2=0;
	int return_value2=0;//variavel que fica com o valor de retorno da funcao playable_card2
	
	/*Quando é a vez do humano*/
	if (turn % 2 == 1)
	{
		setColor(15,0);
	    showRectAt(0,0,75,7);
		resetColor();
			
		gotoxy(1,1);
		printf("Deseja dar a pista de uma cor(c) ou numero(n): ");
		clue = getch();
	}
	/*Quando é a vez do BOT*/
    else
	{	
		gotoxy(1,2);
		setColor(14,0);
		printf("O BOT esta a analisar se existem cartas jogáveis!");
		resetColor();
		
		return_value2 = playable_card2(deck_n,deck_c);
		
		if (return_value2==999)
		{
			/*- Se nao houver cartas jogaveis dar pista sobre
			um número, escolher o mais baixo ainda não identificado. Se todos os
			números estão identificados, dar uma pista sobre uma cor aleatoriamente
			escolhida (que ainda não tenha sido dada). */
			
			gotoxy(2,3);
			printf("O jogador nao possui uma carta jogavel!");	
			
			/*Começamos por verificar do nº mais pequeno ou seja do 1
			até ao 5 se existem pistas dadas desses numeros caso nao exista
			o primeiro a verificar isso vai ser dada uma pista*/
			if(clue_n[0]==0)
			{
				clue = 'n';
			}
			else if(clue_n[1]==0)
			{
				clue = 'n';
			}
			else if(clue_n[2]==0)
			{
				clue = 'n';
			}
			else if(clue_n[3]==0)
			{
				clue = 'n';
			}
			else if(clue_n[4]==0)
			{
				clue = 'n';
			}
			else
			{
				clue = 'c';
			}
				
		}
		/*Se o valor de retorno for diferente de 999 quer dizer que existem cartas jogaveis.
		Os possiveis valores de retorno sao 0,1,2,3,4 (posicoes da carta jogavel no baralho)
		Para cada possivel valor de retorno temos de cobrir todos os possiveis cenarios
		em que essa posicao da carta jogavel é uma carta nº1,nº2,nº3,nº4 ou nº5
		Para cada uma delas temos de verificar se existe uma pista do nº dessa carta
		caso exista vamos dar a pista da sua cor para deste modo sabermos que cor se 
		trata e podermos ter a informação necessaria para joga-la de forma segura para a mesa.
		A unica situacao onde nao precisamos disso é quando a carta é um nº1 ,pois sendo um nº1 jogavel
		podemos so dar a pista dos nº 1.
		O mesmo fazemos para cada return value;
		*/
		else if(return_value2==0)
		{
			gotoxy(2,3);
			printf("O jogador possui uma carta jogavel! VR: %d",return_value2);
			/*Caso seja o nº1 a pista vai sempre ser dada em nº ja que nao importa a cor vai sempre dar certo*/
			if(hand_player[0]==1)
			{
				clue = 'n';
			}
			/*Nº2*/
			else if(hand_player[0]==2)
			{
				if(clue_n[1]==0)
				{
					clue = 'n';
				}
				/*Se ja existir a pista do Nº2 mas da cor ainda nao vamos dar a pista da cor*/
				else
				{
					clue = 'c';				
				}
			}
			/*Nº3*/
				else if(hand_player[0]==3)
			{
				if(clue_n[2]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº4*/
				else if(hand_player[0]==4)
			{
				if(clue_n[3]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº5*/
				else if(hand_player[0]==5)
			{
				if(clue_n[4]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}			
			
		}
		else if(return_value2==1)
		{
			gotoxy(2,3);
			printf("O jogador possui uma carta jogavel! VR: %d",return_value2);
			
				if(hand_player[1]==1)
				{
					clue = 'n';
				}
				/*Nº2*/
			else if(hand_player[1]==2)
			{
				if(clue_n[1]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº3*/
				else if(hand_player[1]==3)
			{
				if(clue_n[2]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº4*/
				else if(hand_player[1]==4)
			{
				if(clue_n[3]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº5*/
				else if(hand_player[1]==5)
			{
				if(clue_n[4]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}	
		}	
		else if(return_value2==2)
		{
			gotoxy(2,3);
			printf("O jogador possui uma carta jogavel! VR: %d",return_value2);
			
			if(hand_player[2]==1)
			{
				clue = 'n';
			}
			/*Nº2*/
			else if(hand_player[2]==2)
			{
				if(clue_n[1]==0)
				{
					clue = 'n';
				}
				else 
				{
					clue = 'c';				
				}
			}
			/*Nº3*/
				else if(hand_player[2]==3)
			{
				if(clue_n[2]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº4*/
				else if(hand_player[2]==4)
			{
				if(clue_n[3]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº5*/
				else if(hand_player[2]==5)
			{
				if(clue_n[4]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
		}	
		else if(return_value2==3)
		{
			gotoxy(2,3);
			printf("O jogador possui uma carta jogavel!%d",return_value2);
			
			if(hand_player[3]==1)
			{
				clue = 'n';
			}
			/*Nº2*/
			else if(hand_player[3]==2)
			{
				if(clue_n[1]==0)
				{
					clue = 'n';
				}
				else 
				{
					clue = 'c';				
				}
			}
			/*Nº3*/
				else if(hand_player[3]==3)
			{
				if(clue_n[2]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº4*/
				else if(hand_player[3]==4)
			{
				if(clue_n[3]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº5*/
				else if(hand_player[3]==5)
			{
				if(clue_n[4]==0)
				{
					clue = 'n';
				}
				else 
				{
					clue = 'c';				
				}
			}
		}	
		else if(return_value2==4)
		{
			gotoxy(2,3);
			printf("O jogador possui uma carta jogavel! VR: %d",return_value2);
			if(hand_player[4]==1)
			{
				clue = 'n';
			}
			/*Nº2*/
			else if(hand_player[4]==2)
			{
				if(clue_n[1]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº3*/
				else if(hand_player[4]==3)
			{
				if(clue_n[2]==0)
				{
					clue = 'n';
				}
				else 
				{
					clue = 'c';				
				}
			}
			/*Nº4*/
				else if(hand_player[4]==4)
			{
				if(clue_n[3]==0)
				{
					clue = 'n';
				}
				else
				{
					clue = 'c';				
				}
			}
			/*Nº5*/
				else if(hand_player[4]==5)
			{
				if(clue_n[4]==0)
				{
					clue = 'n';
				}
				else 
				{
					clue = 'c';	
								
				}
			}
		}				
 	}		
	
		switch(clue)
		{
		//opcao para dar pista da cor das cartas
		case 'c':
			case 'C':
				
			/*Se for a vez do HUMANO*/	
			if(turn % 2 == 1)			
			{	
				gotoxy(2,2);
				printf("Cor que deseja dar 1-verde;2-azul;3-amarelo;4-vermelho;5-branco: ");
				scanf("%d",&cor);	
			}
			/*VEZ DO BOT*/
			else
			{
					gotoxy(1,4);
					setColor(14,0);
					printf("O BOT vai dar pista de uma COR!");
					resetColor();
					
				/*SE CHEGAR AQUI É PORQUE O VETOR DAS PISTAS DOS NUMEROS
				 ESTAVA CHEIO E NAO FOI POSSIVEL DAR A PISTA DE NENHUM NUMERO
				 SENAO EXECUTA SEMPRE O CODIGO EM BAIXO NO ELSE*/	
				if(return_value2==999)
				{
					/*Se todos os
					números estão identificados, dar uma pista sobre a primeira cor
					(que ainda não tenha sido dada).*/
					if(clue_c[0]==0)
					{
						cor=1;
					}
					else if(clue_c[1]==0)
					{
						cor=2;
					}
					else if(clue_c[2]==0)
					{
						cor=3;
					}
					else if(clue_c[3]==0)
					{
						cor=4;
					}
					else if(clue_c[4]==0)
					{
						cor=5;
					}
				}
				/* se existe cartas jogaveis vai dar a pista
				da cor da carta que tem a pista do nº e so falta a cor*/
				else
				{
					/*VERDE*/
					if(deck_c[49-(return_value2*2)]==1)
					{
						cor=1;
					}
					//*AZUL*/
					else if(deck_c[49-(return_value2*2)]==2)
					{
						cor=2;
					}
					/*AMARELO*/
					else if(deck_c[49-(return_value2*2)]==3)
					{
						cor=3;
					}					
					/*VERMELHO*/
					else if(deck_c[49-(return_value2*2)]==4)
					{
						cor=4;
					}
					
					/*BRANCO*/
					else if(deck_c[49-(return_value2*2)]==5)
					{
						cor=5;
					}
				}	
					
			}					
				switch(cor)
				{	
			    //quando a cor é verde
				case 1:
						//fazer o programa percorrer as cartas do bot e ver se alguma carta tem cor verde
						for (i=0,space=0,index; i<5; space=space+13,index = index -2,i++)
						{
							//percorrer o vetor do hand_player2 para saber se alguma carta é verde e a pista e valida
							if (deck_c[index] == 1 )
							{
								/*Se ocorrer no turno jogador, as pistas sao para bot, ou seja,
								vai ser mostrado em cima das cartas quais sao as verdes. 
								Se for no Turno do BOT vai aparecer em cima das cartas do HUMANO*/
								if (turn % 2 == 1)
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(90+space,7);
								   	printf("CARTA VERDE");
								   	resetColor();
								}
								//se for no turno do bot vai aparecer na mao do jogador
								else
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(90+space,46);
								   	printf("CARTA VERDE");
								   	resetColor();
								}
							}						
						}
						/*Se o nº de cartas verdes nao forem zero, ou seja
						existem cartas verdes vamos atribuir o valor um no vector de pistas 
						do jogador em questao se for o bot a jogar vai ser o vector de pistas do humano e vice-versa.
						EX: BOT da pista carta VERDE --> cluep1_c[0]=1 */
						if (cont_n > 0)
						{
							clue_c[0]=1;
							gotoxy(2,5);
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas verdes = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
						
							 getch();
							 save_game();
							 Turn();
						}
						/*Caso nao existam cartas verdes perde na mesma uma pista mas o vector continua
						a zero pois nao faria sentido colocar a 1 se nao possui nenhuma carta verde*/
						else 
						{
							clue_c[0]=0;
							gotoxy(2,5);
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas verdes = %d",cont_n);
							resetColor();
							clue_tokens--;
							/*No fim do turno de cada jogador adicionamos mais 1 valor a variavel turn para
							que assim seja o outro jogador a jogar pois sabemos se for par e adicionarmos
							1 vai ser impar e vice-versa*/
							turn++;
						
							getch();
							save_game();
							Turn();
						}						
				//quando a cor é azul	
				case 2:
						//fazer o programa percorrer as cartas do bot e ver se alguma carta tem cor verde
						for (i=0,space=0,index; i<5; space=space+13,index = index-2,i++)
						{
							//percorrer o vetor do hand_player2 para saber se alguma carta é verde e a pista e valida
							if (deck_c[index] == 2 )
							{
								if (turn % 2 == 1)
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(90+space,7);
								   	printf("CARTA AZUL");
								   	resetColor();
								}
								//se for no turno do bot vai aparecer na mao do jogador
								else
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(90+space,46);
								   	printf("CARTA AZUL");
								   	resetColor();
								}
							}								
						}
						if (cont_n > 0)
						{
							clue_c[1]=1;
							gotoxy(2,5);
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas azuis = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
						
							 getch();
							 save_game();
							 Turn();
						}
						else 
						{
							clue_c[1]=0;
							gotoxy(2,5);
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas azuis = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
						
							getch();
							save_game();
							Turn();
						}										
				//quando a cor é amarelo
				case 3:	
						//fazer o programa percorrer as cartas do bot e ver se alguma carta tem cor verde
						for (i=0,space=0,index; i<5; space=space+13,index = index -2,i++)
						{
							//percorrer o vetor do hand_player2 para saber se alguma carta é verde e a pista e valida
							if (deck_c[index] == 3 )
							{
								if (turn % 2 == 1)
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(90+space,7);
								   	printf("CARTA AMAR");
								   	resetColor();
								}
								//se for no turno do bot vai aparecer na mao do jogador
								else
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(90+space,46);
								   	printf("CARTA AMAR");
								   	resetColor();
								}
							}
						}
						
						if (cont_n > 0)
						{
							clue_c[2]=1;
							gotoxy(2,5);
				
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas amarelas = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
						
							 getch();
							 save_game();
							 Turn();
						}
						else 
						{
							clue_c[2]=0;
							gotoxy(2,5);
				
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas amarelas = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
						
							getch();
							save_game();
							Turn();
						}									
				//quando a cor é vermelho	
				case 4:
						//fazer o programa percorrer as cartas do bot e ver se alguma carta tem cor verde
						for (i=0,space=0, index; i<5; space=space+13,index = index -2,i++)
						{
							//percorrer o vetor do hand_player2 para saber se alguma carta é verde e a pista e valida
							if (deck_c[index] == 4 )
							{
								if (turn % 2 == 1)
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(90+space,7);
								   	printf("CARTA VERMEL");
								   	resetColor();
								}
								//se for no turno do bot vai aparecer na mao do jogador
								else
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(90+space,46);
								   	printf("CARTA VERMEL");
								   	resetColor();
								}
						    }
						}
						if (cont_n > 0)
						{
							clue_c[3]=1;
							gotoxy(2,5);
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas vermelhas = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
						
							 getch();
							 save_game();
							 Turn();
						}
						else 
						{
							clue_c[3]=0;
							gotoxy(2,5);
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas vermelhas = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
						
							 getch();
							 Turn();
						}
				//quando a cor é branco	
				case 5:	
						//fazer o programa percorrer as cartas do bot e ver se alguma carta tem cor verde
						for (i=0,space=0,index; i<5; space=space+13,index = index -2,i++)
						{
							//percorrer o vetor do hand_player2 para saber se alguma carta é verde e a pista e valida
							if (deck_c[index] == 5 )
							{
								if (turn % 2 == 1)
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(90+space,7);
								   	printf("CARTA BRANCA");
								   	resetColor();
								}
								//se for no turno do bot vai aparecer na mao do jogador
								else
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(90+space,46);
								   	printf("CARTA BRANCA");
								   	resetColor();
								}
							}								
						}
						if (cont_n > 0)
						{
							clue_c[4]=1;
							gotoxy(2,5);
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas brancas = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
						
							getch();
							save_game();
							Turn();
						}
						else 
						{
							clue_c[4]=0;
							gotoxy(2,5);
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" ->Nº cartas brancas = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
						
							getch();
							save_game();
							Turn();
						}
						
	}
		    
		//opcao para dar pista do numero
		case 'n':
			case 'N':
				if (turn % 2 == 1)
				{
					gotoxy(2,2);
					setColor(12,0);
					printf("Numero");
					resetColor();
					printf(" que deseja dar como pista (1,2,3,4,5): ");
					scanf("%d",&num);
				}
				else 
				{
					
					gotoxy(1,4);
					setColor(14,0);
					printf("O BOT vai dar pista de um Nº!");
					resetColor();
					
					if(return_value2==999)
					{
						/*Caso nao exista cartas jogaveis dar uma pista
						do numero mais baixo que ainda nao foi dado pista*/
						if(clue_n[0]==0)
						{
							num = 1;
						}
						else if(clue_n[1]==0)
						{
							num =2;
						}
						else if(clue_n[2]==0)
						{
							num =3;
						}
						else if(clue_n[3]==0)
						{
							num =4;
						}
						else if(clue_n[4]==0)
						{
							num =5;
						}
					}
					else
					{
						if(hand_player[return_value2]==1)
						{
							num=1;
						}
						/*CARTAS Nº2*/
						else if(hand_player[return_value2]==2)
						{
							num=2;
						}
						/*CARTAS Nº3*/
						else if(hand_player[return_value2]==3)
						{
							num=3;
						}					
						/*CARTAS Nº4*/
						else if(hand_player[return_value2]==4)
						{
							num=4;
						}
						
						/*CARTAS Nº5*/
						else if(hand_player[return_value2]==5)
						{
							num=5;
						}
					}	
					
				}				
				switch(num)
				{
			    //quando o numero é 1
				case 1:
						//fazer o programa percorrer as cartas do bot e ver se alguma carta tem o numero 1
						for (i=0,space=0, index; i<5; space= space + 13,index = index -2,i++)
						{
							//percorrer o vetor do hand_player2 para saber se alguma carta tem o numero 1 e é valida
							if (deck_n[index] == 1 )
							{
								if (turn % 2 == 1)
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(91+space,7);
								   	printf("CARTA Nº1");
								   	resetColor();
								}
								//se for no turno do bot vai aparecer na mao do jogador
								else
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(91+space,46);
								   	printf("CARTA Nº1");
								   	resetColor();
								}
							}	
						}
						if (cont_n > 0)
						{
							clue_n[0]=1;
							gotoxy(2,5);	
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas nº1 = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
							getch();
							save_game();
							Turn();
						}
						else 
						{
							clue_n[0]=0;
							gotoxy(2,5);			
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas nº1 = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
							getch();
							save_game();
							Turn();
						}
			//	quando o numero é 2	
				case 2:
						    //fazer o programa percorrer as cartas do bot e ver se alguma carta tem o numero 2
						for (i=0,space=0, index; i<5; space= space + 13 ,index = index -2,i++)
						{
							//percorrer o vetor do hand_player2 para saber se alguma carta tem o numero 2 e é valida
							if (deck_n[index] == 2 )
							{
								if (turn % 2 == 1)
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(91+space,7);
								   	printf("CARTA Nº2");
								   	resetColor();
								}
								//se for no turno do bot vai aparecer na mao do jogador
								else
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(91+space,46);
								   	printf("CARTA Nº2");
								   	resetColor();
								}
							}	
						}
						if (cont_n > 0)
						{
							clue_n[1]=1;
							gotoxy(2,5);
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas nº2 = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
							getch();
							save_game();
							Turn();
						}
						else 
						{
							clue_n[1]=0;
							gotoxy(2,5);
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas nº2 = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
							getch();
							save_game();
							Turn();
						}
			//	quando o numero é 3	
				case 3:
						    //fazer o programa percorrer as cartas do bot e ver se alguma carta tem o numero 3
						for (i=0,space=0, index; i<5; space= space +13,index = index -2,i++)
						{
							//percorrer o vetor do hand_player2 para saber se alguma carta tem o numero 3 e é valida
							if (deck_n[index] == 3 )
							{
								if (turn % 2 == 1)
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(91+space,7);
								   	printf("CARTA Nº3");
								   	resetColor();
								}
								//se for no turno do bot vai aparecer na mao do jogador
								else
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(91+space,46);
								   	printf("CARTA Nº3");
								   	resetColor();
								}
							}
						}
						
						if (cont_n > 0)
						{
							clue_n[2]=1;
							gotoxy(2,5);
				
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas nº3 = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
							getch();
							save_game();
							Turn();
						}
						else 
						{
							clue_n[2]=0;
							gotoxy(2,5);
				
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas nº3 = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
							getch();
							save_game();
							Turn();
						}
			//	quando o numero é 4	
				case 4:
					    //fazer o programa percorrer as cartas do bot e ver se alguma carta tem o numero 1
						for (i=0,space=0, index; i<5; space= space + 13,index = index -2,i++)
						{
							//percorrer o vetor do hand_player2 para saber se alguma carta tem o numero 1 e é valida
							if (deck_n[index] == 4 )
							{
								if (turn % 2 == 1)
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(91+space,7);
								   	printf("CARTA Nº4");
								   	resetColor();
								}
								//se for no turno do bot vai aparecer na mao do jogador
								else
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(91+space,46);
								   	printf("CARTA Nº4");
								   	resetColor();
								}
							}
						}
						if (cont_n > 0)
						{
							clue_n[3]=1;
							gotoxy(2,5);
				
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas nº4 = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
							getch();
							save_game();
							Turn();
						}
						else 
						{
							clue_n[3]=0;
							gotoxy(2,5);
				
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas nº4 = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
							getch();
							save_game();
							Turn();
						}
				
			//	quando o numero é 5	
				case 5:	
				           //fazer o programa percorrer as cartas do bot e ver se alguma carta tem o numero 5
						for (i=0,space=0, index; i<5; space= space + 13,index = index -2,i++)
						{
							//percorrer o vetor do hand_player2 para saber se alguma carta tem o numero 5 e é valida
							if (deck_n[index] == 5 )
							{
								if (turn % 2 == 1)
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(91+space,7);
								   	printf("CARTA Nº5");
								   	resetColor();
								}
								//se for no turno do bot vai aparecer na mao do jogador
								else
								{
									cont_n++;
									setColor(5,0);
								   	gotoxy(91+space,46);
								   	printf("CARTA Nº5");
								   	resetColor();
								}
							}	
						}
						if (cont_n > 0)
						{
							clue_n[4]=1;
							gotoxy(2,5);				
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas nº5 = %d",cont_n);
							resetColor();
							clue_tokens--;
							turn++;
							getch();
							save_game();
							Turn();	
						}
						else 
						{
							clue_n[4]=0;
							gotoxy(2,5);				
							setColor(10,0);
							printf("A pista foi dada com sucesso!\n");
							printf(" -> Nº cartas nº5 = %d",cont_n);
							resetColor();
							clue_tokens--;	
							turn++;
							getch();
							save_game();
							Turn();
						}

	  }	
  }
}
print_table(int row, int col, int matrix[row][col])
{
	int i,j,a,b,c,d;
	
	//criação dos da matriz onde as cartas vao ser jogadas
	//sendo a variavel a e b usadas para espaçamento 
	//entre os zeros.
	for (i=0, b=0; i<row-1; i++,b=b+2)
	{
		for (j=0,a=0,c=1; j<col ;j++,a =a+13,c++)
		{
			/*como a cada loop o c++ temos que inicialmente
			é 1 ou seja corresponde as cartas VERDES, depois
			de ter sido criada a coluna das cartas verdes
			recebe mais 1 que corresponde as cartas azuis e assim sucessivamente*/				
			color(matrix,c);
			showRectAt(90+a,22+b,11,2);
			resetColor();
			gotoxy(95+a,23+b);
			setColor(15,0);
			printf("%d",matrix[i][j]);
			resetColor();
		}
    }
    /*Criacao das ultimas 5 cartas que correspondem aos nº5*/
    for (d=0,c=1,a=0;d<5;a=a+13,c++,d++)
	{
		color(matrix,c);
	    showRectAt(90+a,30,11,11);
	    resetColor();
	    gotoxy(95+a,35);
	    setColor(15,0);
	    printf("%d",matrix[4][d]);
	    resetColor();
	}
	

}

play_card(int hand_player[], int deck_c[], int deck_n[],int index)
{
	int index_deck;//posicao da carta que queremos que seja jogada
	int num,j,space;
	int return_value;/*variavel que guarda o valor retornado da funcao playable_card*/
	
	/*VEZ DO HUMANO*/
	if (turn % 2 == 1)
	{
		setColor(15,0);
	    showRectAt(0,0,75,7);
		resetColor();
			
		gotoxy(1,1);
		printf("Qual a posição da carta que deseja jogar?(1,2,3,4,5) ");
		scanf("%d",&index_deck);
		
		/*é necessario subtrair um valor pois os valores
		dos vectores começam do 0 ate ao 4 logo se escolhermos a posicao 1
		vai corresponder a posicao 0 no vector do hand_player ou seja primeira carta*/
		index_deck = index_deck - 1;
		num = hand_player[index_deck];
	} 
	/*VEZ DO BOT*/
	else 
	{
		setColor(15,0);
	    showRectAt(0,0,75,7);
		resetColor();
		gotoxy(1,1);
		printf("É a vez do bot!!");
		
		/*se o bot tiver uma pista de que tem uma carta nº1 vai joga-la*/
		if (cluep2_n[0] == 1)
		{
			for (index_deck=0;index_deck<5;index_deck++)
			{
				/*A primeira carta nº1 que ele encontrar
				na sua mao vai tomar o valor num e sair automaticamente
				do ciclo para joga-la*/
				if(deck_n[index-(index_deck*2)] == 1)
				{
					num = hand_player[index_deck];
					break;
				}				
			}
		}
		/*O bot vai jogar uma carta jogavel*/
		else
		{		
			setColor(15,0);
		    showRectAt(0,0,75,7);
			resetColor();
			//Esta subrotina devolve um valor de 0 a 4 que é a posição da carta jogavel no baralho do bot
			return_value = playable_card(deck_n,deck_c);			 
			 gotoxy(1,8);
			 printf("Valor de retorno: %d",return_value);
			 
			 index_deck = return_value;
			 
			 /*Se return_value for diferente de 999 significa isto que existe uma carta jogavel.
			 A funcao devolve a posicao da carta jogável(0,1,2,3,4), depois disso atribuimos o n dessa carta a num e
			 jogamos essa carta na mesa*/
			 if (return_value == 0)
			 {
			 	num = hand_player[0];
			 } 
			 else if(return_value ==1)
			 {
			 	num = hand_player[1];
			 }
			 else if(return_value ==2)
			 {
			 	num = hand_player[2];
			 }
			 else if(return_value ==3)
			 {
			 	num = hand_player[3];
			 }
			 else if(return_value ==4)
			 {
			 	num = hand_player[4];
			 }
			 /*Se o BOT nao possuir cartas jogáveis vai
			 fazer o seguinte:*/
			 else if(return_value == 999)
			 {
                /*Se existirem pistas o BOT vai dar uma pista ao humano*/
                if (clue_tokens > 0)
				{
					give_clue(hand_player1,deck_c,deck_n,49,cluep1_n,cluep1_c);
				}		
				//se nao existirem pistas vai descartar uma carta
				else
				{
					discard_card(hand_player2,deck_c,deck_n,48);
				}
			 }	 
		}	
	}
 /*O nº da carta que vai ser jogado*/
    switch(num)
	{
				/*Existem 5 cenários possiveis a carta ser nº1,nº2,nº3,nº4 ou nº5 sendo todos similares em termos de código
				Se for para ser jogada uma carta nº1 temos de verificar que cor é essa carta para sabermos onde vamos colocar na mesa.
				Existem 5 opçôes ser verde,azul,amarela,vermelha ou branca sendo todas iguais em termos de código.
				Imaginemos que a carta nº1 é verde temos de verificar que na mesa já foi jogada alguma carta nº1 verde(table[0][0]) caso seja igual a zero
				ou seja ainda nao foi jogada entao estao reunidas as condicoes para podermos joga-la.
				Se for nº2,nº3,nº4 ou nº5 essas condicoes aumentam pq temos de verificar por exemplo quando é nº5 verde, que o nº1 verde,nº2 verde,nº3 verde
				e nº4 verde ja foram jogados. */
				case 1:
			            //se a entrada estiver livre, ou seja 0, e a carta a ser jogada for de cor verde entao tem as condicoes necessarios para o seguinte
			 			if (table[0][0] == 0 && deck_c[index-(index_deck*2)] == 1)// mesmo que ter deck_c[49-(posicao da carta a jogar*2))
						{		   
						
							//o valor da mesa da primeira entrada e primeira coluna ou seja a carta nº1 de cor verde fica igual a 1, sabendo assim que a carta nº1 verde ja foi jogada									   
							table[0][0]=1;
					        
						   	gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(10,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							
							/*Nestes dois swaps trocamos a posica da carta que foi jogada
							com a carta do baralho (shop_deck) que neste caso sao as 40
							cartas restantes do baralho , cada vez que fazemos este swap o
							valor do shop_deck diminui um para deste modo nao haver repeticao
							comecando com o valor 40*/						
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							
							//a posicao da carta que foi jogada na mao do jogador é substituida pela carta
							//que foi trocada anteriormente no swap.
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        //recebe um ponto por a carta ter sido jogada com sucesso
					        points++;
					        //se o jogador jogar uma carta nº1 e tiver a pista de que possui uma carta nº1 é resetada a pista apos jogar a carta
					        //para que deste modo seja possivel que o bot de mais futuras pistas de cartas nº1
					        if(turn % 2 == 1 && cluep1_n[0]==1)
							{
								cluep1_n[0]=0;
							}
						   	break;
					}
						//cor azul
						else if (table[0][1] == 0 && deck_c[index-(index_deck*2)] == 2)
						{
						   table[0][1]=1;
		
		 				    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(11,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
												
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[0]==1)
							{
								cluep1_n[0]=0;
							}
						   break;
						}
						//cor amarelo
						else if (table[0][2] == 0 && deck_c[index-(index_deck*2)]== 3)
						{
						   table[0][2]=1;
		
		 				    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(6,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
											
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  						
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[0]==1)
							{
								cluep1_n[0]=0;
							}
							
						   break;
						}
						//vermelho 
						else if (table[0][3] == 0 && deck_c[index-(index_deck*2)]== 4)
						{
						   table[0][3]=1;
		
		 				    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(12,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  				
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[0]==1)
							{
								cluep1_n[0]=0;
							}
						   break;
						   
						}
						//branco
						else if (table[0][4] == 0 && deck_c[index-(index_deck*2)]== 5)
						{
						   table[0][4]=1;
		
		 				   gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(15,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
									
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[0]==1)
							{
								cluep1_n[0]=0;
							}
							
						   break;
						  }
						  //se a carta for mal jogada os jogadores perdem uma vida
						  //a carta jogada é descartada e é automaticamente dada uma
						  //nova carta do baralho
						else
						{
							gotoxy(2,2);
							setColor(4,0);
							printf("A carta que jogou é incorrecta: -1 vida");
							resetColor();
							gotoxy(2,3);
							printf("A carta Nº ");
							color(0,deck_c[index-(index_deck*2)]);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi descartada.",index_deck+1);
							resetColor();
							
							/*A carta que for inserida mal irá ser descartada para sabermos em que
							posicao da tabela de cartas descartas vai ficar temos de saber:
							*a cor que ela tem de 0 a 4(verde/azul/amarelo/vermelho/branco) para
							a primeira entrada da matriz que é as cores subtraindo 1 no fim.
							*o numero que essa carta possui para deste modo colocarmos na segunda entrada
							da matriz da tabela de cartas descartadas,como vai de 0 a 4 subtraimos o 1 no fim.
							*/
							discard_table[deck_c[index-(index_deck*2)]-1][hand_player[index_deck]-1]++;
							
							/*Aplicamos o swap como em cima para termos uma nova 
							carta do baralho */
							swap(deck_n,index-(index_deck*2),shop_deck-1);
						    swap(deck_c,index-(index_deck*2),shop_deck-1);
						    /*Atualizamos o valor da carta na mao do jogador*/
						    hand_player[index_deck] = deck_n[index-(index_deck*2)];
						    
						    shop_deck--;
						    life_tokens--;
							break;
						}	
						break;
				case 2:
					//se a entrada estiver livre, ou seja 0, e a carta a ser jogada for de cor verde entao tem as condicoes necessarios para o seguinte
			 			if (table[1][0] == 0 && deck_c[index-(index_deck*2)] == 1 && table[0][0] == 1)
						{		   									   
							table[1][0]=2;
											
							gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(10,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
											
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  					
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        if(turn % 2 == 1 && cluep1_n[1]==1 && cluep1_c[0]==1)
							{
								cluep1_n[1]=0;
								cluep1_c[0]=0;
							}
					   		break;
					}
						//cor azul
						else if (table[1][1] == 0 && deck_c[index-(index_deck*2)] == 2 && table[0][1] == 1)
						{
						   table[1][1]=2;
		
		 				    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(11,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
										
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[1]==1 && cluep1_c[1]==1)
							{
								cluep1_n[1]=0;
								cluep1_c[1]=0;
							}
						    break;
						}
						//cor amarelo
						else if (table[1][2] == 0 && deck_c[index-(index_deck*2)]== 3 && table[0][2] == 1)
						{
						   table[1][2]=2;
		
		 				    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(6,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
													
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);		
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        if(turn % 2 == 1 && cluep1_n[1]==1 && cluep1_c[2]==1)
							{
								cluep1_n[1]=0;
								cluep1_c[2]=0;
							}
						    break;
						}
						//vermelho 
						else if (table[1][3] == 0 && deck_c[index-(index_deck*2)]== 4 && table[0][3] == 1)
						{
						   table[1][3]=2;
		
		 				    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(12,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
													
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        if(turn % 2 == 1 && cluep1_n[1]==1 && cluep1_c[3]==1)
							{
								cluep1_n[1]=0;
								cluep1_c[3]=0;
							}
						    break;
						}
						//branco
						else if (table[1][4] == 0 && deck_c[index-(index_deck*2)]== 5 && table[0][4] == 1)
						{
						   table[1][4]=2;
		
		 				   gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(15,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        if(turn % 2 == 1 && cluep1_n[1]==1 && cluep1_c[4]==1)
							{
								cluep1_n[1]=0;
								cluep1_c[4]=0;
							}
						    break;
						}
						else
						{
							gotoxy(2,2);
							setColor(4,0);
							printf("A carta que jogou é incorrecta: -1 vida");
							resetColor();
							gotoxy(2,3);
							printf("A carta Nº ");
							color(0,deck_c[index-(index_deck*2)]);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi descartada.",index_deck+1);
							resetColor();
	
							discard_table[deck_c[index-(index_deck*2)]-1][hand_player[index_deck]-1]++;
							
							swap(deck_n,index-(index_deck*2),shop_deck-1);
						    swap(deck_c,index-(index_deck*2),shop_deck-1);
						    hand_player[index_deck] = deck_n[index-(index_deck*2)];
						    
						    shop_deck--;
						    life_tokens--;
							break;
						}
					break;
				case 3:
					//se a entrada estiver livre, ou seja 0, e a carta a ser jogada for de cor verde entao tem as condicoes necessarios para o seguinte
			 			if (table[2][0] == 0 && deck_c[index-(index_deck*2)] == 1 && table[0][0] == 1 && table[1][0] == 2 )
						{		   								   
						   table[2][0]=3;
						   					
						    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(10,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[2]==1 && cluep1_c[0]==1)
							{
								cluep1_n[2]=0;
								cluep1_c[0]=0;
							}
						   break;
						}
						//cor azul
						else if (table[2][1] == 0 && deck_c[index-(index_deck*2)] == 2 && table[0][1] == 1 && table[1][1] == 2)
						{
						   table[2][1]=3;
		
		 				    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(11,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
								
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					         if(turn % 2 == 1 && cluep1_n[2]==1 && cluep1_c[1]==1)
							{
								cluep1_n[2]=0;
								cluep1_c[1]=0;
							}
						   break;
						}
						//cor amarelo
						else if (table[2][2] == 0 && deck_c[index-(index_deck*2)]== 3 && table[0][2] == 1 && table[1][2]==2)
						{
						   table[2][2]=3;
		
		 				    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(6,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   			   
					        shop_deck--;
					        points++;
					        
					         if(turn % 2 == 1 && cluep1_n[2]==1 && cluep1_c[2]==1)
							{
								cluep1_n[2]=0;
								cluep1_c[2]=0;
							}
						   break;
						}
						//vermelho 
						else if (table[2][3] == 0 && deck_c[index-(index_deck*2)]== 4 && table[0][3] == 1 && table[1][3]==2)
						{
						   table[2][3]=3;
		
		 				    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(12,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
												
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					         if(turn % 2 == 1 && cluep1_n[2]==1 && cluep1_c[3]==1)
							{
								cluep1_n[2]=0;
								cluep1_c[3]=0;
							}
						   break;
						}
						//branco
						else if (table[2][4] == 0 && deck_c[index-(index_deck*2)]== 5 && table[0][4] == 1 && table[1][4]==2)
						{
							table[2][4]=3;
		
		 				   gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(15,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
											
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					         if(turn % 2 == 1 && cluep1_n[2]==1 && cluep1_c[4]==1)
							{
								cluep1_n[1]=0;
								cluep1_c[4]=0;
							}
						   break;
						}
						else
						{
							gotoxy(2,2);
							setColor(4,0);
							printf("A carta que jogou é incorrecta: -1 vida");
							resetColor();
							gotoxy(2,3);
							printf("A carta Nº ");
							color(0,deck_c[index-(index_deck*2)]);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi descartada.",index_deck+1);
							resetColor();
	
							discard_table[deck_c[index-(index_deck*2)]-1][hand_player[index_deck]-1]++;
							
							swap(deck_n,index-(index_deck*2),shop_deck-1);
						    swap(deck_c,index-(index_deck*2),shop_deck-1);
						    hand_player[index_deck] = deck_n[index-(index_deck*2)];
						    
						    shop_deck--;
						    life_tokens--;
							break;
						}
				    break;
				case 4:
				    //se a entrada estiver livre, ou seja 0, e a carta a ser jogada for de cor verde entao tem as condicoes necessarios para o seguinte
			 			if (table[3][0] == 0 && deck_c[index-(index_deck*2)] == 1 && table[0][0] == 1 && table[1][0] == 2 && table[2][0]==3)
						{		  
						 	table[3][0]=4;
							 								   
						    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(10,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							gotoxy(2,3);
							printf("NOTA: Falta mais 1 carta para completar a cor verde!");
													
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					       if(turn % 2 == 1 && cluep1_n[3]==1 && cluep1_c[0]==1)
							{
								cluep1_n[3]=0;
								cluep1_c[0]=0;
							}
						   break;
					}
						//cor azul
						else if (table[3][1] == 0 && deck_c[index-(index_deck*2)] == 2 && table[0][1] == 1 && table[1][1] == 2 && table[2][1]==3)
						{
						   table[3][1]=4;
		
		 				   gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(11,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							gotoxy(2,3);
							printf("NOTA: Falta mais 1 carta para completar a cor azul!");
													
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];				
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[3]==1 && cluep1_c[1]==1)
							{
								cluep1_n[3]=0;
								cluep1_c[1]=0;
							}
						   break;
						}
						//cor amarelo
						else if (table[3][2] == 0 && deck_c[index-(index_deck*2)]== 3 && table[0][2] == 1 && table[1][2]==2 && table[2][2]==3)
						{
					       table[3][2]=4;
		
		 				   gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(6,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							gotoxy(2,3);
							printf("NOTA: Falta mais 1 carta para completar a cor amarelo!");
												
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[3]==1 && cluep1_c[2]==1)
							{
								cluep1_n[3]=0;
								cluep1_c[2]=0;
							}
						   break;
						}
						//vermelho 
						else if (table[3][3] == 0 && deck_c[index-(index_deck*2)]== 4 && table[0][3] == 1 && table[1][3]==2 && table[2][3]==3 )
						{
						   table[3][3]=4;
		
		 				  gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(12,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							gotoxy(2,3);
							printf("NOTA: Falta mais 1 carta para completar a cor vermelho!");
							
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[3]==1 && cluep1_c[3]==1)
							{
								cluep1_n[3]=0;
								cluep1_c[3]=0;
							}
						   break;
						}
						//branco
						else if (table[3][4] == 0 && deck_c[index-(index_deck*2)]== 5 && table[0][4] == 1 && table[1][4]==2 && table[2][4]==3)
						{
						   table[3][4]=4;
		
			 			    gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(15,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							gotoxy(2,3);
							printf("NOTA: Falta mais 1 carta para completar a cor branco!");
												
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[3]==1 && cluep1_c[4]==1)
							{
								cluep1_n[3]=0;
								cluep1_c[4]=0;
							}
						   break;
						}
						else
						{
							gotoxy(2,2);
							setColor(4,0);
							printf("A carta que jogou é incorrecta: -1 vida");
							resetColor();
							gotoxy(2,3);
							printf("A carta Nº ");
							color(0,deck_c[index-(index_deck*2)]);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi descartada.",index_deck+1);
							resetColor();
	
							discard_table[deck_c[index-(index_deck*2)]-1][hand_player[index_deck]-1]++;
							
							swap(deck_n,index-(index_deck*2),shop_deck-1);
						    swap(deck_c,index-(index_deck*2),shop_deck-1);
						    hand_player[index_deck] = deck_n[index-(index_deck*2)];
						    
						    shop_deck--;
						    life_tokens--;
							break;
						}
				    break;
				case 5:
					//caso jogue uma carta nº5 com sucesso ganha uma pista o jogador
					//se a entrada estiver livre, ou seja 0, e a carta a ser jogada for de cor verde entao tem as condicoes necessarios para o seguinte
					//a carta 1 ,2 ,3 e 4 ja terem sido jogadas
			 			if (table[4][0] == 0 && deck_c[index-(index_deck*2)] == 1 && table[0][0] == 1 && table[1][0] == 2 && table[2][0]==3 && table[3][0]==4)
						{		   
									   
							table[4][0]=5;	
																
							gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(10,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							gotoxy(2,3);
							printf("NOTA: Foi-lhe atribuido +1 pista por ter jogado um 5!");
												
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[4]==1 && cluep1_c[0]==1)
							{
								cluep1_n[4]=0;
								cluep1_c[0]=0;
							}
						    break;
						}
						//cor azul
						else if (table[4][1] == 0 && deck_c[index-(index_deck*2)] == 2 && table[0][1] == 1 && table[1][1] == 2 && table[2][1]==3 && table[3][1]==4)
						{
							table[4][1]=5;
			
			 				gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(11,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							gotoxy(2,3);
							printf("NOTA: Foi-lhe atribuido +1 pista por ter jogado um 5!");
												
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[4]==1 && cluep1_c[1]==1)
							{
								cluep1_n[4]=0;
								cluep1_c[1]=0;
							}
						    break;
						}
						//cor amarelo
						else if (table[4][2] == 0 && deck_c[index-(index_deck*2)]== 3 && table[0][2] == 1 && table[1][2]==2 && table[2][2]==3 && table[3][2]==4)
							{
							table[4][2]=5;
			
			 				gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(6,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							gotoxy(2,3);
							printf("NOTA: Foi-lhe atribuido +1 pista por ter jogado um 5!");
												
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[4]==1 && cluep1_c[2]==1)
							{
								cluep1_n[4]=0;
								cluep1_c[2]=0;
							}
							
						    break;
						}
						//vermelho 
						else if (table[4][3] == 0 && deck_c[index-(index_deck*2)]== 4 && table[0][3] == 1 && table[1][3]==2 && table[2][3]==3 && table[3][3]==4 )
						{
							table[4][3]=5;
			
			 				gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(12,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							gotoxy(2,3);
							printf("NOTA: Foi-lhe atribuido +1 pista por ter jogado um 5!");
												
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[4]==1 && cluep1_c[3]==1)
							{
								cluep1_n[4]=0;
								cluep1_c[3]=0;
							}
						    break;
						}
						//branco
						//
						else if (table[4][4] == 0 && deck_c[index-(index_deck*2)]== 5 && table[0][4] == 1 && table[1][4]==2 && table[2][4]==3 && table[3][4]==4)
						{
						    table[4][4]=5;
		
			 				gotoxy(2,2);
						   	printf("A carta Nº ");
							setColor(15,0);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi jogada para a mesa!",index_deck+1);
							resetColor();
							gotoxy(2,3);
							printf("NOTA: Foi-lhe atribuido +1 pista por ter jogado um 5!");
												
							swap(deck_n,index-(index_deck*2),shop_deck-1);
							swap(deck_c,index-(index_deck*2),shop_deck-1);  							
							hand_player[index_deck] = deck_n[index-(index_deck*2)];									   
													   
					        shop_deck--;
					        points++;
					        
					        if(turn % 2 == 1 && cluep1_n[4]==1 && cluep1_c[4]==1)
							{
								cluep1_n[4]=0;
								cluep1_c[4]=0;
							}
							
						    break;

						}
						else
						{	
							gotoxy(2,2);
							setColor(4,0);
							printf("A carta que jogou é incorrecta: -1 vida");
							resetColor();
							gotoxy(2,3);
							printf("A carta Nº ");
							color(0,deck_c[index-(index_deck*2)]);
							printf("%d",hand_player[index_deck]);
							resetColor();
							printf(" na %dº posicao foi descartada.",index_deck+1);
							resetColor();
	
							discard_table[deck_c[index-(index_deck*2)]-1][hand_player[index_deck]-1]++;
							
							swap(deck_n,index-(index_deck*2),shop_deck-1);
						    swap(deck_c,index-(index_deck*2),shop_deck-1);
						    hand_player[index_deck] = deck_n[index-(index_deck*2)];
						    
						    shop_deck--;
						    life_tokens--;
							break;
						}								
	}
	
}

discard_card(int hand_player[],int deck_c[],int deck_n[],int index)
{
	int index_deck,i;
	
	/*VEZ DO HUMANO*/
	if (turn % 2 == 1)
	{
			setColor(15,0);
		    showRectAt(0,0,75,7);
			resetColor();
				
			gotoxy(1,1);
			printf("Qual a posição da carta que deseja descartar(1,2,3,4,5): ");
			scanf("%d",&index_deck);
	}
	/*VEZ DO BOT*/
	else 
	{
		setColor(15,0);
	    showRectAt(0,0,75,7);
		resetColor();
			
		gotoxy(1,2);
		setColor(8,0);
		printf("O bot vai descartar uma carta! ");
		resetColor();
		
		for(i=0;i<5;i++)
		{
			/*Neste Loop procuramos por nº de cartas que nao possuem
			pistas nem do nº e nem da cor para deste modo serem
			descartas.
			*/
			if(hand_player[i]==1)
			{
				//se nao existir pistas da carta nº1 e nem da cor dessa carta descarta essa carta
				if(cluep2_n[0]==0 && cluep2_c[deck_c[48-(i*2)]-1]==0)
				{
					index_deck = i;
					index_deck++;
				}
			}
			else if(hand_player[i]==2)
			{
				if(cluep2_n[1]==0 && cluep2_c[deck_c[48-(i*2)]-1]==0)
				{
					index_deck = i;
					index_deck++;
				}
			}
			else if(hand_player[i]==3 )
			{
				if(cluep2_n[2]==0 && cluep2_c[deck_c[48-(i*2)]-1]==0)
				{
					index_deck = i;
					index_deck++;
				}
			}
			else if(hand_player[i]==4 )
			{
				if(cluep2_n[3]==0 && cluep2_c[deck_c[48-(i*2)]-1]==0)
				{
					index_deck = i;
					index_deck++;
				}
			}
			else if(hand_player[i]==5 )
			{
				if(cluep2_n[4]==0 && cluep2_c[deck_c[48-(i*2)]-1]==0)
				{
					index_deck = i;
					index_deck++;
				}
			}
		}
		/*- caso não exista tal carta, descarta uma carta da qual só tem conhecimento
		do número, começando do mais pequeno para o maior			
		*/
		for(i=0;i<5;i++)
		{
			if(hand_player[i]==1)
			{
				/*Se existir a pista desse nº e nao existir da sua
				cor vai descartar essa carta*/
				if(cluep2_n[0]==1 && cluep2_c[deck_c[48-(i*2)]-1]==0)
				{
					index_deck=i;
					index_deck++;
				}
			}
			else if(hand_player[i]==2)
			{
				if(cluep2_n[1]==1 && cluep2_c[deck_c[48-(i*2)]-1]==0)
				{
					index_deck=i;
					index_deck++;
				}
			}
			else if(hand_player[i]==3)
			{
				if(cluep2_n[2]==1 && cluep2_c[deck_c[48-(i*2)]-1]==0)
				{
					index_deck=i;
					index_deck++;
				}
			}
			else if(hand_player[i]==4)
			{
				if(cluep2_n[3]==1 && cluep2_c[deck_c[48-(i*2)]-1]==0)
				{
					index_deck=i;
					index_deck++;
				}
			}
			else if(hand_player[i]==5)
			{
				if(cluep2_n[4]==1 && cluep2_c[deck_c[48-(i*2)]-1]==0)
				{
					index_deck=i;
					index_deck++;
				}
			}
		}
		/*- caso não exista tal carta, escolhe uma
		 carta das mais pequenas ate a maior
		tem uma só pista (cor ou número).*/
		for(i=0;i<5;i++)
		{
		/*Se a carta for Nº1 e possuir uma pista de nº1 ou uma pista da cor da sua carta vai ser descartada*/
			if(hand_player[i]== 1)
			{
				
				if(cluep2_n[0]==1 || cluep2_c[deck_c[48-(i*2)]-1]==1)
				{
					index_deck=i;
					index_deck++;
				}
			}
			else if(hand_player[i]== 2)
			{
				
				if(cluep2_n[1]==1 || cluep2_c[deck_c[48-(i*2)]-1]==1)
				{
					index_deck=i;
					index_deck++;
				}
			}
			else if(hand_player[i]== 3)
			{
				
				if(cluep2_n[2]==1 || cluep2_c[deck_c[48-(i*2)]-1]==1)
				{
					index_deck=i;
					index_deck++;
				}
			}
			else if(hand_player[i]== 4)
			{
				
				if(cluep2_n[3]==1 || cluep2_c[deck_c[48-(i*2)]-1]==1)
				{
					index_deck=i;
					index_deck++;
				}
			}else if(hand_player[i]== 5)
			{
				
				if(cluep2_n[4]==1 || cluep2_c[deck_c[48-(i*2)]-1]==1)
				{
					index_deck=i;
					index_deck++;
				}
			}
			
		}	
		
		/*- caso não exista tal carta, descarta uma carta aleatória.*/
		index_deck = 1+rand()%5;//gera numeros entre 1 e 5
	}
	
	
	switch(index_deck)
	{
		/*caso o jogador deseja descartar a primeira carta da sua mao
		vamos trocar a posicao da ultima carta do baralho shop deck 
		com a carta que queremos descartar ganhando assim o jogador +1 pista
		Sendo identico o codigo para as 5 nº possiveis.*/
		case 1:
			index_deck--; // pois no vector da mao começa com 0
			
			//condicao para sabermos a cor e numero da carta que vamos descartar
			//para atulizarmos na matriz de cartas descartadas!
			
			//quando a carta é verde
			if (deck_c[index-(index_deck*2)] == 1)
			{
				/*Se for verde sabemos que pertence á primeira
				linha da matriz , agora o valor da coluna ou seja o
				nº da carta descartada menos 1 vai corresponder ao nº 
				que foi descartado, uma vez que a matriz tambem começa com
				zero temos de subtrair 1*/
				discard_table[0][hand_player[index_deck]-1]++;
			}
			//azul
			else if (deck_c[index-(index_deck*2)] == 2)
			{
				discard_table[1][hand_player[index_deck]-1]++;
			}
			//amarelo
			else if (deck_c[index-(index_deck*2)] == 3)
			{
				discard_table[2][hand_player[index_deck]-1]++;
			}
			//vermelho
			else if (deck_c[index-(index_deck*2)] == 4)
			{
				discard_table[3][hand_player[index_deck]-1]++;
			}
			//branco
			else if (deck_c[index-(index_deck*2)] == 5)
			{
				
				
				discard_table[4][hand_player[index_deck]-1]++;
			}
			gotoxy(2,3);
			printf("A carta Nº ");
			/*Definimos a cor atraves da posicao da corta no vector das cores*/
			color(0,deck_c[index-(index_deck*2)]);
			printf("%d",hand_player[index_deck]);
			resetColor();
			printf(" na %dº posicao foi descartada.",index_deck+1);
			resetColor();
			/*Trocamos a carta descartada por uma do baralho de Compra*/
			swap(deck_n,index-(index_deck*2),shop_deck-1);
			swap(deck_c,index-(index_deck*2),shop_deck-1);	
			/*atualizamos o valor da carta na mao do jogador*/							   
			hand_player[index_deck] = deck_n[index-(index_deck*2)];
			
			shop_deck--;
			clue_tokens++; 	//o jogador recebe uma pista
			turn++;
						   
			getch();
			save_game();
			Turn();	 
			break;
			
		case 2:
			index_deck--;
			//verde
			if (deck_c[index-(index_deck*2)] == 1)
			{
				discard_table[0][hand_player[index_deck]-1]++;
			}
			//azul
			else if (deck_c[index-(index_deck*2)] == 2)
			{
				discard_table[1][hand_player[index_deck]-1]++;
			}
			//amarelo
			else if (deck_c[index-(index_deck*2)] == 3)
			{
				discard_table[2][hand_player[index_deck]-1]++;
			}
			//vermelho
			else if (deck_c[index-(index_deck*2)] == 4)
			{
				discard_table[3][hand_player[index_deck]-1]++;
			}
			//branco
			else if (deck_c[index-(index_deck*2)] == 5)
			{
				
				
				discard_table[4][hand_player[index_deck]-1]++;
			}
			gotoxy(2,3);
			printf("A carta Nº ");
			color(0,deck_c[index-(index_deck*2)]);
			printf("%d",hand_player[index_deck]);
			resetColor();
			printf(" na %dº posicao foi descartada.",index_deck+1);
			resetColor();
			
			swap(deck_n,index-(index_deck*2),shop_deck-1);
			swap(deck_c,index-(index_deck*2),shop_deck-1);								   
			hand_player[index_deck] = deck_n[index-(index_deck*2)];
			
			shop_deck--;
			clue_tokens++; 
			turn++;
						   
			getch();
			save_game();
			Turn();	 
			break;
		case 3:
			index_deck--;
			
			//condicao para sabermos a cor e numero da carta que vamos descartar
			//para atulizarmos na matriz de cartas descartadas!
			
			//quando a carta é verde
			if (deck_c[index-(index_deck*2)] == 1)
			{
				discard_table[0][hand_player[index_deck]-1]++;
			}
			//azul
			else if (deck_c[index-(index_deck*2)] == 2)
			{
				discard_table[1][hand_player[index_deck]-1]++;
			}
			//amarelo
			else if (deck_c[index-(index_deck*2)] == 3)
			{
				discard_table[2][hand_player[index_deck]-1]++;
			}
			//vermelho
			else if (deck_c[index-(index_deck*2)] == 4)
			{
				discard_table[3][hand_player[index_deck]-1]++;
			}
			//branco
			else if (deck_c[index-(index_deck*2)] == 5)
			{
				
				
				discard_table[4][hand_player[index_deck]-1]++;
			}
			gotoxy(2,3);
			printf("A carta Nº ");
			color(0,deck_c[index-(index_deck*2)]);
			printf("%d",hand_player[index_deck]);
			resetColor();
			printf(" na %dº posicao foi descartada.",index_deck+1);
			resetColor();
			
			swap(deck_n,index-(index_deck*2),shop_deck-1);
			swap(deck_c,index-(index_deck*2),shop_deck-1);								   
			hand_player[index_deck] = deck_n[index-(index_deck*2)];
			
			shop_deck--;
			clue_tokens++; 
			turn++;
						   
			getch();
			save_game();
			Turn();	
			break;
			 
		case 4:
			index_deck--;
			
			//condicao para sabermos a cor e numero da carta que vamos descartar
			//para atulizarmos na matriz de cartas descartadas!
			
			//quando a carta é verde
			if (deck_c[index-(index_deck*2)] == 1)
			{
				discard_table[0][hand_player[index_deck]-1]++;
			}
			//azul
			else if (deck_c[index-(index_deck*2)] == 2)
			{
				discard_table[1][hand_player[index_deck]-1]++;
			}
			//amarelo
			else if (deck_c[index-(index_deck*2)] == 3)
			{
				discard_table[2][hand_player[index_deck]-1]++;
			}
			//vermelho
			else if (deck_c[index-(index_deck*2)] == 4)
			{
				discard_table[3][hand_player[index_deck]-1]++;
			}
			//branco
			else if (deck_c[index-(index_deck*2)] == 5)
			{
				
				
				discard_table[4][hand_player[index_deck]-1]++;
			}
			gotoxy(2,3);
			printf("A carta Nº ");
			color(0,deck_c[index-(index_deck*2)]);
			printf("%d",hand_player[index_deck]);
			resetColor();
			printf(" na %dº posicao foi descartada.",index_deck+1);
			resetColor();
			
			swap(deck_n,index-(index_deck*2),shop_deck-1);
			swap(deck_c,index-(index_deck*2),shop_deck-1);								   
			hand_player[index_deck] = deck_n[index-(index_deck*2)];
			
			shop_deck--;
			clue_tokens++; 
		    turn++;
						   
			getch();
			save_game();
			Turn();	 
			break;
		case 5:
			index_deck--;
			
			//condicao para sabermos a cor e numero da carta que vamos descartar
			//para atulizarmos na matriz de cartas descartadas!
			
			//quando a carta é verde
			if (deck_c[index-(index_deck*2)] == 1)
			{
				discard_table[0][hand_player[index_deck]-1]++;
			}
			//azul
			else if (deck_c[index-(index_deck*2)] == 2)
			{
				discard_table[1][hand_player[index_deck]-1]++;
			}
			//amarelo
			else if (deck_c[index-(index_deck*2)] == 3)
			{
				discard_table[2][hand_player[index_deck]-1]++;
			}
			//vermelho
			else if (deck_c[index-(index_deck*2)] == 4)
			{
				discard_table[3][hand_player[index_deck]-1]++;
			}
			//branco
			else if (deck_c[index-(index_deck*2)] == 5)
			{
				
				
				discard_table[4][hand_player[index_deck]-1]++;
			}
			
			gotoxy(2,3);
			printf("A carta Nº ");
			color(0,deck_c[index-(index_deck*2)]);
			printf("%d",hand_player[index_deck]);
			resetColor();
			printf(" na %dº posicao foi descartada.",index_deck+1);
			resetColor();
			
			swap(deck_n,index-(index_deck*2),shop_deck-1);
			swap(deck_c,index-(index_deck*2),shop_deck-1);								   
			hand_player[index_deck] = deck_n[index-(index_deck*2)];
			
			shop_deck--;
			clue_tokens++; 
			turn++;
						   
			getch();
			save_game();
			Turn();
			break;	 	
	}
	
}

bot_algorithm(int hand_player1[],int hand_player2[],int deck_c[], int deck_n[],int cluep2_n[],int cluep2_c[])
{
	int space,k,cont=0,i,index=0;
	
	/*Se o BOT for sorteado para ser o primeiro jogador
	vai dar as pistas das cartas nº1 que existem no baralho
	do jogador.
	O seu funcionamento é igual á subrotina give_clue pesquisamos por
	cartas nº1 no vector se houver a variavel cont++ e no fim 
	mostramos quais as cartas nº1 que o jogador tem */
	if (random == 0)
	{
		for (space=0,k=0;k<5;space = space + 13,k++)
		{
			   	if (hand_player1[k] == 1)
				   {
				   	cont++;
				   	setColor(5,0);
				   	gotoxy(91+space,46);
				   	printf("CARTA Nº1");
				   	resetColor();
				   	
				   }
			   }
			   gotoxy(2,2);
			   setColor(14,0);
			   printf("PISTA BOT: Existem %d cartas com o nº1",cont);
			   resetColor();
			   clue_tokens--;
			   gotoxy(2,3);
			   setColor(9,0);
			   printf("PISTAS DISPONIVEIS: %d ",clue_tokens);
			   resetColor();
			   
			   
			   if(cont > 0)
			   {
			   	//para evitar futuras complicacoes colocamos o valor de random para 999 para nao repetir turnos	
        		random=999;
        		//vetor das pistas do jogador atualiza
			   	cluep1_n[0]=1;
			   	turn++;
				   
				getch();
				Turn();	   
			   }
			   else 
			   {
			   	//para evitar futuras complicacoes colocamos o valor de random para 2 para nao repetir turnos	
        		random=999;
			   	cluep1_n[0]=0;
			   	turn++;
				   
				getch();
				Turn();
			   }
			   
    }	
	/*Caso o BOT nao tenha sido o primeiro Jogador
	vai ser executado parte do algoritmo do bot*/
	else 
	{
		gotoxy(1,1);
		setColor(2,0);
		printf("É a vez do bot!");
		resetColor();
		
			//se o bot tiver uma pista dada pelo jogador que possui uma carta nº1
			//vai jogar essa carta, resetando o vetor das pistas para poder dar novamente uma pista	
			if (cluep2_n[0] == 1)
			{		
		     play_card(hand_player2,deck_c,deck_n,48);
		     
		     cluep2_n[0]=0;
		     turn++;
					   	
			 getch();
		     Turn();
			}
			/*Se nao haver pistas do numero 1 para ser jogadas diretamente vai executar
			a funcao playble_card para ver se existe alguma corta jogavel para o bot joga-la.
			Executando a subrotina play_card que é onde se encontra a funcao playable_card*/
			else 
			{
			 play_card(hand_player2,deck_c,deck_n,48);
			 turn++;
						   
			 getch();
		 	 Turn();
			}
			
 }
}

//FAZER UMA FUNCAO QUE JOGA CARTAS JOGAVEIS NO BARALHO DO BOT
int playable_card(int deck_n[],int deck_c[])
{
		//esta funcao retorna a posicao de 0 a 4 da carta jogavel
		//com menor numero (em casa de empate é o que esta mais á esquerda ou seja a primeira no vector) 
		//retorna 999 se nao hover cartas jogaveis
		int i;
		
		/*Se o bot possuir uma pista que tem o numero 2 no seu baralho e possuir a pista que tem a cor verde e se ainda nao tiver sido jogada nenhuma 
		2 verde mas ja tiver sido jogada 1 verde entao o bot vai devolver a posiçao dessa carta para ser jogada*/
		if(cluep2_n[1] == 1 && cluep2_c[0] == 1)
		{
			/*Se as condicoes acima se verificarem vai ser selecionada a primeira carta nº2 VERDE 
			que aparecer na mao do bot*/
			for (i=0;i<5;)
			{
				/*se existir uma carta Nª2 Verde no baralho do bot ele vai devolver
				a posicao onde essa carta esta para assim ser jogada na subrotina do playcard*/
				if(hand_player2[i]==2 && deck_c[48-(i*2)] == 1)
				{
					cluep2_n[1] = 0;
					cluep2_c[0] = 0;				
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		/*Se o bot possuir uma pista que tem o numero 3 no seu baralho e possuir a pista que tem a cor verde e se ainda nao tiver sido jogada nenhuma 
		3 verde mas ja tiver sido jogada 1 verde e 2 verde entao o bot vai devolver a posiçao dessa carta para ser jogada*/
		else if(cluep2_n[2] == 1 && cluep2_c[0] == 1)
		{
			/*Se as condicoes acima se verificarem vai ser selecionada a primeira carta nº3 VERDE 
			que aparecer na mao do bot*/
			for (i=0;i<5;)
			{
				/*se existir uma carta Nª3 Verde no baralho do bot ele vai devolver
				a posicao onde essa carta esta para assim ser jogada na subrotina do playcard*/
				if(hand_player2[i]==3 && deck_c[48-(i*2)] == 1)
				{
					cluep2_c[0] = 0;
					cluep2_n[2] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		/*Se o bot possuir uma pista que tem o numero 4 no seu baralho e possuir a pista que tem a cor verde e se ainda nao tiver sido jogada nenhuma 
		4 verde mas ja tiver sido jogada 1 verde,2 verde e 3 verde entao o bot vai devolver a posiçao dessa carta para ser jogada*/
		else if(cluep2_n[3] == 1 && cluep2_c[0] == 1)
		{
			/*Se as condicoes acima se verificarem vai ser selecionada a primeira carta nº4 VERDE 
			que aparecer na mao do bot*/
			for (i=0;i<5;)
			{
				/*se existir uma carta Nª4 Verde no baralho do bot ele vai devolver
				a posicao onde essa carta esta para assim ser jogada na subrotina do playcard*/
				if(hand_player2[i]==4 && deck_c[48-(i*2)] == 1)
				{
					cluep2_c[0] = 0;
					cluep2_n[3] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		/*Se o bot possuir uma pista que tem o numero 5 no seu baralho e possuir a pista que tem a cor verde e se ainda nao tiver sido jogada nenhuma 
		5 verde mas ja tiver sido jogada 1 verde,2 verde,3 verde e 4 verde entao o bot vai devolver a posiçao dessa carta para ser jogada*/
		else if(cluep2_n[4] == 1 && cluep2_c[0] == 1)
		{
			/*Se as condicoes acima se verificarem vai ser selecionada a primeira carta nº4 VERDE 
			que aparecer na mao do bot*/
			for (i=0;i<5;)
			{
				/*se existir uma carta Nª4 Verde no baralho do bot ele vai devolver
				a posicao onde essa carta esta para assim ser jogada na subrotina do playcard*/
				if(hand_player2[i]==5 && deck_c[48-(i*2)] == 1)
				{
					cluep2_c[0] = 0;
					cluep2_n[4] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		//*COR AZUL*
		/*Se o bot possuir uma pista que tem o numero 2 no seu baralho e possuir a pista que tem a cor azul e se ainda nao tiver sido jogada nenhuma 
		2 azul mas ja tiver sido jogada 1 azul entao o bot vai devolver a posiçao dessa carta para ser jogada*/
		else if(cluep2_n[1] == 1 && cluep2_c[1] == 1)
		{
			/*Se as condicoes acima se verificarem vai ser selecionada a primeira carta nº4 AZUL 
			que aparecer na mao do bot*/
			for (i=0;i<5;)
			{
				/*se existir uma carta Nª2 Verde no baralho do bot ele vai devolver
				a posicao onde essa carta esta para assim ser jogada na subrotina do playcard*/ //
				if(hand_player2[i]==2 && deck_c[48-(i*2)] == 2)
				{
					cluep2_n[1] = 0;
					cluep2_c[1] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[2] == 1 && cluep2_c[1] == 1)
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==3 && deck_c[48-(i*2)] == 2)
				{
					cluep2_n[2] = 0;
					cluep2_c[1] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[3] == 1 && cluep2_c[1] == 1)
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==4 && deck_c[48-(i*2)] == 2)
				{
					cluep2_n[3] = 0;
					cluep2_c[1] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[4] == 1 && cluep2_c[1] == 1)
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==5 && deck_c[48-(i*2)] == 2)
				{
					cluep2_n[4] = 0;
					cluep2_c[1] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		//*COR AMARELO*
		/*Se o bot possuir uma pista que tem o numero 2 no seu baralho e possuir a pista que tem a cor amarelo e se ainda nao tiver sido jogada nenhuma 
		2 amarelo mas ja tiver sido jogada 1 amarelo entao o bot vai devolver a posiçao dessa carta para ser jogada*/
		else if(cluep2_n[1] == 1 && cluep2_c[2] == 1)
		{
			/*Se as condicoes acima se verificarem vai ser selecionada a primeira carta nº2 Amarela 
			que aparecer na mao do bot*/
			for (i=0;i<5;)
			{
				/*se existir uma carta Nª2 Amarelo no baralho do bot ele vai devolver
				a posicao onde essa carta esta para assim ser jogada na subrotina do playcard*/ //
				if(hand_player2[i]==2 && deck_c[48-(i*2)] == 3)
				{
					cluep2_n[1]=0;
					cluep2_c[2] =0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[2] == 1 && cluep2_c[2] == 1)
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==3 && deck_c[48-(i*2)] == 3)
				{
					cluep2_n[2] = 0;
					cluep2_c[2] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[3] == 1 && cluep2_c[2] == 1 )
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==4 && deck_c[48-(i*2)] == 3)
				{
					cluep2_n[3] = 0;
					cluep2_c[2] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[4] == 1 && cluep2_c[2] == 1)
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==5 && deck_c[48-(i*2)] == 3)
				{
					cluep2_n[4] = 0;
					cluep2_c[2] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		//*COR VERMELHO*
		/*Se o bot possuir uma pista que tem o numero 2 no seu baralho e possuir a pista que tem a cor amarelo e se ainda nao tiver sido jogada nenhuma 
		2 amarelo mas ja tiver sido jogada 1 amarelo entao o bot vai devolver a posiçao dessa carta para ser jogada*/
		else if(cluep2_n[1] == 1 && cluep2_c[3] == 1)
		{
			/*Se as condicoes acima se verificarem vai ser selecionada a primeira carta nº2 Amarela 
			que aparecer na mao do bot*/
			for (i=0;i<5;)
			{
				/*se existir uma carta Nª2 Amarelo no baralho do bot ele vai devolver
				a posicao onde essa carta esta para assim ser jogada na subrotina do playcard*/ //
				if(hand_player2[i]==2 && deck_c[48-(i*2)] == 4)
				{
					cluep2_n[1] = 0;
					cluep2_c[3] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[2] == 1 && cluep2_c[3] == 1 )
		{
			for (i=0;i<5;i++)
			{
				if(hand_player2[i]==3 && deck_c[48-(i*2)] == 4)
				{
					cluep2_n[2] = 0;
					cluep2_c[3] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[3] == 1 && cluep2_c[3] == 1)
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==4 && deck_c[48-(i*2)] == 4)
				{
					cluep2_n[3] = 0;
					cluep2_c[3] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[4] == 1 && cluep2_c[3] == 1)
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==5 && deck_c[48-(i*2)] == 4)
				{
					cluep2_n[4] = 0;
					cluep2_c[3] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		//*COR BRANCO*
		/*Se o bot possuir uma pista que tem o numero 2 no seu baralho e possuir a pista que tem a cor amarelo e se ainda nao tiver sido jogada nenhuma 
		2 amarelo mas ja tiver sido jogada 1 amarelo entao o bot vai devolver a posiçao dessa carta para ser jogada*/
		else if(cluep2_n[1] == 1 && cluep2_c[4] == 1)
		{
			/*Se as condicoes acima se verificarem vai ser selecionada a primeira carta nº2 Amarela 
			que aparecer na mao do bot*/
			for (i=0;i<5;)
			{
				/*se existir uma carta Nª2 Amarelo no baralho do bot ele vai devolver
				a posicao onde essa carta esta para assim ser jogada na subrotina do playcard*/ //
				if(hand_player2[i]==2 && deck_c[48-(i*2)] == 5)
				{
					cluep2_n[1] = 0;
					cluep2_c[4] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[2] == 1 && cluep2_c[4] == 1)
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==3 && deck_c[48-(i*2)] == 5)
				{
					cluep2_n[2] = 0;
					cluep2_c[4] = 0;
					return i;
					break;
				}
				else 
				{
					i++;
				}
			}
		}
		else if(cluep2_n[3] == 1 && cluep2_c[4] == 1)
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==4 && deck_c[48-(i*2)] == 5)
				{
					cluep2_n[3] = 0;
					cluep2_c[4] = 0;
					return i;
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else if(cluep2_n[4] == 1 && cluep2_c[4] == 1)
		{
			for (i=0;i<5;)
			{
				if(hand_player2[i]==5 && deck_c[48-(i*2)] == 5)
				{
					cluep2_n[4] = 0;
					cluep2_c[4] = 0;
					return i;
					break;
				}
				else 
				{
					i++;
				}
			}
		}
		
		else
		{
			/*Quando devolver 999 sabemos que nao existem 
			cartas jogaveis no baralho BOT*/
			return 999;
		}
	
}

/*Esta funcao destina-se somente para saber se existem cartas jogaveis no baralho do humano*/
int playable_card2(int deck_n[],int deck_c[])
{
	int i;
	
		for(i=0;i<5;i++)
		{
			/*Vamos fazer com que sejam verificadas todas as cartas da mao do jogador e se existir alguma carta jogavel
			retorna o valor da posicao dessa carta. As cartas sao jogaveis se por exemplo existir 1-Vermelho jogado e o jogador tiver 
			um dois Vermelho na mao, sao contadas todas as hipoteses para cada cor e carta.		
			*/
			/*COR VERDE*/
			if(hand_player1[i]==1 && deck_c[49-(i*2)]==1 && table[0][0]==0)
			{
				return i;
			}
			else if(hand_player1[i]==2 && deck_c[49-(i*2)]==1 && table[0][0]==1 && table[1][0]==0) 
			{
				return i;
			}
			else if(hand_player1[i]==3 && deck_c[49-(i*2)]==1 && table[0][0]==1 && table[1][0]==2 && table[2][0]==0)
			{
				return i;
			}
			else if(hand_player1[i]==4 && deck_c[49-(i*2)]==1 && table[0][0]==1 && table[1][0]==2 && table[2][0]==3 && table[3][0]==0)
			{
				return i;
			}
			else if(hand_player1[i]==5 && deck_c[49-(i*2)]==1 && table[0][0]==1 && table[1][0]==2 && table[2][0]==3 && table[3][0]==4 && table[4][0]==0)
			{
				return i;
			}
			/*COR AZUL*/
			else if(hand_player1[i]==1 && deck_c[49-(i*2)]==2 && table[0][1]==0)
			{
				return i;
			}
			else if(hand_player1[i]==2 && deck_c[49-(i*2)]==2 && table[0][1]==1 && table[1][1]==0) 
			{
				return i;
			}
			else if(hand_player1[i]==3 && deck_c[49-(i*2)]==2 && table[0][1]==1 && table[1][1]==2 && table[2][1]==0)
			{
				return i;
			}
			else if(hand_player1[i]==4 && deck_c[49-(i*2)]==2 && table[0][1]==1 && table[1][1]==2 && table[2][1]==3 && table[3][1]==0)
			{
				return i;
			}
			else if(hand_player1[i]==5 && deck_c[49-(i*2)]==2 && table[0][1]==1 && table[1][1]==2 && table[2][1]==3 && table[3][1]==4 && table[4][1]==0)
			{
				return i;
			}
			/*COR AMARELO*/
			else if(hand_player1[i]==1 && deck_c[49-(i*2)]==3 && table[0][2]==0)
			{
				return i;
			}
			else if(hand_player1[i]==2 && deck_c[49-(i*2)]==3 && table[0][2]==1 && table[1][2]==0) 
			{
				return i;
			}
			else if(hand_player1[i]==3 && deck_c[49-(i*2)]==3 && table[0][2]==1 && table[1][2]==2 && table[2][2]==0)
			{
				return i;
			}
			else if(hand_player1[i]==4 && deck_c[49-(i*2)]==3 && table[0][2]==1 && table[1][2]==2 && table[2][2]==3 && table[3][2]==0)
			{
				return i;
			}
			else if(hand_player1[i]==5 && deck_c[49-(i*2)]==3 && table[0][2]==1 && table[1][2]==2 && table[2][2]==3 && table[3][2]==4 && table[4][2]==0)
			{
				return i;
			}
			/*COR VERMELHA*/
			else if(hand_player1[i]==1 && deck_c[49-(i*2)]==4 && table[0][3]==0)
			{
				return i;
			}
			else if(hand_player1[i]==2 && deck_c[49-(i*2)]==4 && table[0][3]==1 && table[1][3]==0) 
			{
				return i;
			}
			else if(hand_player1[i]==3 && deck_c[49-(i*2)]==4 && table[0][3]==1 && table[1][3]==2 && table[2][3]==0)
			{
				return i;
			}
			else if(hand_player1[i]==4 && deck_c[49-(i*2)]==4 && table[0][3]==1 && table[1][3]==2 && table[2][3]==3 && table[3][3]==0)
			{
				return i;
			}
			else if(hand_player1[i]==5 && deck_c[49-(i*2)]==4 && table[0][3]==1 && table[1][3]==2 && table[2][3]==3 && table[3][3]==4 && table[4][3]==0)
			{
				return i;
			}
			/*COR BRANCO*/
			else if(hand_player1[i]==1 && deck_c[49-(i*2)]==5 && table[0][4]==0)
			{
				return i;
			}
			else if(hand_player1[i]==2 && deck_c[49-(i*2)]==5 && table[0][4]==1 && table[1][4]==0) 
			{
				return i;
			}
			else if(hand_player1[i]==3 && deck_c[49-(i*2)]==5 && table[0][4]==1 && table[1][4]==2 && table[2][4]==0)
			{
				return i;
			}
			else if(hand_player1[i]==4 && deck_c[49-(i*2)]==5 && table[0][4]==1 && table[1][4]==2 && table[2][4]==3 && table[3][4]==0)
			{
				return i;
			}
			else if(hand_player1[i]==5 && deck_c[49-(i*2)]==5 && table[0][4]==1 && table[1][4]==2 && table[2][4]==3 && table[3][4]==4 && table[4][4]==0)
			{
				return i;
			}
		}
	/*Se passar pelo ciclo e nao encontrar nada 
	vai retornar 999 ou seja nao possui cartas
	jogaveis o Jogador*/	
	return 999;	
		
 }
//subrotina que cria um ficheiro de texto com as variaveis todas guardadas
save_game()
{
	/*Nesta subrotina vai ser criado um ficheiro de texto onde vai escrever usando o fprintf
	todas as variaveis globais naquele momento do jogo*/
	int i,j;
	FILE *jp;
	
	jp = fopen("savegame.txt","w");
	/*caso nao consiga abrir o ficheiro de texto*/
	if (jp == NULL)
	{
		gotoxy(4,4);
		printf("Nao foi possivel guardar a partida!");
	}
	/*Caso seja possivel abrir o ficheiro de texto
	vamos escrever as variaveis nele*/
	else
	{
		fprintf(jp,"%d ",random); //,turn,points,name,shop_deck,clue_tokens,life_tokens
		fprintf(jp,"%d ",points);
		fprintf(jp,"%d ",shop_deck);
		fprintf(jp,"%d ",clue_tokens);
		fprintf(jp,"%d \n",life_tokens);
		fprintf(jp,"%s",name);

		
		for(i=0;i<5;i++)
		{
			fprintf(jp,"%d ",cluep1_n[i]);
		} 
		fprintf(jp," Vetor de pistas de cor do BOT:\n");
			
		for(i=0;i<5;i++)
		{
			fprintf(jp,"%d ",cluep2_n[i]);
		} 
		fprintf(jp," Vetor de pistas de numero do BOT:\n");
		
		for(i=0;i<5;i++)
		{
			fprintf(jp,"%d ",cluep1_c[i]);
		} 
		fprintf(jp," Vetor de pistas de cor do jogador 1:\n");
		
		
		for(i=0;i<5;i++)
		{
			fprintf(jp,"%d ",cluep1_n[i]);
		} 
		fprintf(jp," Vetor de pistas de numero do jogador 1:\n");
		
		for(i=0;i<50;i++)
		{
			fprintf(jp,"%d ",deck_c[i]);
		} 
		
		fprintf(jp," Cartas das cores:\n");
		
		for(i=0;i<50;i++)
		{
			fprintf(jp,"%d ",deck_n[i]);
		} 
		fprintf(jp," Cartas dos numeros:\n");
		
		fprintf(jp,"TABELA DE JOGO\n");	
		for (i=0; i<5; i++)
		{
			for (j=0;j<5;j++)
			{
				fprintf(jp,"%d " ,table[i][j]);
			}
			fprintf(jp,"\n");
		}
		
		fprintf(jp,"TABELA DE DESCARTE\n");
		
		for (i=0; i<5; i++)
		{
			for (j=0;j<5;j++)
			{
				fprintf(jp,"%d " ,discard_table[i][j]);
			}
			fprintf(jp,"\n");
		}
		
		gotoxy(1,8);
		setColor(10,0);
		/*pequena mensagem que confirma que foi guardada a partida*/
		printf("A partida foi guardada com sucesso!");
		resetColor();
		/*fecha o ficheiro de texto*/
		fclose(jp);
	}
} 
