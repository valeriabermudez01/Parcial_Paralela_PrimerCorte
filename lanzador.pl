#!/usr/bin/perl

########################################################################################
# Fecha: 17 febrero 2022
# Materia: Parallel Computing
# Tema: Diseño de Experimentos, Automatización de ejecución (promedio y desviación)
########################################################################################


$PATH = `pwd`;
chomp($PATH);
# Variable que represente la cantidad de repeticiones
$N = 31;
#Se crea un vector de ejecutables

@ejecutables = ('bench01','bench02','bench03');
#Se crea un vector de Dimensiones NXN

@dimension = ("400","600","1000","2000");

foreach $exe (@ejecutables){
    foreach $size (@dimension){
        $File="$PATH/"."soluciones/"."$exe"."-$size".".txt";
	#print"$File \n";
	for($i=0;$i<$N;$i++){
		system "$PATH/$exe $size >> $File";
			
	}
    }
    close($File);
}

