#ifndef DIRPICKER_H
#define DIRPICKER_H

#include <QtWidgets/QWidget>

#include <qrutils/utilsDeclSpec.h>

class QLabel;
class QLineEdit;

namespace qReal {
namespace ui {

/// Picks some image from disk, saves into settings.
class QRUTILS_EXPORT dirPicker : public QWidget
{
    Q_OBJECT

public:
    explicit dirPicker(QWidget *parent = nullptr);

    /// Sets parameters of the image picker.
    void configure(const QString &settingsKey, const QString &title);

    /// Saves picked location into settings.
    void save() const;

    /// Restores last picked value.
    void restore();

    bool isSavedDirExist();


private slots:
    void pick();

private:
    QString mSettingsKey;
    QLabel *mLabel;
    QLineEdit *mPathEditor;
};

}
}


#endif // DIRPICKER_H
