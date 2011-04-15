#ifndef CWINDOWCHILD_H
#define CWINDOWCHILD_H

namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{

class CWindow;

class CWindowChild
{
    friend class CWindow;
public: // ####################################################
    CWindowChild(CWindow *win = 0);
    virtual ~CWindowChild();

private: // ####################################################
    CWindow *m_window;

protected: // ####################################################
    CWindow *gWindow() { return m_window; }
    void setGWindow(CWindow *win) { m_window = win; }
};

}
}
}
}
#endif // CWINDOWCHILD_H
