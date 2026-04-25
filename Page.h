#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <vector>
#include "Account.h"
using namespace std;

class Page : public Account
{
private:
    int followersNo = 0;
    vector<int> Followers;

public:
    Page();
    Page(int pageId, const string &title, int maxPosts, int followersNo, vector<int> followers);
    Page(const Page &other);
    ~Page();

    int getId() const override;
    string getName() const override;
    int getMaxPosts() const override;
    int getFollowersNo() const;
    vector<int> &getFollowers();

    void setId(int id) override;
    void setName(const string &name) override;
    void setMaxPosts(int posts) override;
    void setFollowersNo(int num);
    void setFollowers(const std::vector<int> &followersList);

    void addFollower(int userId);
    void signup(int pno);
    friend void updatePage(Page Pa[], int pno);
};

#endif