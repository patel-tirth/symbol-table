
#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;

// This test case checks for scopeOption::CURRENT
TEST_CASE("(6) scope options test") 
{
  symtable<string, string>  table;
  string symbol;
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  table.insert("i", "int");

  table.enterScope("current");
  table.insert("j", "double");
 
  REQUIRE(table.lookup("j",symbol, symtable<string,string>::ScopeOption::CURRENT));
  REQUIRE(symbol == "double");
	
	table.enterScope("third");
	table.insert("l","float");
	
  REQUIRE(!table.lookup("j",symbol, symtable<string,string>::ScopeOption::CURRENT));


  table.enterScope("x");
  table.insert("k", "char");
 

  table.exitScope();	
  REQUIRE((!table.lookup("k", symbol)));
	
}




