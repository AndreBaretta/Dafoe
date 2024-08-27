#ifndef SELLORDERMNG_2318
#define SELLORDERMNG_2318
#include "SellOrderDAO.hpp"

class SellOrderMNG{
public:
   bool enshrinedOrder();
private:
   SellOrderDAO& m_sODAO;
};

#endif
