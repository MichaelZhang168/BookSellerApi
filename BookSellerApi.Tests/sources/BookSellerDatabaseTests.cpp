#include "gtest/gtest.h"
#include "BookSellerDatabase.h"

TEST(BookSellerDatabaseTests, DatabaseCreation) 
{
	BookSellerDatabase dB("BookSeller.db");
	EXPECT_EQ(dB.initialiseDatabase(), SQLITE_OK);

	EXPECT_EQ(dB.initialiseDatabase(), SQLITE_OK);
}

TEST(BookSellerDatabaseTests, DatabaseCreationError)
{
	BookSellerDatabase dB("../README");
	EXPECT_EQ(dB.initialiseDatabase(), SQLITE_NOTADB);
}

TEST(BookSellerDatabaseTests, AddAuthor)
{
	BookSellerDatabase dB("BookSeller.db");
	EXPECT_EQ(dB.initialiseDatabase(), SQLITE_OK);
	EXPECT_EQ(dB.addAuthor("Michael", "Truong", "MT"), SQLITE_OK);
	EXPECT_EQ(dB.addAuthor("Michael", "Truong", "MT"), SQLITE_OK);
	EXPECT_EQ(dB.addAuthor("Michael", "Truong", "MT"), SQLITE_OK);
}

TEST(BookSellerDatabaseTests, AddBook)
{
	BookSellerDatabase dB("BookSeller.db");
	EXPECT_EQ(dB.initialiseDatabase(), SQLITE_OK);
	Date pubDate{ 22,05,2019 };
	EXPECT_EQ(dB.addBook(123456, "Bookworld", pubDate, "This is a fun book to read."), SQLITE_OK);
	EXPECT_EQ(dB.addBook(123456, "Bookworld", pubDate, "This is a fun book to read."), SQLITE_OK);
	EXPECT_EQ(dB.addBook(123456, "Bookworld", pubDate, "This is a fun book to read."), SQLITE_OK);
}

TEST(BookSellerDatabaseTests, AddBookCategory)
{
	BookSellerDatabase dB("BookSeller.db");
	EXPECT_EQ(dB.initialiseDatabase(), SQLITE_OK);
	EXPECT_EQ(dB.addCategory("Non Fiction"), SQLITE_OK);
	EXPECT_EQ(dB.addCategory("Non Fiction"), SQLITE_OK);
	EXPECT_EQ(dB.addCategory("Non Fiction"), SQLITE_OK);
}
