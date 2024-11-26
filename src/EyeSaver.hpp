
#ifndef __EYE_SAVER_HPP__
#define __EYE_SAVER_HPP__

class EyeSaver
{
public:
    EyeSaver();
    ~EyeSaver();

private:
    std::vector<Display> displays;
    std::vector<Window> windows;

    startBreak();

    getDisplays();
    readConfig();
};

#endif
