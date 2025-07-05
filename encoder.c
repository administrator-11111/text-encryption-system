#include <stdio.h>
#include <string.h>
#define ORIGINAL 100
#define ALFABETO 100
#define CODIFICADO 100

void lee_original(char *, int *);
void inicializa_alfabeto(char *);
void codificar(char *, char *, char *, int);
void graba_mensaje(char *);

int main(){
    char original[100];
    char alfabeto[100];
    char codificado[100];
    int N;
    lee_original(original, &N);
    inicializa_alfabeto(alfabeto);
    codificar(original, codificado, alfabeto, N);
    graba_mensaje(codificado);
    return 0;
}

void lee_original(char *original, int *clave) {
    FILE *archivo;
    char datos[ORIGINAL];
    int i, j;
    archivo = fopen("original.txt", "r");
    j = 0;
    *clave = 0;

    for(i = 0; i < ORIGINAL; i++) {
        original[i] = '\0'; 
    }
    i = 0;
    if (archivo != NULL) {
        fgets(datos, ORIGINAL, archivo);
        
        while (!feof(archivo)) {
            // Aquí se obtiene el número
            while(datos[i] >= '0' && datos[i] <= '9') {
                *clave = (*clave * 10) + (datos[i] - '0');
                i++;
            }
            if (datos[i] == '#') i++;
            while (datos[i] != '\0') {
                original[j] = datos[i];
                i++;
                j++;
            }
        }
    }
    fclose(archivo);
}

void inicializa_alfabeto(char *alfabeto) {
    char pre_alfabeto[47] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8',
        '9', '!', ',', '.', ':', ';', '?', '-', '+', '*', '/'}; 
    int i;
    for(i = 0; i < strlen(pre_alfabeto); i++) {
        alfabeto[i] = pre_alfabeto[i]; 
    }
    while (i < 100) {
        alfabeto[i] = '\0';
        i++;
    }
}

void codificar(char *, char *, char *, int) {
    return 0;
}
void graba_mensaje(char *) {
    return 0;
}