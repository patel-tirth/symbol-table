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

// this test case checks if you try to exit the scope when there is no open scope .. it checks if
// exception is thrown correctly
TEST_CASE("(8) Exit scope test") 
{
  symtable<string, string>  table;
  string symbol;
	table.enterScope("global");
	table.insert("i","int");
		table.insert("j","float");
	table.insert("k","double");

	table.insert("l","char");


	
 table.dump(std::cout, symtable<string,string>::ScopeOption::GLOBAL);
	table.enterScope("all");
	table.insert("m","int");
		table.insert("n","float");
	table.insert("o","double");


table.dump(std::cout, symtable<string,string>::ScopeOption::ALL);


//   REQUIRE(table.size() == 0);
//   REQUIRE(table.numscopes() == 0);
// 	 REQUIRE_THROWS(table.exitScope());   
// 	table.enterScope("x");
// 	table.insert("i","int");
// 	table.insert("i","cout");
// 	table.insert("j","double");
// 	REQUIRE(table.size() == 2);
// 	REQUIRE(table.lookup("i",symbol));
// 	REQUIRE(symbol == "cout");
// 	REQUIRE(table.numscopes() == 1);
// 	table.enterScope("y");
// 		REQUIRE(table.numscopes() == 2);
// 	table.exitScope();
// 	REQUIRE(table.numscopes() == 1);
// // 	table.insert("i")
// //  REQUIRE((!table.lookup("i",symbol)));   // not found 
	
//   // exiting a scope when no scope is open throws an error


}



