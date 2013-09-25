#include "JsonBuilder.h"

JsonBuilder::JsonBuilder() {

}

JsonBuilder::JsonBuilder(JsonBuilder& jsonBuilder) {
	this->attrs = jsonBuilder.attrs;
}

QString JsonBuilder::build() const {
	QVector<Json>::const_iterator iter;
	QString result = "{ ";

	for (iter = attrs.constBegin(); iter != attrs.constEnd(); iter++) {
		if (iter != attrs.constBegin())
			result.append(",");

		result.append("\"" + iter->key + "\"").append(":").append(iter->val);	
	}

	result.append(" }");

	return result;
}

void JsonBuilder::add(QString key) {
	Json json = {key, "null"};
	add(json);
}

void JsonBuilder::add(QString key, int val) {
	Json json = {key, QString::number(val)};
	add(json);
}

void JsonBuilder::add(QString key, bool val) {
	Json json = {key, (val) ? "true" : "false"};
	add(json);
}

void JsonBuilder::add(QString key, QString val) {
	Json json = {key, QString("\"") + val + QString("\"")};
	add(json);
}

void JsonBuilder::add(QString key, double val) {
	Json json = {key, QString::number(val)};
	add(json);
}

void JsonBuilder::add(Json json) {
	attrs.push_back(json);
}