// =================================================================
//
// File: main.cpp
// Author: Jorge Israel Sandoval Sánchez - A01710373
// Date: 06/10/2023
//
// =================================================================
#include <iostream>
#include "list.h"
#include "catch.h"
using namespace std;

int main(int argc, char* argv[]) {
	List<int> lst;
	int n, k, a = 0;
	cin>>n>>k;
	for (int i = n; i >= 1; i--) {
		lst.push_front(i);
	}
	cout<<lst.toString()<<endl;
	a = lst.aSalvo(n,k);

	cout<<a;
	
	return 0;
}
