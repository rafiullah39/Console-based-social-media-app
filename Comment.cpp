#include "Comment.h"
#include <iostream>
#include <fstream>

using namespace std;

// ========== Member Functions ==========

Comment::Comment()
{
}

Comment::Comment(int commentId, int writerId, int postNo, const string &text)
{
    this->CommentId = commentId;
    this->WriterId = writerId;
    this->PostNo = postNo;
    this->Text = text;
}

void Comment::postComment(int cno, int id, int post)
{
    PostNo = post;

    cout << "Enter the comment: ";
    getline(cin >> ws, Text);

    CommentId = cno;
    WriterId = id;

    fstream cfile("Comments.txt", ios::app);
    if (!cfile)
    {
        cout << "Unable to open file for appending." << endl;
    }

    cfile << CommentId << " " << WriterId << " " << PostNo << " " << Text << "," << endl;
    cfile.close();

    cout << "Comment posted..." << endl;
}

void Comment::showComment(string Name)
{
    cout << "  -> " << Name << " wrote: " << Text << endl;
}

void Comment::deleteComment(Comment C[], int no, int pno, int pid, int cno)
{
    if (CommentId > 0 && CommentId <= cno)
    {
        for (int i = CommentId - 1; i < cno - 1; i++)
        {
            C[i] = C[i + 1];
        }
        cno--;
        updateComments(C, cno);
        // `updateNumbers()` should be defined in another module
        cout << "Comment Deleted..." << endl;
    }
    else
    {
        cout << "Invalid Comment Id." << endl;
    }
}

// ========== Getters ==========

int Comment::getCommentId() const
{
    return CommentId;
}

int Comment::getWriterId() const
{
    return WriterId;
}

int Comment::getPostNo() const
{
    return PostNo;
}

string Comment::getText() const
{
    return Text;
}

// ========== Setters ==========

void Comment::setCommentId(int id)
{
    CommentId = id;
}

void Comment::setWriterId(int id)
{
    WriterId = id;
}

void Comment::setPostNo(int no)
{
    PostNo = no;
}

void Comment::setText(const string &text)
{
    Text = text;
}

// ========== Friend Function ==========

void updateComments(Comment C[], int cno)
{
    ofstream Comfile("Comments.txt");
    if (!Comfile)
    {
        cout << "Unable to open file for writing." << endl;
    }

    for (int i = 0; i < cno; i++)
    {
        Comfile << C[i].getCommentId() << " "
                << C[i].getWriterId() << " "
                << C[i].getPostNo() << " "
                << C[i].getText() << "," << endl;
    }

    Comfile.close();
}
