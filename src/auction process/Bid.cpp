#include <iostream>
#include "./include/Bid.h"
#include "./include/Auction.h"



Bid::Bid(const Auction& auction, const Member& bidder, int amount) : auction(auction), bidder(bidder), amount(amount) {}

int Bid::getBidId(){
    return bidId;
}

void Bid::setBidId(int bidId){
    bidId = bidId;
}


int Bid::getBidAmount(){
    return amount;
}

void Bid::setBidAmount(double amount) {
    this->amount = amount;
}
