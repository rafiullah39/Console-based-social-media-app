#include "User.h"
#include "Page.h"
#include <iostream>
#include <fstream>

using namespace std;

User::User()
{
    this->friendsNo = 0;
    this->pagesNo = 0;
}

User::User(int id, const string &name, int maxPosts, int friendsNo, int pagesNo, vector<int> friends, vector<int> likedPages)
    : Account(id, name, maxPosts) // base class constructor call
{
    this->friendsNo = friendsNo;
    this->pagesNo = pagesNo;
}

User::User(const User &other) : Account(other.id, other.name, other.maxPosts)
{
    this->friendsNo = other.friendsNo;
    this->pagesNo = other.pagesNo;

    this->Friend = other.Friend;

    this->LikedPages = other.LikedPages;
}

User::~User()
{
}

void User::signup(int no)
{
    cout << "Give required information to create account..." << endl;
    cout << "Enter your Name: ";
    getline(cin >> ws, name);
    id = no;
    fstream ufile("User.txt", ios::app);
    ufile << id << " " << name << ", " << maxPosts << " " << friendsNo << " " << pagesNo << " " << 0 << " " << 0 << endl;
    ufile.close();
    cout << "You have successfully created your account." << endl;
    cout << "Id: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Note: Next time you will need this id to login..." << endl;
}

void User::addFriend(User U[], int no, int fid)
{
    friendsNo++;
    Friend.push_back(fid);
    U[fid - 1].friendsNo++;
    U[fid - 1].Friend.push_back(id);
    updateUser(U, no);
}

void User::likePage(Page Pa[], User U[], int pageId, int no, int pno)
{
    // Add page to this user's liked pages
    pagesNo++;
    LikedPages.push_back(pageId);

    // Add this user's ID to the page's follower list
    Pa[pageId - 1].addFollower(id);

    // Save updated data
    updateUser(U, no);
    updatePage(Pa, pno);
}

void User::setId(int id)
{
    this->id = id;
}

void User::setName(const string &name)
{
    this->name = name;
}

void User::setMaxPosts(int posts)
{
    this->maxPosts = posts;
}

// Getters
int User::getId() const
{
    return this->id;
}

string User::getName() const
{
    return this->name;
}

int User::getMaxPosts() const
{
    return this->maxPosts;
}

int User::getFriendsNo() const
{
    return friendsNo;
}
int User::getPagesNo() const
{
    return pagesNo;
}
int User::getFriend(int index) const
{
    return Friend[index];
}
int User::getLikedPages(int index) const
{
    return LikedPages[index];
}

void User::setFriendsNo(int num)
{
    friendsNo = num;
}
void User::setPagesNo(int num)
{
    pagesNo = num;
}
void User::setFriends(vector<int> friendsArray, int count)
{
    Friend = friendsArray;
}
void User::setLikedPages(vector<int> pagesArray, int count)
{
    LikedPages = pagesArray;
}

void updateUser(User u[], int no)
{
    fstream updatefile("User.txt", ios::out);
    for (int i = 0; i < no; i++)
    {
        updatefile << u[i].id << " " << u[i].name << ", " << u[i].maxPosts << " " << u[i].friendsNo << " ";
        for (int j = 0; j < u[i].friendsNo; j++)
        {
            updatefile << u[i].Friend[j] << " ";
        }
        updatefile << u[i].pagesNo << " ";
        for (int j = 0; j < u[i].pagesNo; j++)
        {
            updatefile << u[i].LikedPages[j] << " ";
        }
        updatefile << endl;
    }
    updatefile.close();
}
