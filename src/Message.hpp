#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

class Message
{
public:
    Message();
    Message(std::string contents);

    ~Message();

    show();

private:
    std::string contents;
}

#endif
