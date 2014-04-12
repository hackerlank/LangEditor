#include "Canvas.h"
#include "Frames.h"
#include "EditLNode.h"
BEGIN_EVENT_TABLE(EditCanvas, wxScrolledWindow)
    EVT_PAINT  (EditCanvas::OnPaint)
	EVT_MOTION (EditCanvas::OnMouseMove)
    EVT_LEFT_DOWN (EditCanvas::OnMouseDown)
    EVT_LEFT_UP (EditCanvas::OnMouseUp)
END_EVENT_TABLE()

EditCanvas::EditCanvas(EditFrame *parent): wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                           wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
	m_owner = parent;
    m_clip = false;
#if wxUSE_GRAPHICS_CONTEXT
    m_useContext = false;
#endif
    m_useBuffer = false;
	SetScrollbars( 10, 10, 100, 240 );
}

void EditCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    if ( m_useBuffer )
    {
        wxBufferedPaintDC bpdc(this);
        Draw(bpdc);
    }
    else
    {
        wxPaintDC pdc(this);
        Draw(pdc);
    }
}

void EditCanvas::Draw(wxDC& pdc)
{
#if wxUSE_GRAPHICS_CONTEXT
    wxGCDC gdc;
    wxGraphicsRenderer* const renderer = wxGraphicsRenderer::
#if TEST_CAIRO_EVERYWHERE
        GetCairoRenderer()
#else
        GetDefaultRenderer()
#endif
        ;

    wxGraphicsContext* context;
    if ( wxPaintDC *paintdc = wxDynamicCast(&pdc, wxPaintDC) )
    {
        context = renderer->CreateContext(*paintdc);
    }
    else if ( wxMemoryDC *memdc = wxDynamicCast(&pdc, wxMemoryDC) )
    {
        context = renderer->CreateContext(*memdc);
    }
#if wxUSE_METAFILE && defined(wxMETAFILE_IS_ENH)
    else if ( wxMetafileDC *metadc = wxDynamicCast(&pdc, wxMetafileDC) )
    {
        context = renderer->CreateContext(*metadc);
    }
#endif
    else
    {
        wxFAIL_MSG( "Unknown wxDC kind" );
        return;
    }

    gdc.SetGraphicsContext(context);

    wxDC &dc = m_useContext ? (wxDC&) gdc : (wxDC&) pdc ;
#else
    wxDC &dc = pdc ;
#endif

    PrepareDC(dc);

    m_owner->PrepareDC(dc);

    if ( m_clip )
        dc.SetClippingRegion(100, 100, 100, 100);

    dc.Clear();

    DrawText(dc);
}


void EditCanvas::DrawText(wxDC& dc)
{
	lang.dc = &dc;
	lang.show();
}


void EditCanvas::OnMouseMove(wxMouseEvent &event)
{
	 wxClientDC dc( this );
        PrepareDC( dc );

        wxPoint pos = event.GetPosition();
        long x = dc.DeviceToLogicalX( pos.x );
        long y = dc.DeviceToLogicalY( pos.y );
        wxString str;
        str.Printf( wxT("Current mouse position: %d,%d"), (int)x, (int)y );
    
}

void EditCanvas::OnMouseDown(wxMouseEvent &event)
{
    int x,y,xx,yy ;
    event.GetPosition(&x,&y);
    CalcUnscrolledPosition( x, y, &xx, &yy );
	wxClientDC dc( this );
    PrepareDC( dc );
	lang.dc = &dc;
	CodeNode *node = lang.pick(xx,yy);
	if (node)
	{
		wxString msg;
		msg.Printf("%s %s",node->nodeName.c_str(),node->getDescInfo().c_str());

		//wxMessageBox(msg, wxT("Propies"), wxOK | wxICON_INFORMATION, this);
	
		(new MyEditLangDialog(this,node))->ShowModal();
		Refresh();
	}
}

void EditCanvas::OnMouseUp(wxMouseEvent &event)
{
       wxPoint endpoint = CalcUnscrolledPosition(event.GetPosition());

}
