#include "DatabaseModel.h"

DatabaseModel::DatabaseModel(std::shared_ptr<QSqlDatabase> db)
	:db(db) {
}