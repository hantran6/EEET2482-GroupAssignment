#include <iostream>
#include <cmath>
#include "Bid.h"
#include "Item.h"



Bid::Bid(int itemId, std::string bidderUsername, double amount) : itemId(itemId), bidderUsername(bidderUsername), amount(amount) {}


double Bid::getBidAmount() {
    return amount;
}

void Bid::setBidAmount(double amount) {
    this->amount = amount;
}

int Bid::getItemId() {
    return itemId;
}

void Bid::setItemId(int itemId) {
    this->itemId = itemId;
}

std::string Bid::getBidderUsername() {
    return bidderUsername;
}

void Bid::setBidderUsername(std::string bidderUsername) {
    this->bidderUsername = bidderUsername;
}

bool Bid::checkIncrement(Item item, double amount) {
    double difference = amount - item.getCurrentBid();
    if(std::fmod(difference, item.getBidIncrement()) == 0) {
        return true;
    } else {
        return false;
    }
}
