#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
using namespace std;

#include "../../../Catch/single_include/catch.hpp"
#define __PROGTEST__

//=================================================================================================
class CTimeStamp
 {
   public:
                   CTimeStamp                              ( int               year,
                                                             int               month,
                                                             int               day,
                                                             int               hour,
                                                             int               minute,
                                                             int               sec );
    int            Compare                                 ( const CTimeStamp & x ) const;
    friend ostream & operator <<                           ( ostream          & os,
                                                             const CTimeStamp & x );
 };
//=================================================================================================
class CMailBody
 {
   public:
                   CMailBody                               ( int               size,
                                                             const char      * data );
     // copy cons/op=/destructor implemented in the class
    friend ostream & operator <<                           ( ostream         & os,
                                                             const CMailBody & x )
     {
       return os << "mail body: " << x . m_Size << " B";
     }
   private:
    int            m_Size;
    char         * m_Data;
 };
//=================================================================================================
class CAttach
 {
   public:
                   CAttach                                 ( int               x )
                    : m_X (x), m_RefCnt ( 1 ) { }
    void           AddRef                                  ( void ) const { m_RefCnt ++; }
    void           Release                                 ( void ) const { if ( !--m_RefCnt ) delete this; }
   private:
    int            m_X;
    mutable int    m_RefCnt;
                   CAttach                                 ( const CAttach   & x );
    CAttach      & operator =                              ( const CAttach   & x );
                  ~CAttach                                 ( void ) { }
    friend ostream & operator <<                           ( ostream         & os,
                                                             const CAttach   & x )
     {
       return os << "attachment: " << x . m_X << " B";
     }
 };
//=================================================================================================

#include "../src/main.cpp"

void showMail ( const list<CMail> & l )
 {
   for ( list<CMail>::const_iterator it = l . begin (); it != l . end (); ++it )
    cout << *it << endl;
 }
void showUsers ( const set<string> & s )
 {
   for ( set<string>::const_iterator it = s . begin (); it != s . end (); ++it )
    cout << *it << endl;
 }

#define CATCH_CONFIG_MAIN

bool        st;
list<CMail> mailList;
set<string> users;
CAttach   * att;

TEST_CASE ("Basic Tests", "[basic],[mandatory]") {

CMailBox m0;
st = m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 24, 13 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 1" ), NULL ) );
REQUIRE ( st ); // st = true
st = m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ), "user2@fit.cvut.cz", CMailBody ( 22, "some different content" ), NULL ) );
REQUIRE ( st ); // st = true
att = new CAttach ( 200 );
st = m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 11, 23, 43 ), "boss1@fit.cvut.cz", CMailBody ( 14, "urgent message" ), att ) );
REQUIRE ( st ); // st = true
st = m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 18, 52, 27 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 2" ), att ) );
 REQUIRE ( st ); // st = true
att -> Release ();
att = new CAttach ( 97 );
st = m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 16, 12, 48 ), "boss1@fit.cvut.cz", CMailBody ( 24, "even more urgent message" ), att ) );
 REQUIRE ( st ); // st = true
att -> Release ();
showMail ( m0 . ListMail ( "inbox",
                           CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                           CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B + attachment: 200 B
2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B
2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B
2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B
2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 200 B
---8<---8<---8<---8<---8<---8<---
*/
showMail ( m0 . ListMail ( "inbox",
                           CTimeStamp ( 2014, 3, 31, 15, 26, 23 ),
                           CTimeStamp ( 2014, 3, 31, 16, 12, 48 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B
2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B
---8<---8<---8<---8<---8<---8<---
*/
showUsers ( m0 . ListAddr ( CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                            CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
boss1@fit.cvut.cz
user1@fit.cvut.cz
user2@fit.cvut.cz
---8<---8<---8<---8<---8<---8<---
*/
showUsers ( m0 . ListAddr ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ),
                            CTimeStamp ( 2014, 3, 31, 16, 12, 48 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
boss1@fit.cvut.cz
user2@fit.cvut.cz
---8<---8<---8<---8<---8<---8<---
*/

CMailBox m1;
st = m1 . NewFolder ( "work" );
 REQUIRE ( st ); // st = true
st = m1 . NewFolder ( "spam" );
 REQUIRE ( st ); // st = true
st = m1 . NewFolder ( "spam" );
 REQUIRE ( !st ); // st = false
st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 24, 13 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 1" ), NULL ) );
 REQUIRE ( st ); // st = true
att = new CAttach ( 500 );
st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ), "user2@fit.cvut.cz", CMailBody ( 22, "some different content" ), att ) );
 REQUIRE ( st ); // st = true
att -> Release ();
st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 11, 23, 43 ), "boss1@fit.cvut.cz", CMailBody ( 14, "urgent message" ), NULL ) );
 REQUIRE ( st ); // st = true
att = new CAttach ( 468 );
st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 18, 52, 27 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 2" ), att ) );
 REQUIRE ( st ); // st = true
att -> Release ();
st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 16, 12, 48 ), "boss1@fit.cvut.cz", CMailBody ( 24, "even more urgent message" ), NULL ) );
 REQUIRE ( st ); // st = true
showMail ( m1 . ListMail ( "inbox",
                           CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                           CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B
2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B
2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B
2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B
2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B
---8<---8<---8<---8<---8<---8<---
*/
showMail ( m1 . ListMail ( "work",
                           CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                           CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
---8<---8<---8<---8<---8<---8<---
*/
st = m1 . MoveMail ( "inbox", "work" );
 REQUIRE ( st ); // st = true
showMail ( m1 . ListMail ( "inbox",
                           CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                           CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
---8<---8<---8<---8<---8<---8<---
*/
showMail ( m1 . ListMail ( "work",
                           CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                           CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B
2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B
2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B
2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B
2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B
---8<---8<---8<---8<---8<---8<---
*/
st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 19, 24, 13 ), "user2@fit.cvut.cz", CMailBody ( 14, "mail content 4" ), NULL ) );
 REQUIRE ( st ); // st = true
att = new CAttach ( 234 );
st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 13, 26, 23 ), "user3@fit.cvut.cz", CMailBody ( 9, "complains" ), att ) );
 REQUIRE ( st ); // st = true
att -> Release ();
showMail ( m1 . ListMail ( "inbox",
                           CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                           CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B
2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B
---8<---8<---8<---8<---8<---8<---
*/
showMail ( m1 . ListMail ( "work",
                           CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                           CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B
2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B
2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B
2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B
2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B
---8<---8<---8<---8<---8<---8<---
*/
st = m1 . MoveMail ( "inbox", "work" );
 REQUIRE ( st ); // st = true
showMail ( m1 . ListMail ( "inbox",
                           CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                           CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
---8<---8<---8<---8<---8<---8<---
*/
showMail ( m1 . ListMail ( "work",
                           CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                           CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
/*
---8<---8<---8<---8<---8<---8<---
2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B
2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B
2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B
2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B
2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B
2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B
2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B
---8<---8<---8<---8<---8<---8<---
*/
}
