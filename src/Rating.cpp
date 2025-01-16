#include "Member.h"
#include "Rating.h"

#include <iostream>

Rating::Rating(){};

void Rating::ratingBuyer(Member buyer) {
    std::cout << "Rate the buyer for your item from 1-5" << std::endl;
    std::cin >> ratingScore;

    std::cout << "Write a comment for your buyer: " << std::endl;

    buyer.getBuyerRatingList().push_back(ratingScore);

    buyer.setBuyerRating(calculateAvgRating(buyer.getBuyerRatingList()));
}

void Rating::ratingSeller(Member seller) {
    std::cout << "Rate the seller for your item from 1-5" << std::endl;
    std::cin >> ratingScore;

    std::cout << "Write a comment for your seller: " << std::endl;

    seller.getSellerRatingList().push_back(ratingScore);

    seller.setBuyerRating(calculateAvgRating(seller.getSellerRatingList()));
}

double Rating::calculateAvgRating(std::vector<double> ratingList) {
    double total = 0.0;
    for(int i = 0; i < ratingList.size(); i++) {
        total += ratingList[i];
    }
    return total / ratingList.size();
}

