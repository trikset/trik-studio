<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ru_RU">
<context>
    <name>QObject</name>
    <message>
        <location filename="../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="+141"/>
        <source>Trying to join a thread with an unknown id. Possible causes: calling fork from a subprogram or trying to merge two threads without a join</source>
        <translation>Попытка присоединиться к потоку с неизвестным идентификатором. Возможные причины: создание нового потока в подпрограмме или попытка объединить два потока без блока слияния задач</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Join block must have exactly one outgoing link</source>
        <translation>Блок слияния задач должен иметь только одну исходящую связь</translation>
    </message>
    <message>
        <location line="+6"/>
        <location line="+45"/>
        <source>Guard property of a link outgoing from a join must contain an id of one of joined threads</source>
        <translation>Свойство «Условие» связи, исходящей из блока слияния задач, должно содержать идентификатор одного из объединяемых потоков</translation>
    </message>
    <message>
        <location line="-38"/>
        <source>Joining threads in a loop is forbidden</source>
        <translation>Соединение потоков в цикле запрещено</translation>
    </message>
    <message>
        <location line="+62"/>
        <source>Trying to fork from a thread with an unknown id. Possible causes: calling fork from a subprogram or trying to merge two threads without a join</source>
        <translation>Попытка создать поток в потоке с неизвестным идентификатором. Возможные причины: создание нового потока в подпрограмме или попытка объединить два потока без блока слияния задач</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Fork block must have at least TWO outgoing links</source>
        <translation>Блок «Параллельные задачи» должен иметь как минимум две исходящие связи</translation>
    </message>
    <message>
        <source>All links outgoing from a fork block must have a thread id specified in a Guard property</source>
        <translation type="vanished">На всех связях, исходящих из блока &quot;Параллельные задачи&quot; должнен быть проставлен идентификатор потока</translation>
    </message>
    <message>
        <location line="+29"/>
        <source>Links outgoing from a fork block must have different thread ids</source>
        <translation>Связи, исходящие из блока «Параллельные задачи», должны иметь разные идентификаторы потоков</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>Fork block must have a link marked with an id of a thread from which the fork is called, &apos;%1&apos; in this case</source>
        <translation>Блок «Параллельные задачи» должен иметь связь, помеченную идентификатором текущего потока, в данном случае «%1»</translation>
    </message>
    <message>
        <location line="+11"/>
        <source>Trying to create a thread with an already occupied id &apos;%1&apos;</source>
        <translation>Попытка создать поток с уже занятым идентификатором «%1»</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Creation of threads in a cycle is forbidden, check for links to before a fork</source>
        <translation>Создание потоков в цикле запрещено. Проверьте входящие связи перед блоком «Параллельные задачи»</translation>
    </message>
    <message>
        <location line="+36"/>
        <source>Outgoing link is not connected</source>
        <translation>Исходящая связь ни к чему не присоединена</translation>
    </message>
    <message>
        <location filename="../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsControlFlowValidator.cpp" line="+37"/>
        <source>There is nothing to generate, diagram doesn&apos;t have Initial Node</source>
        <translation>Нечего создавать. На диаграмме нет блока «Начало»</translation>
    </message>
</context>
<context>
    <name>trik::qts::TrikQtsGeneratorPlugin</name>
    <message>
        <source>Generation (QtScript)</source>
        <translation type="vanished">Генерация (QtScript)</translation>
    </message>
    <message>
        <source>Generation (Java Script)</source>
        <translation type="vanished">Генерация (Java Script)</translation>
    </message>
    <message>
        <source>Generate TRIK code</source>
        <translation type="vanished">Генерировать код на QtScript</translation>
    </message>
    <message>
        <source>Upload program</source>
        <translation type="vanished">Загрузить программу</translation>
    </message>
    <message>
        <source>Run program</source>
        <translation type="vanished">Загрузить и выполнить программу</translation>
    </message>
    <message>
        <source>Stop robot</source>
        <translation type="vanished">Остановить робота</translation>
    </message>
    <message>
        <source>Generate TRIK Code</source>
        <translation type="vanished">Сгенерированть код для ТРИК на QtScript</translation>
    </message>
    <message>
        <source>Upload TRIK Program</source>
        <translation type="vanished">Загрузить программу</translation>
    </message>
    <message>
        <source>Run TRIK Program</source>
        <translation type="vanished">Исполнить программу</translation>
    </message>
    <message>
        <source>Stop TRIK Robot</source>
        <translation type="vanished">Остановить выполнение программы для TRIK</translation>
    </message>
    <message>
        <source>QtScript Source File</source>
        <translation type="vanished">Файл с исходным кодом на QtScript</translation>
    </message>
    <message>
        <source>No connection to robot</source>
        <translation type="vanished">Нет соединения с роботом, проверьте настройки, проверьте, включён ли робот</translation>
    </message>
</context>
<context>
    <name>trik::qts::TrikQtsGeneratorPluginBase</name>
    <message>
        <location filename="../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="+73"/>
        <source>Network operation timed out</source>
        <translation>Время ожидания для выполнения сетевой операции истекло</translation>
    </message>
    <message>
        <location line="+27"/>
        <source>Casing model mismatch, check TRIK Studio settings, &quot;Robots&quot; page. It seems that TRIK casing version selected in TRIK Studio differs from version on robot.</source>
        <translation>Несоответствие модели корпуса. Проверьте параметры TRIK Studio, вкладка «Роботы». Похоже, что версия корпуса TRIK, выбранная в TRIK Studio, отличается от версии у робота.</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Generate TRIK code</source>
        <translation>Создать код TRIK</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Upload program</source>
        <translation>Отправить программу</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Run program</source>
        <translation>Выполнить программу</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Stop robot</source>
        <translation>Остановить робота</translation>
    </message>
    <message>
        <location line="+16"/>
        <source>Generate TRIK Code</source>
        <translation>Создать код TRIK</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Upload TRIK Program</source>
        <translation>Отправить программу TRIK</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Run TRIK Program</source>
        <translation>Выполнить программу TRIK</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Stop TRIK Robot</source>
        <translation>Остановить робота TRIK</translation>
    </message>
    <message>
        <location line="+72"/>
        <source>There are no files to upload. You must open or generate at least one *.js or *.py file.</source>
        <translation>Нет файлов для отправки. Необходимо открыть или создать хотя бы один файл *.js или *.py.</translation>
    </message>
    <message>
        <source>No connection to robot</source>
        <translation type="vanished">Нет соединения с роботом, проверьте настройки, проверьте, включён ли робот</translation>
    </message>
</context>
</TS>
