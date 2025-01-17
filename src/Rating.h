#ifndef RATING_H
#define RATING_H

#include "User.h"
#include "Member.h"
#include "Item.h" 
#include "AuctionSystem.h"
#include <vector>
#include <iostream>

class Rating {
    private:
        double ratingScore;
        std::string review;
        std::vector<Rating> ratingList;
        
    public: 
        Rating(double ratingScore, std::string review);
        void ratingBuyer(Member buyer);
        void ratingSeller(Member seller);

        double calculateAvgRating(std::vector<Rating> ratingList);

        double getRatingScore();
        std::string getReview();

        void setRatingScore(double ratingScore);
        void setReview(std::string review);
};

#endif