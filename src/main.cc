#include <iostream>
#include <getopt.h>

#include "json.hh"
#include "curl_easy.h"
#include "curl_form.h"

using curl::curl_easy;
using curl::curl_form;

void PushToDevice(string token, string message, string user)
{
  
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
}

void ShowHelp()
{
  std::cout << "Doh !!" << std::endl;
}

int main(int argc, char *argv[])
{
  static struct option long_options[] = {
    {"token",   required_argument, 0, 't'},
    {"message", required_argument, 0, 'm'},
    {"user",    required_argument, 0, 'u'},
    {"help",    optional_argument, 0, 'h'},
    {0,0,0,0}
  };

  string token, message, user;
  
  int current_opt;
  int opt_index;
  while((current_opt = getopt_long(argc, argv, "ht:m:u:", long_options, &opt_index)) > 0)
  {
    switch(current_opt) {
    case 't':
      token = optarg;
      break;

    case 'm':
      message = optarg;
      break;

    case 'u':
      user = optarg;
      break;

    case 'h':
      ShowHelp();
      return 0;
    }
  }

  if (token.length() <= 0 || message.length() <= 0 ||
      user.length() <= 0) {

    ShowHelp();
    return 0;
  }

  PushToDevice(token, message, user);

  return 0;
}
