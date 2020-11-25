El proposito principal de la función GNL es leer un archivo de texto que contiene el main de la moulinette.

Para poder leer el archivo, primero es necesario abrilo, por lo que la moulinette en su main va a hacer una llamda al sistema con la función open(). Esta función va a devolver un file descriptor "fd" que no es mas que un número entero positivo (si fuera negativo devolvería error) que sirve de identifador entre el proceso y el archivo que acaba de abrir.

El motivo de este 'fd' es porque ni el usuario ni ningun software cliente puede acceder a los datos contenidos en el kernel por seguridad. Por lo que este número sirve para que puedas decirle al kernel:oye se que no puedo ver el fichero pero quiero que hagas tal cosa en este descriptor de fichero, y el kernel constesta, ah estupendo ya se que fichero es, voy a ello. "Analogía del taller de arte"

Bien, hasta este punto tu nos has hecho nada. La moulinette se ha encargado de abrir un fichero con la función open para facilitarte un "fd" para que puedas tener acceso al fichero .txt y comenzar a leerlo.

Ahora se te esta pidiendo que crees una función que sea capaz de leer con el "fd" el fichero .txt que tiene la moulinete en su main y que devuelvas, en función de lo que ha leído los siguientes valores:

		1 : Se ha leído una línea
		0 : Se ha llegado al final del fichero
		-1 : Ha ocurrido un Error

Para lograrlo, debes gestionar cada linea leida y que cada vez que lea una nueva linea, no devuelva la linea anterior que ya leyo. Se considera linea a un parrafo de texto que termina con un salto de línea "\n"

Cómo último dato, se te dice que a la hora de compilar el programa, se va a hacer con el flag -D BUFFER_SIZE=xx cuyo valor será modificado por el usuario o por la moulinette por lo debes de controlar este valor. El buffer_size es el tamaño maximo de bytes que pueden ser leidos, por lo que para curarnos de salud aquí lo haremos con el máximo


🧪🧠 🧪🧠 🧪🧠 🧪🧠     NO AVANCES HASTA COMPREDER LO DE ARRIBA    🧪🧠 🧪🧠 🧪🧠 🧪🧠


*******************************************************
int		get_next_line(int fd, char **line)
{
	static char		*saved[4096];

	if (fd < 0 || !line)
		return (-1);
	else if (saved[fd] && ft_strchr(saved[fd], '\n'))
		return (put_line(&saved[fd], line));
	else
		return (read_line(saved, fd, line));
}
*******************************************************

Lo primero que hacemos es escribir el prototipo de la función get_next_line() que viene indicada en el subject del proyecto y que recibe 2 parámetros. El primero es el "fd" con el que se accede a la lectura del .txt y el segundo es el valor de lo que ha leido.

	int	fd --> descriptor de fichero para su lectura
	char **line --> el valor de lo que se ha leido del fd

Vamos a declarar un puntero estático de tipo char *saved[4096] donde guardaremos cada linea leida del fichero ".txt"  Le asignamos un tamaño de 4096 que es el máximo permitido.
Que sea estático significa que mantendrá su valor a lo largo del tiempo de ejecución y servirá para guardar en la pila las lineas del fichero que vayamos leyendo. Necesitamos que sea estático porque lo utilizaremos dentro de la función read_line() y queremos mantener su valor cuando salgamos de ella. Recuerda que todas las variales se reinician a 0 cuando termina de ejecutarse la función.

Seguidamente lo que hacemos es ahorrar recursos y tiempo protegiendo a nuestra función. Declaramos un condicional if en el que pregunta si el "fd" en menor que cero (recuerda que no podía ser negativo ya que significa que el fichero no se a podido abiri entonces) o, si que se ha podido abrir el fd pero resulta que estaba vacío, osea, no habia texto, entonces devolvermos un error (-1)


En el siguiente condicional valora si hay lineas guardadas en saved[fd] y además, si encontró un salto de linea. Si así fuera, que entre en la función put_line() pero, espera espera... para poder saber eso primero es necesario leer el "fd" ¿Cómo va a tener nada guardado el puntero saved[fd] y cómo vas a encontrar saltos de linea si aun no has llamado a la función read() para que pueda leer el ".txt"
Entonces esto queda claro, para poder saber que contiene el .txt debemos de leerlo antes, por lo que la primera vez que se ejecute nuestro programa no entrara aquí porque no se cumple la condición y saltara al siguiente else.

Ahora si, como hemos dicho, la primera vez que entre, despés de comprobar si es válido el "fd" y si lo que se ha leído del fd esta guardado en **line (el valor es 0 porque no se ha leido nada de momento), deberemos llamar a la función read() para poder leer el .txt
Esta función se encuentra dentro de read_line() por lo que es la


🧪🧠 🧪🧠 🧪🧠 🧪🧠     NO AVANCES HASTA COMPREDER LO DE ARRIBA    🧪🧠 🧪🧠 🧪🧠 🧪🧠


*******************************************************
int		read_line(char **s, int fd, char **line)
{
	char	buff[BUFFER_SIZE + 1];
	char	*tmp;
	int		dvl;

	while ((dvl = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[dvl] = '\0';
		if (!s[fd])
			s[fd] = ft_substr("", 0, 0);
		tmp = ft_strjoin(s[fd], buff);
		free(s[fd]);
		s[fd] = tmp;
		if (ft_strchr(s[fd], '\n'))
			return (put_line(&s[fd], line));
	}
	if (dvl < 0)
		return (-1);
	else if (dvl == 0 && !s[fd])
	{
		*line = ft_substr("", 0, 0);
		return (0);
	}
	else
		return (put_line(&s[fd], line));
}
*******************************************************

Esta funcion recibe 3 parámetros, los cuales, la primera vez que entra, solo va a tener valor el "fd" ya que

	**s --> es donde va a almacenar el contenido que tenía de antes mas lo que acaba de leer
	fd --> es el número positivo que hace referencia al .txt
	**line --> es donde ponemos una linea cada vez que se llama a la función  *saved

Ahora se declran 3 variables que se explicaran mas adelante, segun avancemos en el código, pero a modo de resumen diremos que

	buff[] -->  Una matriz de caracteres donde se almacenará el contenido leído indicados por el BUFFER_SIZE. Recuerda que BUFFER_SIZE es el tamaño maximo de bytes que pueden ser leidos y que su valor sera pasado en el momento de la compilación en forma de flag (-D BUFFER_SIZE=xx) por el usuario y al presentar el proyecto claro esta, por la moulinette. Por lo tanto, aunque podemos darle otro valor, por motivo de eficiencia, le daremos el mismo valor de lo máximo que puede leer, buff[BUFFER_SIZE].
	Entonces, estamos declarando la cadena buff y la estamos inicializando con "xx" tammaño para guardar algo que va a leer pero que aun no sabemos.

	*tmp --> Es un puntero temporal cuya función sera la de trabajar con la cadena para leer lineas y servirnos de apoyo.

	dvl --> variable de tipo entero donde guardaré el valor de retorno de la función read. Esto es, el número de bites que se han leido.

					---------		---------		---------

Ahora vamos a establecer un while con el que manejaremos la lectura del fichero ".txt"  Este bucle tiene la condición de que si la función read() que es la que lee el fichero, no devuelve un número mayor de cero (esto significaría que no ha leido ningún byte) entonces devuelve error con un return(-1)

Para comprender mejor la función read(), explicaremos cada uno de los parámetros que componen su prototipo, ssize_t read(int fildes, void *buf, size_t nbyte);:

			int fildes --> Toma un primer parámetro, fichero, que es el descriptor del fichero sobre el que se pretende actuar.

			void *buf --> El parámetro buffer es un apuntador al área de memoria donde se va a efectuar la transferencia. O sea, de donde se van a leer los datos en la función read, o donde se van a depositar en el caso de que fuera write.
			ATENCION: Por motivo de eficiencia, el tamaño del *buf sera el mismo que el de BUFFER_SIZE que leer. De esta forma, el tamaño del buffer siempre coincidirá con lo que va a leer y evitaremos el exceso o pedida de memoria.

			size_t nbyte --> El parámetro bytes especifica el número de bytes que se van a transferir.

La funcion read() devuelve el número de bytes que realmente se han transferido. Este dato es realmente útil ya que nos da una pista para saber si se ha llegado al final del fichero. En caso de error, devuelve un -1

Todas las cadenas en "C" debe terminar por un valor nulo para indicar el final de la cadena. Si no fuera así, el programa podría ejecutarse fuera del final de la cadena y no actuar como esperabas.
Por esta razón, estamos añadiendo el valor nulo al final de la cadena de caracteres leidos con buff[dvl] = '\0'
Ten en cuenta que dvl representa la cantidad de bytes que han sido leidos (33 por ejemplo) por lo que al hacer buff[dvl] estamos posicionando el índice de esa cadena en el final buff[33] y como hemos guardado un espacio de mas a la hora de declarar la cadena buff (acuerdate) pues ahora le insertamos el valor nulo indicando que ese es el final.

Ahora toca comprobar si *s tiene contenido. Recordemos que *s almacena el contenido que ya tenia de antes mas cada linea que acaba de leer. Bien, pues la primera vez que entra no tiene nada de contenido porque obviamente no ha leído nada. Así que lo que haré sera crear una condición que me diga que si no tiene nada almacenado cree una nueva cadena con substr y se lo asigne a s[fs]. La forma en la que le asigno esta cadena es curiosa ya que substr("", 0, 0) lo que hace es buscar en la cadena "" una subcadena, y que comience a buscar esta subcadena en la posición especificada que viene indicado en el segundo parámetro que le pasa que es cero, y de la longitud especificada en el 3 parámetro que también es cero. Por lo tanto, de la manera que lo estamos empleando, nos va a devolver una cadena vacía, genial para nuestro propósito que era meterle valor a s[fd]

Lo siguiente que hacemos es resevar la memoría que nos ocuparía la suma de la concatenación de buff, que es el string que contiene todo el texto .txt con *s, que es un string vacío. Una vez que hemos reservado memoría, le asignamos el valor a tmp. Bien hasta aquí tenemos una cadena "tmp" de x bytes reservados pero vacía, sin contenido para mostrar.
La razón de hacer esto es la siguiente: imagina que tenemos 2 probetas, una llena de liquido y la otra vacía. Lo que pretendemos hacer es ir vaciando una de ellas linea a linea. Cada linea que vayamos leyendo la extraeremos de la que tiene todo el líquido "buff" y se lo añadiremos a la que esta vacía "*s"

Ahora, liberamos con free el valor contenido en s[fs] que no era mas que una cadena vacía de x bytes. Liberamos la cadena porque en la siguiente línea vamos a asignar el valor de "tmp" a s[fd].

Lo que hemos hecho hasta aquí con toda esta operación, es pasarle todo el contido de "buff" a "s[fs]" para poder trabajarlo ahora con al funcion put_line()
