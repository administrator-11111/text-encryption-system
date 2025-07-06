#include <stdio.h>
#include <string.h>

void lee_original(char *, int *);
void inicializa_alfabeto(char *);
int posicion_caracter(int, int, int);
void primera_etapa(char *, char *, int);
void segunda_etapa(char *, char *, int);
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
    tamano_alfabeto = strlen(alfabeto);
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

void segunda_etapa(char *precodificado, char *codificado, int clave) {
    char alfabeto[48], aux[100];
    int tamano_alfabeto, i, j;
    inicializa_alfabeto(alfabeto);
    tamano_alfabeto = strlen(alfabeto);
    i = 0;
    while (precodificado[i] != '\0') {
        for(j = 0; j < tamano_alfabeto; j++) {
            if ((precodificado[i] == alfabeto[j]) && (j % 2 == 0 || j == 0)) {
                int pos = posicion_caracter(j, clave, tamano_alfabeto);
                codificado[i] = alfabeto[pos];
                break;
            } 
        }
        i++;
    }
    snprintf(aux, sizeof(aux), "%d#%s", clave, codificado);
    strcpy(codificado, aux);
}

void codificar(char *original, char *codificado, char *alfabeto, int clave) {
    inicializar_arreglo(codificado, strlen(codificado));
    primera_etapa(original, codificado, clave);
    segunda_etapa(codificado, codificado, clave);
}

void graba_mensaje(char *mensaje) {
    FILE *archivo;
    archivo = fopen("codificado.txt", "w");
    if (archivo != NULL) {
        fprintf(archivo, "%s", mensaje);
        fclose(archivo);
    }
}