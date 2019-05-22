#include "BookSellerDatabase.h"
#include <iostream>
#include <fstream>
#include <io.h>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::to_string;

vector<string> BookSellerDatabase::fieldsInRow;
vector<string> BookSellerDatabase::columnName;

BookSellerDatabase::BookSellerDatabase(string _databaseName) :
	dBName(_databaseName),
	bookSellerDb(nullptr),
	errorCode(0),
	authorID(1),
	bookID(1),
	categoryCode(1)
{
}

BookSellerDatabase::~BookSellerDatabase()
{
}

int BookSellerDatabase::initialiseDatabase()
{
	string createCustomerTableSql = "CREATE TABLE CUSTOMERS("
		"CUSTOMER_ID INT PRIMARY KEY NOT NULL, "
		"CUSTOMER_CODE		 TEXT	 NOT NULL, "
		"CUSTOMER_NAME		 TEXT	 NOT NULL, "
		"CUSTOMER_ADDRESS	 TEXT	 NOT NULL, "
		"CUSTOMER_PHONE		 INT			 , "
		"CUSTOMER_EMAIL		 TEXT			 );";

	string createOrdersTableSql = "CREATE TABLE ORDERS("
		"ORDER_DATE			 TEXT	 NOT NULL, "
		"ORDER_VALUE		 REAL	 NOT NULL);";


	string createOrderItemsTableSql = "CREATE TABLE ORDER_ITEMS("
		"ITEM_NUMBER		 INT PRIMARY KEY NOT NULL, "
		"ITEM_AGREED_PRICE	 REAL			 NOT NULL, "
		"ITEM_COMMENT		 TEXT					 );";

	string createBooksTableSql = "CREATE TABLE BOOKS("
		"BOOK_ID			 INT PRIMARY KEY NOT NULL, "
		"ISBN				 INT	 NOT NULL, "
		"BOOK_TITLE			 TEXT	 NOT NULL, "
		"PUBLICATION_DATE	 TEXT	 NOT NULL, "
		"BOOK_COMMENTS		 TEXT			 , "
		"CUSTOMER_EMAIL		 TEXT			 );";

	string createAuthorsTableSql = "CREATE TABLE AUTHORS("
		"AUTHOR_ID			 INT PRIMARY KEY NOT NULL, "
		"AUTHOR_FIRST_NAME	 TEXT	 NOT NULL, "
		"AUTHOR_INITIALS	 TEXT			 , "
		"AUTHOR_LAST_NAME	 TEXT    NOT NULL);";

	string createBookCategoriesTableSql = "CREATE TABLE BOOK_CATEGORIES("
		"BOOK_CATEGORIES_CODE INT PRIMARY KEY NOT NULL, "
		"BOOK_CATEGORY_DESCRIPTION		 TEXT NOT NULL);";

	string createContactsTableSql = "CREATE TABLE CONTACTS("
		"CONTACT_ID			 INT PRIMARY KEY NOT NULL, "
		"CONTACT_FIRST_NAME	 TEXT	 NOT NULL, "
		"CONTACT_LAST_NAME	 TEXT	 NOT NULL, "
		"CONTACT_WORK_PHONE	 INT,			   "
		"CONTACT_CELL_PHONE  INT,			   "
		"CONTACT_OTHER_DETAILS	TEXT		 );";

	string createRefContactTypesTableSql = "CREATE TABLE REF_CONTACT_TYPES("
		"CONTACT_CODE			 INT PRIMARY KEY NOT NULL, "
		"CONTACT_DESCRIPTION	 TEXT					 );";

	ifstream file(dBName.c_str());
	if(file.good())
	{
		string sql = "SELECT AUTHOR_ID FROM AUTHORS;";
		executeSQLWithCallback(sql);
		authorID = fieldsInRow.empty()? 0 : stoi(fieldsInRow.back());
		authorID++;

		sql = "SELECT BOOK_ID FROM BOOKS";
		executeSQLWithCallback(sql);
		bookID = fieldsInRow.empty() ? 0 : stoi(fieldsInRow.back());
		bookID++;

		sql = "SELECT BOOK_CATEGORIES_CODE FROM BOOK_CATEGORIES";
		executeSQLWithCallback(sql);
		categoryCode = fieldsInRow.empty() ? 0 : stoi(fieldsInRow.back());
		categoryCode++;
	}
	else
	{
		if ((executeSQL(createCustomerTableSql) == SQLITE_OK)
			&& (executeSQL(createOrdersTableSql) == SQLITE_OK)
			&& (executeSQL(createOrderItemsTableSql) == SQLITE_OK)
			&& (executeSQL(createBooksTableSql) == SQLITE_OK)
			&& (executeSQL(createAuthorsTableSql) == SQLITE_OK)
			&& (executeSQL(createBookCategoriesTableSql) == SQLITE_OK)
			&& (executeSQL(createContactsTableSql) == SQLITE_OK)
			&& (executeSQL(createRefContactTypesTableSql) == SQLITE_OK))
		{
			cout << "Table Created Successfully." << endl;
		}
	}


	return errorCode;
}

int BookSellerDatabase::addAuthor(string _firstName, string _lastName, string _initial)
{
	string sql = "INSERT INTO AUTHORS "
		"(AUTHOR_ID,AUTHOR_FIRST_NAME, AUTHOR_LAST_NAME, AUTHOR_INITIALS) "
		"VALUES (" + to_string(authorID) + ",'" + _firstName + "','" 
		+ _lastName + "','" + _initial + "')";
	
	authorID++;
	
	return executeSQL(sql);
}

int BookSellerDatabase::addBook(int _isbn, string _bookTitle, Date _publicationDate, string _bookComment, string _custEmail)
{
	string pubDate = to_string(_publicationDate.day) + "-"
					+ to_string(_publicationDate.month) + "-"
					+ to_string(_publicationDate.year);
	string sql = "INSERT INTO BOOKS "
		"(BOOK_ID,ISBN,BOOK_TITLE,PUBLICATION_DATE,BOOK_COMMENTS,CUSTOMER_EMAIL) "
		"VALUES (" + to_string(bookID) + "," + to_string(_isbn) + ",'"
		+ _bookTitle + "','" + pubDate + "','" + _bookComment
		+ "','" + _custEmail + "')";

	bookID++;

	return executeSQL(sql);
}

int BookSellerDatabase::addCategory(string _categoryDescription)
{
	string sql = "INSERT INTO BOOK_CATEGORIES"
		"(BOOK_CATEGORIES_CODE,BOOK_CATEGORY_DESCRIPTION) "
		"VALUES (" + to_string(categoryCode) + ",'" + _categoryDescription + "')";

	categoryCode++;

	return executeSQL(sql);
}

int BookSellerDatabase::callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; ++i) 
	{
		columnName.push_back(azColName[i]);
		fieldsInRow.push_back(argv[i] ? argv[i] : "NULL");
	}

	return 0;
}

int BookSellerDatabase::executeSQLWithCallback(string sql)
{
	char* errorMessage;
	errorCode = sqlite3_open(dBName.c_str(), &bookSellerDb);
	if (errorCode != SQLITE_OK)
	{
		cerr << "Error Opening Database: " << dBName << endl;
		return errorCode;
	}

	fieldsInRow.clear();
	columnName.clear();

	errorCode = sqlite3_exec(bookSellerDb, sql.c_str(), callback, nullptr, &errorMessage);

	if (errorCode != SQLITE_OK) {
		cerr << "Error Create Table: " << errorMessage << endl;
		sqlite3_free(errorMessage);
	}

	sqlite3_close(bookSellerDb);
	return errorCode;
}

int BookSellerDatabase::executeSQL(string sql)
{
	char* errorMessage;
	errorCode = sqlite3_open(dBName.c_str(), &bookSellerDb);
	if (errorCode != SQLITE_OK)
	{
		cerr << "Error Opening Database: " << dBName << endl;
		return errorCode;
	}

	errorCode = sqlite3_exec(bookSellerDb, sql.c_str(), nullptr, nullptr, &errorMessage);

	if (errorCode != SQLITE_OK) {
		cerr << "Error: " << errorMessage << endl;
		sqlite3_free(errorMessage);
	}

	sqlite3_close(bookSellerDb);
	return errorCode;
}

