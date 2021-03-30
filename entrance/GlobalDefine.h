#ifndef _GLOBAL_DEFINE_H_
#define _GLOBAL_DEFINE_H_

/*
 * @brief Universal single linked list struct
 * @property data Data area
 * @property next Next node address
 * */
template<typename Type_Link>
struct LinkOb
{
	Type_Link data;
	LinkOb* next;
};


#endif
