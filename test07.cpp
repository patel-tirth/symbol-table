//
// A symtable unit test based on Catch framework
//
// << YOUR NAME >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;

// this test checks for dynamic symtable.. it checks enter, insert, exit, again enter, insert, exit
TEST_CASE("(7) dynamic symtable test") 
{
  symtable<string, string>  table;
  
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  
  table.insert("i", "int");
  table.insert("j", "double");
  
  REQUIRE(table.size() == 2);
  REQUIRE(table.numscopes() == 1);
  
  table.enterScope("x");
  table.insert("k", "char");
	
  REQUIRE(table.size() == 3);
	
  table.exitScope();
	// scope exited, so size of table and numscopes should decrease
  REQUIRE(table.size() == 2);
  REQUIRE(table.numscopes() == 1); 
  
  table.enterScope("y");
  table.insert("h","double");
	
  REQUIRE(table.size() == 3);
  REQUIRE(table.numscopes() == 2); 
	
  table.exitScope();
  REQUIRE(table.size() == 2);

  
 
}

