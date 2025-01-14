#ifndef RATING_H
#define RATING_H

#include <vector> 
#include <string> 

class Rating {
private:
    vector <int> sellerRatings; 
    vector <int> buyerRatings; 
    int ratingID;
    int score = 3; // score rating score ranging from 1 to 5, default rating = 3 
    double sellerAverageRating; 
    double buyerAverageRating; 

public: 
    Rating ();
    
    void addSellerRating(int rating);

    void addBuyerRating(int rating);

    

};

#endif 