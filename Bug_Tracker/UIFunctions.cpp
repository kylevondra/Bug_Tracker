#include <iostream>
#include <vector>
#include "utils.cpp"
#include "textBlurbs.h"
#include "Bug.h"

Bug* addBug(string* str) {
  //TODO check str has been trimmed and lowercased
  if (str->find("add") == 0) {
    if (str->find_first_of(' ') == 3) {
      std::stringstream ss(*str);
      string temp;
      std::vector<string> args;

      while (getline(ss, temp, ' ')) {
        //std::cout << temp << ", ";
        args.push_back(temp);
      }

      if (args.size() > 5) {
        std::cout << "add: " << tooManyArgs << std::endl;
      }
      else
      if (args.size() < 5) {
        std::cout << "add: " << notEnoughArgs << std::endl;
      }
      else {
        Bug* b = new Bug();
        try {
          short temp = std::stoi(args[2]);
          if (temp < 1 || temp > 3) {
            throw std::invalid_argument("");
          }
          b->setPriority(temp);

          temp = std::stoi(args[3]);
          if (temp < 1 || temp > 3) {
            throw std::invalid_argument("");
          }
          b->setStatus(temp);
        }
        catch (std::invalid_argument& e) {
          std::cout << "add: arguments 2 and 3 must be intergers between 1 - 3" << std::endl;
          std::cout << addHelp << std::endl;

          delete b;
          return NULL;
        }

        if (!parseEmail(&(args[4]))) {
          delete b;
          std::cout << "add: assignee must be a valid email address" << std::endl;
          std::cout << addHelp << std::endl;

          return NULL;
        }

        b->setAssignee(args[4]);
        b->setTitle(args[1]);

        return b;
      }
    }
    std::cout << addHelp << std::endl;
  }
  return NULL;

}
