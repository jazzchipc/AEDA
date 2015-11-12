/*
 * sequentialSearch.h
 *
 *  Created on: 20/10/2015
 *      Author: ASUS
 */

#ifndef SRC_SEQUENTIALSEARCH_H_
#define SRC_SEQUENTIALSEARCH_H_

#include "includes.h"

template <class Comparable>
int sequentialSearch(const vector<Comparable* > &v, Comparable* x)
{
	for (unsigned int i = 0; i < v.size(); i++)
	{
		Comparable a(*v[i]);
		Comparable b(*x);
		if (a == b)
			return i;   // encontrou
	}
    return -1;     // não encontrou
}




#endif /* SRC_SEQUENTIALSEARCH_H_ */
