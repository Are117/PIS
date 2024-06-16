#include <stdio.h>
#include <math.h>
#include <time.h>

// Función para contar los días de un mes
int conteoDiasMes(int mes) {
    int diasPorMes = 31;
    if (mes == 2) {
        diasPorMes = 29;
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasPorMes = 30;
    }
    return diasPorMes;
}

// Función para calcular los días totales entre meses
int calculoEntreMeses(int mesInicial, int mesActual, int diaInicial, int diaActual) {
    int diasTotalesEntreMeses = 0;
    int diasEntreMeses = 0;
    int mesRecorrido = mesInicial;
    int diasMesInicial = conteoDiasMes(mesInicial);
    
    for (mesRecorrido = mesInicial; mesRecorrido < mesActual; mesRecorrido++) {
        diasEntreMeses += conteoDiasMes(mesRecorrido);
    }
    
    diasTotalesEntreMeses = diasEntreMeses - diaInicial + diaActual;
    return diasTotalesEntreMeses;
}

int main() {
    double Latid, Longi;
    printf("Calcularemos la orientación del Sol e inclinación del Panel Solar\n");
    printf("Ingresa primero la Latitud y Longitud para proseguir con el cálculo\n");
    printf("Ingresa la Latitud: ");
    scanf("%lf", &Latid);
    printf("Ingresa la Longitud: ");
    scanf("%lf", &Longi);

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

    int n = calculoEntreMeses(mesInicial, mesActual, diaInicial, diaActual);

    // Declinación del sol
    double PI = 3.14;
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
    printf("La altura del sol es %.2f y tiene una orientación de %.2f grados respecto al norte\n", angulogrados, azimuthgrados);

    return 0;
}