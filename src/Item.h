#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
private:
    int id;
    std::string name;
    std::string category;
    std::string description;
    double startingBid;
    double bidIncrement;
    double currentBid;
    std::string highestBidder;
    std::string sellerUsername;
    double minRating;
    std::string endDateTime;
    bool hasActiveBids;
    std::string startDateTime;

public:
    Item(int id, const std::string &name, const std::string &category, const std::string &description,
         double startingBid, double bidIncrement, const std::string &sellerUsername, double minRating);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getDescription() const;
    double getStartingBid() const;
    double getBidIncrement() const;
    double getCurrentBid() const;
    std::string getHighestBidder() const;
    std::string getSellerUsername() const;
    double getMinRating() const;
    std::string getEndDateTime() const;
    bool getHasActiveBids() const;
    std::string getStartDateTime() const;

    // Setters
    void setName(const std::string &newName);
    void setCategory(const std::string &newCategory);
    void setDescription(const std::string &newDescription);
    void setStartingBid(const double &newStartingBid);
    void setBidIncrement(const double &newBidIncrement);
    void setMinRating(const double &newMinRating);

    void setCurrentBid(const double bid);
    void setHighestBidder(const std::string &bidder);
    void setEndDateTime(const std::string &endTime);
    void setHasActiveBids(bool status);
    void setStartDateTime(const std::string &time);
};

#endif // ITEM_H
