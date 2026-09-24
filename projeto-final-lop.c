#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

// Função de espera interativa baseada no relógio real do sistema
void esperar_interativo(int segundos) {
    clock_t inicio = clock();
    long milissegundos_alvo = (long)segundos * CLOCKS_PER_SEC;

    while ((clock() - inicio) < milissegundos_alvo) {
        if (_kbhit()) {
            char tecla = _getch();
            if (tecla == 'p' || tecla == 'P') {
                printf("\n\n[Sistema Pausado] Pressione qualquer tecla para continuar...\n");
                
                clock_t pausa_inicio = clock();
                _getch();
                inicio += (clock() - pausa_inicio); // Compensa o tempo pausado
                
                printf("\nRetomando o processo...\n");
            }
        }
        _sleep(50); // Pausa leve para aliviar o processador
    }
}

int main() {
    // Variáveis simples para cada posição do painel (0 ou 1)
    int OnOff = 0, NB = 0, NA = 0, FC = 0, FH = 0, Agitd = 0, Bomba = 0, Alert = 0;
    int opcao;

    while (1) {
        // 1. Desenha o Painel Inicial na Tela
        system("cls"); // Limpa a tela no Windows
        printf("===============================================================\n");
        printf(" Controle de uma caldeira \n");
        printf("===============================================================\n");
        printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
        printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n",
                OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
        printf("===============================================================\n\n");

        // Se o sistema está desligado e sem alertas, pede para iniciar
        if (OnOff == 0 && Alert == 0) {
            printf("Situacao do sistema (0 - Desligado / 1 - Ligado): ");
            scanf("%d", &opcao);
            if (opcao == 0) {
                printf("\nSistema desligado!\n");
                printf("Pressione ENTER para continuar...");
                getchar(); getchar();
                continue;
            } else {
                OnOff = 1;
                continue;
            }
        }

        // Se o alerta de emergência disparou
        if (Alert == 1) {
            printf("STOP! Corrija o defeito e aperte alguma tecla para setar novamente!\n");
            printf("Digite 1 para resetar o sistema: ");
            scanf("%d", &opcao);
            OnOff = 0; NB = 0; NA = 0; FC = 0; FH = 0; Agitd = 0; Bomba = 0; Alert = 0;
            continue;
        }

        // sistema ligado: Solicita os sensores de nivel
        printf("Situacao sensor Nbaixo: ");
        scanf("%d", &NB);
        printf("Situacao sensor NAlto: ");
        scanf("%d", &NA);

        // Intertravamento ---
        if ((NB == 0 && NA == 1) || (OnOff == 1 && NB == 1 && NA == 0 && FH == 0 && Agitd == 0)) {
            OnOff = 0;
            Alert = 1;
            continue;
        }

        // --- CASO 1: CALDEIRA VAZIA (N/B = 0 e N/A = 0) ---
        if (NB == 0 && NA == 0) {
            // Ativar válvula de fluido quente
            FH = 1;
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("Aguarde a ativacao da valvula de fluido quente! (observe o atuador F_H) (5s)\n");
            esperar_interativo(5);

            // Enchimento parcial até atingir nível baixo
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("Aguarde o enchimento parcial da caldeira com fluido quente (observe o sensor N/B) (10s)\n");
            esperar_interativo(10);
            NB = 1; // Ativou o sensor após os 10s

            // Ativar válvula de fluido frio
            FC = 1;
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("Aguarde a ativacao da valvula de fluido frio! (observe o atuador F_C) (5s)\n");
            esperar_interativo(5);

            // Enchimento com ambos ativos
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("Aguarde o enchimento da caldeira com fluido quente e frio (observe o atuador F_C) (15s)\n");
            esperar_interativo(15);
            FC = 0; // Desativa a fria 

            // Termina o enchimento com a quente aberta
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("Aguarde o termino do enchimento da caldeira com fluido quente (10s) (observe o atuador F_H e o sensor N/A)\n");
            esperar_interativo(10);
            FH = 0; // Desativa a quente
            NA = 1; // Caldeira cheia
        }

        // mistura e esvaziamento
        if (NB == 1 && NA == 1) {
            // Ativar Agitador
            Agitd = 1;
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("Aguarde a ativacao do agitador! (observe o atuador Agitd) (5s)\n");
            esperar_interativo(5);

            // Agitador trabalhando
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("AGUARDE: Agitador ativo! (20s)\n");
            esperar_interativo(20);

            // Desliga agitador e liga bomba
            Agitd = 0;
            Bomba = 1;
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("Aguarde a ativacao da bomba e desativacao do agitador (observe os atuadores Agitd e bomba) (5s)\n");
            esperar_interativo(5);

            // Esvaziando (Sai do nível Alto)
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("AGUARDE: Esvaziamento do tanque! (observe o sensor N/A) (10s)\n");
            esperar_interativo(10);
            NA = 0;

            // Esvaziando por completo (Sai do nível baixo e desliga bomba)
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("AGUARDE: Esvaziamento do tanque! (observe o sensor N/B e o atuador bomba) (25s)\n");
            esperar_interativo(25);
            NB = 0;
            Bomba = 0;

            // Fim do ciclo
            system("cls");
            printf("===============================================================\n");
            printf(" Controle de uma caldeira \n");
            printf("===============================================================\n");
            printf(" On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert \n");
            printf("   %d    |  %d  |  %d  |  %d  |  %d  |   %d   |   %d   |   %d   \n", OnOff, NB, NA, FC, FH, Agitd, Bomba, Alert);
            printf("===============================================================\n\n");
            printf("Sistema ATIVO, aperte alguma tecla para setar novamente\n");

            // Reseta tudo para permitir uma nova rodada limpa
            OnOff = 0; NB = 0; NA = 0; FC = 0; FH = 0; Agitd = 0; Bomba = 0; Alert = 0;
            printf("\nDigite 1 para continuar: ");
            scanf("%d", &opcao);
        }
    }
    return 0;
}