#include <iostream>
#include <cmath>
#include "./include/Auction.h"
#include "./include/Item.h"
#include "./include/Member.h"


int Auction::auctionIdCounter = 1;

//Constuctor
Auction::Auction(Member& seller, const Item& item, double startingBid, double increment, double minRating) : auctionId(auctionIdCounter++), seller(seller), item(item), startingBid(startingBid), increment(increment), minRating(minRating) {  
    std::cout << "Auction created with ID: " << auctionId << std::endl;
}

double Auction::getStartingBid() {
    return startingBid;
}

void Auction::setStartingBid(double startingBid){
    this->startingBid = startingBid;
}

double Auction::getIncrement() {
    return increment;
}

void Auction::setIncrement(double increment){
    this->increment = increment;
}

double Auction::getMinRating() {
    return minRating;
}

void Auction::setMinRating(double minRating){
    this->minRating = minRating;
}

Member& Auction::getSeller() {
    return seller;
}

Member& Auction::getHighestBidder() {
    return highestBidder;
}

void Auction::setHighestBidder(Member& highestBidder) {
    this->highestBidder = highestBidder;
}

std::vector<Bid> Auction::getBidList() {
            return bids;
        }

double Auction::getCurrentHighestBid() {
    if(bids.empty() || getCurrentHighestBid() == startingBid) {
        std::cout << "No bids for this item yet" << std::endl;
        std::cout << "The starting bid is $" << startingBid << endl;
    } else {
        bids.back().getBidAmount();
    }
}

void Auction::setCurrentHighestBid(int currentHighestBid) {
    this->currentHighestBid = currentHighestBid;
}



void Auction::startAuction(int durationInSeconds) {
    // Record the start time
    startTime = std::chrono::system_clock::now();

    auctionInProcess = true;

    // Calculate the end time by adding the duration to the start time
    endTime = startTime + std::chrono::seconds(durationInSeconds);

}

void Auction::endAuction(){
    auctionInProcess = false;


    int buyerCp = auctionWinner.getCreditPoints();
    buyerCp -= getCurrentHighestBid();
    auctionWinner.updateCreditPoints(buyerCp);

    int sellerCp = getSeller().getCreditPoints();
    sellerCp += getCurrentHighestBid();
    getSeller().updateCreditPoints(sellerCp);
}

void Auction::processBids(){
    if(auctionInProcess) {
        if(currentTime == endTime) {
            auctionWinner = highestBidder;   
            Auction::endAuction();
        }
    }
}

bool Auction::checkCorrectIncrement(double amount) {
    double difference = amount - getCurrentHighestBid();
    if(std::fmod(difference, increment) == 0) {
        return true;
    } else {
        return false;
    }
}

void Auction::placeBid(Member bidder, double amount) {
    if(bids.empty()) {
        setCurrentHighestBid(startingBid);
    }
    if(getCurrentHighestBid() < amount) {
        if(checkCorrectIncrement(amount)) {
            if(bidder.getCreditPoints() >= amount) {
                setCurrentHighestBid(amount);
                setHighestBidder(bidder);
                Bid newBid(*this, bidder, amount);
                bids.push_back(newBid);
            } else {
              std::cerr << "Insufficient amount of credit points.";
            }
        } else {
            std::cerr << "The bidding increment is " << Auction::getIncrement() << ". Your next bid should be at least " << Auction::getCurrentHighestBid() + Auction::getIncrement() << std::endl;
        }
    } else {
        std::cout << "Your placing bid has to be higher than " << Auction::getCurrentHighestBid() << std::endl;
    }
}

void Auction::placeBid(Member bidder, double amount, double bidLimit) {
    if(bids.empty()) {
        setCurrentHighestBid(startingBid);
    }
    if(getCurrentHighestBid() < amount) {
        if(checkCorrectIncrement(amount)) {
            if(bidder.getCreditPoints() >= amount) {
                setCurrentHighestBid(amount);
                setHighestBidder(bidder);
                Bid newBid(*this, bidder, amount);
                bids.push_back(newBid);
            } else {
               std::cerr << "Insufficient amount of credit points.";
            }
        } else {
            std::cerr << "The bidding increment is " << Auction::getIncrement() << ". Your next bid should be at least " << Auction::getCurrentHighestBid() + Auction::getIncrement() << std::endl;
        }
    } else {
        std::cout << "Your placing bid has to be higher than " << Auction::getCurrentHighestBid() << std::endl;
    }
    /*
    bool counterBid;

    do {
        counterBid = false;

        if(&getHighestBidder() != &bidder) {
            // Determine the next bid amount for the bidder
            double nextBid = std::min(bidLimit, getCurrentHighestBid() + getIncrement());

            // Check if the next bid is valid and higher than the current highest bid
            if (nextBid > getCurrentHighestBid()) {
                // Update the highest bid and create a new bid object
                setCurrentHighestBid(nextBid);
                Bid counterNewBid(*this, bidder, nextBid); // Assuming competingMember context
                bids.push_back(counterNewBid);

                std::cout << "New counter-bid placed at " << nextBid << std::endl;
                counterBid = true;
            }
        }

    } while (counterBid && getCurrentHighestBid() < bidLimit);
   */

    while (&getHighestBidder() != &bidder && getCurrentHighestBid() < bidLimit) {
        // Calculate the next bid amount
        double nextBid = std::min(bidLimit, getCurrentHighestBid() + getIncrement());

        // Check if the next bid is valid and higher than the current highest bid
        if (nextBid > getCurrentHighestBid()) {
            setCurrentHighestBid(nextBid);
            setHighestBidder(bidder);
            Bid counterNewBid(*this, bidder, nextBid);
            bids.push_back(counterNewBid);
        } else {
            break;
        }
    }
}


int main() {

}