#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include "User.h"
#include "Page.h"
#include "Post.h"
#include "Comment.h"

using namespace std;

void updateNumbers(int no, int pno, int pid, int cno);
void search(User users[], Page pages[], Post posts[], int no, int pno, int pid);
void loadData(User *&U, int &no, Page *&Pa, int &pno, Post *&P, int &pid, Comment *&C, int &cno);

int main()
{
    // Loading data
    User *U;
    Page *Pa;
    Post *P;
    Comment *C;
    int no, pno, pid, cno;

    loadData(U, no, Pa, pno, P, pid, C, cno);

    // Main program flow

    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------Welcome to SOCIAL SPHERE--------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;

    int acc;
    do
    {
        cout << endl;
        cout << "Select Account type: " << endl;
        cout << "1. Person" << endl;
        cout << "2. Page" << endl;
        cout << "3. Exit" << endl;
        cin >> acc;

        if (acc == 1)
        {
            int opt;
            do
            {
                cout << endl;
                cout << "Select the sign in option:" << endl;
                cout << "1. Login" << endl;
                cout << "2. Sign Up" << endl;
                cout << "3. Back" << endl;
                cin >> opt;

                if (opt == 1)
                {
                    int id;
                    bool login = false;
                    cout << endl;
                    cout << "Enter your id: ";
                    cin >> id;

                    for (int i = 0; i < no; i++)
                    {
                        if (id == U[i].getId())
                        {
                            cout << "------------------------------Signed in as " << U[i].getName() << "------------------------------" << endl;
                            login = true;
                        }
                    }

                    if (login)
                    {
                        int menu;
                        do
                        {
                            cout << endl;
                            cout << "Main Menu:" << endl;
                            cout << "1. Feed" << endl;
                            cout << "2. Manage Profile" << endl;
                            cout << "3. Search" << endl;
                            cout << "4. View a page" << endl;
                            cout << "5. Logout" << endl;
                            cout << "Enter your choice: ";
                            cin >> menu;
                            cout << endl;

                            if (menu == 1)
                            {
                                loadData(U, no, Pa, pno, P, pid, C, cno);
                                cout << "______________________________Feed_______________________________" << endl;
                                int feed = 0;
                                bool displayed;

                                for (int i = 0; i < pid; i++)
                                {
                                    Post &post = P[i];
                                    bool show = false;

                                    if (post.isUser())
                                    {
                                        for (int j = 0; j < U[id - 1].getFriendsNo(); j++)
                                        {
                                            if (post.getAccId() == U[id - 1].getFriend(j))
                                            {
                                                show = true;
                                                break;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (int j = 0; j < U[id - 1].getPagesNo(); j++)
                                        {
                                            if (post.getAccId() == U[id - 1].getLikedPages(j))
                                            {
                                                show = true;
                                                break;
                                            }
                                        }
                                    }

                                    if (show)
                                    {
                                        post.showPost(C, U, cno);
                                        cout << endl;
                                        feed++;
                                    }
                                }

                                if (feed == 0)
                                {
                                    cout << "No posts to show" << endl;
                                    cout << "Note: Add friends or like pages to get posts in your feed" << endl;
                                }
                                else
                                {
                                    int feedopt;
                                    do
                                    {
                                        cout << endl;
                                        cout << "Select from the following options:" << endl;
                                        cout << "1. Like a post" << endl;
                                        cout << "2. Comment on a post" << endl;
                                        cout << "3. Back" << endl;
                                        cin >> feedopt;

                                        if (feedopt == 1)
                                        {
                                            int feedpost;
                                            cout << endl;
                                            cout << "Enter Post Id to like it: ";
                                            cin >> feedpost;
                                            cout << endl;

                                            if (feedpost <= pid)
                                            {
                                                P[feedpost - 1].likePost(P, pid, id);
                                            }
                                            else
                                            {
                                                cout << "Invalid Post Id" << endl;
                                            }
                                        }

                                        if (feedopt == 2)
                                        {
                                            int postId;
                                            cout << "\nEnter Post Id to comment on: ";
                                            cin >> postId;
                                            cout << endl;

                                            if (postId >= 1 && postId <= pid)
                                            {
                                                if (P[postId - 1].getMaxComments() >= 10)
                                                {
                                                    cout << "\nThis post has reached maximum comments limit!\n";
                                                    cout << "Note: Maximum 10 comments can be uploaded on a post\n";
                                                }
                                                else
                                                {
                                                    // Add new Comment
                                                    cno++;
                                                    Comment *temp = new Comment[cno];
                                                    for (int i = 0; i < cno - 1; i++)
                                                    {
                                                        temp[i] = C[i];
                                                    }
                                                    delete[] C;
                                                    C = temp;

                                                    C[cno - 1].postComment(cno, id, postId);
                                                }
                                            }
                                            else
                                            {
                                                cout << "Invalid Post Id" << endl;
                                            }
                                        }
                                    } while (feedopt < 3);
                                }
                            }

                            if (menu == 2)
                            {
                                loadData(U, no, Pa, pno, P, pid, C, cno);
                                int option;
                                do
                                {
                                    cout << endl;
                                    cout << "_________________________Manage Profile__________________________" << endl;
                                    cout << "1. Create a Post" << endl;
                                    cout << "2. Timeline" << endl;
                                    cout << "3. Friend List" << endl;
                                    cout << "4. Liked Pages" << endl;
                                    cout << "5. Back" << endl;
                                    cout << "Enter your choice: " << endl;
                                    cin >> option;

                                    if (option == 1)
                                    {
                                        Post P;
                                        pid++;
                                        P.addPost(pid, U, no);
                                        updateNumbers(no, pno, pid, cno);
                                    }

                                    if (option == 2)
                                    {
                                        loadData(U, no, Pa, pno, P, pid, C, cno);
                                        cout << endl;
                                        cout << "-----Timeline-----" << endl;
                                        cout << "------------------" << endl;
                                        cout << endl;
                                        int userId = U[id - 1].getId();

                                        for (int i = 0; i < pid; i++)
                                        {
                                            if (P[i].isUser() && P[i].getAccId() == userId)
                                            {
                                                P[i].showPost(C, U, cno);
                                            }
                                        }

                                        int timeline;
                                        do
                                        {
                                            cout << endl;
                                            cout << "Select an option from given below: " << endl;
                                            cout << "1. See likes of a post" << endl;
                                            cout << "2. Delete a comment" << endl;
                                            cout << "3. Back" << endl;
                                            cin >> timeline;

                                            if (timeline == 1)
                                            {
                                                int timelinepost;
                                                cout << endl;
                                                cout << "Enter the Post Id to see its likes: ";
                                                cin >> timelinepost;

                                                P[timelinepost - 1].showLikes(U);
                                            }

                                            if (timeline == 2)
                                            {
                                                int cid;
                                                cout << endl;
                                                cout << "Enter comment id to delete that comment: ";
                                                cin >> cid;
                                                C[cid - 1].deleteComment(C, no, pno, pid, cno);
                                            }
                                        } while (timeline < 3);
                                    }

                                    if (option == 3)
                                    {
                                        loadData(U, no, Pa, pno, P, pid, C, cno);
                                        cout << "-------Friend List-------" << endl;
                                        cout << "---------------------" << endl;
                                        if (U[id - 1].getFriendsNo() == 0)
                                        {
                                            cout << "You have No Friends" << endl;
                                        }
                                        else
                                        {
                                            for (int i = 0; i < U[id - 1].getFriendsNo(); i++)
                                            {
                                                cout << "-> " << U[U[id - 1].getFriend(i) - 1].getId() << "- " << U[U[id - 1].getFriend(i) - 1].getName() << endl;
                                            }
                                        }

                                        if (U[id - 1].getFriendsNo() <= (no - 2))
                                        {
                                            int friendsopt;
                                            do
                                            {
                                                cout << endl;
                                                cout << "Choose from following options: " << endl;
                                                cout << "1. Add Friends" << endl;
                                                cout << "2. Back" << endl;
                                                cin >> friendsopt;

                                                if (friendsopt == 1)
                                                {
                                                    if (U[id - 1].getFriendsNo() >= 10)
                                                    {
                                                        cout << "You have reached maximum friends limit" << endl;
                                                        cout << "Note: Maximum 10 friends can be added" << endl;
                                                    }
                                                    else
                                                    {
                                                        int fn;
                                                        cout << "You can add these people as friends" << endl;
                                                        if (U[id - 1].getFriendsNo() == 0)
                                                        {
                                                            for (int i = 0; i < no; i++)
                                                            {
                                                                if (U[i].getId() != U[id - 1].getId())
                                                                {
                                                                    cout << "-> " << U[i].getId() << "- " << U[i].getName() << endl;
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            for (int i = 0; i < no; i++)
                                                            {
                                                                bool display = true;
                                                                for (int j = 0; j < U[id - 1].getFriendsNo(); j++)
                                                                {
                                                                    if (U[i].getId() == U[id - 1].getFriend(j) || U[i].getId() == U[id - 1].getId())
                                                                    {
                                                                        display = false;
                                                                    }
                                                                }
                                                                if (display)
                                                                {
                                                                    cout << "-> " << U[i].getId() << "- " << U[i].getName() << endl;
                                                                }
                                                            }
                                                        }

                                                        cout << "Enter Id of a person to add him as a friend: ";
                                                        cin >> fn;
                                                        bool frnd = true;
                                                        for (int k = 0; k < U[id - 1].getFriendsNo(); k++)
                                                        {
                                                            if (fn == U[id - 1].getFriend(k) || fn == U[id - 1].getId() || fn > no || fn < 1)
                                                            {
                                                                frnd = false;
                                                            }
                                                        }
                                                        if (frnd)
                                                        {
                                                            U[id - 1].addFriend(U, no, fn);
                                                        }
                                                        else
                                                        {
                                                            cout << "Invalid User Id" << endl;
                                                        }
                                                    }
                                                }
                                            } while (friendsopt < 2);
                                        }
                                    }

                                    if (option == 4)
                                    {
                                        loadData(U, no, Pa, pno, P, pid, C, cno);
                                        cout << "-----Liked Pages-----" << endl;
                                        cout << "---------------------" << endl;
                                        if (U[id - 1].getPagesNo() == 0)
                                        {
                                            cout << "No liked pages to show" << endl;
                                        }
                                        else
                                        {
                                            for (int i = 0; i < U[id - 1].getPagesNo(); i++)
                                            {
                                                cout << "-> " << Pa[U[id - 1].getLikedPages(i) - 1].getId() << "- " << Pa[U[id - 1].getLikedPages(i) - 1].getName() << endl;
                                            }
                                        }

                                        if (U[id - 1].getPagesNo() <= (pno - 1))
                                        {
                                            int pagesopt;
                                            do
                                            {
                                                cout << "Choose from following options: " << endl;
                                                cout << "1. Like a Page" << endl;
                                                cout << "2. Back" << endl;
                                                cin >> pagesopt;

                                                if (pagesopt == 1)
                                                {
                                                    if (U[id - 1].getPagesNo() >= 10)
                                                    {
                                                        cout << "You have reached maximum liked pages limit" << endl;
                                                        cout << "Maximum 10 pages can be liked" << endl;
                                                    }
                                                    else
                                                    {
                                                        int pn = 0;
                                                        cout << "You can like these pages" << endl;
                                                        if (U[id - 1].getPagesNo() == 0)
                                                        {
                                                            for (int i = 0; i < pno; i++)
                                                            {
                                                                pn++;
                                                                cout << "-> " << Pa[i].getId() << "- " << Pa[i].getName() << endl;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            for (int i = 0; i < pno; i++)
                                                            {
                                                                for (int j = 0; j < U[id - 1].getPagesNo(); j++)
                                                                {
                                                                    if (Pa[i].getId() != U[id - 1].getLikedPages(j))
                                                                    {
                                                                        pn++;
                                                                        cout << "-> " << Pa[i].getId() << "- " << Pa[i].getName() << endl;
                                                                    }
                                                                }
                                                            }
                                                        }

                                                        cout << "Enter Id to like the Page: ";
                                                        cin >> pn;
                                                        bool pass = true;
                                                        for (int k = 0; k < U[id - 1].getPagesNo(); k++)
                                                        {
                                                            if (pn == U[id - 1].getLikedPages(k) || pn > pno || pn < 1)
                                                            {
                                                                pass = false;
                                                            }
                                                        }
                                                        if (pass)
                                                        {
                                                            U[id - 1].likePage(Pa, U, pn, no, pno);
                                                        }
                                                        else
                                                        {
                                                            cout << "Invalid Page Id" << endl;
                                                        }
                                                    }
                                                }
                                            } while (pagesopt < 2);
                                        }
                                    }
                                } while (option < 3);
                            }

                            if (menu == 3)
                            {
                                loadData(U, no, Pa, pno, P, pid, C, cno);
                                search(U, Pa, P, no, pno, pid);
                            }

                            if (menu == 4)
                            {
                                loadData(U, no, Pa, pno, P, pid, C, cno);
                                int pg;
                                bool login;
                                cout << "Enter your Page Id: ";
                                cin >> pg;

                                for (int i = 0; i < pno; i++)
                                {
                                    if (pg == Pa[i].getId())
                                    {
                                        cout << endl;
                                        cout << "-------------" << Pa[i].getName() << "-------------" << endl;
                                        cout << endl;
                                        login = true;
                                    }
                                }

                                if (login)
                                {
                                    for (int i = 0; i < pid; i++)
                                    {
                                        if (!P[i].isUser())
                                        {
                                            if (P[i].getAccId() == id)
                                            {
                                                P[i].showPost(C, U, cno);
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    cout << "Invalid Id" << endl;
                                }
                            }
                        } while (menu < 5);
                    }
                    else
                    {
                        cout << "Invalid Id" << endl;
                    }
                }

                if (opt == 2)
                {
                    no++;
                    User *temp = new User[no];
                    for (int i = 0; i < no - 1; i++)
                    {
                        temp[i] = U[i];
                    }
                    delete[] U;
                    U = temp;
                    U[no - 1].signup(no);
                    updateNumbers(no, pno, pid, cno);
                }
            } while (opt < 3);
        }

        if (acc == 2)
        {
            int opt;
            do
            {
                cout << endl;
                cout << "Select the sign in option:" << endl;
                cout << "1. Login" << endl;
                cout << "2. Sign Up" << endl;
                cout << "3. Back" << endl;
                cin >> opt;

                if (opt == 1)
                {
                    int id;
                    bool login = false;
                    cout << endl;
                    cout << "Enter your id: ";
                    cin >> id;

                    for (int i = 0; i < pno; i++)
                    {
                        if (id == Pa[i].getId())
                        {
                            cout << "------------------------------Signed in as " << Pa[i].getName() << "------------------------------" << endl;
                            login = true;
                        }
                    }
                    if (login)
                    {
                        int menu;
                        do
                        {
                            cout << "Main Menu: " << endl;
                            cout << "1. Timeline" << endl;
                            cout << "2. Create Post" << endl;
                            cout << "3. Back" << endl;
                            cout << "Enter your choice: ";
                            cin >> menu;

                            if (menu == 1)
                            {
                                loadData(U, no, Pa, pno, P, pid, C, cno);
                                cout << endl;
                                cout << "-----Timeline-----" << endl;
                                cout << "------------------" << endl;
                                cout << endl;
                                for (int i = 0; i < pid; i++)
                                {
                                    if (!P[i].isUser())
                                    {
                                        if (P[i].getAccId() == id)
                                        {
                                            P[i].showPost(C, U, cno);
                                        }
                                    }
                                }
                                int timeline;
                                do
                                {
                                    cout << endl;
                                    cout << "Select an option from given below: " << endl;
                                    cout << "1. See likes of a post" << endl;
                                    cout << "2. Delete a comment" << endl;
                                    cout << "3. Back" << endl;
                                    cin >> timeline;
                                    if (timeline == 1)
                                    {
                                        int timelinepost;
                                        cout << "Enter the Post Id of which likes you want to see: ";
                                        cin >> timelinepost;
                                        P[timelinepost - 1].showLikes(U);
                                    }
                                    if (timeline == 2)
                                    {
                                        int cid;
                                        cout << "Enter comment id to delete that comment: ";
                                        cin >> cid;
                                        C[cid - 1].deleteComment(C, no, pno, pid, cno);
                                    }
                                } while (timeline < 3);
                            }

                            if (menu == 2)
                            {
                                Post P;
                                pid++;
                                P.addPost(pid, Pa, pno);
                                updateNumbers(no, pno, pid, cno);
                            }

                        } while (menu < 3);
                    }
                    else
                    {
                        cout << "Invalid Id" << endl;
                    }
                }

                if (opt == 2)
                {
                    pno++;
                    Page *temp = new Page[pno];
                    for (int i = 0; i < pno - 1; i++)
                    {
                        temp[i] = Pa[i];
                    }
                    delete[] Pa;
                    Pa = temp;
                    Pa[pno - 1].signup(pno);
                    updateNumbers(no, pno, pid, cno);
                }
            } while (opt < 3);
        }
    } while (acc < 3);
}

void updateNumbers(int no, int pno, int pid, int cno)
{
    fstream upfile("Project.txt", ios::out);
    if (!upfile)
    {
        cout << "Error in opening file.\n";
    }
    upfile << no << endl;
    upfile << pno << endl;
    upfile << pid << endl;
    upfile << cno << endl;
    upfile.close();
}

void search(User U[], Page Pa[], Post P[], int no, int pno, int pid)
{
    string keyword;
    cout << "Enter the keyword: ";
    cin >> keyword;
    int u = 0;
    int pa = 0;
    int po = 0;

    cout << "Users: " << endl;
    cout << "------" << endl;
    for (int i = 0; i < no; i++)
    {
        size_t pos1 = U[i].getName().find(keyword);
        if (pos1 != string::npos)
        {
            string temp = U[i].getName().substr(pos1, keyword.length());
            if (temp == keyword)
            {
                cout << "-> " << U[i].getId() << "- " << U[i].getName() << endl;
                u++;
            }
        }
    }
    if (u == 0)
    {
        cout << "Match not found..." << endl;
    }

    cout << endl;
    cout << "Pages: " << endl;
    cout << "------" << endl;
    for (int i = 0; i < pno; i++)
    {
        size_t pos2 = Pa[i].getName().find(keyword);
        if (pos2 != string::npos)
        {
            string temp = Pa[i].getName().substr(pos2, keyword.length());
            if (temp == keyword)
            {
                cout << "-> " << Pa[i].getId() << "- " << Pa[i].getName() << endl;
                pa++;
            }
        }
    }
    if (pa == 0)
    {
        cout << "Match not found..." << endl;
    }

    cout << endl;
    cout << "Posts: " << endl;
    cout << "------" << endl;
    for (int i = 0; i < pid; i++)
    {
        size_t pos3 = P[i].getDescription().find(keyword);
        if (pos3 != string::npos)
        {
            string temp = P[i].getDescription().substr(pos3, keyword.length());
            if (temp == keyword)
            {
                cout << "-> " << P[i].getPostId() << "- " << P[i].getDescription() << endl;
                po++;
            }
        }
    }
    if (po == 0)
    {
        cout << "Match not found..." << endl;
    }
}

void loadData(User *&U, int &no, Page *&Pa, int &pno, Post *&P, int &pid, Comment *&C, int &cno)
{
    // Read project info
    fstream file("Project.txt", ios::in);
    if (!file)
    {
        cout << "Error : Unable to open Project.txt for reading.\n";
        return;
    }
    file >> no >> pno >> pid >> cno;
    file.close();

    // Load Users
    ifstream infile("User.txt");
    if (!infile)
    {
        cout << "Error : Unable to open User.txt for reading.\n";
        return;
    }
    U = new User[no];
    int userCount = 0;
    while (!infile.eof() && userCount < no)
    {
        int Id, MaxPosts = 0, friendsNo = 0, pagesNo = 0;
        string Name;
        vector<int> Friend, LikedPages;

        infile >> Id;
        U[userCount].setId(Id);

        getline(infile, Name, ',');
        U[userCount].setName(Name);

        infile >> MaxPosts;
        U[userCount].setMaxPosts(MaxPosts);

        infile >> friendsNo;
        U[userCount].setFriendsNo(friendsNo);
        for (int i = 0; i < friendsNo; ++i)
        {
            int val;
            infile >> val;
            Friend.push_back(val);
        }
        U[userCount].setFriends(Friend, friendsNo);

        infile >> pagesNo;
        U[userCount].setPagesNo(pagesNo);
        for (int j = 0; j < pagesNo; ++j)
        {
            int val;
            infile >> val;
            LikedPages.push_back(val);
        }
        U[userCount].setLikedPages(LikedPages, pagesNo);

        userCount++;
    }
    infile.close();

    // Load Pages
    ifstream pinfile("Pages.txt");
    if (!pinfile)
    {
        cout << "Unable to open Pages.txt for reading.\n";
        return;
    }
    Pa = new Page[pno];
    int pageCount = 0;
    while (!pinfile.eof() && pageCount < pno)
    {
        int pageId, MaxPosts = 0, followersNo = 0;
        string name;
        vector<int> Followers;

        pinfile >> pageId;
        Pa[pageCount].setId(pageId);

        getline(pinfile, name, ',');
        Pa[pageCount].setName(name);

        pinfile >> MaxPosts;
        Pa[pageCount].setMaxPosts(MaxPosts);

        pinfile >> followersNo;
        Pa[pageCount].setFollowersNo(followersNo);

        for (int j = 0; j < followersNo; ++j)
        {
            int val;
            pinfile >> val;
            Followers.push_back(val);
        }
        Pa[pageCount].setFollowers(Followers);

        pageCount++;
    }
    pinfile.close();

    // Load Posts
    ifstream Postfile("Posts.txt");
    if (!Postfile)
    {
        cout << "Unable to open Posts.txt for reading.\n";
        return;
    }
    P = new Post[pid];
    int postCount = 0;
    while (!Postfile.eof() && postCount < pid)
    {
        int PostId, accId, MaxComments, Likes;
        bool user;
        string Description;
        time_t uploadTime;
        int *Likedby = nullptr;

        Postfile >> PostId >> accId >> user;
        getline(Postfile, Description, ',');
        Postfile >> MaxComments >> Likes;

        if (Likes > 0)
        {
            Likedby = new int[Likes];
            for (int j = 0; j < Likes; ++j)
                Postfile >> Likedby[j];
        }
        Postfile >> uploadTime;

        P[postCount].setPostId(PostId);
        P[postCount].setAccId(accId);
        P[postCount].setUser(user);
        P[postCount].setDescription(Description);
        P[postCount].setMaxComments(MaxComments);
        P[postCount].setLikes(Likes);
        if (Likes > 0)
            P[postCount].setLikedby(Likedby, Likes);
        P[postCount].setUploadTime(uploadTime);

        if (user)
        {
            P[postCount].setName(U[accId - 1].getName());
        }
        else
        {
            P[postCount].setName(Pa[accId - 1].getName());
        }
        delete[] Likedby;
        postCount++;
    }
    Postfile.close();

    // Load Comments
    ifstream Comfile("Comments.txt");
    if (!Comfile)
    {
        cout << "Unable to open Comments.txt for reading.\n";
        return;
    }
    C = new Comment[cno];
    int CCount = 0;
    while (!Comfile.eof() && CCount < cno)
    {
        int CommentId, WriterId, PostNo;
        string Text;

        Comfile >> CommentId >> WriterId >> PostNo;
        getline(Comfile, Text, ',');

        C[CCount].setCommentId(CommentId);
        C[CCount].setWriterId(WriterId);
        C[CCount].setPostNo(PostNo);
        C[CCount].setText(Text);

        CCount++;
    }
    Comfile.close();
}