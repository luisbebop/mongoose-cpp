#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdlib.h>
#include <signal.h>
#include <mongoose/Server.h>
#include <mongoose/WebController.h>
#include "otbImage.h"
#include <iostream>

using namespace std;
using namespace Mongoose;

class MyController : public WebController
{
    public: 
        void hello(Request &request, StreamResponse &response)
        {
            response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
        }

        void otb(Request &request, StreamResponse &response)
        {
			typedef otb::Image<unsigned short, 2> ImageType;
		  	ImageType::Pointer image = ImageType::New();
            response << "otb::Image OTB Hello World !" << endl;
        }

        void setup()
        {
            addRoute("GET", "/hello", MyController, hello);
			addRoute("GET", "/otb", MyController, otb);
        }
};

int main()
{
    MyController myController;
    Server server(8080);
    server.registerController(&myController);
  	std::cout << "server running at 8080 with the endpoints:\n/hello\n/otb" << std::endl;

    server.start(); 

    while (1) {
#ifdef WIN32
		Sleep(10000);
#else
        sleep(10);
#endif
    }
}
