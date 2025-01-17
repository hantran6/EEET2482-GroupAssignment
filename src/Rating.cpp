#include "Member.h"
#include "Rating.h"

#include <iostream>

Rating::Rating(double ratingScore, std::string review) : ratingScore(ratingScore), review(review) {}


double Rating::getRatingScore() {
    return ratingScore;
}

std::string Rating::getReview() {
    return review;
}

void Rating::setRatingScore(double ratingScore) {
    this->ratingScore = ratingScore;
}

void Rating::setReview(std::string review) {
    this->review = review;
}

void Rating::ratingBuyer(Member buyer) {
    std::cout << "Rate the buyer for your item from 1-5" << std::endl;
    std::cin >> ratingScore;

    std::cout << "Write a comment for your buyer: " << std::endl;
    std::cin >> review;

    Rating *newRating = new Rating(ratingScore, review);

    buyer.getBuyerRatingList().push_back(*newRating);

    buyer.setBuyerRatingScore(calculateAvgRating(buyer.getBuyerRatingList()));
}

void Rating::ratingSeller(Member seller) {
    std::cout << "Rate the seller for your item from 1-5" << std::endl;
    std::cin >> ratingScore;

    std::cout << "Write a comment for your seller: " << std::endl;
    std::cin >> review;

    Rating *newRating = new Rating(ratingScore, review);

    seller.getSellerRatingList().push_back(*newRating);

    seller.setBuyerRatingScore(calculateAvgRating(seller.getSellerRatingList()));
}

double Rating::calculateAvgRating(std::vector<Rating> ratingList) {
    double total = 0.0;
    for(int i = 0; i < ratingList.size(); i++) {
        total += ratingList[i].getRatingScore();
    }
    return total / ratingList.size();
}

/*
auctionends() {
    if(currentime == endtime) {
        auctionwinnr = currenthighestbidder;
        double highestbid = getcurrenthighestbid()
        updatecreditpoint(buyer, highestbid);
        updatecreditpoints(seller, highestbid);

        if(getSellerUsername == this->username)
             ratingbuyer(auctionwinner)
        else if(this->username == auctionWinner.getUsername())
            ratingSeller(seller);


    }
}
*/
