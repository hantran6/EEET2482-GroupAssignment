#ifndef RATING_H
#define RATING_H

#include "User.h"
#include "Member.h"
#include "Item.h" 
#include "AuctionSystem.h"
#include <vector>

class Rating {
    private:
        double ratingScore;
        //string ratingComment;
    public: 
        Rating();
        void ratingBuyer(Member buyer);
        void ratingSeller(Member seller);

        double calculateAvgRating(std::vector<double> ratingList);
};

#endif