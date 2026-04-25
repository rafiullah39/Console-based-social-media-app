#ifndef POST_H
#define POST_H

#include <string>
#include <ctime>
using namespace std;

class Post
{
private:
    int PostId;
    int accId;
    bool user;
    time_t uploadTime;
    string Name;
    string Description;
    int MaxComments = 0;
    int Likes = 0;
    int *Likedby = nullptr;
    int Date;

public:
    Post();
    Post(int postId, int accId, bool user, const string &description, int maxComments, int likes, int *likedby, time_t uploadTime, const string &name);
    Post(const Post &other);
    ~Post();

    void addPost(int pid, class User U[], int no);
    void addPost(int pid, class Page Pa[], int pno);
    void showPost(class Comment C[], class User U[], int cno);
    void likePost(Post P[], int pid, int id);
    void showLikes(User U[]);

    int getPostId() const;
    int getAccId() const;
    bool isUser() const;
    time_t getUploadTime() const;
    string getName() const;
    string getDescription() const;
    int getMaxComments() const;
    int getLikes() const;
    int *getLikedby() const;

    void setPostId(int id);
    void setAccId(int id);
    void setUser(bool isUser);
    void setUploadTime(time_t t);
    void setName(const string &name);
    void setDescription(const string &desc);
    void setMaxComments(int num);
    void setLikes(int num);
    void setLikedby(int *likedArray, int count);

    friend void updatePost(Post P[], int pid);
};

#endif
