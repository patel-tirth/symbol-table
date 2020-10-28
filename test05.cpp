
#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;

// Scope option test for global scope 
TEST_CASE("(5) scope options test") 
{
  symtable<string, string>  table;
  string symbol;
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  table.insert("i", "int");

  table.enterScope("q");
  table.insert("j", "double");
 
  REQUIRE(table.lookup("i",symbol, symtable<string,string>::ScopeOption::GLOBAL));
  REQUIRE(symbol == "int");
  REQUIRE(!table.lookup("j",symbol, symtable<string,string>::ScopeOption::GLOBAL));


  table.enterScope("x");
  table.insert("k", "char");
 

  table.exitScope();	
  REQUIRE((!table.lookup("k", symbol)));
	
 }



