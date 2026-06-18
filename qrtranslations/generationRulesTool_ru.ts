<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ru_RU">
<context>
    <name>QObject</name>
    <message>
        <location filename="../../../plugins/generationRulesTool/lexer.cpp" line="29"/>
        <source>whitespace</source>
        <translation>пробел</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/lexer.cpp" line="30"/>
        <source>newline</source>
        <translation>новая строка</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/lexer.cpp" line="33"/>
        <source>identifier</source>
        <translation>идентификатор</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/lexer.cpp" line="72"/>
        <source>text</source>
        <translation>текст</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="31"/>
        <source>This keyword allows to apply to current element</source>
        <translation>Данная конструкция позволяет обратиться к текущему элементу</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="32"/>
        <source>This keyword allows to call some other generator; 
 example: CallGeneratorFor(elementName, generatorName)</source>
        <translation>Эта конструкция позволяет вызвать в данном фрагменте кода генератор для какого-либо другого элемента; 
пример использования: CallGeneratorFor(elementName, generatorName)</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="34"/>
        <source>This keyword allows to define generator for given element; 
 example: Generator newGenerator {}</source>
        <translation>Эта конструкция позволяет задать отдельный генератор внутри элемента;
пример использования: Generator newGenerator {}</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="36"/>
        <source>This keyword allows to traverse collection of elements; 
example: foreach (identifier in list) {}</source>
        <translation>Эта конструкция позволяет обойти коллекцию элементов; 
пример использования: foreach (identifier in list) {}</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="38"/>
        <source>This keyword allows to redirect results of generation for given element into file with given name; 
example: generateToFile(element, fileName, generatorName)</source>
        <translation>Эта конструкция позволяет перенаправить результаты генерации для данного элемента в файл с заданным именем;
пример вызова:  generateToFile(element, fileName, generatorName)</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="41"/>
        <source>This keyword allows to check some condition and depending on results of this check execute first of second subprogram; 
example: if (condition) {program1} else {program2}</source>
        <translation>Эта конструкция позволяет проверить условие и в зависимости от результатов проверки выполнить первую или вторую подпрограмму;
пример использования: if (condition) {program1} else {program2}</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="44"/>
        <source>This keyword is a part of if-expression</source>
        <translation>Эта конструкция является частью условного выражения</translation>
    </message>
    <message>
        <source>This keyword allows to traverse some collection excluding last element, NOT SUPPORTED YET; 
example: foreach_excludeLast (identifier in list) {}</source>
        <translation type="vanished">Данная конструкция позволяет обойти некоторую  коллекцию элементов, исключая последний элемент; 
пример использования: foreach_excludeLast (identifier in list) {}</translation>
    </message>
    <message>
        <source>This keyword allows to exclude element from traversed collection</source>
        <translation type="vanished">Данная конструкция позволяет исключить некоторый текст из итогового вывода</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="45"/>
        <source>This keyword allows to traverse some collection excluding last element; 
example: foreach_excludeLast (identifier in list) {}</source>
        <translation>Эта конструкция позволяет обойти коллекцию элементов, исключая последний элемент; 
пример использования: foreach_excludeLast (identifier in list) {}</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="48"/>
        <source>This keyword allows to exclude some text from the output</source>
        <translation>Эта конструкция позволяет исключить текст из итогового вывода</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="49"/>
        <source>This keyword is a part of foreach-expression</source>
        <translation>Эта конструкция является частью конструкции foreach</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="51"/>
        <source>This keyword inserts newline symbol into generated code</source>
        <translation>Эта конструкция вставляет в создаваемый код символ перевода строки</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="52"/>
        <source>This keyword inserts tab into generated code</source>
        <translation>Эта конструкция вставляет в создаваемый код табуляцию</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="54"/>
        <source>This keyword allows to obtain incoming links for given element</source>
        <translation>Эта конструкция позволяет получить список входящих связей для указанного элемента</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="55"/>
        <source>This keyword allows to obtain outcoming links for given element</source>
        <translation>Эта конструкция позволяет получить список исходящих связей для указанного элемента</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="56"/>
        <source>This keyword allows to obtain all links connected to given element</source>
        <translation>Эта конструкция позволяет получить список всех связей, соединённых с указанным элементом</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="57"/>
        <source>This keyword allows to obtain ending element for given link</source>
        <translation>Эта конструкция позволяет получить элемент, находящийся в конце указанной связи</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/appearance/keywords.h" line="58"/>
        <source>This keyword allows to obtain starting element for given link</source>
        <translation>Эта конструкция позволяет получить элемент, находящийся в начале указанной связи</translation>
    </message>
</context>
<context>
    <name>SpecifyGenerationRulesDialog</name>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyGenerationRulesDialog.ui" line="32"/>
        <source>Dialog</source>
        <translation>Диалоговое окно</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyGenerationRulesDialog.ui" line="90"/>
        <source>Templates:</source>
        <translation>Конструкции:</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyGenerationRulesDialog.ui" line="132"/>
        <source>Element properties:</source>
        <translation>Свойства элемента:</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyGenerationRulesDialog.ui" line="167"/>
        <source>Generation rule:</source>
        <translation>Правило создания:</translation>
    </message>
</context>
<context>
    <name>SpecifyPathToGeneratedCodeDialog</name>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyPathToGeneratedCodeDialog.ui" line="32"/>
        <source>Dialog</source>
        <translation>Диалоговое окно</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyPathToGeneratedCodeDialog.ui" line="60"/>
        <source>Folder:</source>
        <translation>Папка:</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyPathToGeneratedCodeDialog.ui" line="106"/>
        <source>Main file name:</source>
        <translation>Имя основного файла:</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyPathToGeneratedCodeDialog.ui" line="83"/>
        <source>Specify</source>
        <translation>Указать</translation>
    </message>
</context>
<context>
    <name>generationRules::GenerationRulesPlugin</name>
    <message>
        <source>Destroy everything</source>
        <translation type="obsolete">Сгенерировать код для текущей диаграммы</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/generationRulesPlugin.cpp" line="46"/>
        <source>Generate code for current diagram</source>
        <translation>Создать код для текущей диаграммы</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/generationRulesPlugin.cpp" line="63"/>
        <source>Add generation rule</source>
        <translation>Добавить правило создания</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/generationRulesPlugin.cpp" line="131"/>
        <source>Files generated</source>
        <translation>Файлы созданы</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/generationRulesPlugin.cpp" line="131"/>
        <source>All files have been generated to </source>
        <translation>Все файлы были созданы в </translation>
    </message>
</context>
<context>
    <name>qReal::gui::SpecifyGenerationRulesDialog</name>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyGenerationRulesDialog.cpp" line="57"/>
        <source>Specify rules for </source>
        <translation>Указать правила для </translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyGenerationRulesDialog.cpp" line="95"/>
        <source>General templates</source>
        <translation>Конструкции общего назначения</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyGenerationRulesDialog.cpp" line="96"/>
        <source>Text templates</source>
        <translation>Конструкции для работы с текстом</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyGenerationRulesDialog.cpp" line="97"/>
        <source>Links templates</source>
        <translation>Конструкции для работы со связями</translation>
    </message>
</context>
<context>
    <name>qReal::gui::SpecifyPathToGeneratedCodeDialog</name>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyPathToGeneratedCodeDialog.cpp" line="76"/>
        <source>Specify directory:</source>
        <translation>Каталог:</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyPathToGeneratedCodeDialog.cpp" line="100"/>
        <source>Warning</source>
        <translation>Предупреждение</translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyPathToGeneratedCodeDialog.cpp" line="100"/>
        <source>All files and folders from </source>
        <translation>Все файлы и папки из каталога </translation>
    </message>
    <message>
        <location filename="../../../plugins/generationRulesTool/dialogs/specifyPathToGeneratedCodeDialog.cpp" line="101"/>
        <source> directory will be removed. Continue?</source>
        <translation> будут удалены. Продолжить?</translation>
    </message>
</context>
</TS>
