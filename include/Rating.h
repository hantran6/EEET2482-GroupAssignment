#ifndef RATING_H
#define RATING_H

#include <vector> 
#include <string> 

class Rating {
private:
    std::vector <int> sellerRatings; 
    std::vector <int> buyerRatings; 
    double sellerAverageRating; 
    double buyerAverageRating; 
    // int minRatingThreshold; // to specify the min rating required for a buyer to view the item 

public: 
    // Constructor 
    Rating (std::vector <int> sellerRatings, std::vector <int> buyerRatings,double sellerAverageRating, double buyerAverageRating); 
    // Getters and setters 
    double getSellerAverageRating(); 
    double getBuyerAverageRating(); 
    std::vector <int> &getBuyerRating(); 
    std::vector <int> &getSellerRating(); 

    // add ratings for seller (sellers rate buyers)
    void addSellerRating(int rating);
    // add ratings for buyer (buyers rate sellers)
    void addBuyerRating(int rating);
    // update average buyer rating 
    void updateBuyerAvgRating();
    // update average seller rating 
    void updateSellerAvgRating(); 
    // display the ratings 
    void displayRating();
};

#endif 