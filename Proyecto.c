#include <stdio.h>

#define MAX_OYENTES 100
#define NUM_CANCIONES 10

// Funciones para cada inciso
void leerVotos(int votos[MAX_OYENTES][3], int *total_oyentes);
void calcularResultados(int votos[MAX_OYENTES][3], int total_oyentes, int *ganador1, int *ganador2);
void calcularGanadorPremio(int votos[MAX_OYENTES][3], int total_oyentes, int ganador1, int ganador2);

int main() {
    int votos[MAX_OYENTES][3];
    int total_oyentes = 0;
    int cancion1, cancion2;

    printf("=== REGISTRO DE VOTOS ===\n");
    printf("Ingresa los votos en tríos (Cancion1 Cancion2 Cancion3). Ingresa -1 para terminar.\n\n");

    // 1. Leer y almacenar votos
    leerVotos(votos, &total_oyentes);

    if (total_oyentes == 0) {
        printf("No se registraron votos.\n");
        return 0;
    }

    // 2. Calcular votos y obtener las dos más votadas
    calcularResultados(votos, total_oyentes, &cancion1, &cancion2);

    // 3. Calcular el oyente ganador del premio
    calcularGanadorPremio(votos, total_oyentes, cancion1, cancion2);

    return 0;
}

void leerVotos(int votos[MAX_OYENTES][3], int *total_oyentes) {
    int c1, c2, c3;
    while (*total_oyentes < MAX_OYENTES) {
        printf("Oyente %d: ", *total_oyentes);
        scanf("%d %d %d", &c1, &c2, &c3);

        if (c1 == -1) {
            break; // Condición de salida
        }

        votos[*total_oyentes][0] = c1;
        votos[*total_oyentes][1] = c2;
        votos[*total_oyentes][2] = c3;
        (*total_oyentes)++;
    }
}

void calcularResultados(int votos[MAX_OYENTES][3], int total_oyentes, int *ganador1, int *ganador2) {
    int puntajesCanciones[NUM_CANCIONES] = {0};

    // Sumar los puntos de cada canción
    for (int i = 0; i < total_oyentes; i++) {
        puntajesCanciones[votos[i][0]] += 3; // 1er lugar
        puntajesCanciones[votos[i][1]] += 2; // 2do lugar
        puntajesCanciones[votos[i][2]] += 1; // 3er lugar
    }

    printf("\n=== RESULTADOS DE LAS CANCIONES ===\n");
    for (int i = 0; i < NUM_CANCIONES; i++) {
        printf("Cancion %d: %d votos\n", i, puntajesCanciones[i]);
    }

    // Encontrar la 1ra y 2da canción más votada
    int max1 = -1, max2 = -1;
    *ganador1 = -1;
    *ganador2 = -1;

    for (int i = 0; i < NUM_CANCIONES; i++) {
        if (puntajesCanciones[i] > max1) {
            max2 = max1;
            *ganador2 = *ganador1;
            max1 = puntajesCanciones[i];
            *ganador1 = i;
        } else if (puntajesCanciones[i] > max2) {
            max2 = puntajesCanciones[i];
            *ganador2 = i;
        }
    }

    printf("\n1ra canción: %d\n", *ganador1);
    printf("2da canción: %d\n", *ganador2);
}

void calcularGanadorPremio(int votos[MAX_OYENTES][3], int total_oyentes, int cancion1, int cancion2) {
    int puntosOyente[MAX_OYENTES] = {0};
    int maxPuntos = -1;
    int oyenteGanador = -1;

    printf("\n=== PUNTOS DE LOS OYENTES ===\n");
    for (int i = 0; i < total_oyentes; i++) {
        int puntosActuales = 0;
        int voto1 = votos[i][0];
        int voto2 = votos[i][1];
        int voto3 = votos[i][2];

        // 30 puntos si está la canción 1
        if (voto1 == cancion1 || voto2 == cancion1 || voto3 == cancion1) {
            puntosActuales += 30;
        }

        // 20 puntos si está la canción 2
        if (voto1 == cancion2 || voto2 == cancion2 || voto3 == cancion2) {
            puntosActuales += 20;
        }

        // 10 puntos suplementarios si acertó ambos títulos
        int acerto1 = (voto1 == cancion1 || voto2 == cancion1 || voto3 == cancion1);
        int acerto2 = (voto1 == cancion2 || voto2 == cancion2 || voto3 == cancion2);
        if (acerto1 && acerto2) {
            puntosActuales += 10;
        }

        puntosOyente[i] = puntosActuales;
        printf("Oyente %d: %d puntos\n", i, puntosOyente[i]);

        // Verificamos quién tiene el puntaje más alto
        if (puntosOyente[i] > maxPuntos) {
            maxPuntos = puntosOyente[i];
            oyenteGanador = i;
        }
    }

    printf("\n👑 GANADOR DEL PREMIO: El oyente numero %d con %d puntos\n", oyenteGanador, maxPuntos);
}
