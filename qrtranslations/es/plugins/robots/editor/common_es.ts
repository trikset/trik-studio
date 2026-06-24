<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="es_ES">
<context>
    <name>QObject</name>
    <message>
        <source>AbstractNode</source>
        <translation>Bloque base</translation>
    </message>
    <message>
        <source>Clear Screen</source>
        <translation>Limpiar pantalla</translation>
    </message>
    <message>
        <source>Clears everything drawn on the robot`s screen.</source>
        <translation>Borra todo lo dibujado en la pantalla del robot.</translation>
    </message>
    <message>
        <source>Redraw</source>
        <translation>Actualizar imagen</translation>
    </message>
    <message>
        <source>Comment</source>
        <translation>Comentario</translation>
    </message>
    <message>
        <source>This block can hold text notes that are ignored by generators and interpreters. Use it for improving the diagram readability.</source>
        <translation>Este bloque puede contener notas de texto que son ignoradas por los generadores e intérpretes. Úselo para mejorar la legibilidad del diagrama.</translation>
    </message>
    <message>
        <source>Enter some text here...</source>
        <translation>Introduzca texto aquí...</translation>
    </message>
    <message>
        <source>Link</source>
        <translation>Línea de conexión</translation>
    </message>
    <message>
        <source>For creating a link between two elements A and B you can just hover a mouse above A, press the right mouse button and (without releasing it) draw a line to the element B. Alternatively you can just &apos;pull&apos; a link from a small blue circle next to the element.</source>
        <translation>Para crear un enlace entre dos elementos A y B, puede colocar el cursor sobre A, pulsar el botón derecho del ratón y (sin soltarlo) trazar una línea hasta el elemento B. Alternativamente, puede &apos;arrastrar&apos; un enlace desde el pequeño círculo azul junto al elemento.</translation>
    </message>
    <message>
        <source>Guard</source>
        <translation>Condición</translation>
    </message>
    <message>
        <source>EngineCommand</source>
        <translation>Bloque base de motores</translation>
    </message>
    <message>
        <source>EngineMovementCommand</source>
        <translation>Bloque base de activación de motores</translation>
    </message>
    <message>
        <source>100</source>
        <translation>100</translation>
    </message>
    <message>
        <source>Power (%)</source>
        <translation>Potencia (%)</translation>
    </message>
    <message>
        <source>End if</source>
        <translation>Fin de condición</translation>
    </message>
    <message>
        <source>Unites control flow from different condition branches.</source>
        <translation>Une las ramas del bloque &quot;Condición&quot;.</translation>
    </message>
    <message>
        <source>Final Node</source>
        <translation>Fin</translation>
    </message>
    <message>
        <source>The final node of the program. If the program consists of some parallel execution lines the reachment of this block terminates the corresponding execution line. This block can`t have outgoing links.</source>
        <translation>Fin del programa. Si el programa consta de varios segmentos de ejecución paralelos, alcanzar este bloque finaliza el segmento correspondiente. Este bloque no puede tener enlaces salientes.</translation>
    </message>
    <message>
        <source>Fork</source>
        <translation>Tareas paralelas</translation>
    </message>
    <message>
        <source>Separates program execution into a number of threads that will be executed concurrently from the programmers`s point of view. For example in such way signal from sensor and some time interval can be waited synchroniously. This block must have at least two outgoing links. &apos;Guard&apos; property of every link must contain unique thread identifiers, and one of those identifiers must be the same as the identifier of a thread where fork is placed (it must be &apos;main&apos; if it is the first fork in a program.</source>
        <translation>Divide la ejecución del programa en varias tareas que se ejecutarán en paralelo desde el punto de vista del programador. Por ejemplo, de esta forma se puede esperar simultáneamente una señal del sensor y un intervalo de tiempo. Este bloque debe tener al menos dos enlaces salientes. La propiedad &quot;Condición&quot; de cada enlace debe contener identificadores únicos de tareas, y uno de esos identificadores debe coincidir con el identificador de la tarea desde la que se coloca el bloque (debe ser &apos;main&apos; si es el primer bloque de bifurcación en el programa).</translation>
    </message>
    <message>
        <source>Expression</source>
        <translation>Expresión</translation>
    </message>
    <message>
        <source>Evaluates a value of the given expression. Also new variables can be defined in this block. See the &apos;Expressions Syntax&apos; chapter in help for more information about &apos;Function&apos; block syntax.</source>
        <translation>Evalúa el valor de la expresión dada. También se pueden definir nuevas variables en este bloque. Consulte el capítulo &apos;Sintaxis de expresiones&apos; en la ayuda para obtener más información sobre la sintaxis del bloque &apos;Función&apos;.</translation>
    </message>
    <message>
        <source>Expression:</source>
        <translation>Expresión:</translation>
    </message>
    <message>
        <source>Get Button Code</source>
        <translation>Obtener código del botón</translation>
    </message>
    <message>
        <source>Assigns a given variable a value of pressed button. If no button is pressed at the moment and &apos;Wait&apos; property is false when variable is set to -1.</source>
        <translation>Asigna a una variable dada el valor del botón pulsado. Si no se pulsa ningún botón en ese momento y la propiedad &apos;Esperar&apos; es falsa, la variable se establece en -1.</translation>
    </message>
    <message>
        <source>Variable:</source>
        <translation>Variable:</translation>
    </message>
    <message>
        <source>Wait:</source>
        <translation>Esperar:</translation>
    </message>
    <message>
        <source>x</source>
        <translation>x</translation>
    </message>
    <message>
        <source>Variable</source>
        <translation>Variable</translation>
    </message>
    <message>
        <source>Wait</source>
        <translation>Espera</translation>
    </message>
    <message>
        <source>Condition</source>
        <translation>Condición</translation>
    </message>
    <message>
        <source>Separates program execution in correspondece with the given condition. The &apos;Condition&apos; parameter value must be some boolean expression that will determine subsequent program execution line. This block must have two outgoing links, at least one of them must have &apos;Guard&apos; parameter set to &apos;true&apos; or &apos;false&apos;. The execution will be proceed trough the link marked with the guard corresponding to &apos;Condition&apos; parameter of the block.</source>
        <translation>Divide la ejecución del programa según la condición dada. El valor del parámetro &apos;Condición&apos; debe ser una expresión booleana que determinará la siguiente línea de ejecución del programa. Este bloque debe tener dos enlaces salientes, al menos uno de ellos debe tener el parámetro &apos;Condición&apos; establecido en &apos;verdadero&apos; o &apos;falso&apos;. La ejecución continuará por el enlace marcado con la condición que corresponda al valor del parámetro &apos;Condición&apos; del bloque.</translation>
    </message>
    <message>
        <source>Condition:</source>
        <translation>Condición:</translation>
    </message>
    <message>
        <source>x &gt; 0</source>
        <translation>x &gt; 0</translation>
    </message>
    <message>
        <source>Initial Node</source>
        <translation>Inicio</translation>
    </message>
    <message>
        <source>The entry point of the program execution. Each diagram should have only one such block, it must not have incomming links and it must have only one outgoing link. The interpretation process starts from exactly this block.</source>
        <translation>Punto de entrada de la ejecución del programa. Cada diagrama debe tener solo un bloque de este tipo, no debe tener enlaces entrantes y debe tener solo un enlace saliente. El proceso de interpretación comienza exactamente en este bloque.</translation>
    </message>
    <message>
        <source>User Input</source>
        <translation>Entrada de usuario</translation>
    </message>
    <message>
        <source>Reads a value into variable from an input dialog.</source>
        <translation>Lee un valor en una variable desde un cuadro de diálogo de entrada.</translation>
    </message>
    <message>
        <source>Default:</source>
        <translation>Predeterminado:</translation>
    </message>
    <message>
        <source>Text:</source>
        <translation>Texto:</translation>
    </message>
    <message>
        <source>Join</source>
        <translation>Unión de tareas</translation>
    </message>
    <message>
        <source>Joins a number of threads into one. &apos;Guard&apos; property of the single outgoing link must contain an identifier of one of threads being joined. The specified thread would wait until the rest of them finish execution, and then proceed in a normal way.</source>
        <translation>Une varias tareas en una. La propiedad &apos;Condición&apos; del único enlace saliente debe contener el identificador de una de las tareas que se están uniendo. La tarea especificada esperará hasta que las demás terminen su ejecución, y luego continuará normalmente.</translation>
    </message>
    <message>
        <source>Kill Thread</source>
        <translation>Finalizar tarea</translation>
    </message>
    <message>
        <source>Terminates execution of a specified thread.</source>
        <translation>Termina la ejecución de una tarea especificada.</translation>
    </message>
    <message>
        <source>Thread:</source>
        <translation>Tarea:</translation>
    </message>
    <message>
        <source>main</source>
        <translation>main</translation>
    </message>
    <message>
        <source>Thread</source>
        <translation>Tarea</translation>
    </message>
    <message>
        <source>Loop</source>
        <translation>Bucle</translation>
    </message>
    <message>
        <source>This block executes a sequence of blocks for a given number of times. The number of repetitions is specified by the &apos;Iterations&apos; parameter. This block must have two outgoing links. One of them must be marked with the &apos;body&apos; guard (that means that the property &apos;Guard&apos; of the link must be set to &apos;body&apos; value). Another outgoing link must be unmarked: the program execution will be proceeded through this link when it will go through our &apos;Loop&apos; block for the given number of times.</source>
        <translation>Este bloque ejecuta una secuencia de bloques un número determinado de veces. El número de repeticiones se especifica mediante el parámetro &apos;Iteraciones&apos;. Este bloque debe tener dos enlaces salientes. Uno de ellos debe estar marcado con la condición &apos;cuerpo&apos; (es decir, la propiedad &apos;Condición&apos; del enlace debe establecerse en &apos;cuerpo&apos;). El otro enlace saliente debe quedar sin marcar: la ejecución del programa continuará por este enlace cuando haya pasado por el bloque &apos;Bucle&apos; el número de veces indicado.</translation>
    </message>
    <message>
        <source>Iterations:</source>
        <translation>Iteraciones:</translation>
    </message>
    <message>
        <source>10</source>
        <translation>10</translation>
    </message>
    <message>
        <source>Iterations</source>
        <translation>Iteraciones</translation>
    </message>
    <message>
        <source>Marker Down</source>
        <translation>Bajar marcador</translation>
    </message>
    <message>
        <source>Moves the marker of the 2D model robot down to the floor: the robot will draw its trace on the floor after that. If the marker of another color is already drawing at the moment it will be replaced.</source>
        <translation>Baja el marcador del robot en el modelo 2D hasta el suelo: el robot comenzará a dibujar su trayectoria sobre el suelo. Si ya hay un marcador de otro color bajado, será reemplazado.</translation>
    </message>
    <message>
        <source>Color:</source>
        <translation>Color:</translation>
    </message>
    <message>
        <source>Color</source>
        <translation>Color</translation>
    </message>
    <message>
        <source>Marker Up</source>
        <translation>Subir marcador</translation>
    </message>
    <message>
        <source>Lifts the marker of the 2D model robot up: the robot stops drawing its trace on the floor after that.</source>
        <translation>Sube el marcador del robot en el modelo 2D: el robot deja de dibujar su trayectoria sobre el suelo.</translation>
    </message>
    <message>
        <source>Pre-conditional Loop</source>
        <translation>Bucle con condición previa</translation>
    </message>
    <message>
        <source>This block executes a sequence of blocks while condition in &apos;Condition&apos; is true. This block must have two outgoing links. One of them must be marked with the &apos;body&apos; guard (that means that the property &apos;Guard&apos; of the link must be set to &apos;body&apos; value). Another outgoing link must be unmarked: the program execution will be proceeded through this link when condition becomes false.</source>
        <translation>Este bloque ejecuta una secuencia de bloques mientras la condición en &apos;Condición&apos; sea verdadera. Este bloque debe tener dos enlaces salientes. Uno de ellos debe estar marcado con la condición &apos;cuerpo&apos; (es decir, la propiedad &apos;Condición&apos; del enlace debe establecerse en &apos;cuerpo&apos;). El otro enlace saliente debe quedar sin marcar: la ejecución del programa continuará por este enlace cuando la condición se vuelva falsa.</translation>
    </message>
    <message>
        <source>Print Text</source>
        <translation>Imprimir texto</translation>
    </message>
    <message>
        <source>Prints a given line in the specified coordinates on the robot`s screen. The value of &apos;Text&apos; property is interpreted as a plain text unless &apos;Evaluate&apos; property is set to true, then it will be interpreted as an expression (that may be useful for example when debugging variables values).</source>
        <translation>Imprime una línea dada en las coordenadas especificadas de la pantalla del robot. El valor de la propiedad &apos;Texto&apos; se interpreta como texto plano, a menos que la propiedad &apos;Evaluar&apos; esté activada, en cuyo caso se interpretará como una expresión (lo que puede ser útil, por ejemplo, al depurar valores de variables).</translation>
    </message>
    <message>
        <source>X:</source>
        <translation>X:</translation>
    </message>
    <message>
        <source>Y:</source>
        <translation>Y:</translation>
    </message>
    <message>
        <source>Evaluate</source>
        <translation>Evaluar</translation>
    </message>
    <message>
        <source>Enter some text here</source>
        <translation>Introduzca texto aquí</translation>
    </message>
    <message>
        <source>Text</source>
        <translation>Texto</translation>
    </message>
    <message>
        <source>1</source>
        <translation>1</translation>
    </message>
    <message>
        <source>X</source>
        <translation>X</translation>
    </message>
    <message>
        <source>Y</source>
        <translation>Y</translation>
    </message>
    <message>
        <source>Random Initialization</source>
        <translation>Inicialización aleatoria</translation>
    </message>
    <message>
        <source>Sets a variable value to a random value inside given interval.</source>
        <translation>Establece el valor de una variable en un valor aleatorio dentro del intervalo especificado.</translation>
    </message>
    <message>
        <source>From:</source>
        <translation>Desde:</translation>
    </message>
    <message>
        <source>To:</source>
        <translation>Hasta:</translation>
    </message>
    <message>
        <source>0</source>
        <translation>0</translation>
    </message>
    <message>
        <source>From</source>
        <translation>Desde</translation>
    </message>
    <message>
        <source>To</source>
        <translation>Hasta</translation>
    </message>
    <message>
        <source>Receive Message From Thread</source>
        <translation>Recibir mensaje de la tarea</translation>
    </message>
    <message>
        <source>Receive a message sent to a thread from which this block is called.</source>
        <translation>Recibe un mensaje enviado a una tarea desde la cual se llama a este bloque.</translation>
    </message>
    <message>
        <source>Synchronized:</source>
        <translation>Esperar mensaje:</translation>
    </message>
    <message>
        <source>Synchronized</source>
        <translation>Esperar mensaje</translation>
    </message>
    <message>
        <source>RobotsDiagramGroup</source>
        <translation>Diagrama de comportamiento de robots</translation>
    </message>
    <message>
        <source>Robot`s Behaviour Diagram</source>
        <translation>Diagrama de comportamiento del robot</translation>
    </message>
    <message>
        <source>Send Message To Thread</source>
        <translation>Enviar mensaje a la tarea</translation>
    </message>
    <message>
        <source>Sends a message to a specified thread.</source>
        <translation>Envía un mensaje a una tarea especificada.</translation>
    </message>
    <message>
        <source>Message:</source>
        <translation>Mensaje:</translation>
    </message>
    <message>
        <source>Subprogram</source>
        <translation>Subprograma</translation>
    </message>
    <message>
        <source>Subprogram call. Subprograms are used for splitting repetitive program parts into a separate diagram and then calling it from main diagram or other subprograms. When this block is added into a diagram it will be suggested to enter subprogram name. The double click on subprogram call block may open the corresponding subprogram diagram. Moreover user palette will appear containing existing subrpograms, they can be dragged into a diagram like the usual blocks.</source>
        <translation>Llamada a subprograma. Los subprogramas se utilizan para separar partes repetitivas del programa en un diagrama independiente y luego invocarlos desde el diagrama principal u otros subprogramas. Al añadir este bloque al diagrama, se solicitará introducir el nombre del subprograma. Al hacer doble clic en el bloque de llamada al subprograma se puede abrir el diagrama correspondiente. Además, aparecerá una paleta de usuario con los subprogramas existentes, que pueden arrastrarse al diagrama como bloques normales.</translation>
    </message>
    <message>
        <source>Subprogram Diagram</source>
        <translation>Subprograma</translation>
    </message>
    <message>
        <source>SubprogramDiagramGroup</source>
        <translation>Subprograma</translation>
    </message>
    <message>
        <source>Switch</source>
        <translation>Selección</translation>
    </message>
    <message>
        <source>Selects the program execution branch in correspondence with some expression value. The value of the expression written in &apos;Expression&apos; property is compared to the values on the outgoing links. If equal value is found then execution will be proceeded by that branch. Else branch without a marker will be selected.</source>
        <translation>Selecciona la rama de ejecución del programa según el valor de una expresión. El valor de la expresión escrita en la propiedad &apos;Expresión&apos; se compara con los valores en los enlaces salientes. Si se encuentra un valor igual, la ejecución continuará por esa rama. En caso contrario, se seleccionará la rama sin marcador.</translation>
    </message>
    <message>
        <source>Timer</source>
        <translation>Temporizador</translation>
    </message>
    <message>
        <source>Waits for a given time in milliseconds.</source>
        <translation>Espera un tiempo determinado en milisegundos.</translation>
    </message>
    <message>
        <source>Delay:</source>
        <translation>Retardo:</translation>
    </message>
    <message>
        <source>ms</source>
        <translation>ms</translation>
    </message>
    <message>
        <source>1000</source>
        <translation>1000</translation>
    </message>
    <message>
        <source>Delay (ms)</source>
        <translation>Retardo (ms)</translation>
    </message>
    <message>
        <source>Variable Initialization</source>
        <translation>Inicialización de variable</translation>
    </message>
    <message>
        <source>Assigns a given value to a given variable.</source>
        <translation>Asigna un valor determinado a una variable especificada.</translation>
    </message>
    <message>
        <source>Value:</source>
        <translation>Valor:</translation>
    </message>
    <message>
        <source>Value</source>
        <translation>Valor</translation>
    </message>
    <message>
        <source>Algorithms</source>
        <translation>Algoritmos</translation>
    </message>
    <message>
        <source>Actions</source>
        <translation>Acciones</translation>
    </message>
    <message>
        <source>Drawing</source>
        <translation>Dibujo</translation>
    </message>
</context>
<context>
    <name>QObject::QObject</name>
    <message>
        <source>Expression</source>
        <translation>Expresión</translation>
    </message>
    <message>
        <source>Default</source>
        <translation>Por defecto</translation>
    </message>
    <message>
        <source>Text</source>
        <translation>Texto</translation>
    </message>
    <message>
        <source>Variable</source>
        <translation>Variable</translation>
    </message>
    <message>
        <source>Devices configuration</source>
        <translation>Configuración de dispositivos</translation>
    </message>
    <message>
        <source>Message</source>
        <translation>Mensaje</translation>
    </message>
    <message>
        <source>Thread</source>
        <translation>Tarea</translation>
    </message>
</context>
<context>
    <name>RobotsMetamodelPlugin</name>
    <message>
        <source>norm</source>
        <translation>norma</translation>
    </message>
    <message>
        <source>x-axis</source>
        <translation>eje x</translation>
    </message>
    <message>
        <source>y-axis</source>
        <translation>eje y</translation>
    </message>
    <message>
        <source>z-axis</source>
        <translation>eje z</translation>
    </message>
    <message>
        <source>Composite</source>
        <translation>Compuesto</translation>
    </message>
    <message>
        <source>None</source>
        <translation>Ninguno</translation>
    </message>
    <message>
        <source>Shared</source>
        <translation>Compartido</translation>
    </message>
    <message>
        <source>brake</source>
        <translation>freno</translation>
    </message>
    <message>
        <source>float</source>
        <translation>flotante</translation>
    </message>
    <message>
        <source>Concurrent</source>
        <translation>Concurrente</translation>
    </message>
    <message>
        <source>Guarded</source>
        <translation>Protegido</translation>
    </message>
    <message>
        <source>Sequential</source>
        <translation>Secuencial</translation>
    </message>
    <message>
        <source>black</source>
        <translation>negro</translation>
    </message>
    <message>
        <source>blue</source>
        <translation>azul</translation>
    </message>
    <message>
        <source>green</source>
        <translation>verde</translation>
    </message>
    <message>
        <source>red</source>
        <translation>rojo</translation>
    </message>
    <message>
        <source>white</source>
        <translation>blanco</translation>
    </message>
    <message>
        <source>yellow</source>
        <translation>amarillo</translation>
    </message>
    <message>
        <source>greater</source>
        <translation>mayor</translation>
    </message>
    <message>
        <source>less</source>
        <translation>menor</translation>
    </message>
    <message>
        <source>not greater</source>
        <translation>no mayor</translation>
    </message>
    <message>
        <source>not less</source>
        <translation>no menor</translation>
    </message>
    <message>
        <source>false</source>
        <translation>falso</translation>
    </message>
    <message>
        <source>body</source>
        <translation>cuerpo del bucle</translation>
    </message>
    <message>
        <source>true</source>
        <translation>verdadero</translation>
    </message>
    <message>
        <source>In</source>
        <translation>Entrada</translation>
    </message>
    <message>
        <source>Inout</source>
        <translation>Entrada-salida</translation>
    </message>
    <message>
        <source>Out</source>
        <translation>Salida</translation>
    </message>
    <message>
        <source>Return</source>
        <translation>Devuelve</translation>
    </message>
    <message>
        <source>Package</source>
        <translation>Paquete</translation>
    </message>
    <message>
        <source>Private</source>
        <translation>Privado</translation>
    </message>
    <message>
        <source>Protected</source>
        <translation>Protegido</translation>
    </message>
    <message>
        <source>Public</source>
        <translation>Público</translation>
    </message>
</context>
</TS>
