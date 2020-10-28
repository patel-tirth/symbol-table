
#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;

//Lookup test
TEST_CASE("(2) lookUp function test") 
{
  symtable<string, string>  table;
  
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  
  table.insert("i", "int");
  table.insert("j", "double");
  
  
  table.enterScope("x");
  table.insert("k", "char");
 
  string symbol;
  table.exitScope();	
  REQUIRE((!table.lookup("k", symbol)));

  
  REQUIRE(table.lookup("i", symbol));
  REQUIRE(symbol == "int");
  
  REQUIRE(table.lookup("j", symbol));
  REQUIRE(symbol == "double");
  
  REQUIRE((!table.lookup("x", symbol)));
}
