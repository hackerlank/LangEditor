#include "wxCommon.h"
#include "ShowLang.h"
class EditFrame;
// define a scrollable canvas for drawing onto
class EditCanvas: public wxScrolledWindow
{
public:
    EditCanvas( EditFrame *parent );

    void OnPaint(wxPaintEvent &event);

    void ToShow() {  Refresh(); }

    // set or remove the clipping region
    void Clip(bool clip) { m_clip = clip; Refresh(); }
#if wxUSE_GRAPHICS_CONTEXT
    void UseGraphicContext(bool use) { m_useContext = use; Refresh(); }
#endif
    void UseBuffer(bool use) { m_useBuffer = use; Refresh(); }

    void Draw(wxDC& dc);
	
	void DrawText(wxDC& dc);
	ShowLang lang;

	void OnMouseMove(wxMouseEvent &event);
    void OnMouseDown(wxMouseEvent &event);
    void OnMouseUp(wxMouseEvent &event);
protected:
    enum DrawMode
    {
        Draw_Normal,
        Draw_Stretch
    };

	
private:

	EditFrame *m_owner;

    bool         m_clip;

#if wxUSE_GRAPHICS_CONTEXT
    bool         m_useContext ;
#endif
    bool         m_useBuffer;
	bool		 m_rubberBand;
    DECLARE_EVENT_TABLE()
};