#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Account.h"
using namespace std;

class User : public Account
{
private:
    int friendsNo = 0;
    int pagesNo = 0;
    vector<int> Friend;
    vector<int> LikedPages;

public:
    User();
    User(int id, const string &name, int maxPosts, int friendsNo, int pagesNo, vector<int> friends, vector<int> likedPages);
    User(const User &other);
    ~User();

    void signup(int no);
    void addFriend(User U[], int no, int fid);
    void likePage(class Page Pa[], User U[], int page, int no, int pno);

    int getId() const override;
    string getName() const override;
    int getMaxPosts() const override;
    int getFriendsNo() const;
    int getPagesNo() const;
    int getFriend(int index) const;
    int getLikedPages(int index) const;

    void setId(int id) override;
    void setName(const string &name) override;
    void setMaxPosts(int posts) override;
    void setFriendsNo(int num);
    void setPagesNo(int num);
    void setFriends(vector<int> friendsArray, int count);
    void setLikedPages(vector<int> pagesArray, int count);

    friend void updateUser(User u[], int no);
};

#endif
