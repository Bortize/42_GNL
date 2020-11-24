int read (int fichero, void* buffer, unsigned bytes );

Toma un primer parámetro, fichero, que es el descriptor del fichero sobre el que se pretende actuar.

El parámetro buffer es un apuntador al área de memoria donde se va a efectuar la transferencia. O sea, de donde se van a leer los datos en la función read, o donde se van a depositar en el caso de que fuera write.

El parámetro bytes especifica el número de bytes que se van a transferir.

La funcion read() devuelve el número de bytes que realmente se han transferido. Este dato es realmente útil ya que nos da una pista para saber si se ha llegado al final del fichero. En caso de error, devuelve un -1
