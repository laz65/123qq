unit ItfProc;

interface

uses
	Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
	StdCtrls, ComCtrls, ExtCtrls, Mask, HcTLB_TLB;

type
	TItfProc = procedure of object;

type
	TProcItfForm = class(TForm)
		Panel1: TPanel;
		Panel2: TPanel;
		PageCtrl: TPageControl;
		m1: TMemo;
		Panel3: TPanel;
		btnCancel: TButton;
		pgIHcFReg: TTabSheet;
		pgIHcClrAllPLU: TTabSheet;
		pgIHcProgTransaction: TTabSheet;
		pgIHcSqueeze: TTabSheet;
		pgIHcSound: TTabSheet;
		pgIHcDisplay: TTabSheet;
		pgIHcPeripherals: TTabSheet;
		pgIHcGetDriverInfo: TTabSheet;
		pgIHcPayOff: TTabSheet;
		pgIHcComment: TTabSheet;
		pgIHcForm: TTabSheet;
		pgIHcReport: TTabSheet;
		pgIHcRestart: TTabSheet;
		pgIHcExtTables: TTabSheet;
		pcIHcSound: TPageControl;
		pcgOutTone: TTabSheet;
		meOutToneLen: TMaskEdit;
		meOutToneTone: TMaskEdit;
		Label1: TLabel;
		Label2: TLabel;
		btnExecute: TButton;
		pcIHcFReg: TPageControl;
		pcgSmenBegin: TTabSheet;
		pcgBegChk: TTabSheet;
		pcgEndChk: TTabSheet;
		pcgVoidChk: TTabSheet;
		pcgCopyChk: TTabSheet;
		pcgVoidLast: TTabSheet;
		pcgTextComment: TTabSheet;
		pcgBinComment: TTabSheet;
		pcgProd: TTabSheet;
		pcgVoidProd: TTabSheet;
		pcgOplata: TTabSheet;
		pcgInOut: TTabSheet;
		pcgNacSkd: TTabSheet;
		Label3: TLabel;
		Label4: TLabel;
		Label5: TLabel;
		Label6: TLabel;
		Label7: TLabel;
		Label8: TLabel;
		meTextCommentComment: TMaskEdit;
		Label9: TLabel;
		meBinCommentID: TMaskEdit;
		meBinCommentBComment: TMaskEdit;
		Label10: TLabel;
		Label11: TLabel;
		Label12: TLabel;
		Label13: TLabel;
		Label14: TLabel;
		Label15: TLabel;
		Label16: TLabel;
		meProdID: TMaskEdit;
		meProdCena: TMaskEdit;
		meProdKol: TMaskEdit;
		meProdDep: TMaskEdit;
		meProdGrp: TMaskEdit;
		meVoidProdID: TMaskEdit;
		Label17: TLabel;
		meOplataID: TMaskEdit;
		meOplataSum: TMaskEdit;
		meOplataCode: TMaskEdit;
		Label18: TLabel;
		Label19: TLabel;
		Label20: TLabel;
		Label21: TLabel;
		meInOutID: TMaskEdit;
		Label22: TLabel;
		meInOutSum: TMaskEdit;
		Label23: TLabel;
		meNacSkdID: TMaskEdit;
		Label24: TLabel;
		meNacSkdSum: TMaskEdit;
		Label25: TLabel;
		meNacSkdPrc: TMaskEdit;
		pcIHcClrAllPLU: TPageControl;
		pcgClrAllPLU: TTabSheet;
		Label26: TLabel;
		pcIHcProgTransaction: TPageControl;
		pcgProgEnter: TTabSheet;
		pcgProgClose: TTabSheet;
		Label27: TLabel;
		Label28: TLabel;
		pcIHcSqueeze: TPageControl;
		pcgSqueeze: TTabSheet;
		Label29: TLabel;
		pcIHcDisplay: TPageControl;
		pcgOutScr: TTabSheet;
		meOutScrRow: TMaskEdit;
		meOutScrScr2: TMaskEdit;
		Label30: TLabel;
		Label31: TLabel;
		pcIHcPeripherals: TPageControl;
		pcgPutInfo: TTabSheet;
		mePutInfoID: TMaskEdit;
		mePutInfoInfo: TMaskEdit;
		Label32: TLabel;
		Label33: TLabel;
		Label34: TLabel;
		Label35: TLabel;
		Label36: TLabel;
		Label37: TLabel;
		Label38: TLabel;
		Label39: TLabel;
		lGDIName: TLabel;
		lGDITextCommentHeight: TLabel;
		lGDITextCommentWidth: TLabel;
		lGDIPLUCodeWidth: TLabel;
		lGDIPLUNameWidth: TLabel;
		lGDIMaxPLUCount: TLabel;
		pcIHcPayOff: TPageControl;
		pcgPayOff: TTabSheet;
		mePayOffID: TMaskEdit;
		Label40: TLabel;
		mePayOffSum: TMaskEdit;
		Label41: TLabel;
		pcIHcComment: TPageControl;
		pcgOpenComment: TTabSheet;
		Label42: TLabel;
		pcgCloseComment: TTabSheet;
		Label43: TLabel;
		pcgPrintComment: TTabSheet;
		mePrintCommentComment: TMaskEdit;
		Label44: TLabel;
		pcIHcForm: TPageControl;
		pcgOpenForm: TTabSheet;
		pcgCancelForm: TTabSheet;
		pcgCloseForm: TTabSheet;
		pcgPrintOnForm: TTabSheet;
		Label45: TLabel;
		Label46: TLabel;
		Label47: TLabel;
		mePrintOnFormComment: TMaskEdit;
		Label48: TLabel;
		pcIHcReport: TPageControl;
		pcgPrintReport: TTabSheet;
		mePrintReportNumReport: TMaskEdit;
		Label49: TLabel;
		pcIHcRestart: TPageControl;
		pcgRestart: TTabSheet;
		Label50: TLabel;
		pcIHcExtTables: TPageControl;
		pcgClearExtTables: TTabSheet;
		pcgBackupExtTables: TTabSheet;
		pcgRecalcCRC: TTabSheet;
		pcgRestoreExtTables: TTabSheet;
		pcgVerifyExtTables: TTabSheet;
		pcgWriteTable: TTabSheet;
		Label51: TLabel;
		Label52: TLabel;
		Label53: TLabel;
		Label54: TLabel;
		Label55: TLabel;
		meWriteTableTable: TMaskEdit;
		meWriteTablePos: TMaskEdit;
		meWriteTableInfo: TMaskEdit;
		Label56: TLabel;
		Label57: TLabel;
		Label58: TLabel;
    pgIHcPLUFlags: TTabSheet;
    Label63: TLabel;
    Label64: TLabel;
    Label65: TLabel;
    Label66: TLabel;
    Label67: TLabel;
    Label68: TLabel;
    lPLUFlagsOnForm: TLabel;
    lPLUFlagsSingleton: TLabel;
    lPLUFlagsQuota: TLabel;
    lPLUFlagsRestrictedAmount: TLabel;
    lPLUFlagsFractional: TLabel;
    lPLUFlagsMutablePrice: TLabel;
    pgIHcReadCOM: TTabSheet;
    pcIHcReadCOM: TPageControl;
    pgIHcFRegFull: TTabSheet;
    pcIHcFRegFull: TPageControl;
    pcgFullProd: TTabSheet;
    Label69: TLabel;
    Label70: TLabel;
    Label71: TLabel;
    Label72: TLabel;
    Label73: TLabel;
    meFullProdCode: TMaskEdit;
    meFullProdPrice: TMaskEdit;
    meFullProdQty: TMaskEdit;
    meFullProdDep: TMaskEdit;
    meFullProdGrp: TMaskEdit;
    meFullProdTax: TMaskEdit;
    meFullProdName: TMaskEdit;
    Label74: TLabel;
    Label75: TLabel;
    pcgReadCOM: TTabSheet;
    Label76: TLabel;
    Label77: TLabel;
    lReadCOMLine: TLabel;
    lReadCOMID: TLabel;
    Label59: TLabel;
    meReadCOMKind: TMaskEdit;
    pgIHcFRegEx: TTabSheet;
    pcIHcFRegEx: TPageControl;
    pcg2FullProd: TTabSheet;
    pcgFullNac: TTabSheet;
    pcgSubtotal: TTabSheet;
    Label81: TLabel;
    Label82: TLabel;
    Label83: TLabel;
    meFullNacID: TMaskEdit;
    meFullNacSum: TMaskEdit;
    meFullNacPrc: TMaskEdit;
    Label60: TLabel;
    Label61: TLabel;
    Label62: TLabel;
    Label78: TLabel;
    Label79: TLabel;
    Label80: TLabel;
    Label84: TLabel;
    me2FullProdCode: TMaskEdit;
    me2FullProdPrice: TMaskEdit;
    me2FullProdQty: TMaskEdit;
    me2FullProdDep: TMaskEdit;
    me2FullProdGrp: TMaskEdit;
    me2FullProdTax: TMaskEdit;
    me2FullProdName: TMaskEdit;
    meFullNacRec: TMaskEdit;
    meFullNacTax: TMaskEdit;
    Label85: TLabel;
    Label86: TLabel;
    Label87: TLabel;
    lSubtotalSum: TLabel;
		procedure pcgOutToneShow(Sender: TObject);
		procedure pgIHcSoundShow(Sender: TObject);
		procedure btnExecuteClick(Sender: TObject);
		procedure pcgSmenBeginShow(Sender: TObject);
		procedure pgIHcFRegShow(Sender: TObject);
		procedure pcgBegChkShow(Sender: TObject);
		procedure pcgEndChkShow(Sender: TObject);
		procedure pcgVoidChkShow(Sender: TObject);
		procedure pcgCopyChkShow(Sender: TObject);
		procedure pcgVoidLastShow(Sender: TObject);
		procedure pcgTextCommentShow(Sender: TObject);
		procedure pcgBinCommentShow(Sender: TObject);
		procedure pcgProdShow(Sender: TObject);
		procedure pcgVoidProdShow(Sender: TObject);
		procedure pcgOplataShow(Sender: TObject);
		procedure pcgInOutShow(Sender: TObject);
		procedure pcgNacSkdShow(Sender: TObject);
    procedure pcgClrAllPLUShow(Sender: TObject);
    procedure pcgProgEnterShow(Sender: TObject);
    procedure pcgProgCloseShow(Sender: TObject);
    procedure pgIHcGetDriverInfoShow(Sender: TObject);
    procedure pgIHcPayOffShow(Sender: TObject);
    procedure pgIHcPeripheralsShow(Sender: TObject);
    procedure pgIHcProgTransactionShow(Sender: TObject);
    procedure pgIHcReportShow(Sender: TObject);
    procedure pgIHcRestartShow(Sender: TObject);
    procedure pgIHcSqueezeShow(Sender: TObject);
    procedure pgIHcFormShow(Sender: TObject);
    procedure pgIHcExtTablesShow(Sender: TObject);
    procedure pgIHcDisplayShow(Sender: TObject);
    procedure pgIHcCommentShow(Sender: TObject);
    procedure pgIHcClrAllPLUShow(Sender: TObject);
    procedure pcgOutScrShow(Sender: TObject);
    procedure pgIHcPLUFlagsShow(Sender: TObject);
    procedure pgIHcReadCOMShow(Sender: TObject);
    procedure pgIHcFRegFullShow(Sender: TObject);
    procedure pcgWriteTableShow(Sender: TObject);
    procedure pcgVerifyExtTablesShow(Sender: TObject);
    procedure pcgSqueezeShow(Sender: TObject);
    procedure pcgRestoreExtTablesShow(Sender: TObject);
    procedure pcgRestartShow(Sender: TObject);
    procedure pcgRecalcCRCShow(Sender: TObject);
    procedure pcgReadCOMShow(Sender: TObject);
    procedure pcgPutInfoShow(Sender: TObject);
    procedure pcgPrintReportShow(Sender: TObject);
    procedure pcgPrintOnFormShow(Sender: TObject);
    procedure pcgPrintCommentShow(Sender: TObject);
    procedure pcgPayOffShow(Sender: TObject);
    procedure pcgOpenFormShow(Sender: TObject);
    procedure pcgOpenCommentShow(Sender: TObject);
    procedure pcgFullProdShow(Sender: TObject);
    procedure pcgCloseFormShow(Sender: TObject);
    procedure pcgCloseCommentShow(Sender: TObject);
    procedure pcgClearExtTablesShow(Sender: TObject);
    procedure pcgCancelFormShow(Sender: TObject);
    procedure pcgBackupExtTablesShow(Sender: TObject);
    procedure pgIHcFRegExShow(Sender: TObject);
    procedure pcg2FullProdShow(Sender: TObject);
    procedure pcgFullNacShow(Sender: TObject);
    procedure pcgSubtotalShow(Sender: TObject);
	private
		{ Private declarations }
		HcFReg:IHcFReg;
		HcClrAllPLU: IHcClrAllPLU;
		HcProgTransaction: IHcProgTransaction;
		HcSqueeze: IHcSqueeze;
		HcSound:IHcSound;
		HcDisplay: IHcDisplay;
		HcPeripherals: IHcPeripherals;
		HcGetDriverInfo:IHcGetDriverInfo;
		HcPayOff: IHcPayOff;
		HcComment: IHcComment;
		HcForm: IHcForm;
		HcReport: IHcReport;
		HcRestart: IHcRestart;
		HcExtTables: IHcExtTables;
		HcPLUFlags: IHcPLUFlags;
		HcReadCOM: IHcReadCOM;
		HcFRegFull: IHcFRegFull;
		HcFRegEx: IHcFRegEx;
		tipIHc:TItfProc;//main
		tipIHcFReg,tipIHcClrAllPLU,tipIHcProgTransaction,tipIHcSqueeze,
		tipIHcSound,tipIHcDisplay,tipIHcPeripherals,
		tipIHcPayOff,tipIHcComment,tipIHcForm,tipIHcReport,tipIHcRestart,
		tipIHcExtTables,tipIHcFRegFull,tipIHcReadCOM,tipIHcFRegEx:TItfProc;
		//IHcFReg
		procedure mainIHcFReg;
		procedure tipIHcFRegSmenBegin;
		procedure tipIHcFRegBegChk;
		procedure tipIHcFRegEndChk;
		procedure tipIHcFRegVoidChk;
		procedure tipIHcFRegBinComment;
		procedure tipIHcFRegCopyChk;
		procedure tipIHcFRegInOut;
		procedure tipIHcFRegOplata;
		procedure tipIHcFRegProd;
		procedure tipIHcFRegTextComment;
		procedure tipIHcFRegVoidLast;
		procedure tipIHcFRegVoidProd;
		procedure tipIHcFRegNacSkd;
		//tipIHcClrAllPLU
		procedure mainIHcClrAllPLU;
		procedure tipIHcClrAllPLUClrAllPLU;
		//tipIHcProgTransaction
		procedure mainIHcProgTransaction;
		procedure tipIHcProgTransactionProgEnter;
		procedure tipIHcProgTransactionProgClose;
		//tipIHcSqueeze
		procedure mainIHcSqueeze;
		procedure tipIHcSqueezeSqueeze;
		//IHcSound
		procedure mainIHcSound;
		procedure tipIHcSoundOutTone;
		//tipIHcDisplay
		procedure mainIHcDisplay;
		procedure tipIHcDisplayOutScr;
		//tipIHcPeripherals
		procedure mainIHcPeripherals;
		procedure tipIHcPeripheralsPutInfo;
		//tipIHcGetDriverInfo
		//tipIHcPayOff
		procedure mainIHcPayOff;
		procedure tipIHcPayOffPayOff;
		//tipIHcComment
		procedure mainIHcComment;
		procedure tipIHcCommentOpenComment;
		procedure tipIHcCommentCloseComment;
		procedure tipIHcCommentPrintComment;
		//tipIHcForm
		procedure mainIHcForm;
		procedure tipIHcFormOpenForm;
		procedure tipIHcFormCancelForm;
		procedure tipIHcFormCloseForm;
		procedure tipIHcFormPrintOnForm;
		//tipIHcReport
		procedure mainIHcReport;
		procedure tipIHcReportPrintReport;
		//tipIHcRestart
		procedure mainIHcRestart;
		procedure tipIHcRestartRestart;
		//tipIHcExtTables
		procedure mainIHcExtTables;
		procedure tipIHcExtTablesClearExtTables;
		procedure tipIHcExtTablesBackupExtTables;
		procedure tipIHcExtTablesRecalcCRC;
		procedure tipIHcExtTablesRestoreExtTables;
		procedure tipIHcExtTablesVerifyExtTables;
		procedure tipIHcExtTablesWriteTable;
		//tipIHcPLUFlags
		//tipIHcReadCOM
		procedure mainIHcReadCOM;
		procedure tipIHcReadCOMReadCOM;
		//tipIHcFRegFull
		procedure mainIHcFRegFull;
		procedure tipIHcFRegFullFullProd;
		//tipIHcFRegEx
		procedure mainIHcFRegEx;
		procedure tipIHcFRegExFullProd;
		procedure tipIHcFRegExFullNac;
		procedure tipIHcFRegExSubtotal;
	public
		{ Public declarations }
		procitf: Variant;//IDispatch;
		procedure Init;
	end;

var
	ProcItfForm: TProcItfForm;

implementation

{$R *.DFM}

uses
	comobj,activex,variants;

procedure TProcItfForm.Init;
	procedure initTPC(tpc:TPageControl);
	begin
		with tpc do begin
			ActivePage:=Pages[0];
		end;
	end;
var
 i:integer;
begin
	tipIHc:=nil;
	if not Supports(procitf,IHcFReg,HcFReg) then
		pgIHcFReg.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcClrAllPLU,HcClrAllPLU) then
		pgIHcClrAllPLU.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcProgTransaction,HcProgTransaction) then
		pgIHcProgTransaction.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcSqueeze,HcSqueeze) then
		pgIHcSqueeze.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcSound,HcSound) then
		pgIHcSound.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcDisplay,HcDisplay) then
		pgIHcDisplay.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcPeripherals,HcPeripherals) then
		pgIHcPeripherals.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcGetDriverInfo,HcGetDriverInfo) then
		pgIHcGetDriverInfo.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcPayOff,HcPayOff) then
		pgIHcPayOff.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcComment,HcComment) then
		pgIHcComment.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcForm,HcForm) then
		pgIHcForm.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcReport,HcReport) then
		pgIHcReport.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcRestart,HcRestart) then
		pgIHcRestart.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcExtTables,HcExtTables) then
		pgIHcExtTables.TabVisible:=False;//PageControl:=nil;
	if not Supports(procitf,IHcPLUFlags,HcPLUFlags) then
		pgIHcPLUFlags.TabVisible:=False;
	if not Supports(procitf,IHcReadCOM,HcReadCOM) then
		pgIHcReadCOM.TabVisible:=False;
	if not Supports(procitf,IHcFRegEx,HcFRegEx) then begin
		pgIHcFRegEx.TabVisible:=False;
		if not Supports(procitf,IHcFRegFull,HcFRegFull) then
			pgIHcFRegFull.TabVisible:=False;
	end
	else
		pgIHcFRegFull.TabVisible:=False;
	for i:=0 to PageCtrl.PageCount-1 do begin
		if PageCtrl.Pages[i].TabVisible then begin
			PageCtrl.ActivePage:=PageCtrl.Pages[i];
			break;
		end;
	end;
	PageCtrl.SelectNextPage(true);
	PageCtrl.SelectNextPage(false);
	initTPC(pcIHcFReg);
	initTPC(pcIHcClrAllPLU);
	initTPC(pcIHcProgTransaction);
	initTPC(pcIHcSqueeze);
	initTPC(pcIHcSound);
	initTPC(pcIHcDisplay);
	initTPC(pcIHcPeripherals);
	//initTPC(pcIHcGetDriverInfo);
	initTPC(pcIHcPayOff);
	initTPC(pcIHcComment);
	initTPC(pcIHcForm);
	initTPC(pcIHcReport);
	initTPC(pcIHcRestart);
	initTPC(pcIHcExtTables);
	//initTPC(pcIHcPLUFlags);
	initTPC(pcIHcReadCOM);
	initTPC(pcIHcFRegFull);
	initTPC(pcIHcFRegEx);
end;

procedure TProcItfForm.mainIHcSound;
begin
	tipIHcSound;
end;

procedure TProcItfForm.pcgOutToneShow(Sender: TObject);
begin
	tipIHcSound:=tipIHcSoundOutTone;
	ActiveControl:=meOutToneLen;
end;

procedure TProcItfForm.pgIHcSoundShow(Sender: TObject);
begin
	tipIHc:=mainIHcSound;
end;

procedure TProcItfForm.tipIHcSoundOutTone;
begin
	m1.Lines.Add('OutTone('+meOutToneLen.Text+','+meOutToneTone.Text+')');
	HcSound.OutTone(meOutToneLen.Text,meOutToneTone.Text);
end;

procedure TProcItfForm.btnExecuteClick(Sender: TObject);
begin
	try
		tipIHc;
	except
	on E:EOleException do begin
		m1.lines.Add('Код ошибки: '+format('0x%08x',[E.ErrorCode]));
		m1.lines.Add('Сообщение: '+E.Message);
	end;
	end;
end;

procedure TProcItfForm.mainIHcFReg;
begin
	tipIHcFReg;
end;

procedure TProcItfForm.pgIHcFRegShow(Sender: TObject);
begin
	tipIHc:=mainIHcFReg;
end;

procedure TProcItfForm.pcgSmenBeginShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegSmenBegin;
end;

procedure TProcItfForm.tipIHcFRegSmenBegin;
begin
	m1.Lines.Add('SmenBegin()');
	HcFReg.SmenBegin;
end;

procedure TProcItfForm.pcgBegChkShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegBegChk;
end;

procedure TProcItfForm.tipIHcFRegBegChk;
begin
	m1.Lines.Add('BegChk()');
	HcFReg.BegChk;
end;

procedure TProcItfForm.pcgEndChkShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegEndChk;
end;

procedure TProcItfForm.tipIHcFRegEndChk;
begin
	m1.Lines.Add('EndChk()');
	HcFReg.EndChk;
end;

procedure TProcItfForm.pcgVoidChkShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegVoidChk;
end;

procedure TProcItfForm.tipIHcFRegVoidChk;
begin
	m1.Lines.Add('VoidChk()');
	HcFReg.VoidChk;
end;

procedure TProcItfForm.pcgCopyChkShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegCopyChk;
end;

procedure TProcItfForm.tipIHcFRegCopyChk;
begin
	m1.Lines.Add('CopyChk()');
	HcFReg.CopyChk;
end;

procedure TProcItfForm.pcgVoidLastShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegVoidLast;
end;

procedure TProcItfForm.tipIHcFRegVoidLast;
begin
	m1.Lines.Add('VoidLast()');
	HcFReg.VoidLast;
end;

procedure TProcItfForm.pcgTextCommentShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegTextComment;
	ActiveControl:=meTextCommentComment;
end;

procedure TProcItfForm.tipIHcFRegTextComment;
begin
	m1.Lines.Add('TextComment('+meTextCommentComment.Text+')');
	HcFReg.TextComment(meTextCommentComment.Text);
end;

procedure TProcItfForm.pcgBinCommentShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegBinComment;
	ActiveControl:=meBinCommentID;
end;

procedure TProcItfForm.tipIHcFRegBinComment;
begin
	m1.Lines.Add('BinComment('+meBinCommentID.Text+','+meBinCommentBComment.Text+')');
	HcFReg.BinComment(meBinCommentID.Text,meBinCommentBComment.Text);
end;

procedure TProcItfForm.pcgProdShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegProd;
	ActiveControl:=meProdID;
end;

procedure TProcItfForm.tipIHcFRegProd;
begin
	m1.Lines.Add('Prod('+meProdID.Text+','+meProdCena.Text+','+meProdKol.Text+','+meProdDep.Text+','+meProdGrp.Text+')');
	HcFReg.Prod(meProdID.Text,meProdCena.Text,meProdKol.Text,meProdDep.Text,meProdGrp.Text);
end;

procedure TProcItfForm.pcgVoidProdShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegVoidProd;
	ActiveControl:=meVoidProdID;
end;

procedure TProcItfForm.tipIHcFRegVoidProd;
begin
	m1.Lines.Add('VoidProd('+meVoidProdID.Text+')');
	HcFReg.VoidProd(meVoidProdID.Text);
end;

procedure TProcItfForm.pcgOplataShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegOplata;
	ActiveControl:=meOplataID;
end;

procedure TProcItfForm.tipIHcFRegOplata;
begin
	m1.Lines.Add('Oplata('+meOplataID.Text+','+meOplataSum.Text+','+meOplataCode.Text+')');
	HcFReg.Oplata(meOplataID.Text,meOplataSum.Text,meOplataCode.Text);
end;

procedure TProcItfForm.pcgInOutShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegInOut;
	ActiveControl:=meInOutID;
end;

procedure TProcItfForm.tipIHcFRegInOut;
begin
	m1.Lines.Add('InOut('+meInOutID.Text+','+meInOutSum.Text+')');
	HcFReg.InOut(meInOutID.Text,meInOutSum.Text);
end;

procedure TProcItfForm.pcgNacSkdShow(Sender: TObject);
begin
	tipIHcFReg:=tipIHcFRegNacSkd;
	ActiveControl:=meNacSkdID;
end;

procedure TProcItfForm.tipIHcFRegNacSkd;
begin
	m1.Lines.Add('NacSkd('+meNacSkdID.Text+','+meNacSkdSum.Text+','+meNacSkdPrc.Text+')');
	HcFReg.NacSkd(meNacSkdID.Text,meNacSkdSum.Text,meNacSkdPrc.Text);
end;

procedure TProcItfForm.mainIHcClrAllPLU;
begin
	tipIHcClrAllPLU;
end;

procedure TProcItfForm.mainIHcComment;
begin
	tipIHcComment;
end;

procedure TProcItfForm.mainIHcDisplay;
begin
	tipIHcDisplay;
end;

procedure TProcItfForm.mainIHcExtTables;
begin
	tipIHcExtTables;
end;

procedure TProcItfForm.mainIHcForm;
begin
	tipIHcForm;
end;

procedure TProcItfForm.mainIHcFRegFull;
begin
	tipIHcFRegFull;
end;

procedure TProcItfForm.mainIHcPayOff;
begin
	tipIHcPayOff;
end;

procedure TProcItfForm.mainIHcPeripherals;
begin
	tipIHcPeripherals;
end;

procedure TProcItfForm.mainIHcProgTransaction;
begin
	tipIHcProgTransaction;
end;

procedure TProcItfForm.mainIHcReadCOM;
begin
	tipIHcReadCOM;
end;

procedure TProcItfForm.mainIHcReport;
begin
	tipIHcReport;
end;

procedure TProcItfForm.mainIHcRestart;
begin
	tipIHcRestart;
end;

procedure TProcItfForm.mainIHcSqueeze;
begin
	tipIHcSqueeze;
end;

procedure TProcItfForm.mainIHcFRegEx;
begin
	tipIHcFRegEx;
end;

procedure TProcItfForm.tipIHcClrAllPLUClrAllPLU;
begin
	m1.Lines.Add('ClrAllPLU()');
	HcClrAllPLU.ClrAllPLU;
end;

procedure TProcItfForm.tipIHcCommentCloseComment;
begin
	m1.Lines.Add('CloseComment()');
	HcComment.CloseComment;
end;

procedure TProcItfForm.tipIHcCommentOpenComment;
begin
	m1.Lines.Add('OpenComment()');
	HcComment.OpenComment;
end;

procedure TProcItfForm.tipIHcCommentPrintComment;
begin
	m1.Lines.Add('PrintComment('+mePrintCommentComment.Text+')');
	HcComment.PrintComment(mePrintCommentComment.Text);
end;

procedure TProcItfForm.tipIHcDisplayOutScr;
begin
	m1.Lines.Add('OutScr('+meOutScrRow.Text+','+meOutScrScr2.Text+')');
	HcDisplay.OutScr(meOutScrRow.Text,meOutScrScr2.Text);
end;

procedure TProcItfForm.tipIHcExtTablesBackupExtTables;
begin
	m1.Lines.Add('BackupExtTables()');
	HcExtTables.BackupExtTables;
end;

procedure TProcItfForm.tipIHcExtTablesClearExtTables;
begin
	m1.Lines.Add('ClearExtTables()');
	HcExtTables.ClearExtTables;
end;

procedure TProcItfForm.tipIHcExtTablesRecalcCRC;
begin
	m1.Lines.Add('RecalcCRC()');
	HcExtTables.RecalcCRC;
end;

procedure TProcItfForm.tipIHcExtTablesRestoreExtTables;
begin
	m1.Lines.Add('RestoreExtTables()');
	HcExtTables.RestoreExtTables;
end;

procedure TProcItfForm.tipIHcExtTablesVerifyExtTables;
begin
	m1.Lines.Add('VerifyExtTables()');
	HcExtTables.VerifyExtTables;
end;

procedure TProcItfForm.tipIHcExtTablesWriteTable;
begin
	m1.Lines.Add('WriteTable('+meWriteTableTable.Text+','+meWriteTablePos.Text+','+meWriteTableInfo.Text+')');
	HcExtTables.WriteTable(meWriteTableTable.Text,meWriteTablePos.Text,meWriteTableInfo.Text);
end;

procedure TProcItfForm.tipIHcFormCancelForm;
begin
	m1.Lines.Add('CancelForm()');
	HcForm.CancelForm;
end;

procedure TProcItfForm.tipIHcFormCloseForm;
begin
	m1.Lines.Add('CLoseForm()');
	HcForm.CloseForm;
end;

procedure TProcItfForm.tipIHcFormOpenForm;
begin
	m1.Lines.Add('OpenForm()');
	HcForm.OpenForm;
end;

procedure TProcItfForm.tipIHcFormPrintOnForm;
begin
	m1.Lines.Add('PrintOnForm('+mePrintOnFormComment.Text+')');
	HcForm.PrintOnForm(mePrintOnFormComment.Text);
end;

procedure TProcItfForm.tipIHcFRegFullFullProd;
begin
	m1.Lines.Add('FullProd('+meFullProdCode.Text+','+meFullProdPrice.Text+','+meFullProdQty.Text+','+meFullProdDep.Text+','+meFullProdGrp.Text+','+meFullProdTax.Text+','+meFullProdName.Text+')');
	HcFRegFull.FullProd(meFullProdCode.Text,meFullProdPrice.Text,meFullProdQty.Text,meFullProdDep.Text,meFullProdGrp.Text,meFullProdTax.Text,meFullProdName.Text);
end;

procedure TProcItfForm.tipIHcFRegExFullProd;
begin
	m1.Lines.Add('FullProd('+me2FullProdCode.Text+','+me2FullProdPrice.Text+','+me2FullProdQty.Text+','+me2FullProdDep.Text+','+me2FullProdGrp.Text+','+me2FullProdTax.Text+','+me2FullProdName.Text+')');
	HcFRegEx.FullProd(me2FullProdCode.Text,me2FullProdPrice.Text,me2FullProdQty.Text,me2FullProdDep.Text,me2FullProdGrp.Text,me2FullProdTax.Text,me2FullProdName.Text);
end;

procedure TProcItfForm.tipIHcFRegExFullNac;
begin
	m1.Lines.Add('FullNac('+meFullNacID.Text+','+meFullNacSum.Text+','+meFullNacPrc.Text+','+meFullNacRec.Text+','+meFullNacTax.Text+')');
	HcFRegEx.FullNac(meFullNacID.Text,meFullNacSum.Text,meFullNacPrc.Text,meFullNacRec.Text,meFullNacTax.Text);
end;

procedure TProcItfForm.tipIHcFRegExSubtotal;
var
	Sum:OleVariant;
begin
	m1.Lines.Add('Subtotal()');
	HcFRegEx.Subtotal(Sum);
	lSubtotalSum.Caption:=Sum;
	m1.Lines.Add('return Sum='+string(Sum));
end;

procedure TProcItfForm.tipIHcPayOffPayOff;
begin
	m1.Lines.Add('PayOff('+mePayOffID.Text+','+mePayOffSum.Text+')');
	HcPayOff.PayOff(mePayOffID.Text,mePayOffSum.Text);
end;

procedure TProcItfForm.tipIHcPeripheralsPutInfo;
begin
	m1.Lines.Add('PutInfo('+mePutInfoID.Text+','+mePutInfoInfo.Text+')');
	HcPeripherals.PutInfo(mePutInfoID.Text,mePutInfoInfo.Text);
end;

procedure TProcItfForm.tipIHcProgTransactionProgClose;
begin
	m1.Lines.Add('ProgClose()');
	HcProgTransaction.ProgClose;
end;

procedure TProcItfForm.tipIHcProgTransactionProgEnter;
begin
	m1.Lines.Add('ProgEnter()');
	HcProgTransaction.ProgEnter;
end;

function arr2str(const v:OleVariant):string;
var
	i,l,h:Integer;
	b:OleVariant;
	bb:byte;
begin
	result:='';
	l:=VarArrayLowBound(v,1);
	h:=VarArrayHighBound(v,1);
	for i:=l to h do begin
		b:=v[i];
		VariantChangeTypeEx(b,b,0,0,VT_BSTR);
		bb:=b;
		result:=result+format('%02x ',[bb]);
	end;
end;

procedure TProcItfForm.tipIHcReadCOMReadCOM;
var
	ID,Line:OleVariant;
//	vID,vLine:Variant;
begin
	m1.Lines.Add('ReadCOM('+meReadCOMKind.Text+')');
	HcReadCOM.ReadCOM(meReadCOMKind.Text,ID,Line);
	VariantChangeTypeEx(ID,ID,0,0,VT_BSTR);
	lReadCOMID.Caption:=ID;
	Line:=arr2str(Line);
	lReadCOMLine.Caption:=Line;
	m1.Lines.Add('return ID='+ID+' Line='+Line);
end;

procedure TProcItfForm.tipIHcReportPrintReport;
begin
	m1.Lines.Add('PrintReport('+mePrintReportNumReport.Text+')');
	HcReport.PrintReport(mePrintReportNumReport.Text);
end;

procedure TProcItfForm.tipIHcRestartRestart;
begin
	m1.Lines.Add('Restart()');
	HcRestart.Restart;
end;

procedure TProcItfForm.tipIHcSqueezeSqueeze;
begin
	m1.Lines.Add('Squeeze()');
	HcSqueeze.Squeeze;
end;

procedure TProcItfForm.pcgClrAllPLUShow(Sender: TObject);
begin
	tipIHcClrAllPLU:=tipIHcClrAllPLUClrAllPLU;
end;

procedure TProcItfForm.pcgProgEnterShow(Sender: TObject);
begin
	tipIHcProgTransaction:=tipIHcProgTransactionProgEnter;
end;

procedure TProcItfForm.pcgProgCloseShow(Sender: TObject);
begin
	tipIHcProgTransaction:=tipIHcProgTransactionProgClose;
end;

procedure TProcItfForm.pgIHcGetDriverInfoShow(Sender: TObject);
begin
	lGDIName.Caption:=HcGetDriverInfo.Name;
	lGDITextCommentHeight.Caption:=HcGetDriverInfo.TextCommentHeight;
	lGDITextCommentWidth.Caption:=HcGetDriverInfo.TextCommentWidth;
	lGDIPLUCodeWidth.Caption:=HcGetDriverInfo.PLUCodeWidth;
	lGDIPLUNameWidth.Caption:=HcGetDriverInfo.PLUNameWidth;
	lGDIMaxPLUCount.Caption:=HcGetDriverInfo.MaxPLUCount;
end;

procedure TProcItfForm.pgIHcPayOffShow(Sender: TObject);
begin
	tipIHc:=mainIHcPayOff;
end;

procedure TProcItfForm.pgIHcPeripheralsShow(Sender: TObject);
begin
	tipIHc:=mainIHcPeripherals;
end;

procedure TProcItfForm.pgIHcProgTransactionShow(Sender: TObject);
begin
	tipIHc:=mainIHcProgTransaction;
end;

procedure TProcItfForm.pgIHcReportShow(Sender: TObject);
begin
	tipIHc:=mainIHcReport;
end;

procedure TProcItfForm.pgIHcRestartShow(Sender: TObject);
begin
	tipIHc:=mainIHcRestart;
end;

procedure TProcItfForm.pgIHcSqueezeShow(Sender: TObject);
begin
	tipIHc:=mainIHcSqueeze;
end;

procedure TProcItfForm.pgIHcFormShow(Sender: TObject);
begin
	tipIHc:=mainIHcForm;
end;

procedure TProcItfForm.pgIHcExtTablesShow(Sender: TObject);
begin
	tipIHc:=mainIHcExtTables;
end;

procedure TProcItfForm.pgIHcDisplayShow(Sender: TObject);
begin
	tipIHc:=mainIHcDisplay;
end;

procedure TProcItfForm.pgIHcCommentShow(Sender: TObject);
begin
	tipIHc:=mainIHcComment;
end;

procedure TProcItfForm.pgIHcClrAllPLUShow(Sender: TObject);
begin
	tipIHc:=mainIHcClrAllPLU;
end;

procedure TProcItfForm.pcgOutScrShow(Sender: TObject);
begin
	tipIHcDisplay:=tipIHcDisplayOutScr;
	ActiveControl:=meOutScrRow;
end;

procedure TProcItfForm.pgIHcPLUFlagsShow(Sender: TObject);
begin
	lPLUFlagsMutablePrice.Caption:=HcPLUFlags.MutablePrice;
	lPLUFlagsFractional.Caption:=HcPLUFlags.Fractional;
	lPLUFlagsRestrictedAmount.Caption:=HcPLUFlags.RestrictedAmount;
	lPLUFlagsQuota.Caption:=HcPLUFlags.Quota;
	lPLUFlagsSingleton.Caption:=HcPLUFlags.Singleton;
	lPLUFlagsOnForm.Caption:=HcPLUFlags.Onform;
end;

procedure TProcItfForm.pgIHcReadCOMShow(Sender: TObject);
begin
	tipIHc:=mainIHcReadCOM;
end;

procedure TProcItfForm.pgIHcFRegFullShow(Sender: TObject);
begin
	tipIHc:=mainIHcFRegFull;
end;

procedure TProcItfForm.pcgWriteTableShow(Sender: TObject);
begin
	tipIHcExtTables:=tipIHcExtTablesWriteTable;
	ActiveControl:=meWriteTableTable;
end;

procedure TProcItfForm.pcgVerifyExtTablesShow(Sender: TObject);
begin
	tipIHcExtTables:=tipIHcExtTablesVerifyExtTables;
end;

procedure TProcItfForm.pcgSqueezeShow(Sender: TObject);
begin
	tipIHcSqueeze:=tipIHcSqueezeSqueeze;
end;

procedure TProcItfForm.pcgRestoreExtTablesShow(Sender: TObject);
begin
	tipIHcExtTables:=tipIHcExtTablesRestoreExtTables;
end;

procedure TProcItfForm.pcgRestartShow(Sender: TObject);
begin
	tipIHcRestart:=tipIHcRestartRestart;
end;

procedure TProcItfForm.pcgRecalcCRCShow(Sender: TObject);
begin
	tipIHcExtTables:=tipIHcExtTablesRecalcCRC;
end;

procedure TProcItfForm.pcgReadCOMShow(Sender: TObject);
begin
	tipIHcReadCOM:=tipIHcReadCOMReadCOM;
end;

procedure TProcItfForm.pcgPutInfoShow(Sender: TObject);
begin
	tipIHcPeripherals:=tipIHcPeripheralsPutInfo;
	ActiveControl:=mePutInfoID;
end;

procedure TProcItfForm.pcgPrintReportShow(Sender: TObject);
begin
	tipIHcReport:=tipIHcReportPrintReport;
	ActiveControl:=mePrintReportNumReport;
end;

procedure TProcItfForm.pcgPrintOnFormShow(Sender: TObject);
begin
	tipIHcForm:=tipIHcFormPrintOnForm;
	ActiveControl:=mePrintOnFormComment;
end;

procedure TProcItfForm.pcgPrintCommentShow(Sender: TObject);
begin
	tipIHcComment:=tipIHcCommentPrintComment;
	ActiveControl:=mePrintCommentComment;
end;

procedure TProcItfForm.pcgPayOffShow(Sender: TObject);
begin
	tipIHcPayOff:=tipIHcPayOffPayOff;
	ActiveControl:=mePayOffID;
end;

procedure TProcItfForm.pcgOpenFormShow(Sender: TObject);
begin
	tipIHcForm:=tipIHcFormOpenForm;
end;

procedure TProcItfForm.pcgOpenCommentShow(Sender: TObject);
begin
	tipIHcComment:=tipIHcCommentOpenComment;
end;

procedure TProcItfForm.pcgFullProdShow(Sender: TObject);
begin
	tipIHcFRegFull:=tipIHcFRegFullFullProd;
	ActiveControl:=meFullProdCode;
end;

procedure TProcItfForm.pcgCloseFormShow(Sender: TObject);
begin
	tipIHcForm:=tipIHcFormCloseForm;
end;

procedure TProcItfForm.pcgCloseCommentShow(Sender: TObject);
begin
	tipIHcComment:=tipIHcCommentCloseComment;
end;

procedure TProcItfForm.pcgClearExtTablesShow(Sender: TObject);
begin
	tipIHcExtTables:=tipIHcExtTablesClearExtTables;
end;

procedure TProcItfForm.pcgCancelFormShow(Sender: TObject);
begin
	tipIHcForm:=tipIHcFormCancelForm;
end;

procedure TProcItfForm.pcgBackupExtTablesShow(Sender: TObject);
begin
	tipIHcExtTables:=tipIHcExtTablesBackupExtTables;
end;

procedure TProcItfForm.pgIHcFRegExShow(Sender: TObject);
begin
	tipIHc:=mainIHcFRegEx;
end;

procedure TProcItfForm.pcg2FullProdShow(Sender: TObject);
begin
	tipIHcFRegEx:=tipIHcFRegExFullProd;
end;

procedure TProcItfForm.pcgFullNacShow(Sender: TObject);
begin
	tipIHcFRegEx:=tipIHcFRegExFullNac;
end;

procedure TProcItfForm.pcgSubtotalShow(Sender: TObject);
begin
	tipIHcFRegEx:=tipIHcFRegExSubtotal;
end;

end.
