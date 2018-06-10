# Semaforo-Arduino

Se trata de un mini proyecto que hice para probar y aprender a programar Arduino.

Este semáforo no cambia por periodos de tiempo, cambia según como se interactúe con el.

El ciclo empieza con el semáforo para peatones en verde con el Buzzer pitando intermitentemente para que los peatones invidentes sepan que pueden pasar mientras que el semáforo de coches se encuentra en rojo. Para que el semáforo de coches cambie se usa el sensor de ultrasonido que mide la distancia en un área para saber si existen coches detenidos esperando para ello también se tiene que cumplir una regla de 6 segundos seguidos a menos de esa distancia. En este caso y como es un ejemplo puse que si la distancia es menor a 100 centímetros durante 6 segundos cambiara. Una vez se encuentre en verde el semáforo de coches y en rojo el de peatones para que cambie otra vez el peatón tendrá que pulsar el botón.
Los procesos de cambios no son inmediatos una vez accionados tardan 5 segundos en cambiar de verde a rojo además entre los cambios de semáforo a semáforo se aplica un segundo y medio mas.

Componentes 
-	Placa de Elegoo uno R3 
-	Sensor de ultrasonido HC-SR04
-	Botón  (Pequeño)
-	Buzzer pasivo
-	5 Led 
-	5 resistencias 220 ohmios
-	1 resistencia 10k ohmios
