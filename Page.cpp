#include "Page.h"
#include <iostream>
#include <fstream>

using namespace std;

Page::Page()
{
    this->followersNo = 0;
    this->Followers;
}

Page::Page(int pageId, const string &name, int maxPosts, int followersNo, vector<int> followers) : Account(pageId, name, maxPosts)
{
    this->followersNo = followersNo;
    this->Followers = followers;
    for (int i = 0; i < followersNo; i++)
    {
        this->Followers[i] = followers[i];
    }
}

Page::Page(const Page &other) : Account(other.id, other.name, other.maxPosts) // Call base class copy constructor
{
    this->followersNo = other.followersNo;

    this->Followers = other.Followers;
    for (int i = 0; i < followersNo; i++)
    {
        this->Followers[i] = other.Followers[i];
    }
}

Page::~Page()
{
}

void Page::signup(int pno)
{
    cout << "Give required information to create account..." << endl;
    cout << "Enter Page name: ";
    getline(cin >> ws, name);
    id = pno;
    cout << "You have successfully created your account." << endl;
    cout << "Here are your account details..." << endl;
    cout << "Page Id : " << id << endl;
    cout << "Name : " << name << endl;

    fstream pagefile("Pages.txt", ios::app);
    if (!pagefile)
    {
        cout << "Unable to open file for appending." << endl;
    }
    pagefile << id << " " << name << ", " << maxPosts << " " << followersNo << endl;
    pagefile.close();
}

// ========== Getters ==========

int Page::getId() const
{
    return this->id;
}
string Page::getName() const
{
    return this->name;
}
int Page::getMaxPosts() const
{
    return this->maxPosts;
}
void Page::addFollower(int userId)
{
    Followers.push_back(userId);
}

int Page::getFollowersNo() const
{
    return Followers.size();
}

vector<int> &Page::getFollowers()
{
    return Followers;
}

// ========== Setters ==========

void Page::setId(int id)
{
    this->id = id;
}
void Page::setName(const string &name)
{
    this->name = name;
}
void Page::setMaxPosts(int posts)
{
    this->maxPosts = posts;
}
void Page::setFollowersNo(int num)
{
    followersNo = num;
}
void Page::setFollowers(const std::vector<int> &followersList)
{
    this->Followers = followersList;
}

// ========== Friend Function ==========

void updatePage(Page Pa[], int pno)
{
    fstream pfile("Pages.txt", ios::out);
    if (!pfile)
    {
        cout << "Unable to open file for writing." << endl;
    }

    for (int i = 0; i < pno; i++)
    {
        pfile << Pa[i].getId() << " " << Pa[i].getName() << ", " << Pa[i].getMaxPosts() << " " << Pa[i].getFollowersNo() << " ";
        for (int j = 0; j < Pa[i].getFollowersNo(); j++)
        {
            pfile << Pa[i].getFollowers()[j] << " ";
        }
        pfile << endl;
    }

    pfile.close();
}
