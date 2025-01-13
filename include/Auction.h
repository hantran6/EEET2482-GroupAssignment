#ifndef AUCTION_H
#define AUCTION_H

#include <vector>

#include "Item.h"
#include "Bid.h"
#include "Member.h"


class Auction {
    private:
        static int auctionIdCounter;
        int auctionId;
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
        Member highestBidder;
        Member auctionWinner;
        Member seller;

    public:
        // Constructor
        // The bidList is automatically initialized as empty
        Auction();
        Auction(Member& seller, const Item& item, double startingBid, double increment, double minRating);
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

        Member& getSeller();

        std::vector<Bid> getBidList();

        double getCurrentHighestBid();
        void setCurrentHighestBid(int currentHighestBid);

        Member& getHighestBidder();
        void setHighestBidder(Member& highestBidder);
            
        void startAuction(int durationInSeconds);
        void endAuction();
        void processBids();

        void placeBid(Member seller, double amount);
        void placeBid(Member seller, double amount, double bidLimit);

        bool checkCorrectIncrement(double amount);

};

#endif