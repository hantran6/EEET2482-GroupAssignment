#ifndef AUCTION_H
#define AUCTION_H

#include <list>

#include "Item.hpp"
#include "Bid.hpp"


class Auction {
    private:
        int auctionId;
        Item item;
        std::list<Bid> bidList;
        std::chrono::time_point<std::chrono::system_clock> startTime;
        std::chrono::time_point<std::chrono::system_clock> endTime;
        bool auctionInProcess;
        int currentHighestBid;
        //Member highestBidder;
        //Member auctionWinner;

    public:
        // Constructor
        // The bidList is automatically initialized as empty
        Auction(int auctionId, const Item& item);

        int getAuctionId() {
            return auctionId;
        }

        Item getItem() {
            return item;
        }

        std::list<Bid> getBidList() {
            return bidList;
        }
            
        void startAuction(int durationInSeconds);
        void endAuction();
        void processBids();

};

#endif