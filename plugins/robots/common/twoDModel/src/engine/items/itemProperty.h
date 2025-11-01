#pragma once

#include <QObject>

template<typename T>
class ItemProperty final {
	Q_DISABLE_COPY_MOVE(ItemProperty)
public:
	explicit ItemProperty(const QString& name, const T& value)
		: mName(name), mValue(value), mWasChanged(false) {}

	ItemProperty() = default;
	operator const T() const & { return mValue; }

	QString name() const { return mName; }

	bool wasChanged() const { return mWasChanged; }

	void setValue(const T& value) { mValue = value; }

	void changeValue(const T& value) {
		setValue(value);
		mWasChanged = true;
	}

private:
	QString mName;
	T mValue;
	bool mWasChanged;
};
