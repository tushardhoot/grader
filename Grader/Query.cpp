#include "Query.h"

Query::Query(QSqlDatabase db)
	:QSqlQuery(db) {

}

Query::~Query() {
}