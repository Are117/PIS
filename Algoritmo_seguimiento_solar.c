#include <stdio.h>
#include <math.h>
#include <time.h>

// Función para contar los días de un mes
int conteoDiasMes(int mes, int anio) {
    int diasPorMes = 31;  // Inicialmente se asume que el mes tiene 31 días
    if (mes == 2) {
        // Comprobar si el año es bisiesto
        if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
            diasPorMes = 29;  // Año bisiesto
        } else {
            diasPorMes = 28;  // Año no bisiesto
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasPorMes = 30;  // Meses con 30 días (Abril, junio, septiembre y noviembre)
    }
    return diasPorMes;  // Devuelve el número de días del mes
}

// Función para calcular los días totales entre meses
int calculoEntreMeses(int mesInicial, int mesActual, int diaInicial, int diaActual, int anio) {
    int diasTotalesEntreMeses = 0;
    int diasEntreMeses = 0;
    int mesRecorrido = mesInicial;

    for (mesRecorrido = mesInicial; mesRecorrido < mesActual; mesRecorrido++) {
        diasEntreMeses += conteoDiasMes(mesRecorrido, anio);
    }
    
    diasTotalesEntreMeses = diasEntreMeses - diaInicial + diaActual;
    return diasTotalesEntreMeses;
}

int main() {
    double Latid, Longi;
    char buffer[100];
    
    printf("Calcularemos la orientacion del Sol e inclinacion del Panel Solar\n");
    
    // Obtener la Latitud
    while (1) {
        printf("Ingresa la Latitud: ");
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%lf", &Latid) == 1) {
                break;  // Si se pudo leer correctamente, salir del bucle
            } else {
                printf("El Dato ingresado no es valido.\n");
            }
        }
    }
    
    // Obtener la Longitud
    while (1) {
        printf("Ingresa la Longitud: ");
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%lf", &Longi) == 1) {
                break;  // Si se pudo leer correctamente, salir del bucle
            } else {
                printf("El Dato ingresado no es valido.\n");
            }
        } 
    }

    // Obtener la fecha y la hora actual
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    int anioActual = tm->tm_year + 1900;
    int mesActual = tm->tm_mon + 1;
    int diaActual = tm->tm_mday;
    
    int hora = tm->tm_hour;
    int minutos = tm->tm_min;
    int segundos = tm->tm_sec;
    
    int mesInicial = 1;
    int diaInicial = 1; // Suponiendo que queremos contar desde el primer día del primer mes

    int n = calculoEntreMeses(mesInicial, mesActual, diaInicial, diaActual, anioActual);

    // Declinación del sol
    double PI = 3.14159265358979323846; // Mejor usar M_PI definido en math.h
    double dcoseno = ((360.0 / 365.0) * (n + 10)) * PI / 180.0;
    double declinacionsolar = -23.44 * cos(dcoseno);

    // Anomalía solar
    double B = ((360.0 / 365.0) * (n - 81)) * PI / 180.0;

    // Ecuación del tiempo
    double Eot = 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B);

    // Hora local
    double HoraLocal = hora + (minutos / 60.0);

    // Zona horaria y longitud estándar
    int ZonaHoraria = -5;
    int LongituEstandar = ZonaHoraria * 15;

    // Tiempo solar verdadero
    double tsvPre = 4 * (Longi - LongituEstandar) + Eot;
    double tsvPree = tsvPre / 60.0;
    double Tsv = HoraLocal + tsvPree;

    // Ángulo horario solar
    double H = ((15 * (Tsv - 12)) * PI / 180.0);

    // Ángulo de inclinación del sol
    double Latitudrad = Latid * PI / 180.0;
    double declinacionsolarRad = declinacionsolar * PI / 180.0;
    double angulo = asin(sin(declinacionsolarRad) * sin(Latitudrad) + cos(declinacionsolarRad) * cos(Latitudrad) * cos(H));
    double angulogrados = angulo * 180.0 / PI;

    // Azimuth
    double azimuth = (sin(declinacionsolarRad) - sin(angulo) * sin(Latitudrad)) / (cos(angulo) * cos(Latitudrad));
    double azimuth2 = acos(azimuth);
    if (H > 0) {
        azimuth2 = (2 * PI) - azimuth2;
    }
    double azimuthgrados = azimuth2 * 180.0 / PI;

    // Resultados
    printf("La altura del sol es %.2f grados y tiene una orientacion de %.2f grados respecto al norte\n", angulogrados, azimuthgrados);

    return 0;
}
