#include <iostream>
#include <cmath>
#include "./include/Auction.hpp"
#include "./include/Item.hpp"

//Constuctor
Auction::Auction(const Item& item, double startingBid, double increment, double minRating) : auctionId(auctionId++), item(item), startingBid(startingBid), increment(increment), minRating(minRating) {  
    std::cout << "Auction created with ID: " << auctionId << std::endl;
}

double Auction::getStartingBid() {
    return startingBid;
}

void Auction::setStartingBid(double startingBid){
    startingBid = startingBid;
}

double Auction::getIncrement() {
    return increment;
}

void Auction::setIncrement(double increment){
    increment = increment;
}

double Auction::getMinRating() {
    return minRating;
}

void Auction::setMinRating(double minRating){
    minRating = minRating;
}


std::vector<Bid> Auction::getBidList() {
            return bids;
        }

double Auction::getCurrentHighestBid() {
    if(auctionInProcess == true) {
        if(bids.empty()) {
            std::cout << "No bids for this item yet" << std::endl;
        } else {
            bids.back();
        }
    }
}

void Auction::setCurrentHighestBid(int currentHighestBid) {
    currentHighestBid = currentHighestBid;
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

    //int buyerCp = Bid::highestBidder.cp;
    //buyerCp -= highestBid;
    //Member::setCp(buyerCp);

    //int sellerCp = Member::getCP();
    //sellerCp += highestBid;
    //Member::setCp(sellerCp);
}

void Auction::processBids(){
    if(auctionInProcess) {
        if(currentTime == endTime) {
            //auctionWinner = Bid::highestBidder;   
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

void Auction::placeBid(double amount) {
//void Auction::placeBid(Member member, double amount) {
    if(bids.empty() == true) {
        setCurrentHighestBid(startingBid);
    }
    if(getCurrentHighestBid() < amount) {
        if(checkCorrectIncrement) {
            //if(checkCPBalance > amount) {
                setCurrentHighestBid(amount);
                //Bid newBid(getAuctionId, member, amount);
                //bids.push_back(newBid);
            //} else {
            //   std::cerr << "Insufficient amount of credit points.";
            // }
        } else {
            std::cerr << "The bidding increment is " << Auction::getIncrement() << ". Please make a new bid." << std::endl;
        }
    } else {
        std::cout << "Your placing bid has to be higher than " << Auction::getCurrentHighestBid() << std::endl;
    }
}

void Auction::placeBidWithAutoBidLimit(double amount, double bidLimit) {
//void Auction::placeBid(Member member, double amount, double bidLimit) {
    if(bids.empty() == true) {
        setCurrentHighestBid(startingBid);
    }
    if(getCurrentHighestBid() < amount) {
        if(checkCorrectIncrement) {
            //if(checkCPBalance > amount) {
                setCurrentHighestBid(amount);
                //Bid newBid(getAuctionId, member, amount);
                //bids.push_back(newBid);
            //} else {
            //   std::cerr << "Insufficient amount of credit points.";
            // }
        } else {
            std::cerr << "The bidding increment is " << Auction::getIncrement() << ". Please make a new bid." << std::endl;
        }
    } else {
        std::cout << "Your placing bid has to be higher than " << Auction::getCurrentHighestBid() << std::endl;
    }

    bool counterBid;

    do {
        counterBid = false;

        // Determine the next bid amount for the bidder
        double nextBid = std::min(bidLimit, getCurrentHighestBid() + getIncrement());

        // Check if the next bid is valid and higher than the current highest bid
        if (nextBid > getCurrentHighestBid()) {
            // Update the highest bid and create a new bid object
            setCurrentHighestBid(nextBid);
            //Bid counterNewBid(getAuctionId(), competingMember, nextBid); // Assuming competingMember context
            //bids.push_back(counterNewBid);

            std::cout << "New counter-bid placed at " << nextBid << std::endl;
            counterBid = true;
        }

    } while (counterBid && getCurrentHighestBid() < bidLimit);
   
}


int main() {

}