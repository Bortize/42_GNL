El proposito principal de la función GNL es leer un archivo de texto que contiene el main de la moulinette.

Para poder leer el archivo, primero es necesario abrilo, por lo que la moulinette en su main va a hacer una llamda al sistema con la función open(). Esta función va a devolver un file descriptor "fd" que no es mas que un número entero positivo (si fuera negativo devolvería error) que sirve de identifador entre el proceso y el archivo que acaba de abrir.

El motivo de este 'fd' es porque ni el usuario ni ningun software cliente puede acceder a los datos contenidos en el kernel por seguridad. Por lo que este número sirve para que puedas decirle al kernel:oye se que no puedo ver el fichero pero quiero que hagas tal cosa en este descriptor de fichero, y el kernel constesta, ah estupendo ya se que fichero es, voy a ello. "Analogía del taller de arte"

Bien, hasta este punto tu nos has hecho nada. La moulinette se ha encargado de abrir un fichero con la función open para facilitarte un "fd" para que puedas tener acceso al fichero .txt y comenzar a leerlo.

Ahora se te esta pidiendo que crees una función que sea capaz de leer el fichero mediante el "fd" pero que devuelva unicamente cada linea leida y que cada vez que lea una nueva linea, no devuelva la linea anterior que ya leyo. Se considera linea a un parrafo de texto que termina con un salto de línea "\n"

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

