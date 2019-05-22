#include "stdafx.h"
//#include "messagetypes.h"
#include "BookSellerServer.h"

using namespace std;
using namespace web; 
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

BookSellerServer::BookSellerServer(utility::string_t _url) : 
	listener(_url),
	database("BookSeller.db")
{
    listener.support(methods::GET, std::bind(&BookSellerServer::handleGet, this, std::placeholders::_1));
    listener.support(methods::PUT, std::bind(&BookSellerServer::handlePut, this, std::placeholders::_1));

	database.initialiseDatabase();
}

void BookSellerServer::handleGet(http_request message)
{
	// Task 2: Handle request to get books here
	// Task 4: Handle request to search for books here
	message.reply(status_codes::OK);
};

void BookSellerServer::handlePut(http_request message)
{
	// Task 3: Handling request to create order transaction
	message.reply(status_codes::OK);
};
