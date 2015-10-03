unit HcTLB_TLB;

// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// $Rev: 8291 $
// File generated on 11.09.2013 13:18:58 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Common Files\EQL\HcTLB.tlb (1)
// LIBID: {9AC56B40-8546-11D3-9B33-008048C5FDF8}
// LCID: 0
// Helpfile: C:\Program Files\Common Files\EQL\hctlb.hlp
// HelpString: Help Co Common Cash Register Interfaces
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\stdole2.tlb)
// Errors:
//   Hint: Parameter 'Unit' of IHcFullNameProd.FullNameProd changed to 'Unit_'
//   Hint: Parameter 'Type' of IHmFM.PutInfoFM changed to 'Type_'
//   Hint: Parameter 'Unit' of IHmFReg3.FullNameProd changed to 'Unit_'
//   Hint: Parameter 'Unit' of IHmFReg4.FullNameProd changed to 'Unit_'
//   Hint: Parameter 'Unit' of IHmAZSFP.FullNameProd changed to 'Unit_'
// ************************************************************************ //
// *************************************************************************//
// NOTE:                                                                      
// Items guarded by $IFDEF_LIVE_SERVER_AT_DESIGN_TIME are used by properties  
// which return objects that may need to be explicitly created via a function 
// call prior to any access via the property. These items have been disabled  
// in order to prevent accidental use from within the object inspector. You   
// may enable them by defining LIVE_SERVER_AT_DESIGN_TIME or by selectively   
// removing them from the $IFDEF blocks. However, such items must still be    
// programmatically created via a method of the appropriate CoClass before    
// they can be used.                                                          
{$TYPEDADDRESS OFF} // Unit must be compiled without type-checked pointers. 
{$WARN SYMBOL_PLATFORM OFF}
{$WRITEABLECONST ON}
{$VARPROPSETTER ON}
interface

uses Windows, ActiveX, Classes, Graphics, StdVCL, Variants;
  

// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:        
//   Type Libraries     : LIBID_xxxx                                      
//   CoClasses          : CLASS_xxxx                                      
//   DISPInterfaces     : DIID_xxxx                                       
//   Non-DISP interfaces: IID_xxxx                                        
// *********************************************************************//
const
  // TypeLibrary Major and minor versions
  HcTLBMajorVersion = 3;
  HcTLBMinorVersion = 0;

  LIBID_HcTLB: TGUID = '{9AC56B40-8546-11D3-9B33-008048C5FDF8}';

  DIID_IHcFReg: TGUID = '{9AFF0130-854E-11D3-9B33-008048C5FDF8}';
  DIID_IHcClrAllPLU: TGUID = '{BBE14EA0-854F-11D3-9B33-008048C5FDF8}';
  DIID_IHcProgTransaction: TGUID = '{D05A9BC0-854F-11D3-9B33-008048C5FDF8}';
  DIID_IHcSqueeze: TGUID = '{DA540610-854F-11D3-9B33-008048C5FDF8}';
  DIID_IHcSound: TGUID = '{E2BE9C70-854F-11D3-9B33-008048C5FDF8}';
  DIID_IHcDisplay: TGUID = '{ED7273A0-854F-11D3-9B33-008048C5FDF8}';
  DIID_IHcPeripherals: TGUID = '{FDB4EE60-854F-11D3-9B33-008048C5FDF8}';
  DIID_IHcGetDriverInfo: TGUID = '{A9B20870-B549-11D3-9B93-008048C5FDF8}';
  DIID_IHcAuthorize: TGUID = '{2E379AE0-32DF-11D4-9CA7-008048C5FDF8}';
  DIID_IHcAllEraEvents: TGUID = '{0B931E30-B55F-11D3-9B93-008048C5FDF8}';
  DIID_IHcPayOff: TGUID = '{A11BC6E3-5D4A-4066-A87A-B701122058C5}';
  DIID_IHcComment: TGUID = '{03844049-1DC2-497A-ADEE-84A1D54DB6DA}';
  DIID_IHcCommentEx: TGUID = '{5409063F-EC75-4CF5-AA23-E5B288AA81EF}';
  DIID_IHcForm: TGUID = '{1873E96F-AA83-4F67-A4D5-3AD2CE6555E8}';
  DIID_IHcReport: TGUID = '{A4C7AEB0-0476-4224-9B27-A53DDF6BD658}';
  DIID_IHcRestart: TGUID = '{FFEDB686-190E-4083-A6CB-71E4EF6E15D1}';
  DIID_IHcExtTables: TGUID = '{C4E1DA06-6643-467A-B5C1-EF8CD3DE160B}';
  DIID_IHcPLUFlags: TGUID = '{BB449260-C6C1-11D4-9DBE-008048C5FDF8}';
  DIID_IHcReadCOM: TGUID = '{E4023710-C6C5-11D4-9DBE-008048C5FDF8}';
  DIID_IHcFRegFull: TGUID = '{F3DB41E0-C6C5-11D4-9DBE-008048C5FDF8}';
  DIID_IHcFRegEx: TGUID = '{AEC91A90-F789-11D4-9E0D-008048C5FDF8}';
  DIID_IHcScales: TGUID = '{724A3A82-6B93-4D22-B487-C585F7D4A99E}';
  DIID_IHcReturn: TGUID = '{3FCFB05A-116D-412E-B9D7-F96E807044A4}';
  DIID_IHcCrypFM: TGUID = '{F0F39961-7A29-4864-A8D8-FC8E6B27C7ED}';
  DIID_IHcFiscPrnt: TGUID = '{094DCF43-D5D9-41D6-80B6-9F10290BCD9A}';
  DIID_IHcFullNameProd: TGUID = '{5EDE688C-F90D-450F-ADCD-5CB092E83D15}';
  DIID_IHcVatFact: TGUID = '{A4B9810D-1F84-4893-9BE1-72A2E236957A}';
  DIID_IHmLastInfo: TGUID = '{03BD07D2-6F1E-42A7-9021-16B053B079DF}';
  DIID_IHmEuroPay: TGUID = '{9BE22B6A-F8A2-46DD-B209-6358D05689C4}';
  DIID_IHmMetrics: TGUID = '{DF180FD2-8011-4586-A5C0-DD273968011D}';
  DIID_IHmFM: TGUID = '{3184771F-8E45-4ABF-80B9-F007A724B077}';
  DIID_IHmGetRoom: TGUID = '{BC6C595B-BE10-4DF2-87F5-D8DBFC9D5A8E}';
  DIID_IHmChkParam: TGUID = '{AF69C612-C591-4FB1-AE1C-684B29179384}';
  DIID_IHmReadState: TGUID = '{FC383114-4D44-411A-874F-AC749724593D}';
  DIID_IHmPrinterStatus: TGUID = '{24CDEE78-0C15-4767-9E30-0DA674781EEC}';
  DIID_IHmFReg2: TGUID = '{5B4EAE47-83AF-4FF9-9455-31CA48E8E8CC}';
  DIID_IHmFReg3: TGUID = '{763C5592-F3B1-4597-B552-10A8286A8D5A}';
  DIID_IHmFReg4: TGUID = '{3DF3A03A-01BB-490F-B619-DC91C7BAD10D}';
  DIID_IHmPreEndChk: TGUID = '{898C5A33-A7DF-4132-B359-F445405C8581}';
  DIID_IHmCEFReg: TGUID = '{1C2AB807-3371-46B3-ADF4-0838358FA8F2}';
  DIID_IHmAZSFP: TGUID = '{426849A4-A273-4EFD-B424-44542AF79D2B}';
  DIID_IHmAZSController: TGUID = '{4B927538-A046-4292-90AA-20B7A509D331}';
  DIID_IHmFRegWeight: TGUID = '{99DD9245-A46D-4C4C-BD0F-FEEEE7761E85}';
  DIID_IHmSSTRNL: TGUID = '{84E73A3F-7342-43A8-8D75-43C273DA662E}';
type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IHcFReg = dispinterface;
  IHcClrAllPLU = dispinterface;
  IHcProgTransaction = dispinterface;
  IHcSqueeze = dispinterface;
  IHcSound = dispinterface;
  IHcDisplay = dispinterface;
  IHcPeripherals = dispinterface;
  IHcGetDriverInfo = dispinterface;
  IHcAuthorize = dispinterface;
  IHcAllEraEvents = dispinterface;
  IHcPayOff = dispinterface;
  IHcComment = dispinterface;
  IHcCommentEx = dispinterface;
  IHcForm = dispinterface;
  IHcReport = dispinterface;
  IHcRestart = dispinterface;
  IHcExtTables = dispinterface;
  IHcPLUFlags = dispinterface;
  IHcReadCOM = dispinterface;
  IHcFRegFull = dispinterface;
  IHcFRegEx = dispinterface;
  IHcScales = dispinterface;
  IHcReturn = dispinterface;
  IHcCrypFM = dispinterface;
  IHcFiscPrnt = dispinterface;
  IHcFullNameProd = dispinterface;
  IHcVatFact = dispinterface;
  IHmLastInfo = dispinterface;
  IHmEuroPay = dispinterface;
  IHmMetrics = dispinterface;
  IHmFM = dispinterface;
  IHmGetRoom = dispinterface;
  IHmChkParam = dispinterface;
  IHmReadState = dispinterface;
  IHmPrinterStatus = dispinterface;
  IHmFReg2 = dispinterface;
  IHmFReg3 = dispinterface;
  IHmFReg4 = dispinterface;
  IHmPreEndChk = dispinterface;
  IHmCEFReg = dispinterface;
  IHmAZSFP = dispinterface;
  IHmAZSController = dispinterface;
  IHmFRegWeight = dispinterface;
  IHmSSTRNL = dispinterface;

// *********************************************************************//
// DispIntf:  IHcFReg
// Flags:     (4096) Dispatchable
// GUID:      {9AFF0130-854E-11D3-9B33-008048C5FDF8}
// *********************************************************************//
  IHcFReg = dispinterface
    ['{9AFF0130-854E-11D3-9B33-008048C5FDF8}']
    procedure SmenBegin; dispid 257;
    procedure BegChk; dispid 258;
    procedure EndChk; dispid 259;
    procedure VoidChk; dispid 260;
    procedure CopyChk; dispid 261;
    procedure VoidLast; dispid 262;
    procedure TextComment(Comment: OleVariant); dispid 263;
    procedure BinComment(ID: OleVariant; BComment: OleVariant); dispid 264;
    procedure Prod(ID: OleVariant; Cena: OleVariant; Kol: OleVariant; Dep: OleVariant; 
                   Grp: OleVariant); dispid 265;
    procedure VoidProd(ID: OleVariant); dispid 266;
    procedure Oplata(ID: OleVariant; Sum: OleVariant; Code: OleVariant); dispid 267;
    procedure InOut(ID: OleVariant; Sum: OleVariant); dispid 268;
    procedure NacSkd(ID: OleVariant; Sum: OleVariant; Prc: OleVariant); dispid 269;
  end;

// *********************************************************************//
// DispIntf:  IHcClrAllPLU
// Flags:     (4096) Dispatchable
// GUID:      {BBE14EA0-854F-11D3-9B33-008048C5FDF8}
// *********************************************************************//
  IHcClrAllPLU = dispinterface
    ['{BBE14EA0-854F-11D3-9B33-008048C5FDF8}']
    procedure ClrAllPLU; dispid 273;
  end;

// *********************************************************************//
// DispIntf:  IHcProgTransaction
// Flags:     (4096) Dispatchable
// GUID:      {D05A9BC0-854F-11D3-9B33-008048C5FDF8}
// *********************************************************************//
  IHcProgTransaction = dispinterface
    ['{D05A9BC0-854F-11D3-9B33-008048C5FDF8}']
    procedure ProgEnter; dispid 289;
    procedure ProgClose; dispid 290;
  end;

// *********************************************************************//
// DispIntf:  IHcSqueeze
// Flags:     (4096) Dispatchable
// GUID:      {DA540610-854F-11D3-9B33-008048C5FDF8}
// *********************************************************************//
  IHcSqueeze = dispinterface
    ['{DA540610-854F-11D3-9B33-008048C5FDF8}']
    procedure Squeeze; dispid 305;
  end;

// *********************************************************************//
// DispIntf:  IHcSound
// Flags:     (4096) Dispatchable
// GUID:      {E2BE9C70-854F-11D3-9B33-008048C5FDF8}
// *********************************************************************//
  IHcSound = dispinterface
    ['{E2BE9C70-854F-11D3-9B33-008048C5FDF8}']
    procedure OutTone(Len: OleVariant; Tone: OleVariant); dispid 321;
  end;

// *********************************************************************//
// DispIntf:  IHcDisplay
// Flags:     (4096) Dispatchable
// GUID:      {ED7273A0-854F-11D3-9B33-008048C5FDF8}
// *********************************************************************//
  IHcDisplay = dispinterface
    ['{ED7273A0-854F-11D3-9B33-008048C5FDF8}']
    procedure OutScr(Row: OleVariant; Scr2: OleVariant); dispid 337;
  end;

// *********************************************************************//
// DispIntf:  IHcPeripherals
// Flags:     (4096) Dispatchable
// GUID:      {FDB4EE60-854F-11D3-9B33-008048C5FDF8}
// *********************************************************************//
  IHcPeripherals = dispinterface
    ['{FDB4EE60-854F-11D3-9B33-008048C5FDF8}']
    procedure PutInfo(ID: OleVariant; Info: OleVariant); dispid 353;
  end;

// *********************************************************************//
// DispIntf:  IHcGetDriverInfo
// Flags:     (4096) Dispatchable
// GUID:      {A9B20870-B549-11D3-9B93-008048C5FDF8}
// *********************************************************************//
  IHcGetDriverInfo = dispinterface
    ['{A9B20870-B549-11D3-9B93-008048C5FDF8}']
    property Name: OleVariant readonly dispid 513;
    property TextCommentHeight: OleVariant readonly dispid 514;
    property TextCommentWidth: OleVariant readonly dispid 515;
    property PLUCodeWidth: OleVariant readonly dispid 516;
    property PLUNameWidth: OleVariant readonly dispid 517;
    property MaxPLUCount: OleVariant readonly dispid 518;
  end;

// *********************************************************************//
// DispIntf:  IHcAuthorize
// Flags:     (4624) Hidden Restricted Dispatchable
// GUID:      {2E379AE0-32DF-11D4-9CA7-008048C5FDF8}
// *********************************************************************//
  IHcAuthorize = dispinterface
    ['{2E379AE0-32DF-11D4-9CA7-008048C5FDF8}']
    procedure Authorize(Password1: OleVariant; Password2: OleVariant; Seed: OleVariant; 
                        out Info: OleVariant); dispid 385;
  end;

// *********************************************************************//
// DispIntf:  IHcAllEraEvents
// Flags:     (4096) Dispatchable
// GUID:      {0B931E30-B55F-11D3-9B93-008048C5FDF8}
// *********************************************************************//
  IHcAllEraEvents = dispinterface
    ['{0B931E30-B55F-11D3-9B93-008048C5FDF8}']
    procedure UnknownPLU(Code: OleVariant); dispid 257;
    procedure PayQuery(ID: OleVariant; Sum: OleVariant; Code: OleVariant); dispid 258;
    procedure StartZ1; dispid 259;
    procedure DoneZ1; dispid 260;
    procedure StartZ2; dispid 261;
    procedure DoneZ2; dispid 262;
    procedure XchgChk; dispid 263;
    procedure GetInfo(ID: OleVariant; Info: OleVariant); dispid 264;
  end;

// *********************************************************************//
// DispIntf:  IHcPayOff
// Flags:     (4096) Dispatchable
// GUID:      {A11BC6E3-5D4A-4066-A87A-B701122058C5}
// *********************************************************************//
  IHcPayOff = dispinterface
    ['{A11BC6E3-5D4A-4066-A87A-B701122058C5}']
    procedure PayOff(ID: OleVariant; Sum: OleVariant); dispid 369;
  end;

// *********************************************************************//
// DispIntf:  IHcComment
// Flags:     (4096) Dispatchable
// GUID:      {03844049-1DC2-497A-ADEE-84A1D54DB6DA}
// *********************************************************************//
  IHcComment = dispinterface
    ['{03844049-1DC2-497A-ADEE-84A1D54DB6DA}']
    procedure OpenComment; dispid 370;
    procedure CloseComment; dispid 371;
    procedure PrintComment(Comment: OleVariant); dispid 372;
  end;

// *********************************************************************//
// DispIntf:  IHcCommentEx
// Flags:     (4096) Dispatchable
// GUID:      {5409063F-EC75-4CF5-AA23-E5B288AA81EF}
// *********************************************************************//
  IHcCommentEx = dispinterface
    ['{5409063F-EC75-4CF5-AA23-E5B288AA81EF}']
    procedure OpenComment; dispid 370;
    procedure CloseComment; dispid 371;
    procedure PrintComment(Comment: OleVariant); dispid 372;
    procedure PrintCommentExt(Param: OleVariant; Comment: OleVariant); dispid 468;
  end;

// *********************************************************************//
// DispIntf:  IHcForm
// Flags:     (4096) Dispatchable
// GUID:      {1873E96F-AA83-4F67-A4D5-3AD2CE6555E8}
// *********************************************************************//
  IHcForm = dispinterface
    ['{1873E96F-AA83-4F67-A4D5-3AD2CE6555E8}']
    procedure OpenForm; dispid 373;
    procedure CancelForm; dispid 374;
    procedure CloseForm; dispid 375;
    procedure PrintOnForm(Comment: OleVariant); dispid 376;
  end;

// *********************************************************************//
// DispIntf:  IHcReport
// Flags:     (4096) Dispatchable
// GUID:      {A4C7AEB0-0476-4224-9B27-A53DDF6BD658}
// *********************************************************************//
  IHcReport = dispinterface
    ['{A4C7AEB0-0476-4224-9B27-A53DDF6BD658}']
    procedure PrintReport(NumReport: OleVariant); dispid 377;
  end;

// *********************************************************************//
// DispIntf:  IHcRestart
// Flags:     (4096) Dispatchable
// GUID:      {FFEDB686-190E-4083-A6CB-71E4EF6E15D1}
// *********************************************************************//
  IHcRestart = dispinterface
    ['{FFEDB686-190E-4083-A6CB-71E4EF6E15D1}']
    procedure Restart; dispid 378;
  end;

// *********************************************************************//
// DispIntf:  IHcExtTables
// Flags:     (4096) Dispatchable
// GUID:      {C4E1DA06-6643-467A-B5C1-EF8CD3DE160B}
// *********************************************************************//
  IHcExtTables = dispinterface
    ['{C4E1DA06-6643-467A-B5C1-EF8CD3DE160B}']
    procedure ClearExtTables; dispid 379;
    procedure BackupExtTables; dispid 380;
    procedure RecalcCRC; dispid 381;
    procedure RestoreExtTables; dispid 382;
    procedure VerifyExtTables; dispid 383;
    procedure WriteTable(Table: OleVariant; Pos: OleVariant; Info: OleVariant); dispid 384;
  end;

// *********************************************************************//
// DispIntf:  IHcPLUFlags
// Flags:     (4096) Dispatchable
// GUID:      {BB449260-C6C1-11D4-9DBE-008048C5FDF8}
// *********************************************************************//
  IHcPLUFlags = dispinterface
    ['{BB449260-C6C1-11D4-9DBE-008048C5FDF8}']
    property MutablePrice: OleVariant readonly dispid 519;
    property Fractional: OleVariant readonly dispid 520;
    property RestrictedAmount: OleVariant readonly dispid 521;
    property Quota: OleVariant readonly dispid 522;
    property Singleton: OleVariant readonly dispid 523;
    property OnForm: OleVariant readonly dispid 524;
  end;

// *********************************************************************//
// DispIntf:  IHcReadCOM
// Flags:     (4096) Dispatchable
// GUID:      {E4023710-C6C5-11D4-9DBE-008048C5FDF8}
// *********************************************************************//
  IHcReadCOM = dispinterface
    ['{E4023710-C6C5-11D4-9DBE-008048C5FDF8}']
    procedure ReadCOM(Kind: OleVariant; out ID: OleVariant; out Line: OleVariant); dispid 386;
  end;

// *********************************************************************//
// DispIntf:  IHcFRegFull
// Flags:     (4096) Dispatchable
// GUID:      {F3DB41E0-C6C5-11D4-9DBE-008048C5FDF8}
// *********************************************************************//
  IHcFRegFull = dispinterface
    ['{F3DB41E0-C6C5-11D4-9DBE-008048C5FDF8}']
    procedure FullProd(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                       Grp: OleVariant; Tax: OleVariant; Name: OleVariant); dispid 387;
  end;

// *********************************************************************//
// DispIntf:  IHcFRegEx
// Flags:     (4096) Dispatchable
// GUID:      {AEC91A90-F789-11D4-9E0D-008048C5FDF8}
// *********************************************************************//
  IHcFRegEx = dispinterface
    ['{AEC91A90-F789-11D4-9E0D-008048C5FDF8}']
    procedure FullProd(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                       Grp: OleVariant; Tax: OleVariant; Name: OleVariant); dispid 387;
    procedure FullNac(ID: OleVariant; Sum: OleVariant; Prc: OleVariant; Rec: OleVariant; 
                      Tax: OleVariant); dispid 388;
    procedure Subtotal(out Sum: OleVariant); dispid 389;
  end;

// *********************************************************************//
// DispIntf:  IHcScales
// Flags:     (4096) Dispatchable
// GUID:      {724A3A82-6B93-4D22-B487-C585F7D4A99E}
// *********************************************************************//
  IHcScales = dispinterface
    ['{724A3A82-6B93-4D22-B487-C585F7D4A99E}']
    property ScaleAmount: OleVariant readonly dispid 529;
    property ScaleMoney: OleVariant readonly dispid 530;
    property ScalePrc: OleVariant readonly dispid 531;
  end;

// *********************************************************************//
// DispIntf:  IHcReturn
// Flags:     (4096) Dispatchable
// GUID:      {3FCFB05A-116D-412E-B9D7-F96E807044A4}
// *********************************************************************//
  IHcReturn = dispinterface
    ['{3FCFB05A-116D-412E-B9D7-F96E807044A4}']
    procedure BegReturn; dispid 390;
  end;

// *********************************************************************//
// DispIntf:  IHcCrypFM
// Flags:     (4096) Dispatchable
// GUID:      {F0F39961-7A29-4864-A8D8-FC8E6B27C7ED}
// *********************************************************************//
  IHcCrypFM = dispinterface
    ['{F0F39961-7A29-4864-A8D8-FC8E6B27C7ED}']
    procedure ZRepReady(Rec: OleVariant); dispid 391;
  end;

// *********************************************************************//
// DispIntf:  IHcFiscPrnt
// Flags:     (4096) Dispatchable
// GUID:      {094DCF43-D5D9-41D6-80B6-9F10290BCD9A}
// *********************************************************************//
  IHcFiscPrnt = dispinterface
    ['{094DCF43-D5D9-41D6-80B6-9F10290BCD9A}']
    procedure OpenSafe; dispid 392;
    procedure SetClock(Time: OleVariant; Date: OleVariant); dispid 393;
    procedure PutReset(MaxPLU: OleVariant; NChk: OleVariant; Time: OleVariant; Date: OleVariant; 
                       Lang: OleVariant); dispid 394;
    procedure Fiscalisation(CurrDate: OleVariant); dispid 395;
    procedure PutTaxFM(CurrDate: OleVariant); dispid 396;
    procedure PutHdrFM(CurrDate: OleVariant); dispid 397;
    procedure FMReport(NumReport: OleVariant; BegDate: OleVariant; EndDate: OleVariant; 
                       BegRec: OleVariant; EndRec: OleVariant); dispid 398;
  end;

// *********************************************************************//
// DispIntf:  IHcFullNameProd
// Flags:     (4096) Dispatchable
// GUID:      {5EDE688C-F90D-450F-ADCD-5CB092E83D15}
// *********************************************************************//
  IHcFullNameProd = dispinterface
    ['{5EDE688C-F90D-450F-ADCD-5CB092E83D15}']
    procedure FullNameProd(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                           Grp: OleVariant; Tax: OleVariant; Name: OleVariant; Comm: OleVariant; 
                           Unit_: OleVariant); dispid 399;
  end;

// *********************************************************************//
// DispIntf:  IHcVatFact
// Flags:     (4096) Dispatchable
// GUID:      {A4B9810D-1F84-4893-9BE1-72A2E236957A}
// *********************************************************************//
  IHcVatFact = dispinterface
    ['{A4B9810D-1F84-4893-9BE1-72A2E236957A}']
    procedure BegVatFact(Code: OleVariant); dispid 400;
  end;

// *********************************************************************//
// DispIntf:  IHmLastInfo
// Flags:     (4096) Dispatchable
// GUID:      {03BD07D2-6F1E-42A7-9021-16B053B079DF}
// *********************************************************************//
  IHmLastInfo = dispinterface
    ['{03BD07D2-6F1E-42A7-9021-16B053B079DF}']
    procedure LastChkInfo(out Total: OleVariant; out ChkNum: OleVariant; out ChkDate: OleVariant; 
                          out ChkTime: OleVariant; out NKass: OleVariant); dispid 401;
    procedure LastOpInfo(NTax: OleVariant; out Summ: OleVariant; out Mode: OleVariant); dispid 402;
  end;

// *********************************************************************//
// DispIntf:  IHmEuroPay
// Flags:     (4096) Dispatchable
// GUID:      {9BE22B6A-F8A2-46DD-B209-6358D05689C4}
// *********************************************************************//
  IHmEuroPay = dispinterface
    ['{9BE22B6A-F8A2-46DD-B209-6358D05689C4}']
    procedure EuroTotal(ID: OleVariant; out Summ: OleVariant); dispid 431;
  end;

// *********************************************************************//
// DispIntf:  IHmMetrics
// Flags:     (4096) Dispatchable
// GUID:      {DF180FD2-8011-4586-A5C0-DD273968011D}
// *********************************************************************//
  IHmMetrics = dispinterface
    ['{DF180FD2-8011-4586-A5C0-DD273968011D}']
    property dmCtry: OleVariant readonly dispid 544;
    property dmMfg: OleVariant readonly dispid 545;
    property dmTaxChars: OleVariant readonly dispid 546;
  end;

// *********************************************************************//
// DispIntf:  IHmFM
// Flags:     (4096) Dispatchable
// GUID:      {3184771F-8E45-4ABF-80B9-F007A724B077}
// *********************************************************************//
  IHmFM = dispinterface
    ['{3184771F-8E45-4ABF-80B9-F007A724B077}']
    procedure PutInfoFM(CurrDate: OleVariant; Type_: OleVariant); dispid 433;
  end;

// *********************************************************************//
// DispIntf:  IHmGetRoom
// Flags:     (4096) Dispatchable
// GUID:      {BC6C595B-BE10-4DF2-87F5-D8DBFC9D5A8E}
// *********************************************************************//
  IHmGetRoom = dispinterface
    ['{BC6C595B-BE10-4DF2-87F5-D8DBFC9D5A8E}']
    procedure GetFMRoom(out Total: OleVariant; out Used: OleVariant); dispid 434;
    procedure GetJRNRoom(out Total: OleVariant; out Used: OleVariant); dispid 435;
  end;

// *********************************************************************//
// DispIntf:  IHmChkParam
// Flags:     (4096) Dispatchable
// GUID:      {AF69C612-C591-4FB1-AE1C-684B29179384}
// *********************************************************************//
  IHmChkParam = dispinterface
    ['{AF69C612-C591-4FB1-AE1C-684B29179384}']
    procedure ChkParam(out State: OleVariant; out CurrOper: OleVariant; out BegChk: OleVariant; 
                       out BegRep: OleVariant); dispid 452;
  end;

// *********************************************************************//
// DispIntf:  IHmReadState
// Flags:     (4096) Dispatchable
// GUID:      {FC383114-4D44-411A-874F-AC749724593D}
// *********************************************************************//
  IHmReadState = dispinterface
    ['{FC383114-4D44-411A-874F-AC749724593D}']
    procedure ReadState(ID: OleVariant; out State: OleVariant; out FullState: OleVariant); dispid 461;
  end;

// *********************************************************************//
// DispIntf:  IHmPrinterStatus
// Flags:     (4096) Dispatchable
// GUID:      {24CDEE78-0C15-4767-9E30-0DA674781EEC}
// *********************************************************************//
  IHmPrinterStatus = dispinterface
    ['{24CDEE78-0C15-4767-9E30-0DA674781EEC}']
    procedure PrinterStatus(out Param: OleVariant); dispid 471;
  end;

// *********************************************************************//
// DispIntf:  IHmFReg2
// Flags:     (4096) Dispatchable
// GUID:      {5B4EAE47-83AF-4FF9-9455-31CA48E8E8CC}
// *********************************************************************//
  IHmFReg2 = dispinterface
    ['{5B4EAE47-83AF-4FF9-9455-31CA48E8E8CC}']
    procedure SmenBegin; dispid 257;
    procedure BegChk; dispid 258;
    procedure EndChk; dispid 259;
    procedure VoidChk; dispid 260;
    procedure CopyChk; dispid 261;
    procedure VoidLast; dispid 262;
    procedure TextComment(Comment: OleVariant); dispid 263;
    procedure BinComment(ID: OleVariant; BComment: OleVariant); dispid 264;
    procedure Prod(ID: OleVariant; Cena: OleVariant; Kol: OleVariant; Dep: OleVariant; 
                   Grp: OleVariant); dispid 265;
    procedure VoidProd(ID: OleVariant); dispid 266;
    procedure Oplata(ID: OleVariant; Sum: OleVariant; Code: OleVariant); dispid 267;
    procedure InOut(ID: OleVariant; Sum: OleVariant); dispid 268;
    procedure NacSkd(ID: OleVariant; Sum: OleVariant; Prc: OleVariant); dispid 269;
    procedure FullProd(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                       Grp: OleVariant; Tax: OleVariant; Name: OleVariant); dispid 387;
    procedure FullNac(ID: OleVariant; Sum: OleVariant; Prc: OleVariant; Rec: OleVariant; 
                      Tax: OleVariant); dispid 388;
    procedure Subtotal(out Sum: OleVariant); dispid 389;
    procedure BegReturn; dispid 390;
  end;

// *********************************************************************//
// DispIntf:  IHmFReg3
// Flags:     (4096) Dispatchable
// GUID:      {763C5592-F3B1-4597-B552-10A8286A8D5A}
// *********************************************************************//
  IHmFReg3 = dispinterface
    ['{763C5592-F3B1-4597-B552-10A8286A8D5A}']
    procedure SmenBegin; dispid 257;
    procedure BegChk; dispid 258;
    procedure EndChk; dispid 259;
    procedure VoidChk; dispid 260;
    procedure CopyChk; dispid 261;
    procedure VoidLast; dispid 262;
    procedure TextComment(Comment: OleVariant); dispid 263;
    procedure BinComment(ID: OleVariant; BComment: OleVariant); dispid 264;
    procedure Prod(ID: OleVariant; Cena: OleVariant; Kol: OleVariant; Dep: OleVariant; 
                   Grp: OleVariant); dispid 265;
    procedure VoidProd(ID: OleVariant); dispid 266;
    procedure Oplata(ID: OleVariant; Sum: OleVariant; Code: OleVariant); dispid 267;
    procedure InOut(ID: OleVariant; Sum: OleVariant); dispid 268;
    procedure NacSkd(ID: OleVariant; Sum: OleVariant; Prc: OleVariant); dispid 269;
    procedure FullProd(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                       Grp: OleVariant; Tax: OleVariant; Name: OleVariant); dispid 387;
    procedure FullNac(ID: OleVariant; Sum: OleVariant; Prc: OleVariant; Rec: OleVariant; 
                      Tax: OleVariant); dispid 388;
    procedure Subtotal(out Sum: OleVariant); dispid 389;
    procedure BegReturn; dispid 390;
    procedure FullNameProd(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                           Grp: OleVariant; Tax: OleVariant; Name: OleVariant; Comm: OleVariant; 
                           Unit_: OleVariant); dispid 399;
  end;

// *********************************************************************//
// DispIntf:  IHmFReg4
// Flags:     (4096) Dispatchable
// GUID:      {3DF3A03A-01BB-490F-B619-DC91C7BAD10D}
// *********************************************************************//
  IHmFReg4 = dispinterface
    ['{3DF3A03A-01BB-490F-B619-DC91C7BAD10D}']
    procedure SmenBegin; dispid 257;
    procedure BegChk; dispid 258;
    procedure EndChk; dispid 259;
    procedure VoidChk; dispid 260;
    procedure CopyChk; dispid 261;
    procedure VoidLast; dispid 262;
    procedure TextComment(Comment: OleVariant); dispid 263;
    procedure BinComment(ID: OleVariant; BComment: OleVariant); dispid 264;
    procedure Prod(ID: OleVariant; Cena: OleVariant; Kol: OleVariant; Dep: OleVariant; 
                   Grp: OleVariant); dispid 265;
    procedure VoidProd(ID: OleVariant); dispid 266;
    procedure Oplata(ID: OleVariant; Sum: OleVariant; Code: OleVariant); dispid 267;
    procedure InOut(ID: OleVariant; Sum: OleVariant); dispid 268;
    procedure NacSkd(ID: OleVariant; Sum: OleVariant; Prc: OleVariant); dispid 269;
    procedure FullProd(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                       Grp: OleVariant; Tax: OleVariant; Name: OleVariant); dispid 387;
    procedure FullNac(ID: OleVariant; Sum: OleVariant; Prc: OleVariant; Rec: OleVariant; 
                      Tax: OleVariant); dispid 388;
    procedure Subtotal(out Sum: OleVariant); dispid 389;
    procedure BegReturn; dispid 390;
    procedure FullNameProd(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                           Grp: OleVariant; Tax: OleVariant; Name: OleVariant; Comm: OleVariant; 
                           Unit_: OleVariant); dispid 399;
    procedure LastChkInfo(out Total: OleVariant; out ChkNum: OleVariant; out ChkDate: OleVariant; 
                          out ChkTime: OleVariant; out NKass: OleVariant); dispid 401;
    procedure LastOpInfo(NTax: OleVariant; out Summ: OleVariant; out Mode: OleVariant); dispid 402;
  end;

// *********************************************************************//
// DispIntf:  IHmPreEndChk
// Flags:     (4096) Dispatchable
// GUID:      {898C5A33-A7DF-4132-B359-F445405C8581}
// *********************************************************************//
  IHmPreEndChk = dispinterface
    ['{898C5A33-A7DF-4132-B359-F445405C8581}']
    procedure PreEndChk; dispid 432;
  end;

// *********************************************************************//
// DispIntf:  IHmCEFReg
// Flags:     (4096) Dispatchable
// GUID:      {1C2AB807-3371-46B3-ADF4-0838358FA8F2}
// *********************************************************************//
  IHmCEFReg = dispinterface
    ['{1C2AB807-3371-46B3-ADF4-0838358FA8F2}']
    procedure SetRate(ID: OleVariant; Operation: OleVariant; Rate: OleVariant; N0: OleVariant); dispid 403;
    procedure SetCommis(IDIn: OleVariant; IDOut: OleVariant; Commission: OleVariant); dispid 404;
    procedure SetExtra(ID: OleVariant; Name: OleVariant; Prc: OleVariant); dispid 405;
    procedure OutTone(Len: OleVariant; Tone: OleVariant); dispid 321;
    procedure OutScr(Row: OleVariant; Scr2: OleVariant); dispid 337;
    procedure SmenBegin(Mode: OleVariant; SavedDate: OleVariant); dispid 406;
    procedure BegOper; dispid 407;
    procedure EndOper(out NumOper: OleVariant); dispid 408;
    procedure VoidOper; dispid 409;
    procedure RetOper(NumOper: OleVariant); dispid 410;
    procedure Sale(IDOut: OleVariant; SumOut: OleVariant); dispid 411;
    procedure Buy(IDIn: OleVariant; SumIn: OleVariant); dispid 412;
    procedure Sale377(IDOut: OleVariant; SumOut: OleVariant; Ser377: OleVariant; Num377: OleVariant); dispid 413;
    procedure Buy377(IDIn: OleVariant; SumIn: OleVariant; Ser377: OleVariant; Num377: OleVariant; 
                     Client: OleVariant; Country: OleVariant); dispid 414;
    procedure Convert(IDIn: OleVariant; SumIn: OleVariant; IDOut: OleVariant; SumOut: OleVariant; 
                      IDCom: OleVariant); dispid 415;
    procedure Form06(NumOper: OleVariant; Ser06: OleVariant; Num06: OleVariant; Client: OleVariant; 
                     DocSerial: OleVariant; DocNumber: OleVariant; OtherDoc: OleVariant; 
                     Emmited: OleVariant); dispid 416;
    procedure TrChkSale(IDOut: OleVariant; SumOut: OleVariant; IDIn: OleVariant; IDCom: OleVariant); dispid 417;
    procedure TrChkBuy(IDIn: OleVariant; SumIn: OleVariant; IDOut: OleVariant; IDCom: OleVariant); dispid 418;
    procedure BinComment(ID: OleVariant; BComment: OleVariant); dispid 264;
    procedure InOut(Mode: OleVariant; SaveInfo: OleVariant; ID: OleVariant; Sum: OleVariant); dispid 419;
    procedure SetFormDiap(Mode: OleVariant; NDiap: OleVariant; Liter: OleVariant; 
                          BegNum: OleVariant; EndNum: OleVariant); dispid 420;
    procedure DelFormDiap(Mode: OleVariant; NDiap: OleVariant); dispid 421;
    procedure OpenComment(out Date: OleVariant; out NumForm: OleVariant); dispid 422;
    procedure CloseComment; dispid 423;
    procedure PageBreak; dispid 424;
    procedure PrintComment(Right: OleVariant; Line: OleVariant); dispid 425;
    procedure PrintReport(NumReport: OleVariant); dispid 377;
    procedure SetClock(Time: OleVariant; Date: OleVariant); dispid 393;
    procedure PutReset(Time: OleVariant; Date: OleVariant); dispid 426;
    procedure Fiscalisation(CurrDate: OleVariant); dispid 395;
    procedure PutHdrFM(CurrDate: OleVariant); dispid 397;
    procedure PutCurrency(CurrDate: OleVariant); dispid 427;
    procedure ClearCommissionTable; dispid 428;
    procedure FDayFind(NumDayRep: OleVariant; out BegRec: OleVariant; out NumRec: OleVariant); dispid 429;
    procedure FMReport(NumReport: OleVariant; BegDate: OleVariant; EndDate: OleVariant; 
                       BegRec: OleVariant; EndRec: OleVariant); dispid 398;
    procedure LastOpSum(out OperID: OleVariant; out IDIn: OleVariant; out SumIn: OleVariant; 
                        out IDOut: OleVariant; out SumOut: OleVariant; out IdIn1: OleVariant; 
                        out SumIn1: OleVariant; out IdOut1: OleVariant; out SumOut1: OleVariant; 
                        out IdIn2: OleVariant; out SumIn2: OleVariant); dispid 430;
  end;

// *********************************************************************//
// DispIntf:  IHmAZSFP
// Flags:     (4096) Dispatchable
// GUID:      {426849A4-A273-4EFD-B424-44542AF79D2B}
// *********************************************************************//
  IHmAZSFP = dispinterface
    ['{426849A4-A273-4EFD-B424-44542AF79D2B}']
    procedure SmenBegin; dispid 257;
    procedure BegChk; dispid 258;
    procedure EndChk; dispid 259;
    procedure VoidChk; dispid 260;
    procedure CopyChk; dispid 261;
    procedure VoidLast; dispid 262;
    procedure TextComment(Comment: OleVariant); dispid 263;
    procedure BinComment(ID: OleVariant; BComment: OleVariant); dispid 264;
    procedure Prod(ID: OleVariant; Cena: OleVariant; Kol: OleVariant; Dep: OleVariant; 
                   Grp: OleVariant); dispid 265;
    procedure VoidProd(ID: OleVariant); dispid 266;
    procedure Oplata(ID: OleVariant; Sum: OleVariant; Code: OleVariant); dispid 267;
    procedure InOut(ID: OleVariant; Sum: OleVariant); dispid 268;
    procedure NacSkd(ID: OleVariant; Sum: OleVariant; Prc: OleVariant); dispid 269;
    procedure FullProd(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                       Grp: OleVariant; Tax: OleVariant; Name: OleVariant); dispid 387;
    procedure FullNac(ID: OleVariant; Sum: OleVariant; Prc: OleVariant; Rec: OleVariant; 
                      Tax: OleVariant); dispid 388;
    procedure Subtotal(out Sum: OleVariant); dispid 389;
    procedure BegReturn; dispid 390;
    procedure FullNameProd(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                           Grp: OleVariant; Tax: OleVariant; Name: OleVariant; Comm: OleVariant; 
                           Unit_: OleVariant); dispid 399;
    procedure LastChkInfo(out Total: OleVariant; out ChkNum: OleVariant; out ChkDate: OleVariant; 
                          out ChkTime: OleVariant; out NKass: OleVariant); dispid 401;
    procedure LastOpInfo(NTax: OleVariant; out Summ: OleVariant; out Mode: OleVariant); dispid 402;
    procedure ChkParam(out State: OleVariant; out CurrOper: OleVariant; out BegChk: OleVariant; 
                       out BegRep: OleVariant); dispid 452;
    procedure PreEndChk; dispid 432;
    procedure VerifyConfig(out CRC: OleVariant); dispid 436;
    procedure CheckTankOper(TankID: OleVariant; out ChkID: OleVariant); dispid 453;
    procedure PrintTankOper(CmdID: OleVariant; TankID: OleVariant; OperID: OleVariant; 
                            Volume: OleVariant; out ChkID: OleVariant); dispid 437;
    procedure CheckFuelOper(PipeID: OleVariant; OperID: OleVariant; PayID: OleVariant; 
                            Discount: OleVariant; Volume: OleVariant; out ChkID: OleVariant); dispid 438;
    procedure PrintFuelOper(CmdID: OleVariant; PipeID: OleVariant; OperID: OleVariant; 
                            PayID: OleVariant; Discount: OleVariant; Volume: OleVariant; 
                            out ChkID: OleVariant); dispid 439;
    procedure PutSNumFM(CurrDate: OleVariant; SNum: OleVariant); dispid 454;
    procedure PutResetF(MaxPLU: OleVariant; MaxFChk: OleVariant; NChk: OleVariant; 
                        Time: OleVariant; Date: OleVariant; Lang: OleVariant); dispid 455;
    procedure ClearFChk; dispid 456;
    procedure PrintFChk; dispid 457;
    procedure WriteFChk(ID: OleVariant; Buf: OleVariant); dispid 458;
    procedure GetLastChkID(out ChkID: OleVariant; out CmdID: OleVariant; out ChkState: OleVariant; 
                           out FuelOperID: OleVariant); dispid 460;
    procedure SetNewOper(Pswd: OleVariant; Name: OleVariant; out ID: OleVariant); dispid 467;
  end;

// *********************************************************************//
// DispIntf:  IHmAZSController
// Flags:     (4096) Dispatchable
// GUID:      {4B927538-A046-4292-90AA-20B7A509D331}
// *********************************************************************//
  IHmAZSController = dispinterface
    ['{4B927538-A046-4292-90AA-20B7A509D331}']
    procedure ChkParam(out State: OleVariant; out CurrOper: OleVariant; out BegChk: OleVariant; 
                       out BegRep: OleVariant); dispid 452;
    procedure StartConfig; dispid 440;
    procedure EndConfig; dispid 441;
    procedure VerifyConfig(out CRC: OleVariant); dispid 436;
    procedure StartTankOper(TankID: OleVariant; CRC: OleVariant; ChkID: OleVariant; 
                            out CmdID: OleVariant); dispid 442;
    procedure DoneTankOper(TankID: OleVariant; out CmdID: OleVariant); dispid 451;
    procedure EndTankOper(TankID: OleVariant; Volume: OleVariant; Flag: OleVariant; 
                          ChkID: OleVariant); dispid 443;
    procedure StartFuelOper(PipeID: OleVariant; FuelOperID: OleVariant; Limit: OleVariant; 
                            PreCmdID: OleVariant; CRC: OleVariant; ChkID: OleVariant; 
                            out CmdID: OleVariant); dispid 444;
    procedure StopFuelOper(CmdID: OleVariant); dispid 445;
    procedure DoneFuelOper(StatID: OleVariant; out Limit: OleVariant; out Volume: OleVariant; 
                           out FuelOperID: OleVariant; out PipeID: OleVariant; out CmdID: OleVariant); dispid 446;
    procedure EndFuelOper(CmdID: OleVariant; Discount: OleVariant; PayID: OleVariant; 
                          ChkID: OleVariant); dispid 447;
    procedure LightCtrl(StatID: OleVariant; State: OleVariant); dispid 448;
    procedure QueryTotalizers(StatID: OleVariant); dispid 449;
    procedure PutSNumFM(CurrDate: OleVariant; SNum: OleVariant); dispid 454;
    procedure PutResetF(MaxPLU: OleVariant; MaxFChk: OleVariant; NChk: OleVariant; 
                        Time: OleVariant; Date: OleVariant; Lang: OleVariant); dispid 455;
    procedure ClearFChk; dispid 456;
    procedure SignFChk; dispid 459;
  end;

// *********************************************************************//
// DispIntf:  IHmFRegWeight
// Flags:     (4096) Dispatchable
// GUID:      {99DD9245-A46D-4C4C-BD0F-FEEEE7761E85}
// *********************************************************************//
  IHmFRegWeight = dispinterface
    ['{99DD9245-A46D-4C4C-BD0F-FEEEE7761E85}']
    procedure FullProdComm(Code: OleVariant; Price: OleVariant; Qty: OleVariant; Dep: OleVariant; 
                           Grp: OleVariant; Tax: OleVariant; Name: OleVariant; Comm: OleVariant); dispid 462;
  end;

// *********************************************************************//
// DispIntf:  IHmSSTRNL
// Flags:     (4096) Dispatchable
// GUID:      {84E73A3F-7342-43A8-8D75-43C273DA662E}
// *********************************************************************//
  IHmSSTRNL = dispinterface
    ['{84E73A3F-7342-43A8-8D75-43C273DA662E}']
    procedure HashBegin(out NZRep: OleVariant; out NChk: OleVariant; out TChk: OleVariant); dispid 472;
    procedure HashBeginRecov(out NZRep: OleVariant; out SerNum: OleVariant; out SerLet: OleVariant); dispid 473;
    procedure HashUpdate(NPack: OleVariant; Data: OleVariant); dispid 474;
    procedure HashEnd(NPack: OleVariant; Data: OleVariant); dispid 475;
    procedure HashEndRecov; dispid 476;
    procedure HashPrint; dispid 477;
    procedure HashAbort; dispid 478;
    procedure HashGetSign(ZRepID: OleVariant; ChkID: OleVariant; out NZRep: OleVariant; 
                          out NChk: OleVariant; out TChk: OleVariant; out Time: OleVariant; 
                          out Date: OleVariant; out SerNum: OleVariant; out SetLet: OleVariant; 
                          out Sign: OleVariant); dispid 479;
    procedure HashGetZRep(ZRepID: OleVariant; out NZRep: OleVariant; out NChk: OleVariant; 
                          out TChk: OleVariant; out Time: OleVariant; out Date: OleVariant; 
                          out SerNum: OleVariant; out SetLet: OleVariant; out Sign: OleVariant); dispid 480;
  end;

implementation

uses ComObj;

end.
