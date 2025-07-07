#include <stdio.h>
#include <string.h>

void inicializar_arreglo(char *, int);
void lee_original(char *, int *);
void inicializa_alfabeto(char *);
int posicion_caracter(int, int, int);
int verificar_multiplo(char, int);
void decodificar(char *, char *, char *, int);
void graba_mensaje(char *);
void primera_etapa(char *, char *, int);
void segunda_etapa(char *, char *, int);


int main(){
    char original[100];
    char alfabeto[100];
    char codificado[100];
    int N;
    lee_original(original, &N);
    printf("%d#%s\n", N, original);
    inicializa_alfabeto(alfabeto);
    decodificar(original, codificado, alfabeto, N);
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
    char datos[120];
    int i, j;
    archivo = fopen("codificado.txt", "r");
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
    nueva_posicion = posicion + clave;
    if (nueva_posicion >= tam) {
        nueva_posicion -= tam;
    }
    return nueva_posicion;
}

void primera_etapa(char *original, char *codificado, int clave) {
    char alfabeto[48];
    int tamano_alfabeto, i, j;
    tamano_alfabeto = 47;
    i = 0;
    inicializa_alfabeto(alfabeto);
    inicializar_arreglo(codificado, 100);
    while (original[i] != '\0') {
        for(j = 0; j < tamano_alfabeto; j++) {
            if ((original[i] == alfabeto[j])) {
                if (verificar_multiplo(original[i], clave) == 1) {
                    int pos = posicion_caracter(j, clave, tamano_alfabeto);
                    if (j % 2 == 0 || j == 0) {
                        codificado[i] = alfabeto[pos];
                    }
                } else {
                    codificado[i] = original[i];
                }
            } 
        }
        i++;
    }
}

void segunda_etapa(char *precodificado, char *decodificado, int clave) {
    char alfabeto[48], resultado[100], aux[100];
    int tamano_alfabeto, i, j;
    inicializa_alfabeto(alfabeto);
    inicializar_arreglo(resultado, 100);
    tamano_alfabeto = 47;
    i = 0;
    while (precodificado[i] != '\0') {
        for (j = 0; j < tamano_alfabeto; j++) {
            if (precodificado[i] == alfabeto[j]) {
                int pos = posicion_caracter(j, clave, tamano_alfabeto);
                resultado[i] = alfabeto[pos];
            }
        }
        i++;
    }
    snprintf(aux, sizeof(aux), "%d#%s", clave, resultado);
    strcpy(decodificado, aux);
}

void decodificar(char *original, char *codificado, char *alfabeto, int clave) {
    primera_etapa(original, codificado, clave);
    printf("1. original: %s, codificado: %s\n", original, codificado);
    segunda_etapa(codificado, codificado, clave);
    printf("2. original: %s, codificado: %s\n", original, codificado);
}

void graba_mensaje(char *mensaje) {
    FILE *archivo;
    archivo = fopen("decodificado.txt", "w");
    if (archivo != NULL) {
        fprintf(archivo, "%s", mensaje);
        fclose(archivo);
    }
}

int verificar_multiplo(char mensaje, int clave) {
    char alfabeto[48];
    int tamano_alfabeto = 47, retorno, i, j;
    inicializa_alfabeto(alfabeto);
    retorno = 0;
    i = 0;
    for (j = 0; j < tamano_alfabeto; j++) {
        if (mensaje == alfabeto[j] && (j % 2 != 0)) {
            int pos = posicion_caracter(j, clave, tamano_alfabeto);
            //mensaje = alfabeto[pos];
            if (pos % 2 == 0 || pos == 0) {
                retorno = 1;
            }
            printf("%c[%d] -> %c[%d] = %d\n", alfabeto[j], j, alfabeto[pos], pos, retorno);
        }
    }
    return retorno;
}