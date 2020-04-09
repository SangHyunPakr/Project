#pragma once

class ClickStep
{
public:

	explicit ClickStep();
	explicit ClickStep( int Step1 );
	explicit ClickStep( int Step1 , int Step2 );
	explicit ClickStep( int Step1 , int Step2 , int Step3 );
	explicit ClickStep( int Step1 , int Step2 , int Step3 , int Step4 );

	BOOL operator==( const ClickStep& rhs ) const;
		
private:

	enum { MAX = 5 };
	int step_[MAX];
	int count_;
};

namespace DialogUtil
{
	enum DialogPos
	{
		ePOS_DIALOG_TITLE,
		ePOS_DIALOG_RIGHT,
		ePOS_DIALOG_CENTER,
		ePOS_DIALOG_BOTTOM,
	};

	void CreateDialogInstance( int TemplateID , CRect Rect    , CWnd* Parent , CDialog* Son , const ClickStep& step = ClickStep() );
	void CreateDialogInstance( int TemplateID , DialogPos Pos , CWnd* Parent , CDialog* Son , const ClickStep& step = ClickStep() );
	void ReleaseDialogInstance();
	
	CDialog* GetDialog( int TemplateID );

	void ShowDialog( const ClickStep& step ); 
	void ShowDialog( int ShowDialogID , int HideDialogID );
	void ShowDialog( int ShowDialogID );


	int GetLastDialogID();

	void SetLastBottomBtnID( int ID );
	void SetLastRightBtnID( int ID );

	int GetLastBottomBtnID();
	int GetLastRightBtnID();
};