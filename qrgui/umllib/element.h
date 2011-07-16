#pragma once

#include <QtGui/QGraphicsItem>
#include <QtGui/QAction>

#include "../kernel/ids.h"
#include "../editorPluginInterface/elementRepoInterface.h"
#include "elementTitle.h"

#include "contextMenuAction.h"
#include "../editorPluginInterface/elementImpl.h"

#include "../models/graphicalModelAssistApi.h"
#include "../models/logicalModelAssistApi.h"

/** @brief size of a point port */
const int kvadratik = 10;

/** @class Element
 * 	@brief base class for an element on a diagram
  * */
class Element : public QObject, public QGraphicsItem, public ElementRepoInterface
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)
public:

	Element();
	virtual ~Element(){}

	void setId(qReal::Id &id);

	void initEmbeddedControls();

	virtual void updateData();

	virtual qReal::Id id() const;
	virtual qReal::Id logicalId() const;
	virtual QString name() const;

	virtual void connectToPort() {}  // for edge
	virtual void checkConnectionsToPort() {}  // for node
	virtual QList<ContextMenuAction*> contextMenuActions();

	virtual bool initPossibleEdges() = 0;
	virtual void initTitles();
	// for inline editing we should be able to change properties value. right now via graphical
	// representation. also labels could store indices and get data themselves
	virtual void setLogicalProperty(QString const &roleName, QString const &value);
	QString logicalProperty(QString const &roleName) const;

	virtual void setColorRect(bool bl) = 0;

	void setAssistApi(qReal::models::GraphicalModelAssistApi *graphicalAssistApi, qReal::models::LogicalModelAssistApi *logicalAssistApi);

public slots:
	void singleSelectionState(const bool singleSelected);
	void selectionState(const bool selected);

signals:
	void switchFolding(bool);

protected:

	bool mMoving;
	qReal::Id mId;
	ElementImpl* mElementImpl;
	QList<ElementTitle*> mTitles;

	qReal::models::GraphicalModelAssistApi *mGraphicalAssistApi;
	qReal::models::LogicalModelAssistApi *mLogicalAssistApi;

	void initTitlesBy(QRectF const& contents);
};
