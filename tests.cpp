/*
 * main.cpp
 *
 *  Created on: 05/08/2015
 *      Author: pperezm
 */
#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.h"
#include "list.h"

TEST_CASE("testing get", "[List]") {
	List<int> b1, b2, b3, b4, b5;
	for (int i = 5; i >=1; i--)
	{
		b1.push_front(i);
	}
	for (int i = 7; i >=1; i--)
	{
		b2.push_front(i);
	}
	for (int i = 50; i >=1; i--)
	{
		b3.push_front(i);
	}
	for (int i = 100; i >=1; i--)
	{
		b4.push_front(i);
	}
	SECTION ( "5 personas" ) {
		REQUIRE(b1.aSalvo(5,2) == 3);
	}
	SECTION ( "7 personas" ) {
		REQUIRE(b2.aSalvo(7,3) == 1);
	}
	SECTION ( "50 personas" ) {
		REQUIRE(b3.aSalvo(50,9) == 45);
	}
	SECTION ( "100 personas" ) {
		REQUIRE(b4.aSalvo(100,9) == 34);
	}
	SECTION ( "No hay nadie" ) {
		REQUIRE(b5.aSalvo(0,0) == -1);
	}
}