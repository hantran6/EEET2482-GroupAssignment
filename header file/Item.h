#ifndef ITEM_H 
#define ITEM_H

#include <string> 
#include <map> 
class Item {
/* 
-seller: Member
-currentHighestBidder: Member

-startDateTime: DateTime
-endDateTime: DateTime

*/
private: 
    // Attributes 
    int itemID; 
    int startingBid; 
    int currentBid; 
    int bidIncrement; 
    int minRatingThreshold; 
    float minRating; 
    

    std::string name; 
    std::string category; 
    std::string description; 

    std::map<std::string, std::string> listingDetails;  
    bool hasActiveBids;  


public: 
    
    // Constructor
    Item(std::string name, std::string category, std::string description, int startingBid)
        : name(name), category(category), description(description),
        startingBid(startingBid), currentBid(currentBid), hasActiveBids(false) {}
  
    // Setters and getters
    std::string getName();
    int getCurrentBid();

    void placeBid(int amount, std::string &bidder);
    void displayItems ();
    void createListing(); 
    
    // update new details 
    void updateListing(const std::map<std::string, std::string>& details);

    // Delete a listing if no active bid available 
    bool deleteListing();
};

#endif 

