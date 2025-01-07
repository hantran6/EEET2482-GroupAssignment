#include <Item.h> 
#include <iostream> 
#include <iomanip> 
#include <ctime> 

Item::Item(std::string itemName, std::string itemCategory, std::string desc, int startBid)
: name(itemName), category(itemCategory), shortDescription(desc), startingBid(startBid),
currentBid(startBid), hasActiveBids(false), bidIncrement(10), minRatingThreshold(0), currentHighestBid(0) {}

// Place a bid on the item
void Item::placeBid(int amount, std::string &bidder) {
    if (amount < currentBid + bidIncrement) {
        std::cerr << "Error: Bid must be at least " << bidIncrement << " CP higher than the current bid.\n";
        return;
    }
    currentBid = amount; 
    currentHighestBidder = bidder; 
    hasActiveBids = true;  

    


}

