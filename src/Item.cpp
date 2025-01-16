#include "Item.h"

Item::Item(int id, const std::string& name, const std::string& category, const std::string& description,
           int startingBid, int bidIncrement, const std::string& sellerUsername, int minRating)
    : id(id), name(name), category(category), description(description), startingBid(startingBid), 
      bidIncrement(bidIncrement), currentBid(0), highestBidder("None"), sellerUsername(sellerUsername), 
      minRating(minRating), endDateTime("Unset") {}

int Item::getId() const { return id; }
std::string Item::getName() const { return name; }
std::string Item::getCategory() const { return category; }
std::string Item::getDescription() const { return description; }
int Item::getStartingBid() const { return startingBid; }
int Item::getBidIncrement() const { return bidIncrement; }
int Item::getCurrentBid() const { return currentBid; }
std::string Item::getHighestBidder() const { return highestBidder; }
std::string Item::getSellerUsername() const { return sellerUsername; }
int Item::getMinRating() const { return minRating; }
std::string Item::getEndDateTime() const { return endDateTime; }
bool Item::getHasActiveBids() const { return hasActiveBids; }
std::string Item::getStartDateTime() const { return startDateTime; }

void Item::setCurrentBid(int bid) { currentBid = bid; }
void Item::setHighestBidder(const std::string& bidder) { highestBidder = bidder; }
void Item::setEndDateTime(const std::string& endTime) { endDateTime = endTime; }
void Item::setHasActiveBids(bool status) { hasActiveBids = status; }
void Item::setStartDateTime(const std::string& time) { startDateTime = time; }

