#include "Bug.h"
#include <iostream>
#include <string>

use namespace std;

int main() {
	Bug a(123456, "Code Doesn't Compile", 1, 1, "bob@gmail.com");
	Bug b(222222, "Syntax error occurs at line 15", 0, 2, "Donovan@yahoo.com");
	Bug c(663636, "Code Doesn't Compile", 0, 0, "Kyle@hotmail.com");
	Bug d(123123, "Code creates", 2, 2, "Matt@aol.com");

	return 0;
}
