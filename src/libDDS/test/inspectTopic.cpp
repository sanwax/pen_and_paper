#include <libDDS/topics/TopicSubscription.h>
#include <iostream>
#include <iomanip>

int
main()
{
	dds::topics::TopicSubscription p;
	const auto type=p.type();
	std::cout<<"[MAIN] Topic type (dec): "<<type<<std::endl;
	std::cout<<"[MAIN] Topic type (hex): "<<std::hex<<std::setfill('0')<<std::setw(sizeof(type)*2)<<type<<std::endl;
	return 0;
}
