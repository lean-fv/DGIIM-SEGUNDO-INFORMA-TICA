-Indicar algunos de los posibles momentos en los que se invoca el planificador() en el código del SO. ¿Qué acciones previas se deberán haber realizado?
    Al entrar un proceso en la cola de preparados -debe haberse incializado el PCB
    Cuando se activa la E/S -la RSI (rutina de servicio) se encarga de llamar al planificador (?)
-¿Cuáles son los puntos de entrada a la ejecución del sistema operativo?

-Indicar las diferencias entre interrupciones y excepciones
    Las interrupciones las lanza el programa por una E/S (el hardware es el responsable) y las excepciones el so.
    Las excepciones se deben a algo indebido.
    Se tratan ambas de la misma forma.
    Las excepciones son síncronas al proceso, tocarán el contexto del proceso,
    las interrupciones son asíncronas al proceso.
-¿Dónde se salvan los registros del procesador cuando invocamos a la función dispatcher() o cambio_contexto()?
    En el PCB.
-Si un proceso se está ejecutando y se produce una interrupción- ¿Qué posibles transiciones de estados de procesos tendremos?
    Dicho proceso pasará de ejecución a la cola de preparados/ de bloqueado a preparado.
