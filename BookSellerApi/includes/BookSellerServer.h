#pragma once
#include "BookSellerDatabase.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class BookSellerServer
{
public:
	BookSellerServer() = delete;
	BookSellerServer(utility::string_t _url);

	pplx::task<void> open() { return listener.open(); }
	pplx::task<void> close() { return listener.close(); }

private:

	void handleGet(http_request message);
	void handlePut(http_request message);

	http_listener listener;
	BookSellerDatabase database;
};
