#include "Item.h"

Item::Item(int id, const std::string &name, const std::string &category, const std::string &description,
           double startingBid, double bidIncrement, const std::string &sellerUsername, double minRating)
    : id(id), name(name), category(category), description(description), startingBid(startingBid),
      bidIncrement(bidIncrement), currentBid(0), highestBidder("None"), sellerUsername(sellerUsername),
      minRating(minRating), hasActiveBids(false), startDateTime(""), endDateTime("") {}

int Item::getId() const { return id; }
std::string Item::getName() const { return name; }
std::string Item::getCategory() const { return category; }
std::string Item::getDescription() const { return description; }
double Item::getStartingBid() const { return startingBid; }
double Item::getBidIncrement() const { return bidIncrement; }
double Item::getCurrentBid() const { return currentBid; }
std::string Item::getHighestBidder() const { return highestBidder; }
std::string Item::getSellerUsername() const { return sellerUsername; }
double Item::getMinRating() const { return minRating; }
std::string Item::getEndDateTime() const { return endDateTime; }
bool Item::getHasActiveBids() const { return hasActiveBids; }
std::string Item::getStartDateTime() const { return startDateTime; }

void Item::setName(const std::string &newName)
{
  this->name = newName;
}

void Item::setCategory(const std::string &newCategory)
{
  this->category = newCategory;
}

void Item::setDescription(const std::string &newDescription)
{
  this->description = newDescription;
}

void Item::setStartingBid(const double &bid)
{
  this->startingBid = bid;
}

void Item::setBidIncrement(const double &increment)
{
  this->bidIncrement = increment;
}

void Item::setMinRating(const double &rating)
{
  this->minRating = rating;
}
void Item::setCurrentBid(const double bid) { currentBid = bid; }
void Item::setHighestBidder(const std::string &bidder) { highestBidder = bidder; }
void Item::setEndDateTime(const std::string &endTime) { endDateTime = endTime; }
void Item::setHasActiveBids(bool status) { hasActiveBids = status; }
void Item::setStartDateTime(const std::string &time) { startDateTime = time; }
