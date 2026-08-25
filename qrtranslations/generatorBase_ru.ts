<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ru_RU">
<context>
    <name>QObject</name>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/primaryControlFlowValidator.cpp" line="+44"/>
        <source>There is nothing to generate, diagram doesn&apos;t have Initial Node</source>
        <translation>Создание невозможно, на диаграмме нет начальных блоков</translation>
    </message>
    <message>
        <location line="+5"/>
        <source>Initial node must not have incoming links</source>
        <translation>Блок «Начало» не должен иметь входящих связей</translation>
    </message>
    <message>
        <location line="+34"/>
        <source>This element must have exactly ONE outgoing link</source>
        <translation>Этот элемент должен иметь ровно одну исходящую связь</translation>
    </message>
    <message>
        <location line="+10"/>
        <source>Final node must not have outgoing links</source>
        <oldsource>Final node must not have outgioing links</oldsource>
        <translation>Блок «Конец» не должен иметь исходящих связей</translation>
    </message>
    <message>
        <location line="+8"/>
        <source>If block must have exactly TWO outgoing links</source>
        <translation>Блок «Условие» должен иметь ровно две исходящие связи</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>Two outgoing links marked with &apos;true&apos; found</source>
        <translation>Найдены две исходящие связи, помеченные значением «истина»</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>Two outgoing links marked with &apos;false&apos; found</source>
        <translation>Найдены две исходящие связи, помеченные значением «ложь»</translation>
    </message>
    <message>
        <location line="+9"/>
        <source>There must be at least one link with &quot;true&quot; or &quot;false&quot; marker on it</source>
        <translation>Должна быть как минимум одна связь, помеченная значением «истина» или «ложь»</translation>
    </message>
    <message>
        <location line="+29"/>
        <source>Loop block must have exactly TWO outgoing links</source>
        <translation>Блок «Цикл» должен иметь ровно две исходящие связи</translation>
    </message>
    <message>
        <location line="+14"/>
        <source>Two outgoing links marked with &quot;body&quot; found</source>
        <translation>Найдены две исходящие связи, помеченные значением «тело цикла»</translation>
    </message>
    <message>
        <location line="+8"/>
        <source>There must be a link with &quot;body&quot; marker on it</source>
        <translation>Должна быть связь, помеченная значением «тело цикла»</translation>
    </message>
    <message>
        <location line="+38"/>
        <source>There must be exactly one link without marker on it (default branch)</source>
        <translation>Должна быть ровно одна связь без маркера (ветвь по умолчанию)</translation>
    </message>
    <message>
        <location line="+16"/>
        <source>There must be a link without marker on it (default branch)</source>
        <translation>Должна быть связь без маркера (ветвь по умолчанию)</translation>
    </message>
    <message>
        <location line="-44"/>
        <source>Outgoing links from loop block must be connected to different blocks</source>
        <translation>Исходящие связи блока «Цикл» должны быть присоединены к разным блокам</translation>
    </message>
    <message>
        <location line="+18"/>
        <source>There must be at list TWO links outgoing from switch block</source>
        <translation>Блок «Выбор» должен иметь как минимум две исходящие связи</translation>
    </message>
    <message>
        <location line="+17"/>
        <source>Duplicate case branch: &apos;%1&apos;</source>
        <translation>Найдено более одной ветки «%1»</translation>
    </message>
    <message>
        <location line="+22"/>
        <source>Fork block must have at least TWO outgoing links</source>
        <translation>Блок «Параллельные задачи» должен иметь как минимум две исходящие связи</translation>
    </message>
    <message>
        <location line="-6"/>
        <source>Unknown block type</source>
        <translation>Неизвестный блок</translation>
    </message>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/masterGeneratorBase.cpp" line="+79"/>
        <source>There is no opened diagram</source>
        <translation>Сначала откройте диаграмму</translation>
    </message>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/primaryControlFlowValidator.cpp" line="+32"/>
        <source>Outgoing link is not connected</source>
        <translation>Исходящая связь ни с чем не соединена</translation>
    </message>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/parts/subprograms.cpp" line="+83"/>
        <source>Graphical diagram instance not found</source>
        <translation>Графическая модель диаграммы с подпрограммой не найдена</translation>
    </message>
    <message>
        <location line="+125"/>
        <source>Please enter valid c-style name for subprogram &quot;</source>
        <translation>Введите корректное имя в стиле языка C для подпрограммы &quot;</translation>
    </message>
    <message>
        <location line="+6"/>
        <source>Subprograms should have unique names, please rename</source>
        <translation>Подпрограммы должны иметь уникальные имена. Переименуйте подпрограмму</translation>
    </message>
    <message>
        <source>Duplicate identifier: </source>
        <translation type="vanished">Такой идентификатор уже используется: </translation>
    </message>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/converters/reservedVariablesConverter.cpp" line="+64"/>
        <source>Device on port %1 is not configured. Please select it on the &quot;Configure devices&quot; panel on the right-hand side.</source>
        <translation>Устройство на порте %1 не настроено. Выберите его тип на панели «Параметры устройств» справа.</translation>
    </message>
    <message>
        <location line="+4"/>
        <source>/* ERROR: SELECT DEVICE TYPE */</source>
        <translation>/* ОШИБКА: ВЫБЕРИТЕ ТИП УСТРОЙСТВА */</translation>
    </message>
</context>
<context>
    <name>generatorBase::MasterGeneratorBase</name>
    <message>
        <location filename="../../../../plugins/robots/generators/generatorBase/src/masterGeneratorBase.cpp" line="+40"/>
        <source>This diagram cannot be generated into the structured code. Generating it into the code with &apos;goto&apos; statements.</source>
        <translation>Эта диаграмма не может быть сгенерирована в структурированный код. Выполняется генерация в код с помощью операторов «goto».</translation>
    </message>
    <message>
        <location line="+15"/>
        <source>This diagram cannot be even generated into the code with &apos;goto&apos;statements. Please contact the developers.</source>
        <translation>Эта диаграмма не может быть сгенерирована в код даже с помощью операторов «goto». Обратитесь к разработчикам.</translation>
    </message>
    <message>
        <location line="+2"/>
        <source>This diagram cannot be generated into the structured code.</source>
        <translation>Эта диаграмма не может быть сгенерирована в структурированный код.</translation>
    </message>
</context>
</TS>
