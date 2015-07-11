#pragma once

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore>
#include <qrkernel/ids.h>
#include <qrgui/plugins/pluginManager/explosion.h>
#include <qrgui/plugins/editorPluginInterface/editorInterface.h>

namespace editorPluginTestingFramework {

class ConvertingMethods
{
public:
	/// converters for methods output converting into string list
	static QStringList convertQListExplosionDataIntoStringList(QList<qReal::EditorInterface::ExplosionData> const &explDataList);
	static QStringList convertingQPairListIntoStringList(QList<QPair<QString, QString>>  const &qPairList);
	static QStringList convertIdListIntoStringList(qReal::IdList const idList);
	static QStringList convertStringIntoStringList(const QString &string);
	static QStringList convertBoolIntoStringList(bool const &boolValue);
	static QStringList convertIdIntoStringList(qReal::Id const &id);
	static QStringList convertIntIntoStringList(int const &integer);
	static QStringList convertExplosionListIntoStringList(QList<qReal::Explosion> explosion);

	/// converter to string with special symbols to parse in html
	static QString transformateOutput(const QStringList &output
			, qReal::Id const &id = qReal::Id::rootId()
			, const QString &name = ""
			);

	/// methods for parsing (common for htmlMaker and methodsCheckerForTravis)
	/// parses result for one method - because results can be equal, but in different order
	static QSet<QString> resultToCompare(const QString &method);
};

}
