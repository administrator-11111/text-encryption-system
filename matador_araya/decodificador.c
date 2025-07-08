#include <stdio.h>
#include <string.h>

void inicializar_arreglo(char *, int);
void lee_original(char *, int *, char *);
void inicializa_alfabeto(char *);
int posicion_caracter_inversa(int, int, int);
void segunda_etapa_inversa(char *, char *, int, char *);
void primera_etapa_inversa(char *, char *, int);
void decodificar(char *, char *, char *, int, char *);
void graba_mensaje(char *);


int main(){
    char original[100];
    char alfabeto[100];
    char decodificado[100];
    char modificacion[100];
    int N;

    lee_original(original, &N, modificacion);
    inicializa_alfabeto(alfabeto);
    decodificar(original, decodificado, alfabeto, N, modificacion);
    graba_mensaje(decodificado);
    return 0;
}

void inicializar_arreglo(char *arreglo, int tam) {
    for (int i = 0; i < tam; i++) {
        arreglo[i] = '\0';
    }
}

void lee_original(char *mensaje, int *clave, char *modificado) {
    FILE *archivo;
    char linea1[120], linea2[120];
    int i = 0, j = 0;

    archivo = fopen("codificado.txt", "r");
    if (archivo != NULL) {
        fgets(linea1, sizeof(linea1), archivo);  // Línea de pares modificados
        fgets(linea2, sizeof(linea2), archivo);  // Línea del mensaje con clave

        // Guardar vector de pares modificados
        strncpy(modificado, linea1, 100);

        // Extraer clave y mensaje
        i = 0;
        *clave = 0;
        while (linea2[i] >= '0' && linea2[i] <= '9') {
            *clave = (*clave * 10) + (linea2[i] - '0');
            i++;
        }
        if (linea2[i] == '#') i++;
        while (linea2[i] != '\0' && linea2[i] != '\n') {
            mensaje[j++] = linea2[i++];
        }
        mensaje[j] = '\0';
        fclose(archivo);
    }
}

void inicializa_alfabeto(char *alfabeto) {
    char pre_alfabeto[48] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8',
        '9', '!', ',', '.', ':', ';', '?', '-', '+', '*', '/', '\0'}; 
    for (int i = 0; i < 48; i++) {
        alfabeto[i] = pre_alfabeto[i]; 
    }
}

int posicion_caracter_inversa(int posicion, int clave, int tam) {
    return (posicion + (clave % tam)) % tam;
}

// Revierte la segunda etapa usando el vector de modificación
void segunda_etapa_inversa(char *codificado, char *resultado, int clave, char *modificado) {
    char alfabeto[48];
    int tamano_alfabeto = 47;
    inicializa_alfabeto(alfabeto);
    int i = 0, j;

    while (codificado[i] != '\0') {
        resultado[i] = codificado[i];  // por defecto sin cambio
        if (modificado[i] == '1') {
            for (j = 0; j < tamano_alfabeto; j++) {
                if (codificado[i] == alfabeto[j]) {
                    int pos = posicion_caracter_inversa(j, clave, tamano_alfabeto);
                    resultado[i] = alfabeto[pos];
                    break;
                }
            }
        }
        i++;
    }
    resultado[i] = '\0';
}

// Revierte la primera etapa completa
void primera_etapa_inversa(char *entrada, char *salida, int clave) {
    char alfabeto[48], aux[100];
    int tamano_alfabeto = 47;
    inicializa_alfabeto(alfabeto);
    int i = 0, j;

    while (entrada[i] != '\0') {
        for (j = 0; j < tamano_alfabeto; j++) {
            if (entrada[i] == alfabeto[j]) {
                int pos = posicion_caracter_inversa(j, clave, tamano_alfabeto);
                aux[i] = alfabeto[pos];
                break;
            }
        }
        i++;
    }
    aux[i] = '\0';
    snprintf(salida, 100, "%d#%s", clave, aux);
}

void decodificar(char *original, char *decodificado, char *alfabeto, int clave, char *modificado) {
    char paso1[100];
    segunda_etapa_inversa(original, paso1, clave, modificado);
    primera_etapa_inversa(paso1, decodificado, clave);
}

void graba_mensaje(char *mensaje) {
    FILE *archivo = fopen("decodificado.txt", "w");
    if (archivo != NULL) {
        fprintf(archivo, "%s", mensaje);
        fclose(archivo);
    }
}