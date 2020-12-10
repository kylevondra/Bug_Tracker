#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>
#include <iostream>

//transform a string to lowercase
string* to_lower(string* str) {
  transform(str->begin(), str->end(), str->begin(), ::tolower);
  return str;
}

const char* whitespace = " \t";

//trim leading whitespace
string* trimLeft(string* str, const char* ws = whitespace) {
  str->erase(0, str->find_first_not_of(ws));
  return str;
}

//trim tailing whitespace
string* trimRight(string* str, const char* ws = whitespace) {
  str->erase(str->find_last_not_of(ws) + 1);
  return str;
}

//trim leading and trailed whitespace
string* trim(string* str, const char* ws = whitespace) {
  return trimLeft(trimRight(str, ws), ws);
}

string illegalCharsStrict("`~!@#$%^&*()_=+[]{}\\|;:'\",<>./?");
string illegalCharsLoose("`~!@#$%^&*()=+[]{}\\|;:'\",<>/?");

bool parseIP(string* input) { //check is a string is a valid IP address
  char* cstr = new char [input->length() + 1]; //create char array
  strcpy(cstr, input->c_str()); //make string input into char array
  char* token = strtok(cstr, "."); //tokenize cstr on .
  std::vector<int> tokens;

  try {
    while(token != NULL) { //loop through char[]
      tokens.push_back(std::stoi(token)); //finding all tokens
      token = strtok(NULL, ".");
    }
  }
  catch(std::invalid_argument& e) { //catch invalid arguement if tokens are not ints
    return false;
  }

  if (tokens.size() == 4) { //check that there are exactly for tokens
    for (int i = 0; i < 4; i++) { //loop through them
      if (tokens[i] < 0 || tokens[i] > 255) { //check bounds
        break;
      }
      if (i == 3 && tokens[0] >= 1) { //check bounds on first IP field cant be 0
        return true;
      }
    }
  }

  return false;
}

//check if a string is a valid email address
bool parseEmail(string* input) {
  size_t pos;
  if ((pos = input->find("@")) != string::npos) {
    size_t tempPos = input->find('"', 1); //check for closing quotes
    if (tempPos != string::npos) { //note: if username has quotes, entire name must be enclosed
      pos = tempPos + 1;
    }

    string str = (*input).substr(0, pos); //str = username
    if (str[0] != '"' || str[str.length() - 1] != '"') { //if username is not bounded by quotes
      if (str.find_first_of(illegalCharsLoose) != string::npos || str.find(" ") != string::npos) { //check for illegal chars
        return false;
      }
    }

    str = input->substr(pos + 1, input->length() - pos + 1); //str = everything after @
    if (!parseIP(&str)) { //if hostname is not an IP
      if ((pos = str.find(".")) != string::npos) { // pos = . if it exists
        string domain = str.substr(0, pos); //domain = everything between @ and .
        if (domain.find_first_of(illegalCharsStrict) == string::npos && domain.length() != 0) { //if domain doesnt contain illegal chars
          if (str.find_first_of(illegalCharsStrict, pos + 1) == string::npos && str.length() != 0) { //if high level domain doesnt contain illegal chars
            return true;
          }
        }
      }
      return false;
    }
    return true;
  }
  return false;
}

#endif
