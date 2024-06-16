# ALGORITMO DE SEGUIMIENTO SOLAR

## Descripción del Proyecto
Es comúnmente conocido que el rumbo aparente del sol cambia con los días. Esto se debe principalmente a la duración del día a lo largo del año y los ángulos de declinación, de altitud, de azimut entre otros. La variación del rumbo del sol se convierte en la principal problemática a resolver para que nuestro prototipo sea eficiente. La radiación solar es captada de mejor manera cuando la placa solar está en dirección perpendicular a los rayos del sol. Para conseguir lo anteriormente mencionado, es necesario idear un algoritmo que considere todas las variaciones anteriormente descritas y consiga que el prototipo se mueva siguiendo las diferentes rotaciones del sol para lograr una dirección perpendicular a lo largo del día todos los meses del año.
## Requisitos
El algoritmo necesita 2 datos ingresados por el usuario:
- Latitud
- Longitud

Datos que adquiere por medio del sistema:
- Hora actuales
- Minutos actuales
- Segundos actuales
- Fecha actual en día, mes y año

En cuanto al software, se necesita:
- El sensor de luz
- El servomotor
- El Arduino
- El panel solar.

## Instrucciones de Instalación
## Uso
Al ejecutar el algpritmo, nos pedirá ingresar los valores de longitud y latitud.
a continuación presentamos un ejemplo de estos valores para calcular la altitud e inclinación solar en el campus de la UNL:
- Longitud:-79.199453
- Latitud:-4.030216

al ingresar los valores, el algoritmo  mostrará en pantalla la altitud e inclinación solar, tomando como punto de referencia las coordenadas ingresadas 
