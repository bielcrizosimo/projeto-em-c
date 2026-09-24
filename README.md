Sistema de Controle Industrial de Caldeira em C

Um sistema robusto de automação discreta e segurança de processos simulado em linguagem C, desenvolvido para o curso Técnico em Mecatrônica pelo SENAI.

Sobre o Projeto ->

Este projeto em C simula o controle automatizado de uma planta industrial de caldeiras. O software gerencia o enchimento de fluidos quente e frio, a homogeneização por agitação mecânica e o esvaziamento por bombeamento

O grande diferencial do algoritmo é a implementação de uma máquina de estados finitos integrada a uma malha de intertravamento de segurança ativo, capaz de detectar falhas físicas em tempo de execução.

Arquitetura de I/O (Mapeamento de 8 Bits)

O estado da planta é representado dinamicamente em tempo real através de um vetor de registradores bit a bit:

Bit 1 | Bit 2 | Bit 3 | Bit 4 | Bit 5 | Bit 6 | Bit 7 | Bit 8

On/Off | N/B | N/A | F_C | F_H | Agitd | Bomba | Alert

Liga/Desliga | Nível Baixo | Nível Alto | Válvula Frio | Válvula Quente | Agitador | Bomba | Emergência

Fluxo de Funcionamento

O ciclo operacional completo exige um tempo de retenção ativa de 100 segundos, divididos em sequências estritas:
- Passos 01 a 05: Inicialização, injeção fracionada de fluido quente (F_H) e frio (F_C), e monitoramento de nível até atingir o limite máximo.
- Passos 06 a 08: Partida do agitador mecânico (Agitd) por 20 segundos para homogeneização e equalização térmica (prevenção contra choques térmicos e cavitação).
- Passos 09 a 11: Acionamento da bomba de recalque (Bomba), escoamento progressivo e finalização do ciclo com segurança.

Engenharia de Segurança: Intertravamento

O software protege a integridade física da caldeira contra falhas de hardware através de uma barreira booleana executada no topo de cada ciclo de varredura:

if ((NB == 0 && NA == 1) || (OnOff == 1 && NB == 1 && NA == 0 && FH == 0 && Agitd == 0)) {
    OnOff = 0;
    Alert = 1;
    continue;
}

- Inconsistência Geométrica: Identifica se o sensor superior indica presença de líquido sem ocupar a base (NB=0 e NA=1), travando o sistema instantaneamente.
- Proteção contra Estado Órfão: Impede inicializações de caldeiras com volume residual desconhecido após quedas de energia.

Como Compilar e Executar

Certifique-se de ter um compilador compatível com ANSI C (como o GCC) instalado em sua máquina.

1. Clone o repositório ou baixe o código-fonte:
git clone https://github.com/bielcrizosimo/projeto-em-c.git

2. Navegue até a pasta do projeto pelo terminal:
cd "projeto-em-c"

3. Compile o programa:
gcc projeto-final-lop.c -o caldeira

4. Execute o binário:
./caldeira

Autor

- Gabriel Crizósimo

Escola SENAI Almirante Tamandaré — Curso Técnico em Mecatrônica
