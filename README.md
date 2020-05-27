Para compilar:

# gcc bd2_r.c -o bd2 -lgsl -lm -lgslcblas


Para executar:

# ./bd2 3,2,1,0,1 7,3,1,0,1,3 1,0,1 1 teste 1 21

3,2,1,0,1 = Primeiro BD no formato v,k,lambda, primeiroSlotAtivo, segundoSlotAtivo,...
7,3,1.0.1.3 = Segundo BD no formato v,k,lambda, primeiroSlotAtivo, segundoSlotAtivo, terceiroSlotAtivo,...
1,0,1 = Conjunto de probabilidades de entrega do enlace P no formato: p_inicial (probabilidade inicial), incremento, p_final (probabilidade final)
1 = número de repetições
teste = prefixo do arquivo de saída
1 = número de saltos
21 = mmc 
