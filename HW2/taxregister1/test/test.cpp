#define CATCH_CONFIG_MAIN

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "catch.hpp"
#include "../src/taxregister.cpp"

TEST_CASE( "Simple Tests", "[taxregister]" ) {
  CTaxRegister b1;
  int income, expense;
  REQUIRE ( b1.Birth("a","ttt") );
  REQUIRE ( b1.Income("a","ttt", 780) );
  REQUIRE ( b1.Expense("a", "ttt", 69) );

  b1.Audit("a", "ttt", income, expense);

  REQUIRE ( income == 780 );
  REQUIRE ( expense == 69 );
  REQUIRE ( b1.Income("a", "ttt", 89) );

  b1.Audit("a", "ttt", income, expense);

  REQUIRE (income == 780+89);
  REQUIRE (expense == 69);

  REQUIRE ( !b1.Birth("a", "ttt") );
  REQUIRE ( b1.Birth("at", "tt") );
}
