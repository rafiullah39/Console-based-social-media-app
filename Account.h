#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account
{
protected:
    int id;
    string name;
    int maxPosts;

public:
    // Default constructor
    Account();

    // Parameterized constructor
    Account(int id, const string &name, int maxPosts);

    // Virtual destructor
    virtual ~Account();

    // Pure virtual function
    virtual void signup(int id) = 0;

    // Getters
    virtual int getId() const;
    virtual string getName() const;
    virtual int getMaxPosts() const;

    // Setters
    virtual void setId(int id);
    virtual void setName(const string &name);
    virtual void setMaxPosts(int posts);
};

#endif
