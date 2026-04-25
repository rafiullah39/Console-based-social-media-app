#include "Account.h"

// Default constructor
Account::Account()
{
    this->id = 0;
    this->name = "";
    this->maxPosts = 0;
}

// Parameterized constructor
Account::Account(int id, const string &name, int maxPosts)
{
    this->id = id;
    this->name = name;
    this->maxPosts = maxPosts;
}

// Destructor
Account::~Account()
{
    // No dynamic memory to release, but needed for polymorphism
}

// Getters
int Account::getId() const
{
    return this->id;
}

string Account::getName() const
{
    return this->name;
}

int Account::getMaxPosts() const
{
    return this->maxPosts;
}

// Setters
void Account::setId(int id)
{
    this->id = id;
}

void Account::setName(const string &name)
{
    this->name = name;
}

void Account::setMaxPosts(int posts)
{
    this->maxPosts = posts;
}
