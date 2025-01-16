#include "Utils.h"
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>

namespace Utils
{

    // Validate password strength
    bool isValidPassword(const std::string &password)
    {
        const std::regex strongPasswordRegex(
            R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%^&*()\-_=+{};:,<.>]).{8,})");

        const std::vector<std::string> weakPasswords = {"12345", "password", "123456", "admin"};

        if (!std::regex_match(password, strongPasswordRegex))
        {
            showError("Password must be at least 8 characters long and include at least one uppercase letter, "
                      "one lowercase letter, one digit, and one special character.");
            return false;
        }

        if (std::find(weakPasswords.begin(), weakPasswords.end(), password) != weakPasswords.end())
        {
            showError("Weak password not allowed.");
            return false;
        }

        return true;
    }

    // Validate email format
    bool isValidEmail(const std::string &email)
    {
        const std::regex emailRegex(R"(([\w.%+-]+)@([\w.-]+)\.([a-zA-Z]{2,}))");

        if (!std::regex_match(email, emailRegex))
        {
            showError("Invalid email format. Email must include a domain and end with '@example.com' or similar.");
        }
        return std::regex_match(email, emailRegex);
    }

    // Validate username
    bool isValidUsername(const std::string &username)
    {
        if (username.length() < 3 || username.length() > 15)
        {
            showError("Username must be 3-15 characters long");
            return false;
        }

        for (char ch : username)
        {
            if (!isalnum(ch) && ch != '_')
            {
                showError("Username can only contain letters, numbers, or underscores.");
                return false;
            }
        }

        return true;
    }

    // Get current date and time as string
    std::string getCurrentDateTime()
    {
        std::time_t now = std::time(nullptr);
        std::tm *localTime = std::localtime(&now);
        std::ostringstream oss;
        oss << (localTime->tm_year + 1900) << "-"
            << (localTime->tm_mon + 1) << "-"
            << localTime->tm_mday << " "
            << localTime->tm_hour << ":"
            << localTime->tm_min << ":"
            << localTime->tm_sec;
        return oss.str();
    }

    
    void showError(const std::string &message)
    {
        std::cout << "\n[ERROR] " << message << "\n\n";
    }

    void showInfo(const std::string &message)
    {
        std::cout << "\n[INFO] " << message << "\n\n";
    }

    void showSuccess(const std::string &message)
    {
        std::cout << "\n[SUCCESS] " << message << "\n\n";
    }

    void showWarning(const std::string &message)
    {
        std::cout << "\n[WARNING] " << message << "\n\n";
    }

}
