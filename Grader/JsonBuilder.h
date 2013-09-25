#ifndef JSONBUILDER_H
#define JSONBUILDER_H

#include <QObject>
#include <QString>
#include <QVector>

class JsonBuilder : public QObject {
	Q_OBJECT
	public:
		JsonBuilder();
		JsonBuilder(JsonBuilder& jsonBuilder);
		static struct Json {
			QString key;
			QString val;
		};

		QString build() const;
		void add(QString key); // assuming null val
		void add(QString key, QString val);
		void add(QString key, int val);
		void add(QString key, double val);
		void add(QString key, bool val);
		void add(Json json);
	private:
		QVector<Json> attrs;

};

#endif