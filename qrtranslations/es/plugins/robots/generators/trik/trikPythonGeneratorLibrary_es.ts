<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="es_ES">
<context>
    <name>QObject</name>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonControlFlowValidator.cpp" line="35"/>
        <source>There is nothing to generate, diagram doesn&apos;t have Initial Node</source>
        <translation>No hay nada que generar, el diagrama no tiene un nodo inicial</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="141"/>
        <source>Trying to join a thread with an unknown id. Possible causes: calling fork from a subprogram or trying to merge two threads without a join</source>
        <translation>Intentando unir un hilo con un identificador desconocido. Posibles causas: llamar a fork desde un subprograma o intentar fusionar dos hilos sin un bloque join</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="148"/>
        <source>Join block must have exactly one outgoing link</source>
        <translation>El bloque de unión debe tener exactamente un enlace de salida</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="154"/>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="199"/>
        <source>Guard property of a link outgoing from a join must contain an id of one of joined threads</source>
        <translation>La propiedad de guarda de un enlace que sale de un bloque de unión debe contener el identificador de uno de los hilos unidos</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="161"/>
        <source>Joining threads in a loop is forbidden</source>
        <translation>Está prohibido unir hilos dentro de un bucle</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="223"/>
        <source>Trying to fork from a thread with an unknown id. Possible causes: calling fork from a subprogram or trying to merge two threads without a join</source>
        <translation>Intentando crear un fork desde un hilo con identificador desconocido. Posibles causas: llamar a fork desde un subprograma o intentar fusionar dos hilos sin un bloque join</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="229"/>
        <source>Fork block must have at least TWO outgoing links</source>
        <translation>El bloque fork debe tener al menos DOS enlaces de salida</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="258"/>
        <source>Links outgoing from a fork block must have different thread ids</source>
        <translation>Los enlaces que salen del bloque fork deben tener identificadores de hilo diferentes</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="273"/>
        <source>Fork block must have a link marked with an id of a thread from which the fork is called, &apos;%1&apos; in this case</source>
        <translation>El bloque fork debe tener un enlace marcado con el identificador del hilo desde el cual se llama al fork, en este caso &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="284"/>
        <source>Trying to create a thread with an already occupied id &apos;%1&apos;</source>
        <translation>Intentando crear un hilo con un identificador ya ocupado &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="294"/>
        <source>Creation of threads in a cycle is forbidden, check for links to before a fork</source>
        <translation>Está prohibida la creación de hilos en un ciclo, verifique los enlaces que conducen a bloques anteriores al bloque fork</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/threadsValidator.cpp" line="330"/>
        <source>Outgoing link is not connected</source>
        <translation>El enlace de salida no está conectado</translation>
    </message>
</context>
<context>
    <name>trik::python::TrikPythonGeneratorPluginBase</name>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="73"/>
        <source>Network operation timed out</source>
        <translation>La operación de red ha excedido el tiempo de espera, verifique la configuración y asegúrese de que el robot esté encendido</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="100"/>
        <source>Casing model mismatch, check TRIK Studio settings, &quot;Robots&quot; page. It seems that TRIK casing version selected in TRIK Studio differs from version on robot.</source>
        <translation>El modelo del chasis no coincide, verifique la configuración en TRIK Studio, pestaña &quot;Robots&quot;. Parece que la versión del chasis seleccionada en TRIK Studio es diferente de la del robot.</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="109"/>
        <source>Generate python code</source>
        <translation>Generar código en Python</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="116"/>
        <source>Upload program</source>
        <translation>Cargar programa</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="123"/>
        <source>Run program</source>
        <translation>Cargar y ejecutar programa</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="130"/>
        <source>Stop robot</source>
        <translation>Detener robot</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="146"/>
        <source>Generate Python code</source>
        <translation>Generar código para TRIK en QtScript</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="147"/>
        <source>Upload Python program</source>
        <translation>Cargar programa</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="148"/>
        <source>Run Python program</source>
        <translation>Ejecutar programa</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="149"/>
        <source>Stop Python program</source>
        <translation>Detener la ejecución del programa para TRIK</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikPythonGeneratorLibrary/src/trikPythonGeneratorPluginBase.cpp" line="221"/>
        <source>There are no files to upload. You must open or generate at least one *.js or *.py file.</source>
        <translation>No hay archivos para cargar. Debe abrir o generar al menos un archivo *.js o *.py.</translation>
    </message>
</context>
</TS>
