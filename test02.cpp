//
// A symtable unit test based on Catch framework
//
// << Tirth Patel >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

#include <iostream>
#include "symtable.h"

#include "catch.hpp"

using namespace std;

// this  checks for multiple same  variable declaration
TEST_CASE("(3) multiple same variable declaration  test") 
{
  symtable<string, string>  table;
  string symbol;
	
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  
  table.insert("i", "int");
  table.insert("j", "double");
  table.insert("i","cout");
	
  REQUIRE(table.lookup("i", symbol));

	
  REQUIRE(table.size() == 2);
  REQUIRE(table.numscopes() == 1);
  

  REQUIRE((!table.lookup("x", symbol)));
}



