// $Id: xmlostream.test.cxx,v 1.1 2004/01/25 02:35:10 eraxxon Exp $
// -*-C++-*-

//***************************************************************************
//
// File:
//    xmlostream.cxx
//
// Purpose:
//    [The purpose of this file]
//
// Description:
//    [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <iostream>
#include <fstream>
#include <sstream>

//************************** Boost Include Files ****************************

#include <boost/test/included/unit_test_framework.hpp> // preclude library
#include <boost/test/unit_test.hpp>

using boost::unit_test_framework::test_suite;

//*************************** User Include Files ****************************

#include <lib/support/xmlostream.h>

//*************************** Forward Declarations ***************************

using namespace xml;

void Test1();
void Test2();
void Test3();
void Test4();

//****************************************************************************

test_suite*
init_unit_test_suite(int argc, char* argv[]) {
  test_suite* test = BOOST_TEST_SUITE("xml::ostream");
  
  test->add(BOOST_TEST_CASE(&Test1));
  test->add(BOOST_TEST_CASE(&Test2));
  test->add(BOOST_TEST_CASE(&Test3));
  test->add(BOOST_TEST_CASE(&Test4));
  
  return test;
}

//****************************************************************************

void
Test1() 
{
  // A simple example that calls xml::ostream the class methods directly
  xml::ostream os(std::cout.rdbuf());
  
  os.SetIndentStep(3);
  os.SetIndentAmnt(3);

  BOOST_CHECKPOINT("Test 1");
  os.BegElem("Elem1");
  os.Attr("attr1", 123);
  os.Attr("attr2", "true!");
  os.BegElem("Elem2");
  os.EndElem();
  os.EndElem();
  os << std::endl;
}

void
Test2() 
{
  // A more concise way of writing the above, using xml::ostream operators
  xml::ostream os(std::cout.rdbuf());

  // Note that the indendation will go to the left not the right!
  os << SetIndentStep(-2) << SetIndentAmnt(10);
  
  BOOST_CHECKPOINT("Test 2a");
  os << BegElem("Elem1") << Attr("attr1", 123) << Attr("attr2", "true!");
  os << BegElem("Elem2") << EndElem;
  os << EndElem;
  os << std::endl;
  
  // Same as above, but uses explicit begin and end attribute operators
  BOOST_CHECKPOINT("Test 2b");
  os << BegElem("Elem1") 
     << BegAttr("attr1") << 123 << EndAttr
     << BegAttr("attr2") << "tr" << "ue!" << EndAttr
     << EndAttrs;
  os << BegElem("Elem2") << EndElem;
  os << EndElem;
  os << std::endl;
}

void
Test3()
{
  // An example using stream operators and sstreams.  Note the
  // embedded comments.
  std::streambuf* buf1 = std::cout.rdbuf(); 
  xml::ostream os1(buf1); // could substitute with an arbitrary ostream.
  
  std::ostringstream sstr;
  std::streambuf* buf2 = sstr.rdbuf();
  xml::ostream os2(buf2);
  
  os2 << SetIndentStep(2);

  BOOST_CHECKPOINT("Test 3");
  os2 << Comment("A beginning comment.");
  os2 << BegElem("PGM");
  os2 << BegElem("F") << Attr("n", "foo.cc") << EndAttrs;
  os2 << Comment("A comment for a P");
  os2 << BegElem("P") << Attr("id", 786) << Attr("attr2", "true!") << EndElem;
  os2 << BegElem("Question") << EndAttrs;
  os2 << BegComment << "(Are you " << 6 << " years old?)" << EndComment;
  os2 << EndElem;
  os2 << EndElem << EndElem;
  
  os1 << sstr.str();
  os1 << std::endl;
}

void
Test4() 
{
  // Test xml::ostream error catching
  xml::ostream os(std::cout.rdbuf());
  
  BOOST_CHECKPOINT("Unmatched BegElem/EndElem (extra EndElem)");
  os << BegElem("Elem1") << EndElem;
  BOOST_CHECK_THROW(os << EndElem, xml::ostream::Exception);
  os << std::endl;

  BOOST_CHECKPOINT("Unmatched BegAttr/EndAttr (a missing EndAttr is ok)");
  os << BegElem("Elem1") << BegAttr("id") << 42 << EndElem;
  os << BegElem("Elem1") << BegAttr("id") << 42 << EndAttrs << EndElem;
  os << std::endl;
  // no error should be generated

  BOOST_CHECKPOINT("Unmatched BegAttr/EndAttr (extra EndAttr)");
  os << BegElem("Elem1") << Attr("id", 123);
  BOOST_CHECK_THROW(os << EndAttr, xml::ostream::Exception);
  os << EndElem << std::endl;
  
#if 0
  os << BegElem("Elem1") << Attr("id", 123);
  BOOST_CHECK_THROW(os << EndAttr, xml::ostream::Exception);
#endif
}

