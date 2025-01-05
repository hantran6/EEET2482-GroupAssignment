#ifndef BID_H
#define BID_H

#include "Auction.hpp"


class Bid {
    private:
        int bidId;
        int amount;
        Item item;
        //Member bidder;
        std::chrono::time_point<std::chrono::system_clock> bidTime;

    public:
        Bid(Auction auctionId, Item item);
        void placeBid(Auction auctionId);
        void autoBidLimit(Auction auctionId,int bidLimit);

};

#endif