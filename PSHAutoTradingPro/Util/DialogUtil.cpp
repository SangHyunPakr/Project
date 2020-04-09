#include "stdafx.h"
#include "DialogUtil.h"

ClickStep::ClickStep() : count_( 0 )
{
	ZeroMemory( step_ , sizeof( step_ ) );
}

ClickStep::ClickStep( int Step1 ) : count_( 1 )
{
	ZeroMemory( step_ , sizeof( step_ ) );
	step_[0] = Step1;
}

ClickStep::ClickStep( int Step1 , int Step2 ) : count_( 2 )
{
	ZeroMemory( step_ , sizeof( step_ ) );
	step_[0] = Step1;
	step_[1] = Step2;
}

ClickStep::ClickStep( int Step1 , int Step2 , int Step3 ) : count_( 3 )
{
	ZeroMemory( step_ , sizeof( step_ ) );
	step_[0] = Step1;
	step_[1] = Step2;
	step_[2] = Step3;
}

ClickStep::ClickStep( int Step1 , int Step2 , int Step3 , int Step4 ) : count_( 4 )
{
	ZeroMemory( step_ , sizeof( step_ ) );
	step_[0] = Step1;
	step_[1] = Step2;
	step_[2] = Step3;
	step_[3] = Step4;
}

BOOL ClickStep::operator==( const ClickStep& rhs ) const
{
	if ( count_ != rhs.count_ ) return FALSE;

	for ( int i = 0 ; i < count_ ; ++i )
	{
		if ( step_[i] != rhs.step_[i] ) return FALSE;
	}

	return TRUE;
}

namespace DialogUtil
{
	struct DialogEntry
	{
		DialogEntry( int template_id = 0 , CDialog* instance = NULL , const ClickStep& step = ClickStep() ) 
			: template_id_( template_id ) , instance_(instance) , step_(step)  {}

		int			template_id_;
		CDialog*	instance_;
		ClickStep	step_;
	};

	static SyncMap< int , DialogEntry* > dialog_map_;
	static int last_showing_dialog_ = 0;

	static int last_bottom_btn_id_ = 0;
	static int last_right_btn_id_ = 0;

	//---------------------------------------------------------------------------------
	// Util
	static int GetDialogID( CDialog* p )
	{
		dialog_map_.Enter();

		int ID = 0;
		std::find_if( dialog_map_.begin() , dialog_map_.end() , [&]( auto& rhs )
		{
			if ( rhs.second->instance_ == p ) 
			{
				ID = rhs.second->template_id_;
				return TRUE;
			}

			return FALSE;
		});

		dialog_map_.Leave();

		return ID;
	}
	//---------------------------------------------------------------------------------

	void CreateDialogInstance( int TemplateID , CRect Rect , CWnd* Parent , CDialog* Son , const ClickStep& step )
	{
		Son->Create( TemplateID , Parent );
		Son->SetWindowPos( NULL , Rect.left , Rect.top , Rect.right , Rect.bottom , SWP_HIDEWINDOW | SWP_NOZORDER );
		Son->ShowWindow( SW_HIDE );

		dialog_map_.Set( TemplateID , new DialogEntry( TemplateID , Son , step ) );
	}

	void CreateDialogInstance( int TemplateID , DialogPos Pos , CWnd* Parent , CDialog* Son , const ClickStep& step )
	{
		static int width  = ::GetSystemMetrics(SM_CXSCREEN);
		static int height = ::GetSystemMetrics(SM_CYSCREEN);

		switch( Pos )
		{
		case DialogPos::ePOS_DIALOG_TITLE:
			CreateDialogInstance( TemplateID , CRect( 0 , 0 , width , TITLE_WIDTH ) , Parent , Son , step );
			break;

		case DialogPos::ePOS_DIALOG_RIGHT:
			CreateDialogInstance( TemplateID , CRect( width - RIGHT_WIDTH , TITLE_HEIGHT , RIGHT_WIDTH , height - TITLE_HEIGHT - TITLE_HEIGHT ) , Parent , Son , step );
			break;

		case DialogPos::ePOS_DIALOG_CENTER:
			CreateDialogInstance( TemplateID , CRect( 0 , TITLE_HEIGHT , width - RIGHT_WIDTH , height - TITLE_HEIGHT - TITLE_HEIGHT ) , Parent , Son , step );
			break;

		case DialogPos::ePOS_DIALOG_BOTTOM:
			CreateDialogInstance( TemplateID , CRect( 0 , height - TITLE_HEIGHT , width , TITLE_WIDTH ) , Parent , Son , step );
			break;
		}	
	}

	void ReleaseDialogInstance()
	{
		ReleaseContainer( dialog_map_ , []( std::pair< const int , DialogEntry* >& dialog_entry ) 
											{ 
												dialog_entry.second->instance_->DestroyWindow();
												delete dialog_entry.second->instance_;
												delete dialog_entry.second;
											} );
	}

	CDialog* GetDialog( int TemplateID )
	{
		if ( !TemplateID || !dialog_map_.Has(TemplateID) ) return NULL;

		return dialog_map_.Get( TemplateID )->instance_;
	}

	CDialog* GetDialog( const ClickStep& step )
	{
		dialog_map_.Enter();

		CDialog* ret = NULL;
		std::find_if( dialog_map_.begin() , dialog_map_.end() , [&]( auto& rhs )
		{
			if ( rhs.second->step_ == step ) 
			{
				ret = rhs.second->instance_;
				return TRUE;
			}

			return FALSE;
		});

		dialog_map_.Leave();

		return ret;
	}

	void ShowDialog( int ShowDialogID , int HideDialogID )
	{
		if ( HideDialogID )
			dialog_map_.Get( HideDialogID )->instance_->ShowWindow( SW_HIDE );

		if ( ShowDialogID )
		{
			dialog_map_.Get( ShowDialogID )->instance_->ShowWindow( SW_SHOW );
			last_showing_dialog_ = ShowDialogID;
		}
	}

	void ShowDialog( int ShowDialogID )
	{
		ShowDialog( ShowDialogID , last_showing_dialog_ );
	}

	void ShowDialog( const ClickStep& step )
	{
		CDialog* p = GetDialog( step );
		if ( !p ) return;

		ShowDialog( GetDialogID( p ) , last_showing_dialog_ );
	}

	int GetLastDialogID()
	{
		return last_showing_dialog_;
	}

	void SetLastBottomBtnID( int ID )
	{ 
		last_bottom_btn_id_ = ID; 
		last_right_btn_id_ = 0;
	}

	void SetLastRightBtnID( int ID ) { last_right_btn_id_ = ID; }

	int GetLastBottomBtnID() { return last_bottom_btn_id_; }
	int GetLastRightBtnID()  { return last_right_btn_id_; }


};