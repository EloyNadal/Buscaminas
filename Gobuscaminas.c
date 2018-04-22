#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

#define DIM 11

void crearTablero();
void mostrarTablero();
int letraxnum(char letra);
int comprobarBomba();
void colocarBomba();
char numxletra(int num);
void crearTableroJ(char matJ[DIM][DIM], int matCPU[DIM][DIM]);
void mostrarTableroJ(char vectY[], char mat[DIM][DIM], int bombRest);
void crearTableroV(char matV[DIM][DIM], char matJ[DIM][DIM]);
int comprobarBombaChar(char mat[DIM][DIM], int posI, int posJ);
int comprobarBombaV(char mat[DIM][DIM], int posI, int posJ);
void limpiarMatriz(char matV[DIM][DIM], char matJ[DIM][DIM], int posI, int posJ);
int escanearTablero(char matV[DIM][DIM]);
void gameOver(int colorTxt, int colorFnd, int del, char mat[40][35]);

void main(){

	char vectY[DIM] = {" ABCDEFGHIJ"}; 
	int matCPU[DIM][DIM];
	int bombas, posJ, posI, ok, comp, limpio, colorTxt, colorFnd, del;
	char letra;
	char matJ[DIM][DIM], matV[DIM][DIM];
	char matGO[40][35] = {"                              "};
	
	/*
	funcionamiento del random.
	int x;

	srand (time(NULL));
	x = rand() % 11;

	printf("%d",x);*/

	system("COLOR 70");
	colorTxt = 0;
	colorFnd = 112;
	del = 100;
	
	srand (time(NULL));	
	bombas = 10;
	crearTablero(matCPU);
	system("cls");
	printf("\n\n\n\t\t\tCargando\n");
	while (bombas != 0){

		system("cls");
		/*mostrarTablero(vectY, matCPU, bombas); muestra a la cpu creando el tablero*/
		/*printf("Introduce posicion donde colocar bombas.\n");
		scanf("%c%d", &letra, &posJ);
            	posI = letraxnum(letra);
            	fflush(stdin);*/
            	posI = rand() % 11;
            	posJ = rand() % 11;
		ok = comprobarBomba(matCPU, posI, posJ);

            	if (ok == 1){
	            	colocarBomba(matCPU, posI, posJ);
        	    	bombas--;
        	}
            	
	}
	system("cls");
	printf("\n\n\n\t\t\tCargando.\n");
	fflush(stdin);
	/*printf("Pulsar boton para convertir matriz int a char\n");
	scanf("%c", &letra);
	fflush(stdin);*/
	bombas = 10;
	crearTableroJ(matJ, matCPU);
	/*mostrarTableroJ(vectY, matJ, bombas); Muestra la matriz int convertida a char*/

	/*printf("Pulsar para crear la matriz donde jugar.\n");
	scanf("%c", &letra);
	fflush(stdin); para la partida para ver las matrices anteriores creadas*/
	system("cls");
	printf("\n\n\n\t\t\tCargando..\n");		
	crearTableroV(matV, matJ);
	comp = 1;
	
	while (comp == 1){
		system("cls"); /*en cuanto este acabado este system tiene que funcionar*/
		mostrarTableroJ(vectY, matV, bombas);
		printf("Indica la posicion (p.ej. e6), si esta fuera de rango sera para anadir bandera.\n");
		scanf("%c%d", &letra, &posJ);
		posI = letraxnum(letra);
		fflush(stdin);
		if ((posI == -1) || (posJ > 10)){
			printf("Indica posicion donde colocar bandera.\n");
			scanf("%c%d", &letra, &posJ);
			posI = letraxnum(letra);	
			fflush(stdin);
			matV[posI][posJ] = 'P';
			bombas = bombas - 1;
		}
		else{
			ok = comprobarBombaV(matJ, posI, posJ);
			if (ok == 1){
				matV[posI][posJ] = matJ[posI][posJ];
				if (matJ[posI][posJ] == 'x'){
					comp = 0;
					printf("\tHAS TOCADO BOMBA!!\n");
					gameOver(colorTxt, colorFnd, del, matGO);
					system("COLOR 07");
				}
				else{
					limpiarMatriz(matV, matJ, posI, posJ);
					
					
				}
			}
		}
		limpio = escanearTablero(matV);
		if (limpio == 0){
			printf("\tHAS GANADO!!!\n");
			comp = 0;
			system("COLOR 07");
		}
		
			

	}
		
		
		
	
	
}

void crearTablero(int mat[DIM][DIM]){

	int i,j;

	i = 0;
	for (j = 0; j < DIM; j++){
		mat[i][j] = j;
	}
	
	for (i = 1; i < DIM; i++){
		
		for (j = 1; j < DIM; j++){
			mat[i][j] = 0;
		}	
	}
}

void mostrarTablero(char vectY[], int mat[DIM][DIM], int bombRest){

	int i, j;
	
	printf("\n\t\t\tBombas Restantes: %d\n\n", bombRest);

	for (i = 0; i < DIM; i++){

		if (i == 0){
			printf("\t\t\t     ");
			for (j = 1; j < DIM; j++){
				printf("%d  ",mat[i][j]);
			}
			printf("\n");
			
		}
		
		if (i > 0){
			printf("\t\t\t%c", vectY[i]);
		
			printf("    ");
			for (j = 1; j < DIM; j++){
				printf("%d  ", mat[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

int letraxnum(char letra){

	switch (tolower(letra)){
	
		case 'a': return 1;
    		case 'b': return 2;
		case 'c': return 3;
    		case 'd': return 4;
    		case 'e': return 5;
    		case 'f': return 6;
		case 'g': return 7;
    		case 'h': return 8;
    		case 'i': return 9;
    		case 'j': return 10;
    		default: return -1;
    	}
}

int comprobarBomba(int mat[DIM][DIM], int posI, int posJ){

	if ((mat[posI][posJ] != 99) && (posI > 0) && (posJ > 0)){
		return(1);
	}
	else{
		return(-1);
	}
}



void colocarBomba(int mat[DIM][DIM], int posI, int posJ){

	int i, j;
	i = posI;
	
	mat[posI][posJ] = 99;

	if (i > 1){
		for (j = (posJ - 1); j < (posJ + 2); j++){
			if (mat[posI - 1][j] != 99){
				mat[posI - 1][j] = mat[posI - 1][j] + 1;
			}
		}
	}
	if (mat[posI][posJ - 1] != 99){
		mat[posI][posJ - 1] = mat[posI][posJ - 1] + 1;
	}
	if (mat[posI][posJ + 1] != 99){
		mat[posI][posJ + 1] = mat[posI][posJ + 1] + 1;
	}
	if (i < 10){
		for (j = (posJ - 1); j < (posJ + 2); j++){
			if (mat[posI + 1][j] != 99){
				mat[posI + 1][j] = mat[posI + 1][j] + 1;
			}
		}
	}
}

char numxletra(int num){

	switch (num){

		case 0: return '/';	
		case 1: return '1';
    		case 2: return '2';
		case 3: return '3';
    		case 4: return '4';
    		case 5: return '5';
    		case 6: return '6';
		case 7: return '7';
    		case 8: return '8';
    		case 9: return '9';
    		case 10: return '0';
    		case 99: return 'x';
    		default: return 'f';
    	}
}

	

void crearTableroJ(char matJ[DIM][DIM], int matCPU[DIM][DIM]){

	int i, j, num;
	char caracter;

		i = 0;
		for (j = 0; j < DIM; j++){
			num = matCPU[i][j];
			caracter = numxletra(num);
			matJ[i][j] = caracter;
		}
	
		for (i = 1; i < DIM; i++){
		
			for (j = 1; j < DIM; j++){
				caracter = matCPU[i][j];
				matJ[i][j] = numxletra(caracter);
			}	
		}
}

void mostrarTableroJ(char vectY[], char mat[DIM][DIM], int bombRest){

	int i, j;
	
	printf("\n\t\t\tBombas Restantes: %d\n\n", bombRest);

	for (i = 0; i < DIM; i++){

		if (i == 0){
			printf("\t\t\t     ");
			for (j = 1; j < DIM; j++){
				printf("%c  ",mat[i][j]);
			}
			printf("\n");
			
		}
		
		if (i > 0){
			printf("\t\t\t%c", vectY[i]);
		
			printf("    ");
			for (j = 1; j < DIM; j++){
				if (mat[i][j] == 'P'){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 124);/*12 fnegro trojo*/
					printf("%c  ", mat[i][j]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);/*15 fnegro tblanco*/
				}
				else{
				printf("%c  ", mat[i][j]);
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}

void crearTableroV(char matV[DIM][DIM], char matJ[DIM][DIM]){

	int i, j;

	i = 0;
	for (j = 0; j < DIM; j++){
		matV[i][j] = matJ[i][j];
	}
	
	for (i = 1; i < DIM; i++){
		
		for (j = 1; j < DIM; j++){
			matV[i][j] = ' ';
		}	
	}
}

int comprobarBombaV(char mat[DIM][DIM], int posI, int posJ){

	if (((posI > 0) || (posI < 11)) && (posJ > 0) || ((posJ < 11))){
		return(1);
	}
	else{
		return(-1);
	}
}

void limpiarMatriz(char matV[DIM][DIM], char matJ[DIM][DIM], int posI, int posJ){

	int i, j, comp, in, jn, ok, comp2;

	i = 1;
	comp = 1;
	/*matJ es la original, matV es donde juego*/
		/*while (comp == 1){
				comp2 = 1;
				comp = 0;
				if (matJ[posI][posJ] == '/'){
					matJ[posI][posJ] = '-';
					i = posI - 1;
					while (i < (posI + 2) && (comp2 == 1)){
						j = posJ - 1;
						while (j < (posJ + 2) && (comp2 == 1)){
							
								if (matJ[i][j] != 'x'){
									if ((matJ[i][j] == '/') && (matV[i][j] != '-')){ 
										matV[i][j] = '-';
										
										comp2 = 0;
										posI = i;
										posJ = j;
										printf("%d %d\n", posI, posJ);
										printf("si\n");
									
									}
									else{
										
											matV[i][j] = matJ[i][j];
											printf("no\n");
									}
								}
								j++;
							
						}
						i++;
					}
				comp = 1;
				}
		}*/
		while (comp == 1){
			i = 1;
			comp = 0;
			while(i < DIM){
			
				j = 1;

				while(j < DIM){

					if ((matV[i][j] == '/') || (matV[i][j] == '-')){
						matV[i][j] = '-';
						in = i;
						jn = j;

						while ((i > 1) && (matJ[i][j] == '/')){
							i--;
							if ((matV[i][j] == ' ') && (matJ[i][j] != 'x')){
								matV[i][j] = matJ[i][j];
								if (matV[i][j] == '/'){
									matV[i][j] = '-';
								}
								comp = 1;
							}
						}
						i = in;
						while ((i < 10) && (matJ[i][j] == '/')){
							i++;
							if ((matV[i][j] == ' ') && (matJ[i][j] != 'x')){
								matV[i][j] = matJ[i][j];
								if (matV[i][j] == '/'){
									matV[i][j] = '-';
								}
								comp = 1;
							}
						}
						i = in;
						while ((j > 1) && (matJ[i][j] == '/')){
							j--;
							if ((matV[i][j] == ' ') && (matJ[i][j] != 'x')){
								matV[i][j] = matJ[i][j];
								if (matV[i][j] == '/'){
									matV[i][j] = '-';
								}
								comp = 1;
							}
						}
						j = jn;
						while ((j < 10) && (matJ[i][j] == '/')){
							j++;
							if ((matV[i][j] == ' ') && (matJ[i][j] != 'x')){
								matV[i][j] = matJ[i][j];
								if (matV[i][j] == '/'){
									matV[i][j] = '-';
								}
								comp = 1;
							}
						}
						j = jn;
					}
					j++;
				}
				i++;
			
			}
						
							
	}
}

int escanearTablero(char matV[DIM][DIM]){

	int i, j, comp;

	comp = 0;
	i = 1;
	while ((i < DIM) && (comp == 0)){
		j = 1;
		while ((j < DIM) && (comp == 0)){
			if (matV[i][j] == ' '){
				comp = 1;
			}
			j++;
		}
		i++;
	}
	return(comp);
}

void gameOver(int colorTxt, int colorFnd, int del, char mat[40][35]){

int i,j;

for(i = 0; i < 40; i++){
		printf("\n");
	}
	i = 0;
	printf("\t\t\t\t\t");
	Sleep(del);
	for (j = 0; j < 30; j++){

		if (((j > 0) && (j < 5)) || (j == 9) || (j == 14) || (j == 18) || ((j > 20) && (j < 26)))  {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTxt);
		}
		printf("%c",mat[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFnd);
	}
	printf("\n");
	i = 1;
	printf("\t\t\t\t\t");
	Sleep(del);
	for (j = 0; j < 30; j++){

		if ((j == 0) || (j == 8) || (j == 10) || (j == 14) || (j == 15) || (j == 17) || (j == 18) || (j == 21)){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTxt);
		}
		printf("%c",mat[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFnd);
	}
	printf("\n");
	i = 2;
	printf("\t\t\t\t\t");
	Sleep(del);
	for (j = 0; j < 30; j++){

		if ((j == 0) || (j == 3) || (j == 4) || (j == 7) || (j == 11) || (j == 14) || (j == 16) || (j == 18) || ((j > 20) && (j < 24))){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTxt);
		}
		printf("%c",mat[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFnd);
	}
	printf("\n");
	i = 3;
	printf("\t\t\t\t\t");
	Sleep(del);
	for (j = 0; j < 30; j++){

		if ((j == 0) || (j == 4) || ((j > 6) && (j < 12)) || (j == 14) || (j == 18) || (j == 21)){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTxt);
		}
		printf("%c",mat[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFnd);
	}
	printf("\n");
	i = 4;
	printf("\t\t\t\t\t");
	Sleep(del);
	for (j = 0; j < 30; j++){

		if (((j > 0) && (j < 5)) || (j == 7) || (j == 11) || (j == 14) || (j == 18) || ((j > 20) && (j < 26))){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTxt);
		}
		printf("%c",mat[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFnd);
	}
	Sleep(del);
	printf("\n");
	Sleep(del);
	printf("\n");
	i = 5;
	printf("\t\t\t\t\t");
	Sleep(del);
	for (j = 0; j < 30; j++){

		if (((j > 0) && (j < 4)) || (j == 7) || (j == 11) || ((j > 13) && (j < 19)) || ((j > 20) && (j < 25))){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTxt);
		}
		printf("%c",mat[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFnd);
	}
	printf("\n");
	i = 6;
	printf("\t\t\t\t\t");
	Sleep(del);
	for (j = 0; j < 30; j++){

		if ((j == 0) || (j == 4) || (j == 7) || (j == 11) || (j == 14) || (j == 21) || (j == 25)){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTxt);
		}
		printf("%c",mat[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFnd);
	}
	printf("\n");
	i = 7;
	printf("\t\t\t\t\t");
	Sleep(del);
	for (j = 0; j < 30; j++){

		if ((j == 0) || (j == 4) || (j == 7) || (j == 11) || ((j > 13) && (j < 17)) || ((j > 20) && (j < 25))){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTxt);
		}
		printf("%c",mat[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFnd);
	}
	printf("\n");
	i = 8;
	printf("\t\t\t\t\t");
	Sleep(del);
	for (j = 0; j < 30; j++){

		if ((j == 0) || (j == 4) || (j == 8) || (j == 10) || (j == 14) || (j == 21) || (j == 25)){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTxt);
		}
		printf("%c",mat[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFnd);
	}
	printf("\n");
	i = 9;
	printf("\t\t\t\t\t");
	Sleep(del);
	for (j = 0; j < 30; j++){

		if (((j > 0) && (j < 4)) || (j == 9) || ((j > 13) && (j < 19)) || (j == 21) || (j == 25)){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTxt);
		}
		printf("%c",mat[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorFnd);
	}



	
	for(i = 0; i < 10; i++){
			Sleep(del);
			printf("\n");
	}
	
	system("Pause");
}

			
	
