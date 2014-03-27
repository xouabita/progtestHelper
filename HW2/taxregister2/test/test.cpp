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

TEST_CASE( "Basic tests", "[taxregister]" ) {
  CTaxRegister b1;
  string acct;
  int sumIncome, sumExpense;
  bool status;

  REQUIRE ( b1 . Birth( "John Smith", "Oak Road 23", "123/456/789"));
  REQUIRE ( b1 . Birth ( "Jane Hacker", "Main Street 17", "Xuj5#94" ));
  REQUIRE ( b1 . Birth ( "Peter Hacker", "Main Street 17", "634oddT" ));
  REQUIRE ( b1 . Birth ( "John Smith", "Main Street 17", "Z343rwZ" ));
  REQUIRE ( b1 . Income ( "Xuj5#94", 1000 ));
  REQUIRE ( b1 . Income ( "634oddT", 2000 ));
  REQUIRE ( b1 . Income ( "123/456/789", 3000 ));
  REQUIRE ( b1 . Income ( "634oddT", 4000 ));
  REQUIRE ( b1 . Income ( "Peter Hacker", "Main Street 17", 2000 ));
  REQUIRE ( b1 . Expense ( "Jane Hacker", "Main Street 17", 2000 ));
  REQUIRE ( b1 . Expense ( "John Smith", "Main Street 17", 500 ));
  REQUIRE ( b1 . Expense ( "Jane Hacker", "Main Street 17", 1000 ));
  REQUIRE ( b1 . Expense ( "Xuj5#94", 1300 ));

  REQUIRE ( b1 . Audit ( "John Smith", "Oak Road 23", acct, sumIncome, sumExpense ));
  REQUIRE ( acct == "123/456/789" );
  REQUIRE ( sumIncome == 3000 );
  REQUIRE ( sumExpense == 0 );

  REQUIRE ( b1 . Audit ( "Jane Hacker", "Main Street 17", acct, sumIncome, sumExpense ));
  REQUIRE ( acct == "Xuj5#94" );
  REQUIRE ( sumIncome == 1000 );
  REQUIRE ( sumExpense == 4300 );

  REQUIRE ( b1 . Audit ( "Peter Hacker", "Main Street 17", acct, sumIncome, sumExpense ));
  REQUIRE ( acct == "634oddT" );
  REQUIRE ( sumIncome == 8000 );
  REQUIRE ( sumExpense == 0 );

  REQUIRE ( b1 . Audit ( "John Smith", "Main Street 17", acct, sumIncome, sumExpense ));
  REQUIRE ( acct == "Z343rwZ" );
  REQUIRE ( sumIncome == 0 );
  REQUIRE ( sumExpense == 500 );

  REQUIRE ( b1 . Death ( "John Smith", "Main Street 17" ));

  CTaxRegister b2;


  REQUIRE (b2 . Birth ( "John Smith", "Oak Road 23", "123/456/789" ));
  status = b2 . Birth ( "Jane Hacker", "Main Street 17", "Xuj5#94" );
  status = b2 . Income ( "634oddT", 4000 );
  REQUIRE (!status);
  status = b2 . Expense ( "John Smith", "Main Street 18", 500 );
  REQUIRE (!status);
  status = b2 . Audit ( "John Nowak", "Second Street 23", acct, sumIncome, sumExpense );
  REQUIRE (!status);
  status = b2 . Death ( "Peter Nowak", "5-th Avenue" );
  REQUIRE (!status);
  status = b2 . Birth ( "Jane Hacker", "Main Street 17", "4et689A" );
  REQUIRE (!status);
  status = b2 . Birth ( "Joe Hacker", "Elm Street 23", "Xuj5#94" );
  REQUIRE (!status);
  status = b2 . Death ( "Jane Hacker", "Main Street 17" );
  REQUIRE (status);
  status = b2 . Birth ( "Joe Hacker", "Elm Street 23", "Xuj5#94" );
  REQUIRE (status);
  status = b2 . Audit ( "Joe Hacker", "Elm Street 23", acct, sumIncome, sumExpense );
  REQUIRE (status); REQUIRE ( acct == "Xuj5#94");
  REQUIRE (sumIncome == 0); REQUIRE (sumExpense == 0);
  status = b2 . Birth ( "Joe Hacker", "Elm Street 23", "AAj5#94" );
  REQUIRE (!status);
}
