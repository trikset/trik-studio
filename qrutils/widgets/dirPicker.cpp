#include "dirPicker.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStyle>

#include <qrkernel/settingsManager.h>
#include <qrutils/widgets/qRealFileDialog.h>

using namespace qReal::ui;


dirPicker::dirPicker(QWidget *parent)
    : QWidget(parent)
{
    mLabel = new QLabel(this);
    mPathEditor = new QLineEdit(this);
    QPushButton *button = new QPushButton(style()->standardIcon(QStyle::SP_DirIcon), tr("Browse..."), this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(mLabel);
    layout->addWidget(mPathEditor);
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, &dirPicker::pick);
}

void dirPicker::configure(const QString &settingsKey, const QString &title)
{
    mSettingsKey = settingsKey;
    mLabel->setText(title);
}

bool dirPicker::isSavedDirExist(){
    return QDir(SettingsManager::value(mSettingsKey).toString()).exists();

}

void dirPicker::save() const
{
    if (!mPathEditor->text().isEmpty() && !mSettingsKey.isEmpty()) {
        SettingsManager::setValue(mSettingsKey, mPathEditor->text());
    }
}

void dirPicker::restore()
{
    if (!mSettingsKey.isEmpty()) {
        mPathEditor->setText(SettingsManager::value(mSettingsKey).toString());
    }
}

void dirPicker::pick()
{
    QDir dirPath=QFileDialog::getExistingDirectory(this, "Get Any File");
    SettingsManager::setValue(mSettingsKey, dirPath.absolutePath());
    mPathEditor->setText(dirPath.absolutePath());
}
