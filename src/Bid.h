#ifndef BID_H
#define BID_H

#include "Item.h"
#include "Member.h"
#include <string>


class Bid {
    private:
        int itemId;
        double amount;
        std::string bidderUsername;
        std::chrono::time_point<std::chrono::system_clock> bidTime;

    public:
        Bid(int itemId, std::string bidderUsername, double amount);

        int getItemId();
        void setItemId(int itemId);

        double getBidAmount();
        void setBidAmount(double amount);

        std::string getBidderUsername();
        void setBidderUsername(std::string bidderUsername);


      

};

#endif