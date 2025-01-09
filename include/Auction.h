#ifndef AUCTION_H
#define AUCTION_H

#include <vector>

#include "Item.h"
#include "Bid.h"


class Auction {
    private:
        int auctionId = 1;
        Item item;
        double startingBid;
        double increment;
        double minRating;
        std::vector<Bid> bids;
        std::chrono::time_point<std::chrono::system_clock> startTime;
        std::chrono::time_point<std::chrono::system_clock> endTime;
        std::chrono::time_point<std::chrono::system_clock> currentTime;
        bool auctionInProcess  = false;
        int currentHighestBid;
        //Member highestBidder;
        //Member auctionWinner;

    public:
        // Constructor
        // The bidList is automatically initialized as empty
        Auction();
        Auction(const Item& item, double startingBid, double increment, double minRating);
        //Auction(int auctionId, const Item& item);

        int getAuctionId() {
            return auctionId;
        }

        Item getItem() {
            return item;
        }

        double getStartingBid();
        void setStartingBid(double startingBid);

        double getIncrement();
        void setIncrement(double increment);

        double getMinRating();
        void setMinRating(double minRating);

        std::vector<Bid> getBidList();

        double getCurrentHighestBid();
        void setCurrentHighestBid(int currentHighestBid);

        //void setHighestBidder(Member highestBidder);
            
        void startAuction(int durationInSeconds);
        void endAuction();
        void processBids();

        void placeBid(double amount);
        void placeBidWithAutoBidLimit(double amount, double bidLimit);

        bool checkCorrectIncrement(double amount);

};

#endif