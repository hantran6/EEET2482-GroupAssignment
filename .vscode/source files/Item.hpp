#ifndef ITEM_H 
#define ITEM_H

#include <string> 
#include <map> 
#include <ctime> // to handle date and time 

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
    int currentHighestBid; 

    std::string name; 
    std::string category; 
    std::string shortDescription; 

    std::map<std::string, std::string> listingDetails;  
    bool hasActiveBids;  


public: 
    // Constructor 
    Item(std::string itemName, std::string itemCategory, std::string desc, int startBid);
  
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