#Script para gráficos no GNUPlot
reset
# Inserido para dar suporte a coisas como 10^6 nos labels
#set decimal locale
set termopt enhanced
set encoding iso_8859_1
set datafile missing '-'
# Em Gráficos para artigos, nao coloque títulos
#set title 'DC 5.86% to DC 42.85%' 
set ylabel 'Energy consumption'
set xlabel 'Duty Cycle'
#set   autoscale                        # scale axes automatically
#unset log                              # remove any log-scaling
#set logscale x
unset label                            # remove any previous labels
#set xtic (5,10,15,20,25,30,35,40,45)                         # set xtics manualmente
set ytic auto                          # set ytics automatically
set xtic auto
#set ytic (400,600,800,1000,1200,1400,1600,1800)

set style line 1 lc rgb '#DAA520' lt 1 lw 2 pt 3 ps 1.5   # 5 quadrado, 6 circulo, 3 estrela , 7 bola
set style line 2 lc rgb '#FF0000' lt 1 lw 2 pt 5 ps 1.5   
set style line 3 lc rgb '#4682B4' lt 1 lw 2 pt 6 ps 1.5 
set style line 4 lc rgb '#008B8B' lt 1 lw 2 pt 7 ps 1.5 
set style line 5 lc rgb '#4B0082' lt 1 lw 2 pt 1 ps 1.5 


#wl significa with line

# Inserido para evitar que barras de erro façam valores negativos aparecerem no eixo-y:
set yrange [0:*]

# Control the look of the error bars
#set errorbars linecolor black
#set bars front

set terminal png size 800,600 enhanced font "Arial,16"  
set output 'energia.png' # setando o nome da saída

set key center top inside #legenda do lado esquerdo

#f(x) = x


plot "teste - energia.dat" using ($1):($2) title "DC 10.98%" with linespoints ls 1, \
"teste - energia.dat" using ($1):($3) title "DC 5.86%%" with linespoints ls 2, \

#plot "teste - energia.dat" using ($1):($2) title "DC 42.85%" with linespoints ls 1, \
#"prob-normal.dat" using ($1):($2):($3) notitle with yerrorbars,\
#"prob-normal.dat" using ($1):($4) title "DC 100%" with linespoints ls 2, \
#"prob-normal.dat" using ($1):($4):($5) notitle with yerrorbars,\
#"prob-normal.dat" using ($1):($6) title "DC 7.65%"  with linespoints ls 3, \
#"prob-normal.dat" using ($1):($6):($7) notitle with yerrorbars,\
#"prob-normal.dat" using ($1):($8) title "DC 6.22%"  with linespoints ls 4, \
#"prob-normal.dat" using ($1):($8):($9) notitle with yerrorbars

#"teste-DC-2-er.dat" using ($1):($10) title "DC 5.86%"  with linespoints ls 5, \
#"teste-DC-2-er.dat" using ($1):($10):($11) notitle with yerrorbars

