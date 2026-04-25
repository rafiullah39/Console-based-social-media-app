#ifndef COMMENT_H
#define COMMENT_H

#include <string>
using namespace std;

class Comment
{
private:
    int CommentId;
    int WriterId;
    int PostNo;
    string Text;

public:
    Comment();
    Comment(int commentId, int writerId, int postNo, const string &text);

    void postComment(int cno, int id, int post);
    void showComment(string Name);
    void deleteComment(Comment C[], int no, int pno, int pid, int cno);

    int getCommentId() const;
    int getWriterId() const;
    int getPostNo() const;
    string getText() const;

    void setCommentId(int id);
    void setWriterId(int id);
    void setPostNo(int no);
    void setText(const string &text);

    friend void updateComments(Comment C[], int cno);
};

#endif
