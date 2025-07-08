#include <stdio.h>
#include <string.h>

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

void inicializar_arreglo(char *arreglo, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        arreglo[i] = '\0';
    }
}

void lee_original(char *original, int *clave) {
    FILE *archivo;
    char datos[100];
    int i, j;
    archivo = fopen("original.txt", "r");
    i = 0;
    j = 0;
    *clave = 0;
    if (archivo != NULL) {
        fgets(datos, sizeof(datos), archivo);
        while (datos[i] >= '0' && datos[i] <= '9') {
            *clave = (*clave * 10) + (datos[i] - '0');
            i++;
        }
        if (datos[i] == '#') i++;
        while (datos[i] != '\0') {
            original[j] = datos[i];
            i++;
            j++;
        }
        original[j] = '\0';
        fclose(archivo);
    }
}

void inicializa_alfabeto(char *alfabeto) {
    char pre_alfabeto[48] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8',
        '9', '!', ',', '.', ':', ';', '?', '-', '+', '*', '/', '\0'}; 
    int i;
    for (i = 0; i < 48; i++) {
        alfabeto[i] = pre_alfabeto[i]; 
    }
}

int posicion_caracter(int posicion, int clave, int tam) {
    int nueva_posicion;
    nueva_posicion = (posicion - (clave % tam) + tam) % tam;
    return nueva_posicion;
}

void primera_etapa(char *original, char *codificado, int clave) {
    char alfabeto[48];
    int tamano_alfabeto, i, j;
    inicializa_alfabeto(alfabeto);
    tamano_alfabeto = 47;
    for (i = 0; i < 100; i++) {
        codificado[i] = original[i];
    }
    i = 0;
    while (original[i] != '\0') {
        for (j = 0; j < tamano_alfabeto; j++) {
            if (original[i] == alfabeto[j]) {
                int pos = posicion_caracter(j, clave, tamano_alfabeto);
                codificado[i] = alfabeto[pos];
                break;
            }
        }
        i++;
    }
}

void segunda_etapa(char *modificado, char *codificado, int clave) {
    char alfabeto[48], aux[100];
    int tamano_alfabeto, i, j;
    inicializa_alfabeto(alfabeto);
    tamano_alfabeto = 47;
    for ( i = 0; i < 100; i++){
        modificado[i] = '0';
    }
    i = 0;
    while (codificado[i] != '\0') {
        for(j = 0; j < tamano_alfabeto; j++) {
            if ((codificado[i] == alfabeto[j]) && (j % 2 == 0 || j == 0)) {
                int pos = posicion_caracter(j, clave, tamano_alfabeto);
                codificado[i] = alfabeto[pos];
                modificado[i] = '1';
                break;
            }
        }
        i++;
    }
    snprintf(aux, sizeof(aux), "%d#%s", clave, codificado);
    strcpy(codificado, aux);
}

void codificar(char *original, char *codificado, char *alfabeto, int clave) {
    char modificado[100];
    int i;
    FILE *archivo;
    archivo = fopen("codificado.txt", "w");
    primera_etapa(original, codificado, clave);
    segunda_etapa(modificado, codificado, clave);
    for ( i = 0; i < 100; i++){
        fprintf(archivo, "%c", modificado[i]);
    }
    fclose(archivo);
}

void graba_mensaje(char *mensaje) {
    FILE *archivo;
    archivo = fopen("codificado.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "\n");
        fprintf(archivo, "%s", mensaje);
        fclose(archivo);
    }
}