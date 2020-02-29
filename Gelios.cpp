//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("UnitForm\ufmStartDecision.cpp", fmStartDecision);
USEFORM("UnitForm\ufmTrackShow.cpp", fmTrackShow);
USEFORM("UnitForm\ufmViewDecision.cpp", fmViewDecision);
USEFORM("UnitForm\ufmViewPredicateTrackConstructor.cpp", fmViewPredicateTrackConstructor);
USEFORM("UnitForm\ufmPredicatePathView.cpp", fmPredicatePathView);
USEFORM("UnitForm\ufmParamAlternativeLoader.cpp", fmParamAlternativeLoader);
USEFORM("UnitForm\ufmPredicateFull.cpp", fmPredicateFull);
USEFORM("UnitForm\ufmPredicatePathConstructor.cpp", fmPredicatePathConstructor);
USEFORM("UnitForm\ufmPredicatePathConstructorOgr.cpp", fmPredicatePathConstructorOgr);
USEFORM("UnitForm\uFrmHelp.cpp", frmHelp);
USEFORM("UnitForm\ufrmPredicateView.cpp", frmPredicateView);
USEFORM("UnitForm\ufSetup.cpp", FmSetup);
USEFORM("UnitForm\uMetodOpt.cpp", FmMetodOpt);
USEFORM("UnitForm\ufrmDialogExit.cpp", frmDialogExit);
USEFORM("UnitForm\ufmViewPredicateTrackConstructorAuto.cpp", fmViewPredicateTrackConstructorAuto);
USEFORM("UnitForm\ufmViewResult.cpp", fmViewResult);
USEFORM("UnitForm\ufrmAlternateView.cpp", frmAlternateView);
USEFORM("UnitForm\ufrmAlternateViewSelect.cpp", frmAlternateViewSelect);
USEFORM("UnitForm\uFmParamAlternative.cpp", fmParamAlternative);
USEFORM("UnitForm\ufAbount.cpp", fAbount);
USEFORM("UnitForm\uFmGridSovm.cpp", FmGridSovm);
USEFORM("UnitForm\ufmOzenkView.cpp", fmOzenkView);
USEFORM("TFSTools\ufToolMain.cpp", fmToolMain);
USEFORM("ImportModule\opim_f.cpp", opt_sadacha);
USEFORM("ImportModule\REDACT_F.cpp", redact_char);
USEFORM("uMainFrm.cpp", frmMain);
USEFORM("GSTools\ufGenerStruct.cpp", Form1);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->CreateForm(__classid(Topt_sadacha), &opt_sadacha);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
