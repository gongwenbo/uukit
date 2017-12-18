#ifndef DATA_BASE_H
#define DATA_BASE_H
#include "common.h"
#define DATABASE_SERVER_INFO "tcp://127.0.0.1:3306"
class DataBase{

	private:
		sql::Driver *driver_;
  		sql::Connection *con_;
  		sql::Statement *stmt_;
  		sql::ResultSet *res_;
	public:
		DataBase(const sql::SQLString& user_name,const sql::SQLString& password);
		~DataBase();
		int GetDataFromDb(const std::string& commond);
		//int PutDataFromDb(const std::string& commond);

};

#endif

