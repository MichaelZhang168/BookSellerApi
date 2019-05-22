#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

struct DateStruct
{
	int day;
	int month;
	int year;
};

using Date = DateStruct;

class BookSellerDatabase
{
public:
	BookSellerDatabase() = delete;
	BookSellerDatabase(string _databaseName);
	~BookSellerDatabase();

	int initialiseDatabase();
	int addAuthor(string _firstName, string _lastName, string _initial);
	int addBook(int _isbn, string _bookTitle, Date _publicationDate, string _bookComment = "", string _custEmail = "");
	int addCategory(string categoryDescription);

private:
	int executeSQL(string sql);
	int executeSQLWithCallback(string sql);
	static int callback(void* data, int argc, char** argv, char** azColName);

	string dBName;
	sqlite3* bookSellerDb;
	int errorCode;
	int authorID;
	int bookID;
	int categoryCode;
	static vector<string> fieldsInRow;
	static vector<string> columnName;
};