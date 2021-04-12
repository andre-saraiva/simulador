Para compilar:

# gcc bd2_r.c -o bd2 -lgsl -lm -lgslcblas


Para executar:

# ./bd2 7,3,1,0,1,3 9,4,1,0,1,4,7 1,0,1 5 teste 1 63

7,3,1,0,1,3 = Primeiro BD no formato v,k,lambda, primeiroSlotAtivo, segundoSlotAtivo,...
9,4,1,0,1,4,7 = Segundo BD no formato v,k,lambda, primeiroSlotAtivo, segundoSlotAtivo, terceiroSlotAtivo,...
1,0,1 = Conjunto de probabilidades de entrega do enlace P no formato: p_inicial (probabilidade inicial), incremento, p_final (probabilidade final)
5 = número de repetições
teste = prefixo do arquivo de saída
1 = número de saltos
21 = mmc 


Este comando faria 5 simulações (para p = 0,2; p = 0,4; p = 0,6; p = 0,8 e p = 1,0) com dois nós executando o block design 7,3,1 (que tem ciclos de três slots com os slots 0,1 e 3 ativos em cada ciclo). Para cada simulação, são executadas 5 repetições e os valores de NDT (em slots) são impressos nos arquivos "simulacoes_bd_0.200000.txt", "simulacoes_bd_0.400000.txt", "simulacoes_bd_0.600000.txt", ...

Instalação da Biblioteca LIBGSL

sudo apt-get install libgsl-dev
