#include <iostream>
#include "Auction.hpp"
#include "Item.hpp"

//Constuctor
Auction::Auction(int auctionId, const Item& item) : auctionId(auctionId), item(item) {  
    std::cout << "Auction created with ID: " << auctionId << std::endl;
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
    std::chrono::time_point<std::chrono::system_clock> currentTime;
    

    if(currentTime == endTime) {
        //auctionWinner = Bid::highestBidder;   
        Auction::endAuction();
    }
}


int main() {

}