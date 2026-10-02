<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ru_RU">
<context>
    <name>QObject</name>
    <message>
        <source>Emulates robot`s behaviour on TRIK Studio 2D model separately from programming environment. Passed .qrs will be interpreted just like when &apos;Run&apos; button was pressed in TRIK Studio.</source>
        <translation type="vanished">Эмулирует поведение робота на 2D модели TRIK Studio отдельно от редактора программ. Указанный файл сохранения .qrs будет исполнен, как в случае нажатия на кнопку &quot;Запуск&quot; в среде.</translation>
    </message>
    <message>
        <location filename="../../../../plugins/robots/checker/twoDModelRunner/main.cpp" line="+30"/>
        <source>Emulates robot`s behaviour on TRIK Studio 2D model separately from programming environment. Passed .qrs will be interpreted just like when &apos;Run&apos; button was pressed in TRIK Studio. 
In background mode the session will be terminated just after the execution ended and return code will then contain binary information about program correctness.Example: 
</source>
        <translation>Эмулирует поведение робота на 2D модели TRIK Studio отдельно от программного окружения. Передаваемые файлы .qrs будут интерпретироваться так же, как при нажатии кнопки «Выполнить» в TRIK Studio. 
В фоновом режиме сеанс будет завершён сразу после окончания выполнения программы, а код возврата будет содержать двоичные данные о корректности программы. Например: 
</translation>
    </message>
    <message>
        <location line="+72"/>
        <source>Save file to be interpreted.</source>
        <translation>Сохранить файл для интерпретации.</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Run emulation in background.</source>
        <translation>Выполнить эмуляцию в фоновом режиме.</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>A path to file where checker results will be written (JSON).</source>
        <translation>Путь к файлу, в который будут записаны результаты проверки (JSON).</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Inputs for JavaScript solution.</source>
        <translation>Входные данные для решения JavaScript.</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Set to &quot;script&quot; for execution of js/py from the project or set to &quot;diagram&quot; for block diagram.</source>
        <translation>Установите «сценарий» для выполнения сценария js/py из проекта или «диаграмма» для выполнения блок-диаграммы.</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Speed factor, try from 5 to 20, or even 1000 (at your own risk!).</source>
        <translation>Ускорение, используйте от 5 до 20 или даже 1000 (на свой страх и риск).</translation>
    </message>
    <message>
        <location line="-10"/>
        <source>A path to file where robot`s trajectory will be written. The writing will not be performed not immediately, each trajectory point will be written just when obtained by checker, so FIFOs are recommended to be targets for this option.</source>
        <translation>Путь к файлу, в который будет записана траектория робота. Запись будет производиться не сразу; каждая точка траектории будет записываться только после получения средством проверки. Поэтому рекомендуется использовать FIFO-файлы в качестве значения этого параметра.</translation>
    </message>
    <message>
        <location line="+13"/>
        <source>Close the window and exit if the diagram/script finishes without errors.</source>
        <translation>Закрыть окно, если диаграмма или сценарий завершились без ошибок.</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Close the window and exit after diagram/script finishes.</source>
        <translation>Закрыть окно и выйти после завершения диаграммы или сценария.</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Shows robot&apos;s console.</source>
        <translation>Отображает консоль робота.</translation>
    </message>
    <message>
        <source>A path to file where robot`s trajectory will be written. The writing will not be performed not immediately, each trajectory point will be written just when obtained by checker, engine so FIFOs are recommended to be targets for this option.</source>
        <translation type="obsolete">Путь к файлу, куда будует выводиться траектория робота. Записть не будет осуществлена одномоментно, каждый узел траектории будет записан по факту его подсчета проверяющей системой</translation>
    </message>
</context>
<context>
    <name>twoDModel::Runner</name>
    <message>
        <location filename="../../../../plugins/robots/checker/twoDModelRunner/runner.cpp" line="+203"/>
        <source>Robot console</source>
        <translation>Консоль робота</translation>
    </message>
</context>
</TS>
