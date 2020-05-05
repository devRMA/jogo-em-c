#include <stdio.h> //biblioteca dos printf's e scanf's
#include <string.h> //biblioteca que manipula strings
#include <locale.h> //biblioteca que possibilita o uso de acentua��o nos prints
#include <stdlib.h> //biblioteca que tem o comando para limpar a tela
#include <windows.h> //Biblioteca que permite mudar a cor do print
#include <Windows.h> //Biblioteca que tem o comando Sleep(tempo);

// para limpar a tela � s� usar system("cls");

#define nome_do_jogo "Projeto" //constante que guarda o nome do jogo

//Constantes que guardam o codigo de cada cor(usado no procedimento mudar_cor)
#define vermelho_escuro 4
#define cinza 8
#define azul 9
#define verde 10
#define celeste 11
#define vermelho 12
#define roxo 13
#define amarelo 14
//variavel que vai ficar responsavel por ficar recebendo a escolha do player
int escolha = 0;
//Variavel que vai guardar a posi��o inicial do player 1
int pos_p1 = 33;
//Variavel que vai guardar a posi��o inicial do player 2
int pos_p2 = 35;
//Variavel que faz o controle se os players j� jogaram
int p1_ja_jogou = 0, p2_ja_jogou = 0;

//Variavel que vai guardar o HP do player 1
int hp_p1 = 15;
//Variavel que vai guardar o HP do player 2
int hp_p2 = 15;

//Variavel do tipo bool que vai guardar se o player est� se defendendo
int p1_defendendo = 0, p2_defendendo = 0;

//Variavel bool que vai guardar se o player est� atacando
int p1_atacando = 0, p2_atacando = 0;
//Variavel que guarda a quantos turnos os players est�o se defendendo
int turnos_p1_defendendo = 0, turnos_p2_defendendo = 0;
int turnos = 1; //turnos do jogo

void mudar_cor(int cor) //fun��o para mudar a cor do print
{
    //IMPORTANTE: UMA VEZ CHAMADA ESSA FUN��O, TODOS OS PRINTS SAIR�O COM A MESMA COR, PARA VOLTAR
    //AO NORMAL, TEM QUE CHAMAR ELA, PASSANDO COMO PAR�METRO -1
    /*codigos das cores:
    cinza - 8
    azul - 9
    verde - 10
    celeste - 11
    vermelho - 12
    roxo - 13
    amarelo - 14
    resetar - 15*/
    int num_cor = 15;
    switch (cor) //verifica qual cor foi passado como parametro
    {
        case 4: //se o que foi digitado for 4(vermelho escuro):
            num_cor = 4;//a variavel vai receber o codigo conforme o comentario anterior
            break; //pula a compara��o com os outros casos
        case 8://se o que foi digitado for 8(cinza):
            num_cor = 8; //a variavel vai receber o codigo conforme o comentario anterior
            break; //pula a compara��o com os outros casos
        case 9:
            num_cor = 9;
            break;
        case 10:
            num_cor = 10;
            break;
        case 11:
            num_cor = 11;
            break;
        case 12:
            num_cor = 12;
            break;
        case 13:
            num_cor = 13;
            break;
        case 14:
            num_cor = 14;
            break;
		case 207:
			num_cor = 207;
			break;
        default: //se nenhum dos casos for realizado, ele vai executar o default
            num_cor = 15; //reseta as cores
    }
    //codigo para mudar a cor do print
    HANDLE  hConsole; //n�o sei como essas 3 linhas funcionam, s� sei que muda a cor
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, num_cor);
}
//Fun��o que vai realizar o ataque do player
int atacar(int qual_player/*1 para player 1, e 2 para player 2*/)
{
    int quantas_casas_tem_entre_os_players = (pos_p2 - pos_p1);//pega a dist�ncia entre os players(o n�mero de casas entre eles)

    //se os players estiverem perto o bastante para atacar
    if (quantas_casas_tem_entre_os_players <= 3 && quantas_casas_tem_entre_os_players > 0)
    {
        if (qual_player == 1) //se foi o player 1, a variavel bool muda para True
        {
            p1_atacando = 1;
            return 1; //se o player conseguiu atacar
        }
        else //senao, a variavel do player 2, fica True
        {
            p2_atacando = 1;
            return 1; //se o player conseguiu atacar
        }
    }
    return 0; //se o player estiver muito longe, retorna falso
}
void ataque(int ataque_p1, int ataque_p2)
{
    // define o dano valendo 3
    int dano = 3;
    if(ataque_p1){// se o player 1 atacar, ele pede uma rea��o do player 2.
        status();
        escolhas_p2();
        if(! p2_defendendo) //se o player 2 n�o estiver e defendendo
        {
            mudar_cor(vermelho);
            printf("O player 1 est� atacando, o que voc� quer fazer? ");
            mudar_cor(-1);
            scanf("%d", &escolha);
            p2_ja_jogou = 1;
            int quantas_casas_tem_entre_os_players = (pos_p2 - pos_p1);//pega a dist�ncia entre os players

            if (escolha == 1) //escolheu avan�ar
            {
                int maximo_de_casas_pode_andar = 5;
                if ((pos_p2 - pos_p1+1) >= 5) //se o n�mero de casas entre os players for maior que 5, o n�mero maximo de casas fica com 5
                {
                    maximo_de_casas_pode_andar = 5;
                }
                else
                {
                    maximo_de_casas_pode_andar = (pos_p2 - (pos_p1+1)); //pega quantas casas tem livre para a movimenta��o
                    //                                             +1 para que os players n�o fiquem na mesma casa
                }
                printf("Digite quantas casas voc� quer andar (de 1 a %d): ", maximo_de_casas_pode_andar);
                scanf("%d", &escolha); //recebe quantas casas o player quer avan�as
                if (escolha >= 1 && escolha <= maximo_de_casas_pode_andar)
                {
                    if (quantas_casas_tem_entre_os_players > 1) //se os jogadores n�o estiverem um olhando para a cara do outro
                    {
                        if (pos_p2 - (pos_p1+escolha) >= 0) //se, quando o player andar, ele n�o atravessar o player 1
                        {
                            pos_p2 -= escolha; //a posi��o atual do player 2 tira quantas casas ele escolheu andar
                        }
                        else
                        {
                            pos_p2 -= (pos_p2 - (pos_p1+1)); //mais do que esse valor o player 2 vai passar para o lado esquerdo
                            //                         +1 para que os players n�o fiquem na mesma casa
                        }
                    }
                }
                else
                {
                    mudar_cor(207);
                    printf("Escolha uma quantidade valida! Perdeu o turno");
                    Sleep(2000);
                    mudar_cor(-1);
                }
            }
            else if (escolha == 2) //escolheu recuar
            {
                int maximo_de_casas_pode_recuar = 5;

                //verifica��o de quantas casas livres para recuar

                if (pos_p2 < 45) //se o n�mero de casas entre o player e a parede (posi��o 50) for menor que 45
                {
                    maximo_de_casas_pode_recuar = 5;
                }
                else
                {
                    maximo_de_casas_pode_recuar = (50 - pos_p2);
                    //se ele estiver menos de 5 casas da parede, ele s� vai poder recuar , no maximo, a posi��o dele -1
                    //pois, ele n�o vai poder entrar na parede(posi��o 0)
                }

                //verifica��o de escolha
                if (maximo_de_casas_pode_recuar != 0) //se o jogador estiver com pelo menos 1 casa para recuar
                {
                    printf("Digite quantas casas voc� quer recuar (de 1 a %d): ", maximo_de_casas_pode_recuar);
                    scanf("%d", &escolha); //recebe quantas casas o player quer recuar
                    if (escolha >= 1 && escolha <= maximo_de_casas_pode_recuar) //se a escolha do player for valida (esta dentro das escolhas)
                    {
                        pos_p2 += escolha; //o valor � simplesmente retirado, pois j� foi verificado se o n�mero � valido
                    }
                    else //se n�o estiver, ele perde o turno
                    {
                        mudar_cor(207); //mensagem com o fundo vermelho
                        printf("Escolha uma quantidade valida! Perdeu o turno");
                        Sleep(2000);
                        mudar_cor(-1);
                    }
                }
                else
                {
                    mudar_cor(207);
                    printf("Voc� j� est� no canto da arena! N�o tem como recuar mais!");
                    Sleep(2000);
                    mudar_cor(-1);
                }
            }
            else if (escolha == 3) //escolheu atacar
            {
                p2_atacando = 1;
            }
            else if (escolha == 4) //escolheu defender
            {
                p2_defendendo = 1;
            }
            else //escolheu um n�mero menor que 1 e maior que 4
            {
                mudar_cor(207);
                printf("Escolha inv�lida, perdeu um turno.");
                Sleep(2000);
                mudar_cor(-1);
            }
            if(p2_defendendo){// se, enquanto o player 1 estiver atacando o player 2 estiver defendendo
                // tira 1 de vida do player 2
                hp_p2 -= 1;
            } else if(p2_atacando && p1_atacando){
                hp_p2 -= 3;
                hp_p1 -= 3;
            }
        }
        else
        {
            hp_p2 -= 1;
        }
    }
    else if(ataque_p2)
    {
        status();
        escolhas_p1();
        if(! p1_defendendo)
        {
            mudar_cor(vermelho);
            printf("O player 2 est� atacando, o que voc� quer fazer? ");
            mudar_cor(-1);
            scanf("%d", &escolha);
            p1_ja_jogou = 1;
            int quantas_casas_tem_entre_os_players = (pos_p2 - pos_p1);//pega a dist�ncia entre os players

            if (escolha == 1) //escolheu avan�ar
            {
                int maximo_de_casas_pode_andar = 5;
                if ((pos_p2 - pos_p1+1) >= 5) //se o n�mero de casas entre os players for maior que 5, o n�mero maximo de casas fica com 5
                {
                    maximo_de_casas_pode_andar = 5;
                }
                else
                {
                    maximo_de_casas_pode_andar = (pos_p2 - (pos_p1+1)); //pega quantas casas tem livre para a movimenta��o
                    //                                             +1 para que os players n�o fiquem na mesma casa
                }
                printf("Digite quantas casas voc� quer andar (de 1 a %d): ", maximo_de_casas_pode_andar);
                scanf("%d", &escolha); //recebe quantas casas o player quer avan�as
                if (escolha >= 1 && escolha <= maximo_de_casas_pode_andar)
                {
                    if (quantas_casas_tem_entre_os_players > 1) //se os jogadores n�o estiverem um olhando para a cara do outro
                    {
                        if (pos_p2 - (pos_p1+escolha) >= 0) //se, quando o player andar, ele n�o atravessar o player 2
                        {
                            pos_p1 += escolha; //a posi��o atual do player 1 soma quantas casas ele escolheu andar
                        }
                        else
                        {
                            pos_p1 += (pos_p2 - (pos_p1+1)); //mais do que esse valor o player 1 vai passar para o lado direito
                            //                         +1 para que os players n�o fiquem na mesma casa
                        }
                    }
                }
                else
                {
                    mudar_cor(207);
                    printf("Escolha uma quantidade valida! Perdeu o turno");
                    Sleep(2000);
                    mudar_cor(-1);
                }
            }
            else if (escolha == 2) //escolheu recuar
            {
                int maximo_de_casas_pode_recuar = 5;

                //verifica��o de quantas casas livres para recuar

                if (pos_p1 > 5) //se o n�mero de casas entre o player e a parede (posi��o 0) for maior que 5
                {
                    maximo_de_casas_pode_recuar = 5;
                }
                else
                {
                    maximo_de_casas_pode_recuar = (pos_p1 - 1);
                    //se ele estiver menos de 5 casas da parede, ele s� vai poder recuar , no maximo, a posi��o dele -1
                    //pois, ele n�o vai poder entrar na parede(posi��o 0)
                }

                //verifica��o de escolha
                if (maximo_de_casas_pode_recuar != 0) //se o jogador estiver com pelo menos 1 casa para recuar
                {
                    printf("Digite quantas casas voc� quer recuar (de 1 a %d): ", maximo_de_casas_pode_recuar);
                    scanf("%d", &escolha); //recebe quantas casas o player quer recuar
                    if (escolha >= 1 && escolha <= maximo_de_casas_pode_recuar) //se a escolha do player for valida (esta dentro das escolhas)
                    {
                        pos_p1 -= escolha; //o valor � simplesmente retirado, pois j� foi verificado se o n�mero � valido
                    }
                    else //se n�o estiver, ele perde o turno
                    {
                        mudar_cor(207); //mensagem com o fundo vermelho
                        printf("Escolha uma quantidade valida! Perdeu o turno");
                        Sleep(2000);
                        mudar_cor(-1);
                    }
                }
                else
                {
                    mudar_cor(207);
                    printf("Voc� j� est� no canto da arena! N�o tem como recuar mais!");
                    Sleep(2000);
                    mudar_cor(-1);
                }
            }
            else if (escolha == 3) //escolheu atacar
            {
                p1_atacando = 1;
            }
            else if (escolha == 4) //escolheu defender
            {
                p1_defendendo = 1;
            }
            else //escolheu um n�mero menor que 1 e maior que 4
            {
                mudar_cor(207);
                printf("Escolha inv�lida, perdeu um turno.");
                Sleep(2000);
                mudar_cor(-1);
            }
            if(p1_defendendo){
                hp_p1 -= 1;
            } else if(p2_atacando && p1_atacando){
                hp_p2 -= 3;
                hp_p1 -= 3;
            }
        }
        else
        {
            hp_p1 -= 1;
        }
    }
    // reseta as vari�veis
    p1_atacando = 0;
    p2_atacando = 0;
    p2_defendendo = 0;
    p1_defendendo = 0;
}
void status() //um procedimento que da print nos status
{
    setlocale(LC_ALL, ""); //desabilita o padr�o portugu�s dos prints
    setlocale(LC_ALL, "C"); //habilita o padr�o do C, para dar print na barra de hp
    system("cls"); //limpa a tela
    printf("\t\tTurno: %d\n", turnos);
    mudar_cor(amarelo);
    printf("Jogador 1\t\t\tJogador 2\n");
    mudar_cor(-1);
    if (p1_defendendo) //se o player 1 estiver se defendendo, o hp dele fica um pouco escuro
    {
        mudar_cor(vermelho_escuro);
    }
    else //sen�o, fica vermelho claro
    {
        mudar_cor(vermelho);
    }
    printf("HP:"); //come�a a dar print nas barras de hp do player 1
    //printf("HP:%d\t\t\t\tHp:%d\n", hp_p1, hp_p2); //assim ele s� mostra os n�meros
    for (int c = 1; c <= hp_p1; c++) //assim, ele da print nas barras conforme a quantidade de hp
    {
        //printf("|");
        printf("%c", 219); //da print em uma barra cheia para representar a barra de hp
    }
    if(hp_p1 < 15)
    {
        for(int c = 0; c <= (15-hp_p1); c++)
        {
            printf("%c", 176); //da print em uma barra vazia para representar o dano sofrido
        }
    }
    if (p2_defendendo) //se o player 2 estiver se defendendo, o hp dele fica um pouco escuro
    {
        mudar_cor(vermelho_escuro);
    }
    else //sen�o, fica vermelho claro
    {
        mudar_cor(vermelho);
    }
    printf("\t\tHP:");
    for (int c = 1; c <= hp_p2; c++)
    {
        //printf("|");
        printf("%c", 219);
    }
    if(hp_p2 < 15)
    {
        for(int c = 0; c <= (15-hp_p2); c++)
        {
            printf("%c", 176); //da print em uma barra vazia para representar o dano sofrido
        }
    }
    mudar_cor(celeste);
    printf("\n\\");
    for (int c = 1; c <= 50; c++)//processo para alterar a �cone do personagem se estiver se defendendo
    {
        if(c == pos_p1)
        {
            if (p1_defendendo)
            {
                mudar_cor(azul);
                printf("(");
                mudar_cor(verde);
                printf("P1");
                mudar_cor(azul);
                printf(")");
                mudar_cor(celeste);
            }
            else
            {
                mudar_cor(verde);
                printf("P1");
                mudar_cor(celeste);
            }
        }
        if(c == pos_p2)
        {
            if (p2_defendendo)
            {
                mudar_cor(azul);
                printf("(");
                mudar_cor(verde);
                printf("P2");
                mudar_cor(azul);
                printf(")");
                mudar_cor(celeste);
            }
            else
            {
                mudar_cor(verde);
                printf("P2");
                mudar_cor(celeste);
            }
        }
        else
        {
            printf("_");
        }
    }
    setlocale(LC_ALL, "");
    printf("/\n");
    //printf("\nPosi��o:%d\t\t\tPosi��o:%d\n", pos_p1, pos_p2);
    mudar_cor(-1);
    // esses \t fazem o mesmo espa�o de uma TAB
    /*
    printa:
    Jogador 1                       Jogador 2
    HP:(uma barra para cada hp)     Hp:15
    Posi��o:1                       Posi��o:50*/


}
void escolhas_p1()
{
    int quantas_casas_tem_entre_os_players = (pos_p2 - pos_p1);//pega a dist�ncia entre os players
    //variaveis do tipo bool que controlam as poss�veis a��es do player
    int pode_atacar = 0, pode_defender = 1, pode_andar = 0, pode_recuar = 0;

    //se os players estiverem perto o bastante para atacar
    if (quantas_casas_tem_entre_os_players <= 3 && quantas_casas_tem_entre_os_players > 0)
    {
        pode_atacar = 1;
    }
    if (p1_defendendo) //se o player j� estiver defendendo
    {
        pode_defender = 0;
    }
    if ((pos_p2 - (pos_p1+1)) >= 1) //se as casas entres os players for maior que 1
    {
        pode_andar = 1;
    }
    if (pos_p1 > 1 || pos_p2 < 50)
    {
        pode_recuar = 1;
    }
    if ( pode_andar) //ele vai mudar a cor do proximo print conforme o estado da variavel
        mudar_cor(verde); //n�o precisa ter chave quando � s� um comando
    else
        mudar_cor(cinza); //se o player poder fazer a jogada, vai ficar verde, sen�o, cinza
    printf("\n\n1 - Avan�ar");
    if ( pode_atacar)
        mudar_cor(verde);
    else
        mudar_cor(cinza);
    printf("\t3 - Atacar\n");
    if (pode_recuar)
        mudar_cor(verde);
    else
        mudar_cor(cinza);
    printf("\n2 - Recuar");
    if (pode_defender)
        mudar_cor(verde);
    else
        mudar_cor(cinza);
    printf("\t4 - Defender\n");
    mudar_cor(-1); //reseta a cor dos prints
    /*
    da print em:
    1 - Avan�ar     3 - Atacar

    2 - Recuar      4 - Defender

    com a cor cinza nas op��es, se n�o for poss�vel realizar a a��o, e verde se for poss�vel
    */
}
void escolhas_p2()
{
    int quantas_casas_tem_entre_os_players = (pos_p2 - pos_p1);//pega a dist�ncia entre os players
    //variaveis do tipo bool que controlam as poss�veis a��es do player
    int pode_atacar = 0, pode_defender = 1, pode_andar = 0, pode_recuar = 0;

    //se os players estiverem perto o bastante para atacar
    if (quantas_casas_tem_entre_os_players <= 3 && quantas_casas_tem_entre_os_players > 0)
    {
        pode_atacar = 1;

    }
    if (p2_defendendo) //se o player j� estiver defendendo
    {
        pode_defender = 0;
    }
    if ((pos_p2 - (pos_p1+1)) >= 1) //se as casas entres os players for maior que 1
    {
        pode_andar = 1;
    }
    if (pos_p2 < 50)
    {
        pode_recuar = 1;
    }
    if ( pode_andar) //ele vai mudar a cor do proximo print conforme o estado da variavel
        mudar_cor(verde); //n�o precisa ter chave quando � s� um comando
    else
        mudar_cor(cinza); //se o player poder fazer a jogada, vai ficar verde, sen�o, cinza
    printf("\n\n1 - Avan�ar");
    if ( pode_atacar)
        mudar_cor(verde);
    else
        mudar_cor(cinza);
    printf("\t3 - Atacar\n");
    if (pode_recuar)
        mudar_cor(verde);
    else
        mudar_cor(cinza);
    printf("\n2 - Recuar");
    if (pode_defender)
        mudar_cor(verde);
    else
        mudar_cor(cinza);
    printf("\t4 - Defender\n");
    mudar_cor(-1); //reseta a cor dos prints
    /*
    da print em:
    1 - Avan�ar     3 - Atacar

    2 - Recuar      4 - Defender

    com a cor cinza nas op��es, se n�o for poss�vel realizar a a��o, e verde se for poss�vel
    */
}
void player1()
{
    p1_ja_jogou = 1;
    int quantas_casas_tem_entre_os_players = (pos_p2 - pos_p1);//pega a dist�ncia entre os players

    if (escolha == 1) //escolheu avan�ar
    {
        int maximo_de_casas_pode_andar = 5;
        if ((pos_p2 - pos_p1+1) >= 5) //se o n�mero de casas entre os players for maior que 5, o n�mero maximo de casas fica com 5
        {
            maximo_de_casas_pode_andar = 5;
        }
        else
        {
            maximo_de_casas_pode_andar = (pos_p2 - (pos_p1+1)); //pega quantas casas tem livre para a movimenta��o
            //                                             +1 para que os players n�o fiquem na mesma casa
        }
        printf("Digite quantas casas voc� quer andar (de 1 a %d): ", maximo_de_casas_pode_andar);
        scanf("%d", &escolha); //recebe quantas casas o player quer avan�as
        if (escolha >= 1 && escolha <= maximo_de_casas_pode_andar)
        {
            if (quantas_casas_tem_entre_os_players > 1) //se os jogadores n�o estiverem um olhando para a cara do outro
            {
                if (pos_p2 - (pos_p1+escolha) >= 0) //se, quando o player andar, ele n�o atravessar o player 2
                {
                    pos_p1 += escolha; //a posi��o atual do player 1 soma quantas casas ele escolheu andar
                }
                else
                {
                    pos_p1 += (pos_p2 - (pos_p1+1)); //mais do que esse valor o player 1 vai passar para o lado direito
                    //                         +1 para que os players n�o fiquem na mesma casa
                }
            }
        }
        else
        {
            mudar_cor(207);
            printf("Escolha uma quantidade valida! Perdeu o turno");
            Sleep(2000);
            mudar_cor(-1);
        }
    }
    else if (escolha == 2) //escolheu recuar
    {
        int maximo_de_casas_pode_recuar = 5;

        //verifica��o de quantas casas livres para recuar

        if (pos_p1 > 5) //se o n�mero de casas entre o player e a parede (posi��o 0) for maior que 5
        {
            maximo_de_casas_pode_recuar = 5;
        }
        else
        {
            maximo_de_casas_pode_recuar = (pos_p1 - 1);
            //se ele estiver menos de 5 casas da parede, ele s� vai poder recuar , no maximo, a posi��o dele -1
            //pois, ele n�o vai poder entrar na parede(posi��o 0)
        }

        //verifica��o de escolha
        if (maximo_de_casas_pode_recuar != 0) //se o jogador estiver com pelo menos 1 casa para recuar
        {
            printf("Digite quantas casas voc� quer recuar (de 1 a %d): ", maximo_de_casas_pode_recuar);
            scanf("%d", &escolha); //recebe quantas casas o player quer recuar
            if (escolha >= 1 && escolha <= maximo_de_casas_pode_recuar) //se a escolha do player for valida (esta dentro das escolhas)
            {
                pos_p1 -= escolha; //o valor � simplesmente retirado, pois j� foi verificado se o n�mero � valido
            }
            else //se n�o estiver, ele perde o turno
            {
                mudar_cor(207); //mensagem com o fundo vermelho
                printf("Escolha uma quantidade valida! Perdeu o turno");
                Sleep(2000);
                mudar_cor(-1);
            }
        }
        else
        {
            mudar_cor(207);
            printf("Voc� j� est� no canto da arena! N�o tem como recuar mais!");
            Sleep(2000);
            mudar_cor(-1);
        }
    }
    else if (escolha == 3) //escolheu atacar
    {
        if (atacar(1)) //se a fun��o retornou true, � pq o ataque � possivel, logo a variavel global foi mudada
        {
            ataque(p1_atacando, p2_atacando);
            Sleep(2000);
        }
        else //se a fun��o retornou false, � porque o player est� muito longe para atacar
        {
            mudar_cor(207);
            printf("Player 2 esta muito longe.");
            Sleep(2000);
            mudar_cor(-1);
        }
    }
    else if (escolha == 4) //escolheu defender
    {
        p1_defendendo = 1;
        turnos_p1_defendendo++;
    }
    else //escolheu um n�mero menor que 1 e maior que 4
    {
		mudar_cor(207);
        printf("Escolha inv�lida, perdeu um turno.");
        Sleep(2000);
		mudar_cor(-1);
    }
}
void player2()
{
    int quantas_casas_tem_entre_os_players = (pos_p2 - pos_p1);//pega a dist�ncia entre os players

    if (escolha == 1) //escolheu avan�ar
    {
        int maximo_de_casas_pode_andar = 5;
        if ((pos_p2 - pos_p1+1) > 5) //se o n�mero de casas entre os players for maior que 5, o n�mero maximo de casas fica com 5
        {
            maximo_de_casas_pode_andar = 5;
        }
        else
        {
            maximo_de_casas_pode_andar = (pos_p2 - (pos_p1+1)); //pega quantas casas tem livre para a movimenta��o
            //                                             +1 para que os players n�o fiquem na mesma casa
        }
        printf("Digite quantas casas voc� quer andar (de 1 a %d): ", maximo_de_casas_pode_andar);
        scanf("%d", &escolha); //recebe quantas casas o player quer avan�as
        if (escolha >= 1 && escolha <= maximo_de_casas_pode_andar)
        {
            if (quantas_casas_tem_entre_os_players > 1) //se os jogadores n�o estiverem um olhando para a cara do outro
            {
                if (pos_p2 - (pos_p1+escolha) >= 0) //se, quando o player andar, ele n�o atravessar o player 1
                {
                    pos_p2 -= escolha; //a posi��o atual do player 2 tira quantas casas ele escolheu andar
                }
                else
                {
                    pos_p2 -= (pos_p2 - (pos_p1+1)); //mais do que esse valor o player 2 vai passar para o lado esquerdo
                    //                         +1 para que os players n�o fiquem na mesma casa
                }
            }
        }
        else
        {
            mudar_cor(207);
            printf("Escolha uma quantidade valida! Perdeu o turno");
            Sleep(2000);
            mudar_cor(-1);
        }
    }
    else if (escolha == 2) //escolheu recuar
    {
        int maximo_de_casas_pode_recuar = 5;

        //verifica��o de quantas casas livres para recuar

        if (pos_p2 < 45) //se o n�mero de casas entre o player e a parede (posi��o 50) for menor que 45
        {
            maximo_de_casas_pode_recuar = 5;
        }
        else
        {
            maximo_de_casas_pode_recuar = (50 - pos_p2);
            //se ele estiver menos de 5 casas da parede, ele s� vai poder recuar , no maximo, a posi��o dele -1
            //pois, ele n�o vai poder entrar na parede(posi��o 0)
        }

        //verifica��o de escolha
        if (maximo_de_casas_pode_recuar != 0) //se o jogador estiver com pelo menos 1 casa para recuar
        {
            printf("Digite quantas casas voc� quer recuar (de 1 a %d): ", maximo_de_casas_pode_recuar);
            scanf("%d", &escolha); //recebe quantas casas o player quer recuar
            if (escolha >= 1 && escolha <= maximo_de_casas_pode_recuar) //se a escolha do player for valida (esta dentro das escolhas)
            {
                pos_p2 += escolha; //o valor � simplesmente retirado, pois j� foi verificado se o n�mero � valido
            }
            else //se n�o estiver, ele perde o turno
            {
                mudar_cor(207); //mensagem com o fundo vermelho
                printf("Escolha uma quantidade valida! Perdeu o turno");
                Sleep(2000);
                mudar_cor(-1);
            }
        }
        else
        {
            mudar_cor(207);
            printf("Voc� j� est� no canto da arena! N�o tem como recuar mais!");
            Sleep(2000);
            mudar_cor(-1);
        }
    }
    else if (escolha == 3) //escolheu atacar
    {
        if (atacar(2)) //se a fun��o retornou true, � pq o ataque � possivel, logo a variavel global foi mudada
        {
            ataque(p1_atacando, p2_atacando);
            Sleep(2000);
        }
        else //se a fun��o retornou false, � porque o player est� muito longe para atacar
        {
            mudar_cor(207);
            printf("Player 2 esta muito longe.");
            Sleep(2000);
            mudar_cor(-1);
        }
    }
    else if (escolha == 4) //escolheu defender
    {
        p2_defendendo = 1;
        turnos_p2_defendendo++;
    }
    else //escolheu um n�mero menor que 1 e maior que 4
    {
		mudar_cor(207);
        printf("Escolha inv�lida, perdeu um turno.");
        Sleep(2000);
		mudar_cor(-1);
    }
    p2_ja_jogou = 1;
}
int main()
{
    setlocale(LC_ALL, "");


    //Variavel do tipo bool que guarda se o jogo deve continuar ou n�o
    int jogo_deve_continuar = 1;

    //Variavel que vai guardar quantos turnos j� passaram
    mudar_cor(roxo);
    printf("Bem vindo ao %s!!", nome_do_jogo);
    Sleep(3000); //espera 3 segundos
    mudar_cor(-1); //reseta a cor

    while (jogo_deve_continuar)
    {
        if(! p1_ja_jogou) //se o player 1 n�o jogou
        {
            if(p1_defendendo) //verifica quantos a turnos que o player est� se defendendo, se for 1, ele para de se defender, se for 0, ele continua se defendendo
            {
                if(turnos_p1_defendendo == 0)
                {
                    p1_defendendo = 1;
                }
                else if(turnos_p1_defendendo == 1)
                {
                    turnos_p1_defendendo = 0;
                    p1_defendendo = 0;
                }
            }
            status(); //da um print na posi��o e  no hp atual de cada players
            escolhas_p1(); //da um print nas escolhas que o player pode fazer
            mudar_cor(azul);
            printf("\n\nJogador 1, qual a��o voc� quer fazer: ");
            scanf("%d", &escolha); //recebe o input do player 1
            mudar_cor(-1); //reseta a cor dos prints
            player1();
            p1_ja_jogou = 1;
        }
        if (! p2_ja_jogou) //se o player 2 n�o jogou
        {
            if(p2_defendendo) //verifica quantos a turnos que o player est� se defendendo, se for 1, ele para de se defender, se for 0, ele continua se defendendo
            {
                if(turnos_p2_defendendo == 0)
                {
                    p2_defendendo = 1;
                }
                else if (turnos_p2_defendendo == 1)
                {
                    turnos_p2_defendendo = 0;
                    p2_defendendo = 0;
                }
            }
            status(); //da um print na posi��o e  no hp atual de cada players
            escolhas_p2(); //da um print nas escolhas que o player pode fazer
            mudar_cor(azul);
            printf("\n\nJogador 2, qual a��o voc� quer fazer: ");
            scanf("%d", &escolha); //recebe o input do player 2
            mudar_cor(-1); //reseta a cor dos prints
            player2();
        }
        if (hp_p1 <= 0 && hp_p2 <= 0)
        {
            jogo_deve_continuar = 0;
            system("cls"); //limpa a tela
            mudar_cor(verde);
            printf("Empate!\n");
            mudar_cor(-1);
            jogo_deve_continuar = 0;
        }
        else if (hp_p1 <= 0) //Se a vida do player 1, for menor ou igual a 0, o jogo para e da um print dizendo que o player 2 ganhou
        {
            jogo_deve_continuar = 0;
            system("cls"); //limpa a tela
            mudar_cor(verde);
            printf("O jogador 2 ganhou!\n");
            mudar_cor(-1);
            jogo_deve_continuar = 0;
        }
        else if (hp_p2 <= 0) //Se a vida do player 2, for menor ou igual a 0, o jogo para e da um print dizendo que o player 1 ganhou
        {
            jogo_deve_continuar = 0;
            system("cls"); //limpa a tela
            mudar_cor(verde); //printa a mensagem a baixo em verde
            printf("O jogador 1 ganhou!\n");
            mudar_cor(-1); //reseta o print
            jogo_deve_continuar = 0;
        }
        else //sen�o, jogo continua
        {
            jogo_deve_continuar = 1;
            turnos++; //se o jogo continuar, � adicionado 1 turno
            //reseta as variaveis
            p1_atacando = 0;
            p2_atacando = 0;
            p1_ja_jogou = 0;
            p2_ja_jogou = 0;
        }

    }

    return 0;
}

/*
codigo que da print em todas as cores e seus respectivos codigos:

#include <stdio.h>
#include <windows.h>
void mudar_cor(int cor)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}
int main()
{
   for(int c = 0; c <= 255; c++)
   {
       mudar_cor(c);
       printf("Print colorido com o codigo %d\n", c);}
    return 0;
}
*/
