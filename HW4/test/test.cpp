#define CATCH_CONFIG_MAIN
#define __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "../../Catch/single_include/catch.hpp"
#include "../src/main.cpp"


TEST_CASE ("Basic Tests", "[basic]") {

  bool status;
  int  balance;
  char accCpy[100], debCpy[100], credCpy[100], signCpy[100];

  CBank a;
  status = a . NewAccount ( "123456", 1000 );
  REQUIRE ( status );
  status = a . NewAccount ( "987654", -500 );
  REQUIRE ( status );
  status = a . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
  REQUIRE ( status );
  status = a . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
  REQUIRE ( status );
  status = a . NewAccount ( "111111", 5000 );
  REQUIRE ( status );
  status = a . Transaction ( "111111", "987654", 290, "Okh6e+8rAiuT5=" );
  REQUIRE ( status );
  balance = a . Account ( "123456" ). Balance ( );
  REQUIRE ( balance == -2190 );
  balance = a . Account ( "987654" ). Balance ( );
  REQUIRE ( balance == 2980);
  balance = a . Account ( "111111" ). Balance ( );
  REQUIRE ( balance == 4710 );
  cout << a . Account ( "123456" );
/*
---8<---8<---8<---8<---8<---8<---8<---
123456:
   1000
 - 300, to: 987654, sign: XAbG5uKz6E=
 - 2890, to: 987654, sign: AbG5uKz6E=
 = -2190
---8<---8<---8<---8<---8<---8<---8<---
*/
  cout << a . Account ( "987654" );
/*
---8<---8<---8<---8<---8<---8<---8<---
987654:
   -500
 + 300, from: 123456, sign: XAbG5uKz6E=
 + 2890, from: 123456, sign: AbG5uKz6E=
 + 290, from: 111111, sign: Okh6e+8rAiuT5=
 = 2980
---8<---8<---8<---8<---8<---8<---8<---
*/
  cout << a . Account ( "111111" );
/*
---8<---8<---8<---8<---8<---8<---8<---
111111:
   5000
 - 290, to: 987654, sign: Okh6e+8rAiuT5=
 = 4710
---8<---8<---8<---8<---8<---8<---8<---
*/
  status = a . TrimAccount ( "987654" );
  REQUIRE ( status );
  status = a . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
  REQUIRE ( status );
  cout << a . Account ( "987654" );
  balance = a . Account ( "987654" ) . Balance ();
  REQUIRE ( balance == 3103 );
/*
---8<---8<---8<---8<---8<---8<---8<---
987654:
   2980
 + 123, from: 111111, sign: asdf78wrnASDT3W
 = 3103
---8<---8<---8<---8<---8<---8<---8<---
*/

  CBank c;
  strncpy ( accCpy, "123456", sizeof ( accCpy ) );
  status = c . NewAccount ( accCpy, 1000 );
  REQUIRE ( status );  // status = true
  strncpy ( accCpy, "987654", sizeof ( accCpy ) );
  status = c . NewAccount ( accCpy, -500 );
  REQUIRE ( status ); // status = true
  strncpy ( debCpy, "123456", sizeof ( debCpy ) );
  strncpy ( credCpy, "987654", sizeof ( credCpy ) );
  strncpy ( signCpy, "XAbG5uKz6E=", sizeof ( signCpy ) );
  status = c . Transaction ( debCpy, credCpy, 300, signCpy );
  REQUIRE ( status ); // status = true
  strncpy ( debCpy, "123456", sizeof ( debCpy ) );
  strncpy ( credCpy, "987654", sizeof ( credCpy ) );
  strncpy ( signCpy, "AbG5uKz6E=", sizeof ( signCpy ) );
  status = c . Transaction ( debCpy, credCpy, 2890, signCpy );
  REQUIRE ( status ); // status = true
  strncpy ( accCpy, "111111", sizeof ( accCpy ) );
  status = c . NewAccount ( accCpy, 5000 );
  REQUIRE ( status ); // status = true
  strncpy ( debCpy, "111111", sizeof ( debCpy ) );
  strncpy ( credCpy, "987654", sizeof ( credCpy ) );
  strncpy ( signCpy, "Okh6e+8rAiuT5=", sizeof ( signCpy ) );
  status = c . Transaction ( debCpy, credCpy, 2890, signCpy );
  REQUIRE ( status ); // status = true
  balance = c . Account ( "123456" ). Balance ( );
  REQUIRE ( balance == -2190 );
  balance = c . Account ( "987654" ). Balance ( );
  REQUIRE ( balance == 5580 );
  balance = c . Account ( "111111" ). Balance ( );
  REQUIRE ( balance  == 2110 );
  cout << c . Account ( "123456" );
/*
---8<---8<---8<---8<---8<---8<---8<---
123456:
   1000
 - 300, to: 987654, sign: XAbG5uKz6E=
 - 2890, to: 987654, sign: AbG5uKz6E=
 = -2190
---8<---8<---8<---8<---8<---8<---8<---
*/
  cout << c . Account ( "987654" );
/*
---8<---8<---8<---8<---8<---8<---8<---
987654:
   -500
 + 300, from: 123456, sign: XAbG5uKz6E=
 + 2890, from: 123456, sign: AbG5uKz6E=
 + 2890, from: 111111, sign: Okh6e+8rAiuT5=
 = 5580
---8<---8<---8<---8<---8<---8<---8<---
*/
  cout << c . Account ( "111111" );
/*
---8<---8<---8<---8<---8<---8<---8<---
111111:
   5000
 - 2890, to: 987654, sign: Okh6e+8rAiuT5=
 = 2110
---8<---8<---8<---8<---8<---8<---8<---
*/
status = c . TrimAccount ( "987654" );
 // status = true
strncpy ( debCpy, "111111", sizeof ( debCpy ) );
strncpy ( credCpy, "987654", sizeof ( credCpy ) );
strncpy ( signCpy, "asdf78wrnASDT3W", sizeof ( signCpy ) );
status = c . Transaction ( debCpy, credCpy, 123, signCpy );
 // status = true
cout << c . Account ( "987654" );
/*
---8<---8<---8<---8<---8<---8<---8<---
987654:
   5580
 + 123, from: 111111, sign: asdf78wrnASDT3W
 = 5703
---8<---8<---8<---8<---8<---8<---8<---
*/

balance = c . Account ( "987654" ) . Balance ();
REQUIRE ( balance == 5703 );

  CBank e;
  status = e . NewAccount ( "123456", 1000 );
  REQUIRE ( status ); // status = true
  status = e . NewAccount ( "987654", -500 );
  REQUIRE ( status ); // status = true
  status = e . NewAccount ( "123456", 3000 );
  REQUIRE ( !status ); // status = false
  status = e . Transaction ( "123456", "666", 100, "123nr6dfqkwbv5" );
  REQUIRE ( !status ); // status = false
  status = e . Transaction ( "666", "123456", 100, "34dGD74JsdfKGH" );
  REQUIRE ( !status ); // status = false
  status = e . Transaction ( "123456", "123456", 100, "Juaw7Jasdkjb5" );
  REQUIRE ( !status );// status = false
  try { balance = e . Account ( "666" ). Balance ( ); status = false; }
  catch (int e) { status = true; }
  REQUIRE ( status ); // exception thrown
  try { cout << e . Account ( "666" ); status = false; }
  catch (int e) { status = true; } // exception thrown
  REQUIRE ( status );
  status = e . TrimAccount ( "666" );
  REQUIRE ( !status ); // status = false

CBank g;
status = g . NewAccount ( "123456", 1000 );
REQUIRE ( status );  // status = true
status = g . NewAccount ( "987654", -500 );
REQUIRE ( status ); // status = true
status = g . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
REQUIRE ( status ); // status = true
status = g . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
REQUIRE ( status ); // status = true
status = g . NewAccount ( "111111", 5000 );
REQUIRE ( status ); // status = true
status = g . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" );
REQUIRE ( status ); // status = true
CBank h ( g );
status = g . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
REQUIRE ( status ); // status = true
status = h . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" );
REQUIRE ( status ); // status = true
status = g . NewAccount ( "99999999", 7000 );
REQUIRE ( status ); // status = true
status = g . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" );
REQUIRE ( status ); // status = true
status = g . TrimAccount ( "111111" );
REQUIRE ( status ); // status = true
status = g . Transaction ( "123456", "111111", 221, "Q23wr234ER==" );
REQUIRE ( status ); // status = true
cout << g . Account ( "111111" );
/*
---8<---8<---8<---8<---8<---8<---8<---
111111:
   -1802
 + 221, from: 123456, sign: Q23wr234ER==
 = -1581
---8<---8<---8<---8<---8<---8<---8<---
*/
balance = g . Account ( "111111" ) . Balance ();
REQUIRE ( balance == -1581 );

cout << g . Account ( "99999999" );
/*
---8<---8<---8<---8<---8<---8<---8<---
99999999:
   7000
 + 3789, from: 111111, sign: aher5asdVsAD
 = 10789
---8<---8<---8<---8<---8<---8<---8<---
*/
balance = g . Account ( "99999999" ) . Balance ();
REQUIRE ( balance == 10789 );

cout << g . Account ( "987654" );
/*
---8<---8<---8<---8<---8<---8<---8<---
987654:
   -500
 + 300, from: 123456, sign: XAbG5uKz6E=
 + 2890, from: 123456, sign: AbG5uKz6E=
 + 2890, from: 111111, sign: Okh6e+8rAiuT5=
 + 123, from: 111111, sign: asdf78wrnASDT3W
 = 5703
---8<---8<---8<---8<---8<---8<---8<---
*/
balance = g . Account ( "987654" )  . Balance ();
REQUIRE ( balance == 5703 );

cout << h . Account ( "111111" );
/*
---8<---8<---8<---8<---8<---8<---8<---
111111:
   5000
 - 2890, to: 987654, sign: Okh6e+8rAiuT5=
 - 789, to: 987654, sign: SGDFTYE3sdfsd3W
 = 1321
---8<---8<---8<---8<---8<---8<---8<---
*/
balance = h . Account ( "111111" ) . Balance ();
REQUIRE ( balance == 1321 );

try { cout << h . Account ( "99999999" ); status = false; }
catch (int e) { status = true; }
REQUIRE ( status ); // exception thrown
cout << h . Account ( "987654" );
/*
---8<---8<---8<---8<---8<---8<---8<---
987654:
   -500
 + 300, from: 123456, sign: XAbG5uKz6E=
 + 2890, from: 123456, sign: AbG5uKz6E=
 + 2890, from: 111111, sign: Okh6e+8rAiuT5=
 + 789, from: 111111, sign: SGDFTYE3sdfsd3W
 = 6369
---8<---8<---8<---8<---8<---8<---8<---
*/
balance = h . Account ( "987654" ) . Balance ();
REQUIRE ( balance == 6369 );

CBank i;
CBank j;
status = i . NewAccount ( "123456", 1000 );
REQUIRE ( status ); // status = true
status = i . NewAccount ( "987654", -500 );
REQUIRE ( status ); // status = true
status = i . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
REQUIRE ( status ); // status = true
status = i . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
REQUIRE ( status ); // status = true
status = i . NewAccount ( "111111", 5000 );
REQUIRE ( status ); // status = true
status = i . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" );
REQUIRE ( status ); // status = true
j = i;
status = i . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
REQUIRE ( status ); // status = true
status = j . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" );
REQUIRE ( status ); // status = true
status = i . NewAccount ( "99999999", 7000 );
REQUIRE ( status ); // status = true
status = i . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" );
REQUIRE ( status ); // status = true
status = i . TrimAccount ( "111111" );
REQUIRE ( status ); // status = true
cout << i . Account ( "111111" );
/*
---8<---8<---8<---8<---8<---8<---8<---
111111:
   -1802
 = -1802
---8<---8<---8<---8<---8<---8<---8<---
*/
balance = i . Account ( "111111" ) . Balance ();
REQUIRE ( balance == -1802 );

cout << j . Account ( "111111" );
/*
---8<---8<---8<---8<---8<---8<---8<---
111111:
   5000
 - 2890, to: 987654, sign: Okh6e+8rAiuT5=
 - 789, to: 987654, sign: SGDFTYE3sdfsd3W
 = 1321
---8<---8<---8<---8<---8<---8<---8<---
*/
balance = j . Account ( "111111" ) . Balance ();
REQUIRE ( balance == 1321 );

}

TEST_CASE ("Output Tests", "[output]") {
  stringstream stream;
  string test; int res;
  char accCpy[100], debCpy[100], credCpy[100], signCpy[100];

  CBank a;
  a . NewAccount ( "123456", 1000 );
  a . NewAccount ( "987654", -500 );
  a . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
  a . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
  a . NewAccount ( "111111", 5000 );
  a . Transaction ( "111111", "987654", 290, "Okh6e+8rAiuT5=" );
  stream << a . Account ( "123456" );
test =
"123456:\n"
"   1000\n"
" - 300, to: 987654, sign: XAbG5uKz6E=\n"
" - 2890, to: 987654, sign: AbG5uKz6E=\n"
" = -2190\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

stream << a . Account ( "987654" );
test =
"987654:\n"
"   -500\n"
" + 300, from: 123456, sign: XAbG5uKz6E=\n"
" + 2890, from: 123456, sign: AbG5uKz6E=\n"
" + 290, from: 111111, sign: Okh6e+8rAiuT5=\n"
" = 2980\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

stream << a . Account ( "111111" );
test=

"111111:\n"
"   5000\n"
" - 290, to: 987654, sign: Okh6e+8rAiuT5=\n"
" = 4710\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

a . TrimAccount ( "987654" );
a . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
stream << a . Account ( "987654" );
test=

"987654:\n"
"   2980\n"
" + 123, from: 111111, sign: asdf78wrnASDT3W\n"
" = 3103\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

CBank c;
strncpy ( accCpy, "123456", sizeof ( accCpy ) );
c . NewAccount ( accCpy, 1000 );
strncpy ( accCpy, "987654", sizeof ( accCpy ) );
c . NewAccount ( accCpy, -500 );
strncpy ( debCpy, "123456", sizeof ( debCpy ) );
strncpy ( credCpy, "987654", sizeof ( credCpy ) );
strncpy ( signCpy, "XAbG5uKz6E=", sizeof ( signCpy ) );
c . Transaction ( debCpy, credCpy, 300, signCpy );
strncpy ( debCpy, "123456", sizeof ( debCpy ) );
strncpy ( credCpy, "987654", sizeof ( credCpy ) );
strncpy ( signCpy, "AbG5uKz6E=", sizeof ( signCpy ) );
c . Transaction ( debCpy, credCpy, 2890, signCpy );
strncpy ( accCpy, "111111", sizeof ( accCpy ) );
c . NewAccount ( accCpy, 5000 );
strncpy ( debCpy, "111111", sizeof ( debCpy ) );
strncpy ( credCpy, "987654", sizeof ( credCpy ) );
strncpy ( signCpy, "Okh6e+8rAiuT5=", sizeof ( signCpy ) );
c . Transaction ( debCpy, credCpy, 2890, signCpy );

stream << c . Account ( "123456" );
test=

"123456:\n"
"   1000\n"
" - 300, to: 987654, sign: XAbG5uKz6E=\n"
" - 2890, to: 987654, sign: AbG5uKz6E=\n"
" = -2190\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

stream << c . Account ( "987654" );
test=

"987654:\n"
"   -500\n"
" + 300, from: 123456, sign: XAbG5uKz6E=\n"
" + 2890, from: 123456, sign: AbG5uKz6E=\n"
" + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n"
" = 5580\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

stream << c . Account ( "111111" );
test=

"111111:\n"
"   5000\n"
" - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n"
" = 2110\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

c . TrimAccount ( "987654" );
strncpy ( debCpy, "111111", sizeof ( debCpy ) );
strncpy ( credCpy, "987654", sizeof ( credCpy ) );
strncpy ( signCpy, "asdf78wrnASDT3W", sizeof ( signCpy ) );
c . Transaction ( debCpy, credCpy, 123, signCpy );

stream << c . Account ( "987654" );
test=

"987654:\n"
"   5580\n"
" + 123, from: 111111, sign: asdf78wrnASDT3W\n"
" = 5703\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

CBank e;
e . NewAccount ( "123456", 1000 );
e . NewAccount ( "987654", -500 );
e . NewAccount ( "123456", 3000 );
e . Transaction ( "123456", "666", 100, "123nr6dfqkwbv5" );
e . Transaction ( "666", "123456", 100, "34dGD74JsdfKGH" );

CBank g;
g . NewAccount ( "123456", 1000 );
g . NewAccount ( "987654", -500 );
g . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
g . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
g . NewAccount ( "111111", 5000 );
g . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" );
CBank h ( g );
g . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
h . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" );
g . NewAccount ( "99999999", 7000 );
g . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" );
g . TrimAccount ( "111111" );
g . Transaction ( "123456", "111111", 221, "Q23wr234ER==" );

stream << g . Account ( "111111" );
test=

"111111:\n"
"   -1802\n"
" + 221, from: 123456, sign: Q23wr234ER==\n"
" = -1581\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

stream << g . Account ( "99999999" );
test=

"99999999:\n"
"   7000\n"
" + 3789, from: 111111, sign: aher5asdVsAD\n"
" = 10789\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

stream << g . Account ( "987654" );
test=

"987654:\n"
"   -500\n"
" + 300, from: 123456, sign: XAbG5uKz6E=\n"
" + 2890, from: 123456, sign: AbG5uKz6E=\n"
" + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n"
" + 123, from: 111111, sign: asdf78wrnASDT3W\n"
" = 5703\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

stream << h . Account ( "111111" );
test=

"111111:\n"
"   5000\n"
" - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n"
" - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n"
" = 1321\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

stream << h . Account ( "987654" );
test=

"987654:\n"
"   -500\n"
" + 300, from: 123456, sign: XAbG5uKz6E=\n"
" + 2890, from: 123456, sign: AbG5uKz6E=\n"
" + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n"
" + 789, from: 111111, sign: SGDFTYE3sdfsd3W\n"
" = 6369\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

CBank i;
CBank j;
i . NewAccount ( "123456", 1000 );
i . NewAccount ( "987654", -500 );
i . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
i . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
i . NewAccount ( "111111", 5000 );
i . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" );
j = i;
i . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
j . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" );
i . NewAccount ( "99999999", 7000 );
i . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" );
i . TrimAccount ( "111111" );

stream << i . Account ( "111111" );
test=

"111111:\n"
"   -1802\n"
" = -1802\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");

stream << j . Account ( "111111" );
test=
"111111:\n"
"   5000\n"
" - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n"
" - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n"
" = 1321\n";

res = test.compare(stream.str());
if (res != 0) {
  cout << "Invalid output : " << endl << endl << "You:" << endl;
  cout << stream.str() << endl;
  cout << endl << " !!!!! VS. P R O G T E S T " << endl << endl;
  cout << test;
}
REQUIRE (res == 0); stream.str("");
}

TEST_CASE ("Custom Tests", "[custom]") {
  // Other tests here
}
