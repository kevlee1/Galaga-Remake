#include <iostream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

using namespace std;

int main(int argc, char *argv[])
{

    string url = "https://polecat.me/api/plainferret";

    try

    {
        std::cout << "A random ferret: " << curlpp::options::Url(url) << std::endl;
        return 0;
    }
    catch (curlpp::LogicError &e)
    {
        std::cout << "Logic error: " << e.what() << std::endl;
    }
    catch (curlpp::RuntimeError &e)
    {
        std::cout << "Run time error: " << e.what() << std::endl;
    }

    return 1;
}