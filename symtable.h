/*symtable.h*/

// 
// << Tirth Patel >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #03: symtable
//
// Symbol Table: a symbol table is a stack of scopes, typically used by a
// compiler to keep track of symbols in a program (functions, variables,
// types, etc.).  In most programming languages, you "enter scope" when you 
// see {, and "exit scope" when you see the corresponding }.  Example:
//
// int main()
// {              <-- enterScope()
//    int i;      <-- enter "i" into symbol table as type "int"
//    .
//    .
//    while (true)
//    {              <-- enterScope()
//       char i;     <-- enter "i" into symbol table as type "char"
//
// Notice there are two variables named "i", which is legal because
// they are in different scopes.
//

#pragma once

#include <iostream>
#include <deque>
#include <map>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename KeyT, typename SymbolT>
class symtable
{
public:
  //
  // A symbol table is a stack of scopes.  Every scope has a name, and 
  // we use a map to hold the symbols in that scope.  You can *add* to
  // this class, but you must use the Name and Symbols as given to store
  // the scope name, and scope symbols, respectively.
  //
  class Scope
  {
  public:
    string              Name;
    map<KeyT, SymbolT>  Symbols; 

    // constructors:
    Scope()
    {
      // default empty string and an empty map:
    }

    Scope(string name)
    {
      this->Name = name;
      // empty map created by map's constructor:
    }
  };

private:
  //
  // TODO: implementation details
  //
  deque<Scope> mydeque;   // deque of scopes 
  int Size = 0;             // to keep track of number of symbols in symbol table 
  int NumScopes = 0;         // to keep track of total scopes 

public:
  enum class ScopeOption
  {
    ALL, 
    CURRENT,
    GLOBAL
  };

  //
  // default constructor:
  //
  // Creates a new, empty symbol table.  No scope is open.
  //
  symtable()
  {
    //  
    // TODO: note that member variables will have their default constructor 
    // called automatically, so there may be nothing to do here.
    //
    
  }

  //
  // size
  //
  // Returns total # of symbols in the symbol table.
  //
  // Complexity: O(1)
  //
  int size() const
  {
	return Size;
  }

  //
  // numscopes
  //
  // Returns the # of open scopes.
  //
  // Complexity: O(1)
  //
  int numscopes() const
  {
    return mydeque.size();   
  }

  //
  // enterScope
  //
  // Enters a new, open scope in the symbol table, effectively "pushing" on
  // a new scope.  You must provide a name for the new scope, although
  // the name is currently used only for debugging purposes.
  //
  // NOTE: the first scope you enter is known as the GLOBAL scope, since this
  // is typically where GLOBAL symbols are stored.  
  //
  // Complexity: O(1)
  //
  void enterScope(string name)
  { 
     mydeque.push_front(name);
	 NumScopes++;
	
  }

  //
  // exitScope
  //
  // Exits the current open scope, discarding all symbols in this scope.
  // This effectively "pops" the symbol table so that it returns to the 
  // previously open scope.  A runtime_error is thrown if no scope is 
  // currently open.  
  //
  // Complexity: O(1)
  //
  void exitScope()
  {
    //
    // TODO:
    //
    if(mydeque.empty())
	{
		throw runtime_error("No open scope");
	}
	Size = Size - mydeque.front().Symbols.size();
    mydeque.pop_front();   // pop the front of the deck which is current scope 
  }	

  //
  // curScope
  //
  // Returns a copy of the current scope.  A runtime_error is thrown if
  // no scope is currently open.
  //
  // Complexity: O(N) where N is the # of symbols in the current scope
  //
  Scope curScope() const
  {
	  Scope scope = mydeque.front();   // a cope of current scope 
    //
    // TODO:
    if(mydeque.empty())
	{
		throw runtime_error("Empty symtable");
	}
	else 
     return scope;
	
  }

  //
  // insert
  //
  // Inserts the (key, symbol) pair in the *current* scope.  If the key
  // already exists in the current scope, the associated symbol is replaced
  // by this new symbol.
  //
  // Complexity: O(lgN) where N is the # of symbols in current scope
  //
  void insert(KeyT key, SymbolT symbol)
  {
	if(mydeque.front().Symbols.count(key) == 1)   // if key is found .. already exists 
	{
		mydeque.front().Symbols[key] = symbol;      //   overwrite the key with new symbol
	}
	else{   // add a key and symbol and increcent the size
	
		mydeque.front().Symbols[key] = symbol ;
		Size++;                                 
	}
		
	
  }

  //
  // lookup
  //
  // Searches the symbol table for the first (key, symbol) pair that 
  // matches the given key.  The search starts in the current scope, and 
  // proceeds "outward" to the GLOBAL scope.  If a matching (key, symbol)
  // pair is found, true is returned along with a copy of the symbol (via 
  // "symbol" reference parameter).  If not found, false is returned and
  // the "symbol" parameter is left unchanged.
  //
  // NOTE: the search can be controlled by the "option" parameter.  By 
  // default, the entire symbol table is searched as described above.
  // However, the search can also be limited to just the current scope, 
  // or just the GLOBAL scope, via the "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   string                   symbol;
  //   bool                     found;
  //   ...
  //   found = table.lookup("i", 
  //                        symbol, 
  //                        symtable<string,string>::ScopeOption::CURRENT);
  //
  // Complexity: O(SlgN) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  bool lookup(KeyT key, 
              SymbolT& symbol, 
              ScopeOption option = ScopeOption::ALL) const
  {
  
	if(option == ScopeOption::ALL)
	{
	for(size_t i= 0 ; i < mydeque.size(); ++i)
	 {
		auto ptr = mydeque[i].Symbols.find(key);     // point the iterator at the key 
		if(ptr != mydeque[i].Symbols.end())      // if key is present 
		{
			symbol = ptr->second;                   // make the symbol the value of what 			  								  //iterator points at
			return true  ;
		}
	    
	 }
	}
	else if(option == ScopeOption::CURRENT)
	{
	auto ptr = mydeque.front().Symbols.find(key);    // get the iterator to point to current scope

		if(ptr  != mydeque.front().Symbols.end())             // make the symbol the value of what 
				  								          //iterator points at
		{
			symbol = ptr->second;                         //  copy of symbol via reference parameter
				return true;
		}
	}
	else if(option == ScopeOption::GLOBAL)
	{
		auto ptr = mydeque.back().Symbols.find(key);      // get the iterator point to global scope 
												          // back of the deque 
		if( ptr != mydeque.back().Symbols.end())
		{
			symbol = ptr->second;                        // copy of symbol via reference parameter
			return true;
			}
	}
    
    return false;
  }

  //
  // dump
  // 
  // Dumps the contents of the symbol table to the output stream, 
  // starting with the current scope and working "outward" to the GLOBAL
  // scope.  You can dump the entire symbol table (the default), or dump
  // just the current scope or global scope; this is controlled by the 
  // "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   ...
  //   table.dump(std::cout, symtable<string,string>::ScopeOption::GLOBAL);
  //
  // Complexity: O(S*N) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  void dump(ostream& output, ScopeOption option = ScopeOption::ALL) const
  {
    output << "**************************************************" << endl;

    if (option == ScopeOption::ALL)
      output << "*************** SYMBOL TABLE (ALL) ***************" << endl;
    else if (option == ScopeOption::CURRENT)
      output << "*************** SYMBOL TABLE (CUR) ***************" << endl;
    else // global:
      output << "*************** SYMBOL TABLE (GBL) ***************" << endl;

    output << "** # of scopes: " << this->numscopes() << endl;
    output << "** # of symbols: " << this->size() << endl;
	if(option == ScopeOption::CURRENT)
	{
	  output<<"** "<<mydeque.front().Name<<" **"<<endl;   // current scope is at front of deque

		for(auto &A : mydeque.front().Symbols)
		{
			output<<A.first<<": "<<A.second<<endl;
		}
	}
	else if (option == ScopeOption::GLOBAL)
	{
		output<<"** "<<mydeque.back().Name<<" **"<<endl;   // global scope is at the back of deque
		for(auto &A : mydeque.back().Symbols)
		{
			output<<A.first<<": "<<A.second<<endl;
		}
	}
	else if (option == ScopeOption::ALL)
		{

		for(size_t i = 0 ; i <mydeque.size(); ++i)   // loop through deque and then loop through scopes
		{
		  output<<"** "<<mydeque[i].Name<<" **"<<endl;

			for(auto &A : mydeque[i].Symbols)
			{
		   output<<A.first<<": "<<A.second<<endl;
		    }

		}

	}
	
    //
    // output format per scope:
    //
    // ** scopename **
    // key: symbol
    // key: symbol
    // ...
    //

    output << "**************************************************" << endl;
  }

};
