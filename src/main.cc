#include <iostream>

#include "json.hh"
#include "curl_easy.h"
#include "curl_form.h"

using curl::curl_easy;
using curl::curl_form;

int main(int argc, char *argv[])
{

  // enter your api token here
  const string token = "";

  // enter user id here
  const string user = "";
  const string message = "test message from cli";

  string msg = "token="+token+"&user="+user+"&message="+message;

  curl_easy easy;

  curl_pair<CURLoption,string> url_opt(CURLOPT_URL, "https://api.pushover.net/1/messages.json");

  try {
    easy.add(url_opt);

    easy.add(curl_pair<CURLoption,bool>(CURLOPT_SSL_VERIFYPEER,false));
    easy.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));
    easy.add(curl_pair<CURLoption, string>(CURLOPT_POSTFIELDS, msg));

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
