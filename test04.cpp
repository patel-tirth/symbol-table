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

// CurScope test to check whether the program makes a copy of curScope and finds the correct symbol
// corresponding to that key 
TEST_CASE("(4) Curr Scope test") 
{
symtable<string, string>  table;
symtable<string, string>::Scope  scope;
	
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
	
  table.insert("i", "int");
  table.insert("j", "double");
  scope = table.curScope();
  
  REQUIRE(scope.Symbols.find("i")->second == "int");

  REQUIRE(scope.Symbols.find("j")->second == "double");

  REQUIRE(scope.Symbols.size() == 2);
  REQUIRE(table.numscopes() == 1);
  
  table.enterScope("x");
  table.insert("k", "char");
  scope = table.curScope();
  
  REQUIRE(scope.Symbols.find("k")->second == "char");
  REQUIRE(scope.Symbols.find("i") == scope.Symbols.end()); // i is not in this scope.. so find points
														   // at the end of map 

  REQUIRE(scope.Symbols.size() == 1);
  REQUIRE(table.numscopes() == 2); 
 
}

