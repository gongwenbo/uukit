#include "database.h"
DataBase::DataBase(const sql::SQLString& user_name,const sql::SQLString& password)){

	sql::Driver *driver_=new sql::Driver();
  	sql::Connection *con_=new sql::Connection();
  	sql::Statement *stmt_=new sql::Statement();
  	sql::ResultSet *res_=new sql::ResultSet();

	driver_ = get_driver_instance();	
  	con_ = driver_->connect(DATABASE_SERVER_INFO, user_name, password);	
 
}


int DataBase::GetDataFromDb(const std::string&data_base_name,const std::string& commond){

 	con_->setSchema(data_base_name);
	stmt_ = con_->createStatement();
    res_ = stmt_->executeQuery(commond);
	while (res->next()) {
    /* Access column data by alias or column name */
    cout << res->getString("species") << endl;

    /* Access column data by numeric offset, 1 is the first column */
    cout << res->getString(1) << endl;
 
	}
	return 0;

}








