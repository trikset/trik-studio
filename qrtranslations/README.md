# Translation management

TRIK Studio uses Qt Linguist to manage translations.
However, you **do not** need to use the `lupdate` utility to update translation files.

To update files with translations, you need to add `autolupdate` value to the `CONFIG` variable when configuring the project.

```bash
qmake -r CONFIG+=autolupdate ...
```

## Creating translations for new languages

To generate translation files for a new language, you need to:
1. Create a folder in the `qrtranslations/` directory named after the language code (for example, `ru`).
2. Run the translation update mechanism (`qmake -r CONFIG+=autolupdate ...`).
3. The created folder will contain translation files that can be populated in the usual way (for example, using Qt Linguist).
