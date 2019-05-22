#include "BookSellerServerApi.h"
#include <iostream>

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<BookSellerServer> g_http;
using std::cout;
using std::cin;

void on_initialize(const string_t& _address)
{
    uri_builder uri(_address);
    uri.append_path(U("BookSellerServer/Action/"));

    auto addr = uri.to_uri().to_string();
	g_http = std::unique_ptr<BookSellerServer>(new BookSellerServer(addr));
	g_http->open().wait();
    
    ucout << utility::string_t(U("Server started on address: ")) << addr << std::endl;
}

void on_shutdown()
{
	g_http->close().wait();
}

void startBookSellerServer(utility::string_t port)
{
    utility::string_t address = U("http://localhost:");
    address.append(port);

    on_initialize(address);
    cout << "Press anykey to terminate Server." << std::endl;

	char inputChar;
	cin >> inputChar;

    on_shutdown();
}