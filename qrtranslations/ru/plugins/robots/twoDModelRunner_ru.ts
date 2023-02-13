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
        <translation>Эмулирует поведение робота на 2D модели TRIK Studio отдельно от редактора программ. Указанный файл сохранения .qrs будет исполнен, как в случае нажатия на кнопку &quot;Запуск&quot; в среде. 
В режиме проверки сессия будет автоматически закрыта по факту завершения исполнения программы, в этом случае код возврата будет содержать бинарную информацию о корректности программы. Пример: 
</translation>
    </message>
    <message>
        <location line="+72"/>
        <source>Save file to be interpreted.</source>
        <translation>Файл сохранения, который будет исполнен.</translation>
    </message>
    <message>
        <location line="+1"/>
        <source>Run emulation in background.</source>
        <translation>Произвести эмуляцию в фоне.</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>A path to file where checker results will be written (JSON).</source>
        <translation>Путь к файлу, куда будут записаны результаты проверки (JSON).</translation>
    </message>
    <message>
        <location line="+7"/>
        <source>Inputs for JavaScript solution.</source>
        <translation>Входные данные для JavaScript файла.</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>Set to &quot;script&quot; for execution of js/py from the project or set to &quot;diagram&quot; for block diagram.</source>
        <translation>Установите &quot;script&quot; для выполнения js/py скрипта из проекта или установите &quot;diagram&quot; для выполнения диаграммы блоков.</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>Speed factor, try from 5 to 20, or even 1000 (at your own risk!).</source>
        <translation>Ускорение, попробуйте от 5 до 20, но можно пробовать и 1000.</translation>
    </message>
    <message>
        <location line="-10"/>
        <source>A path to file where robot`s trajectory will be written. The writing will not be performed not immediately, each trajectory point will be written just when obtained by checker, so FIFOs are recommended to be targets for this option.</source>
        <translation>Путь к файлу, куда будет выводиться траектори робота. Запись не будет осуществлена единомоментно, каждый узел траектории будет записан по факту его просчета проверяющей системой. Поэтому разумно использования FIFO-файлов в качестве значения этого параметра.</translation>
    </message>
    <message>
        <location line="+13"/>
        <source>Close the window and exit if the diagram/script finishes without errors.</source>
        <translation>Закрыть окно если диаграмма/скрипт были выполнены без ошибок.</translation>
    </message>
    <message>
        <location line="+3"/>
        <source>Close the window and exit after diagram/script finishes.</source>
        <translation type="unfinished"></translation>
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
