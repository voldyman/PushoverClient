#include <iostream>

#include "json.hh"
#include "curl_easy.h"

using curl::curl_easy;

int main(int argc, char *argv[])
{
  JSON::Object obj;
  obj["foo"] = "bar";
  obj["bar"] = "baz";
  obj["Num"] = 2;

  std::cout << "Hello World" << std::endl;
  std::cout << "Json: " << obj << std::endl;
  curl_easy easy;
  easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,"http://aura.tripent.net") );
  easy.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));
  try {
    easy.perform();
  } catch (curl_easy_exception error) {
    // If you want to get the entire error stack we can do:
    vector<pair<string,string>> errors = error.what();
    // Otherwise we could print the stack like this:
    error.print_traceback();
    // Note that the printing the stack will erase it
  }
  return 0;
}
