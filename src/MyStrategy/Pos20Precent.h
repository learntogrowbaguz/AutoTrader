#ifndef IPositionControl_H
#define IPositionControl_H
#include "stdafx.h"
#include <vector>

class Order;
typedef std::vector<Order> OrderVec;

namespace PP{
	class PositionProfitMgr;
};


class  Pos20Precent
{
public:
	explicit Pos20Precent();
	~Pos20Precent(){};
		
	void BindAccount(PP::PositionProfitMgr* mgr) { m_ppMgr = mgr; }

	//return fail or success
	bool CompleteOrders(OrderVec& orders);
		
private:
	PP::PositionProfitMgr* m_ppMgr;
};

#endif