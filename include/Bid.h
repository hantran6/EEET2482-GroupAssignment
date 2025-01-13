#ifndef BID_H
#define BID_H

#include "Auction.h"
#include "Member.h"


class Bid {
    private:
        int bidId;
        int amount;
        Auction auction;
        //Item item;
        Member bidder;
        std::chrono::time_point<std::chrono::system_clock> bidTime;

    public:
        Bid(const Auction& auction, const Member& bidder, int amount);

        int getBidId();
        void setBidId(int bidId);

        int getBidAmount();
        void setBidAmount(int amount);

       

};

#endif