
// OPENGL_MFCView.h: COPENGLMFCView 类的接口
//

#pragma once





class COPENGLMFCView : public CView
{

	friend class CCreate;
private:
	HGLRC m_hRC;
	CClientDC* m_pDC;
protected: // 仅从序列化创建
	COPENGLMFCView();
	DECLARE_DYNCREATE(COPENGLMFCView)

// 特性
public:
	COPENGLMFCDoc* GetDocument() const;
	void COPENGLMFCView::myDisPlay(void);
	void COPENGLMFCView::review(void);


// 操作
public:
	BOOL COPENGLMFCView::PreTranslateMessage(MSG* pMsg);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~COPENGLMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	bool bSetDCPixelFormat();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnVideo();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void createcubee();
	void createsphere(float * it, bool sel);
	void COPENGLMFCView::createcube(float* it, bool sel);
	void COPENGLMFCView::createlight(float* it, bool sel);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnOrder();
	//afx_msg void OnUpdateOrder(CCmdUI *pCmdUI);
	//afx_msg void On32776();
	//afx_msg void OnVideo();
	afx_msg void OnVideoo();
};

#ifndef _DEBUG  // OPENGL_MFCView.cpp 中的调试版本
inline COPENGLMFCDoc* COPENGLMFCView::GetDocument() const
   { return reinterpret_cast<COPENGLMFCDoc*>(m_pDocument); }
#endif

