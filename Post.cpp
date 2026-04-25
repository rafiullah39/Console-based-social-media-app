#include "Post.h"
#include "User.h"
#include "Page.h"
#include "Comment.h"
#include <iostream>
#include <fstream>

using namespace std;

Post::Post()
{
    Likedby = new int[10]; // Assuming a default max of 10 likes
}

Post::Post(int postId, int accId, bool user, const string &description, int maxComments, int likes, int *likedby, time_t uploadTime, const string &name)
{
    this->PostId = postId;
    this->accId = accId;
    this->user = user;
    this->Description = description;
    this->MaxComments = maxComments;
    this->Likes = likes;
    this->uploadTime = uploadTime;
    this->Name = name;

    this->Likedby = new int[likes];
    for (int i = 0; i < likes; i++)
    {
        this->Likedby[i] = likedby[i];
    }
}

Post::Post(const Post &other)
{
    this->PostId = other.PostId;
    this->accId = other.accId;
    this->user = other.user;
    this->uploadTime = other.uploadTime;
    this->Name = other.Name;
    this->Description = other.Description;
    this->MaxComments = other.MaxComments;
    this->Likes = other.Likes;
    this->Date = other.Date;

    this->Likedby = new int[Likes];
    for (int i = 0; i < Likes; i++)
    {
        this->Likedby[i] = other.Likedby[i];
    }
}

Post::~Post()
{
    delete[] Likedby;
}

void Post::addPost(int pid, User U[], int no)
{
    user = true;
    cout << "Enter your ID to share post: ";
    cin >> accId;

    if (U[accId - 1].getMaxPosts() >= 10)
    {
        cout << "You have reached maximum posts limit" << endl;
        return;
    }

    U[accId - 1].setMaxPosts(U[accId - 1].getMaxPosts() + 1);
    updateUser(U, no);

    cout << "Write description of post: ";
    getline(cin >> ws, Description);

    PostId = pid;
    uploadTime = time(nullptr);

    fstream postfile("Posts.txt", ios::app);
    if (!postfile)
    {
        cout << "Unable to open file for appending." << endl;
    }

    MaxComments = 0;
    Likes = 0;

    postfile << PostId << " " << accId << " " << user << " " << Description << ", " << MaxComments << " " << Likes << " ";
    postfile << uploadTime << endl;
    postfile.close();

    cout << "Post uploaded..." << endl;
}

void Post::addPost(int pid, Page Pa[], int pno)
{
    user = false;
    cout << "Enter your ID to share post: ";
    cin >> accId;

    if (Pa[accId - 1].getMaxPosts() >= 10)
    {
        cout << "You have reached maximum posts limit" << endl;
        return;
    }

    Pa[accId - 1].setMaxPosts(Pa[accId - 1].getMaxPosts() + 1);
    updatePage(Pa, pno);

    cout << "Write description of post: ";
    getline(cin >> ws, Description);

    PostId = pid;
    uploadTime = time(nullptr);

    fstream postfile("Posts.txt", ios::app);
    if (!postfile)
    {
        cout << "Unable to open file for appending." << endl;
    }

    postfile << PostId << " " << accId << " " << user << " " << Description << ", " << MaxComments << " " << Likes << " ";
    postfile << uploadTime << endl;
    postfile.close();

    cout << "Post uploaded..." << endl;
}

void Post::showPost(Comment C[], User U[], int cno)
{
    cout << "--" << PostId << "_" << Name << " shared: " << Description << endl;
    cout << "  (" << Likes << " Likes)" << endl;

    for (int i = 0; i < cno; i++)
    {
        if (C[i].getPostNo() == PostId)
        {
            C[i].showComment(U[C[i].getWriterId() - 1].getName());
        }
    }
    cout << endl;
}

void Post::likePost(Post P[], int pid, int id)
{
    Likedby[Likes++] = id;
    updatePost(P, pid);
    cout << "Post liked..." << endl;
}

void Post::showLikes(User U[])
{
    if (Likes == 0)
    {
        cout << "No likes on this post" << endl;
    }
    else
    {
        cout << "This post is liked by following people: " << endl;
        for (int i = 0; i < Likes; i++)
        {
            cout << "-> " << U[Likedby[i] - 1].getName() << endl;
        }
    }
}

// ========== Getters ==========

int Post::getPostId() const
{
    return PostId;
}

int Post::getAccId() const
{
    return accId;
}

bool Post::isUser() const
{
    return user;
}

time_t Post::getUploadTime() const
{
    return uploadTime;
}

string Post::getName() const
{
    return Name;
}

string Post::getDescription() const
{
    return Description;
}

int Post::getMaxComments() const
{
    return MaxComments;
}

int Post::getLikes() const
{
    return Likes;
}

int *Post::getLikedby() const
{
    return Likedby;
}

// ========== Setters ==========

void Post::setPostId(int id)
{
    PostId = id;
}

void Post::setAccId(int id)
{
    accId = id;
}

void Post::setUser(bool isUser)
{
    user = isUser;
}

void Post::setUploadTime(time_t t)
{
    uploadTime = t;
}

void Post::setName(const string &name)
{
    Name = name;
}

void Post::setDescription(const string &desc)
{
    Description = desc;
}

void Post::setMaxComments(int num)
{
    MaxComments = num;
}

void Post::setLikes(int num)
{
    Likes = num;
}

void Post::setLikedby(int *likedArray, int count)
{
    delete[] Likedby;
    Likedby = new int[count];
    for (int i = 0; i < count; i++)
    {
        Likedby[i] = likedArray[i];
    }
}

// ========== Friend Function ==========

void updatePost(Post P[], int pid)
{
    fstream Postfile("Posts.txt", ios::out);
    if (!Postfile)
    {
        cout << "Unable to open file for writing." << endl;
    }

    for (int i = 0; i < pid; i++)
    {
        Postfile << P[i].getPostId() << " "
                 << P[i].getAccId() << " "
                 << P[i].getDescription() << ", "
                 << P[i].getMaxComments() << " "
                 << P[i].getLikes() << " ";

        for (int j = 0; j < P[i].getLikes(); j++)
        {
            Postfile << P[i].getLikedby()[j] << " ";
        }

        Postfile << P[i].getUploadTime();
        Postfile << endl;
    }

    Postfile.close();
}
